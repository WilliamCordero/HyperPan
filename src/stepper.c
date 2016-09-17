/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bcm2835.h>
#include "stepper.h"
#include "verbose.h"
stepper stepper_init(int sleep,int step,int dir,int m0,int m1,char *name){
    char *msj;
    stepper tmp;
    bcm2835_gpio_fsel(sleep,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(sleep,LOW);
    tmp.sleep=sleep;
    bcm2835_gpio_fsel(step,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(step,LOW);
    tmp.step=step;
    bcm2835_gpio_fsel(dir,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(dir,LOW);
    tmp.dir=dir;    
//    bcm2835_gpio_fsel(m0,BCM2835_GPIO_FSEL_OUTP);
//    bcm2835_gpio_write(m0,LOW);
    tmp.m0=m0;    
    bcm2835_gpio_fsel(m1,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(m1,LOW);
    tmp.m1=m1;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"Initializing stepper %s.",tmp.name);
    verbose(3,msj);free(msj);
    alert_led();
    return tmp;
}
int stepper_mode(stepper motor,int mode){
    char *msj;
    switch(mode){ //M0
        case 2:case 16:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(motor.m0,HIGH);break;
        case 4:case 32:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_set_pud(motor.m0,BCM2835_GPIO_PUD_OFF);break;
        default:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(motor.m0,LOW);
    }
    switch(mode){ //M1
        case 8:case 16:case 32:
            bcm2835_gpio_write(motor.m1,HIGH);break;
        default:
            bcm2835_gpio_write(motor.m1,LOW);
    }
    switch(mode){
        case 1:case 2:case 4:case 8:case 16:case 32:
            asprintf(&msj,"%s: set mode 1/%i.",motor.name,mode);
            verbose(3,msj);free(msj);
            break;
        default:
            asprintf(&msj,"%s: invalid mode 1/%i, using mode 1/1.",motor.name,mode);
            warning(msj);free(msj);
    }
}
int stepper_on(stepper motor){
    bcm2835_gpio_write(motor.sleep,HIGH);
}
int stepper_off(stepper motor){
    bcm2835_gpio_write(motor.sleep,LOW);
}
int pulse(stepper motor){
        bcm2835_gpio_write(motor.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        bcm2835_gpio_write(motor.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
}
int stepper_walk(stepper motor,int dir,int n){
    for(;0<n;n--)pulse(motor);
}
int stepper_walk_sync(stepper phi,int phi_n,int phi_dir,stepper theta,int theta_n,int theta_dir){
    int l_n,s_n,l_dir,s_dir,l,i,ii,x,b,t=1,tt=0,l_c=0,s_c=0;
    stepper l_st,s_st;
    char *steps,*msj;
    if(phi_n<theta_n){  
        l_st=theta;l_n=theta_n;l_dir=theta_dir;
        s_st=phi;s_n=phi_n;s_dir=phi_dir;
    }else{
        l_st=phi;l_n=phi_n;l_dir=phi_dir;
        s_st=theta;s_n=theta_n;s_dir=theta_dir;
    }
    b=(l_n/16)/ACCEL;
    steps=(char *)malloc(l=(sizeof(char)*l_n)+((ACCEL*ACCEL)*b));
    for(i=0;i<l;steps[i++]=0);
    for(i=ACCEL;0<i;i--)
        for(x=0;x<b;x++,t++,tt++){
            steps[tt]=steps[tt]|1|((t%(s_n?(l_n/s_n):t+1))?0:2);
            for(ii=i;0<ii;ii--,tt++);
        }
    for(i=(l_n-((t-1)*2));0<i;i--,t++,tt++)steps[tt]=steps[tt]|1|((t%(s_n?(l_n/s_n):t+1))?0:2);
    for(i=0;i<ACCEL;i++)
        for(x=0;x<b;x++,t++,tt++){
            for(ii=0;ii<i;ii++,tt++);
            steps[tt]=steps[tt]|1|((t%(s_n?(l_n/s_n):t+1))?0:2);
        }
    bcm2835_gpio_write(l_st.dir,l_dir?HIGH:LOW);
    bcm2835_gpio_write(s_st.dir,s_dir?HIGH:LOW);
    for(i=0;i<tt;i++){
        if(steps[i]&1){
            bcm2835_gpio_write(l_st.step,HIGH);
            l_c++;
        }
        if(steps[i]&2){
            bcm2835_gpio_write(s_st.step,HIGH);
            s_c++;
        }
        bcm2835_delayMicroseconds(PULSE);
        if(steps[i]&1)bcm2835_gpio_write(l_st.step,LOW);
        if(steps[i]&2)bcm2835_gpio_write(s_st.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
    }
    asprintf(&msj,"%s: %i %s: %i",l_st.name,l_c,s_st.name,s_c);
    verbose(3,msj);free(msj);
}
int stepper_walk_round(stepper motor,int dir,int n){
    int i,ii,t=0;
    char *msj;
    for(i=ACCEL;0<i;i--,t++){
        pulse(motor);
        for(ii=(sin(((((i*90)/ACCEL)*M_PI)/180))*i);0<ii;ii--)bcm2835_delayMicroseconds(PULSE*2);
    } 
    asprintf(&msj,"%s: rt=%i",motor.name,t);
    verbose(3,msj);free(msj);
    for(i=(n-(t*2));0<i;i--,t++)pulse(motor);
    asprintf(&msj,"%s: rt=%i",motor.name,t);
    verbose(3,msj);free(msj);
    for(i=0;i<ACCEL;i++,t++){
        for(ii=0;ii<(sin(((((i*90)/ACCEL)*M_PI)/180))*i);ii++)bcm2835_delayMicroseconds(PULSE*2);
        pulse(motor);
    } 
    asprintf(&msj,"%s: rt=%i",motor.name,t);
    verbose(3,msj);free(msj);
}

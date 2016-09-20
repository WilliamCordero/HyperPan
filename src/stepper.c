/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "stepper.h"
#include "verbose.h"
stepper stepper_init(int sleep,int step,int dir,int m0,int m1,int mode,int steps,char *name){
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
    tmp.m0=m0;    
//    bcm2835_gpio_fsel(m1,BCM2835_GPIO_FSEL_OUTP);
//    bcm2835_gpio_write(m1,LOW);
    tmp.m1=m1;
    tmp.mode=mode;
    tmp.steps=steps;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"%s: init().",tmp.name);
    verbose(L_FALL,msj);free(msj);
    stepper_mode(tmp,mode);
    stepper_on(tmp);
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
            asprintf(&msj,"%s: 1/%i mode.",motor.name,mode);
            verbose(L_ACCT,msj);free(msj);
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
int stepper_walk_sync(stepper l_st,int l_n,stepper s_st,int s_n){
    int x,l_c=0,s_c=0,b=abs(l_n)/BORDER;
    double m=(double)abs(l_n)/(double)abs(s_n);
    char *msj;
    if(abs(l_n)<abs(s_n))return stepper_walk_sync(s_st,s_n,l_st,l_n);
    bcm2835_gpio_write(l_st.dir,l_n<0?LOW:HIGH);
    bcm2835_gpio_write(s_st.dir,s_n<0?LOW:HIGH);
    for(x=b;0<x;x--){
        bcm2835_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)bcm2835_gpio_write(s_st.step,HIGH);
        bcm2835_delayMicroseconds(PULSE+(((PULSE*ACCEL*x)/b)/2));
        if((m*s_c)<=l_c){bcm2835_gpio_write(s_st.step,LOW);s_c++;}
        bcm2835_gpio_write(l_st.step,LOW);l_c++;
        bcm2835_delayMicroseconds(PULSE+(((PULSE*ACCEL*x)/b)/2));
    }
    for(x=abs(l_n)-(b*2);0<x;x--){
        bcm2835_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)bcm2835_gpio_write(s_st.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        if((m*s_c)<=l_c){bcm2835_gpio_write(s_st.step,LOW);s_c++;}
        bcm2835_gpio_write(l_st.step,LOW);l_c++;
        bcm2835_delayMicroseconds(PULSE);
    }
    for(x=0;x<b;x++){
        bcm2835_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)bcm2835_gpio_write(s_st.step,HIGH);
        bcm2835_delayMicroseconds(PULSE+(((PULSE*ACCEL*x)/b)/2));
        if((m*s_c)<=l_c){bcm2835_gpio_write(s_st.step,LOW);s_c++;}
        bcm2835_gpio_write(l_st.step,LOW);l_c++;
        bcm2835_delayMicroseconds(PULSE+(((PULSE*ACCEL*x)/b)/2));
    }
    asprintf(&msj,"%s: %c%i steps.",l_st.name,l_n<0?'-':'+',l_c);
    verbose(L_ACCT,msj);free(msj);
    asprintf(&msj,"%s: %c%i steps.",s_st.name,s_n<0?'-':'+',s_c);
    verbose(L_ACCT,msj);free(msj);
}
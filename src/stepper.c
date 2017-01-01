/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <argp.h>
#include "config.h"
#include "verbose.h"
#include "slave.h"
#include "stepper.h"
int stepper_mode(stepper motor,int mode){
    switch(mode){ //M0
        case 2:case 16:
            w_gpio_fsel(motor.m0,GPIO_FSEL_OUTP);
            w_gpio_write(motor.m0,HIGH);break;
        case 4:case 32:
            w_gpio_fsel(motor.m0,GPIO_FSEL_INPT);
            w_gpio_set_pud(motor.m0,GPIO_PUD_OFF);break;
        default:
            w_gpio_fsel(motor.m0,GPIO_FSEL_OUTP);
            w_gpio_write(motor.m0,LOW);
    }
    switch(mode){ //M1
        case 8:case 16:case 32:
            w_gpio_write(motor.m1,HIGH);break;
        default:
            w_gpio_write(motor.m1,LOW);
    }
    switch(mode){
        case 1:case 2:case 4:case 8:case 16:case 32:break;
        default:warning("%s: invalid mode 1/%i, using mode 1/1",motor.name,mode);
    }
}
stepper stepper_init(int sleep,int step,int dir,int m0,int m1,int mode,int steps,char *name){
    stepper tmp;
    w_gpio_fsel(sleep,GPIO_FSEL_OUTP);
    w_gpio_write(sleep,LOW);
    tmp.sleep=sleep;
    w_gpio_fsel(step,GPIO_FSEL_OUTP);
    w_gpio_write(step,LOW);
    tmp.step=step;
    w_gpio_fsel(dir,GPIO_FSEL_OUTP);
    w_gpio_write(dir,LOW);
    tmp.dir=dir;    
    tmp.m0=m0;    
    w_gpio_fsel(m1,GPIO_FSEL_OUTP);
    w_gpio_write(m1,LOW);
    tmp.m1=m1;
    tmp.mode=mode;
    tmp.steps=steps;
    stepper_mode(tmp,mode);
    verbose(L_STPR,"%s: ☆: 1/%d",tmp.name=name,mode);
    stepper_on(tmp);
    return tmp;
}
int stepper_on(stepper motor){
    w_gpio_write(motor.sleep,HIGH);
}
int stepper_off(stepper motor){
    w_gpio_write(motor.sleep,LOW);
}
int stepper_walk(stepper l_st,int l_n,stepper s_st,int s_n,int mm,int max,int border){
    int x,l_c=0,s_c=0,b,top=(l_st.steps/4)*l_st.mode;
    double m=(double)abs(l_n)/(double)abs(s_n);
    double min=(abs(l_n)<top)?mm+((max-mm)*(top-abs(l_n))/top):mm;
    if(abs(l_n)<abs(s_n))return stepper_walk(s_st,s_n,l_st,l_n,min,max,border);
    b=abs(l_n)/(2+(((border-2)*abs(l_n))/((l_st.steps/4)*l_st.mode)));
    w_gpio_write(l_st.dir,l_n<0?HIGH:LOW);
    w_gpio_write(s_st.dir,s_n<0?HIGH:LOW);
    for(x=b;0<x;x--){
        double adj=((max*x)/b)/2;
        w_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)w_gpio_write(s_st.step,HIGH);
        w_delayMicroseconds(min+adj);
        if((m*s_c)<=l_c){w_gpio_write(s_st.step,LOW);s_c++;}
        w_gpio_write(l_st.step,LOW);l_c++;
        w_delayMicroseconds(min+adj);
//        verbose(L_TEST,"1: %.0f+%.1f %d",min,adj*2,x);
    }
    for(x=abs(l_n)-(b*2);0<x;x--){
        w_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)w_gpio_write(s_st.step,HIGH);
        w_delayMicroseconds(min);
        if((m*s_c)<=l_c){w_gpio_write(s_st.step,LOW);s_c++;}
        w_gpio_write(l_st.step,LOW);l_c++;
        w_delayMicroseconds(min);
//        verbose(L_TEST,"2: %.0f+0 %d",min,x);
    }
    for(x=0;x<b;x++){
        double adj=((max*x)/b)/2;
        w_gpio_write(l_st.step,HIGH);
        if((m*s_c)<=l_c)w_gpio_write(s_st.step,HIGH);
        w_delayMicroseconds(min+adj);
        if((m*s_c)<=l_c){w_gpio_write(s_st.step,LOW);s_c++;}
        w_gpio_write(l_st.step,LOW);l_c++;
        w_delayMicroseconds(min+adj);
//        verbose(L_TEST,"3: %.0f+%.1f %d",min,adj*2,x);
    }
    verbose(L_STPR,"%s: %s: %d",l_st.name,l_n<0?"←":"→",l_c);
    verbose(L_STPR,"%s: %s: %d",s_st.name,s_n<0?"←":"→",s_c);
}
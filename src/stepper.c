/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <bcm2835.h>
#include "stepper.h"

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

int stepper_walk(stepper motor,int dir,int steps){
    int i;
    bcm2835_gpio_write(motor.dir,dir?HIGH:LOW);
    for(i=0;i<steps;i++){
        bcm2835_gpio_write(motor.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        bcm2835_gpio_write(motor.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
    }
}
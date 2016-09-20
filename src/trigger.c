/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "trigger.h"
#include "verbose.h"
trigger trigger_init(int focus_mode,int focus_delay,char *name){
    trigger tmp;char *msj;
    tmp.shutter=SHUTTER;
    bcm2835_gpio_fsel(SHUTTER,BCM2835_GPIO_FSEL_OUTP);
    tmp.shutter_speed=SPEED;
    tmp.focus=FOCUS;
    bcm2835_gpio_fsel(FOCUS,BCM2835_GPIO_FSEL_OUTP);
    tmp.focus_mode=focus_mode;
    tmp.focus_delay=focus_delay;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"%s: init().",tmp.name);
    verbose(L_FALL,msj);free(msj);
    return tmp;
}
int trigger_shot(trigger trigger,int speed){
    char *msj;
    if(trigger.focus_mode){
        asprintf(&msj,"%s: Focus: %iμs.",trigger.name,trigger.focus_delay);
        verbose(L_TRGR,msj);free(msj);
        bcm2835_gpio_write(trigger.focus,HIGH);
        bcm2835_delayMicroseconds(trigger.focus_delay);
    }
    asprintf(&msj,"%s: Shoot: %iμs.",trigger.name,speed?speed:trigger.shutter_speed);
    verbose(L_TRGR,msj);free(msj);
    bcm2835_gpio_write(trigger.shutter,HIGH);
    bcm2835_delayMicroseconds(speed?speed:trigger.shutter_speed);
    bcm2835_gpio_write(trigger.shutter,LOW);
    if(trigger.focus_mode)bcm2835_gpio_write(trigger.focus,LOW);
}
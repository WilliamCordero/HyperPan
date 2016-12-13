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
#include "config.h"
#include "trigger.h"
#include "verbose.h"
int trigger_init(int focus_mode,int focus_delay,char *name){
    trigger=(struct trig*)malloc(sizeof(struct trig));
    trigger->shutter=SHUTTER;
    bcm2835_gpio_fsel(SHUTTER,BCM2835_GPIO_FSEL_OUTP);
    trigger->shutter_speed=SPEED;
    trigger->focus=FOCUS;
    bcm2835_gpio_fsel(FOCUS,BCM2835_GPIO_FSEL_OUTP);
    trigger->focus_mode=focus_mode;
    trigger->focus_delay=focus_delay;
    verbose(L_INFO,"%s: init()",trigger->name=name);
}
int trigger_shot(int speed){
    if(trigger->focus_mode){
        verbose(L_TRGR,"%s: Focus: %iμs.",trigger->name,trigger->focus_delay);
        bcm2835_gpio_write(trigger->focus,HIGH);
        bcm2835_delayMicroseconds(trigger->focus_delay);
    }
    verbose(L_TRGR,"%s: Shoot: %iμs.",trigger->name,speed?speed:trigger->shutter_speed);
    //bcm2835_delayMicroseconds(7*1000000);
    bcm2835_gpio_write(trigger->shutter,HIGH);
    bcm2835_delayMicroseconds(speed?speed:trigger->shutter_speed);
    bcm2835_gpio_write(trigger->shutter,LOW);
    if(trigger->focus_mode)bcm2835_gpio_write(trigger->focus,LOW);
}
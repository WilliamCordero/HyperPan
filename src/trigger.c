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
int trigger_init(char *name){
    trigger=(struct trig*)malloc(sizeof(struct trig));
    trigger->shutter=SHUTTER;
    bcm2835_gpio_fsel(SHUTTER,BCM2835_GPIO_FSEL_OUTP);
    trigger->focus=FOCUS;
    bcm2835_gpio_fsel(FOCUS,BCM2835_GPIO_FSEL_OUTP);
    trigger->shutter_speed=a->speed;
    trigger->shutter_delay=a->delay;
    trigger->focus_mode=a->focus;
    verbose(L_INFO,"%s: ★",trigger->name=name);
    trigger_wakeup();
}
int trigger_shot(double speed){
    if(trigger->focus_mode){
        verbose(L_TRGR,"%s: focus: ON",trigger->name);
        if(!a->dummy)bcm2835_gpio_write(trigger->focus,HIGH);
    }
    if(trigger->shutter_delay){
        verbose(L_TRGR,"%s: delay: %8.0fμs",trigger->name,trigger->shutter_delay*M);
        bcm2835_delayMicroseconds(trigger->shutter_delay*M);
    }
    verbose(L_TRGR,"%s: shoot: %8.0fμs",trigger->name,speed?speed:trigger->shutter_speed*M);
    if(!a->dummy)bcm2835_gpio_write(trigger->shutter,HIGH);
    bcm2835_delayMicroseconds(speed?speed:trigger->shutter_speed*M);
    if(!a->dummy)bcm2835_gpio_write(trigger->shutter,LOW);
    if(trigger->focus_mode)if(!a->dummy)bcm2835_gpio_write(trigger->focus,LOW);
}
int trigger_wakeup(){
    verbose(L_TRGR,"%s: ☼",trigger->name);
    if(!a->dummy)bcm2835_gpio_write(trigger->focus,HIGH);
    bcm2835_delayMicroseconds(trigger->shutter_speed*M);
    if(!a->dummy)bcm2835_gpio_write(trigger->focus,LOW);
}
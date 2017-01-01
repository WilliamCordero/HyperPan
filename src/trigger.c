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
#include "slave.h"
int trigger_init(char *name){
    trigger=(struct trig*)malloc(sizeof(struct trig));
    trigger->shutter=SHUTTER;
    w_gpio_fsel(SHUTTER,BCM2835_GPIO_FSEL_OUTP);
    trigger->focus=FOCUS;
    w_gpio_fsel(FOCUS,BCM2835_GPIO_FSEL_OUTP);
    trigger->shutter_speed=a->speed;
    trigger->shutter_delay=a->delay;
    trigger->focus_mode=a->focus;
    verbose(L_TRGR,"%s: ★:",trigger->name=name);
    trigger_wakeup();
}
int trigger_shot(double speed){
    if(a->shutter){
        if(trigger->focus_mode){
            verbose(L_TRGR,"%s: ◎:",trigger->name);
            w_gpio_write(trigger->focus,HIGH);
        }
        if(trigger->shutter_delay){
            verbose(L_TRGR,"%s: ⇴: %.0fμs",trigger->name,trigger->shutter_delay*M);
            w_delayMicroseconds(trigger->shutter_delay*M);
        }
        verbose(L_TRGR,"%s: ↯: %.0fμs",trigger->name,speed?speed:trigger->shutter_speed*M);
        w_gpio_write(trigger->shutter,HIGH);
        w_delayMicroseconds(speed?speed:trigger->shutter_speed*M);
        w_gpio_write(trigger->shutter,LOW);
        if(trigger->focus_mode)w_gpio_write(trigger->focus,LOW);
    }
}
int trigger_wakeup(){
    if(a->shutter){
        verbose(L_TRGR,"%s: ☼:",trigger->name);
        w_gpio_write(trigger->focus,HIGH);
        w_delayMicroseconds(trigger->shutter_speed*M);
        w_gpio_write(trigger->focus,LOW);
    }
}
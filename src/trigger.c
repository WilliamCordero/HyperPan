/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <bcm2835.h>
#include "trigger.h"

trigger trigger_init(int focus_mode,int focus_delay){
    trigger temp;
    temp.shutter=SHUTTER;
    bcm2835_gpio_fsel(SHUTTER,BCM2835_GPIO_FSEL_OUTP);
    temp.shutter_speed=SPEED;
    temp.focus=FOCUS;
    bcm2835_gpio_fsel(FOCUS,BCM2835_GPIO_FSEL_OUTP);
    temp.focus_mode=focus_mode;
    temp.focus_delay=focus_delay;
    verbose(3,"Initializing trigger.");
    alert_led();
    return temp;
}

int trigger_shot(trigger trigger,int speed){
    char *msj;
    if(trigger.focus_mode){
        asprintf(&msj,"Focusing for %i μs.",trigger.focus_delay);
        verbose(1,msj);free(msj);
        bcm2835_gpio_write(trigger.focus,HIGH);
        bcm2835_delayMicroseconds(trigger.focus_delay);
    }
    asprintf(&msj,"Shooting for %i μs.",speed?speed:trigger.shutter_speed);
    verbose(1,msj);free(msj);
    bcm2835_gpio_write(trigger.shutter,HIGH);
    bcm2835_delayMicroseconds(speed?speed:trigger.shutter_speed);
    bcm2835_gpio_write(trigger.shutter,LOW);
    if(trigger.focus_mode)bcm2835_gpio_write(trigger.focus,LOW);
}
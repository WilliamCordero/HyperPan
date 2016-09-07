/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <bcm2835.h>
#include "trigger.h"

trigger trigger_init(int shutter,int focus,int focus_mode,int focus_delay,int shutter_speed){
    trigger temp;
    temp.shutter=shutter;
    bcm2835_gpio_fsel(shutter,BCM2835_GPIO_FSEL_OUTP);
    temp.shutter_speed=shutter_speed;
    temp.focus=focus;
    bcm2835_gpio_fsel(focus,BCM2835_GPIO_FSEL_OUTP);
    temp.focus_mode=focus_mode;
    temp.focus_delay=focus_delay;
    printf("Hola Mundo");
    return temp;
}

int trigger_shot(trigger trigger,int speed){
    if(trigger.focus_mode){
        bcm2835_gpio_write(trigger.focus,HIGH);
        bcm2835_delayMicroseconds(trigger.focus_delay);
    }
    bcm2835_gpio_write(trigger.shutter,HIGH);
    bcm2835_delayMicroseconds(speed?speed:trigger.shutter_speed);
    bcm2835_gpio_write(trigger.shutter,LOW);
    if(trigger.focus_mode){
        bcm2835_gpio_write(trigger.focus,LOW);
    }
}
/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <bcm2835.h>
#include "verbose.h"

int verbose(int level, char *msj){
    if(level<=verbose_level){
//        alert_led();
        printf("|> %s\n",msj);
    }
}

int warning(char *msj){
    alert_led();alert_led();
    fprintf(stderr,"|> Warning: %s\n",msj);
}

int error(char *msj){
    alert_led();alert_led();
    fprintf(stderr,"|> Error: %s\n",msj);
    exit(1);
}

int alert_led(){
    int i;
    bcm2835_gpio_fsel(ALERT_GPIO,BCM2835_GPIO_FSEL_OUTP);
    for(i=0;i<3;i++){
        bcm2835_gpio_write(ALERT_GPIO,HIGH);
        bcm2835_delayMicroseconds(ALERT_BLINK);
        bcm2835_gpio_write(ALERT_GPIO,LOW);
        bcm2835_delayMicroseconds(ALERT_BLINK);
    }
}
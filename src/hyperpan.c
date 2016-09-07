/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "trigger.h"

int main(int argc,char**argv){
//    int i;
    struct trigger trigger;
    
//    printf("Debug:\n");
//    for(i=0;i<argc;i++)printf("%i: %s\n",i,argv[i]);

    if(!bcm2835_init())return 1;
    trigger=trigger_init(17,4,1,1);
    trigger_shot(trigger,1);

/*
    while(1){
        bcm2835_gpio_write(21,HIGH);
        bcm2835_delayMicroseconds(50000);
        bcm2835_gpio_write(21,LOW);
        bcm2835_delayMicroseconds(50000);
    }
 */

    bcm2835_close();
    printf("Bye.\n");
    return 0;
}

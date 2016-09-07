/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "trigger.h"
#include "verbose.h"

int main(int argc,char**argv){
//    int i;
    struct trigger trigger;
    verbose_level=255;
//    for(i=0;i<argc;i++)printf("%i: %s\n",i,argv[i]);
    if(!bcm2835_init())return 1;
    
    
    trigger=trigger_init(MF,0);
    trigger_shot(trigger,0);

    
    bcm2835_close();
    printf("Bye.\n");
    return 0;
}

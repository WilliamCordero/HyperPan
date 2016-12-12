/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <argp.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "config.h"
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"
#include "sphere.h"
#include "camera.h"
int main(int argc,char**argv){
    if(!bcm2835_init()){printf("bcm2835_init :(\n");return 1;}
    verbose_init(argc,argv);
    camera_on();
    camera_action();
    camera_off();
    verbose(L_INFO,"ω:");alert_led();
    bcm2835_close();
    return 0;
}
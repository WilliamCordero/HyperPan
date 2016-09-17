/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <bcm2835.h>
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"

#define PHI_SLEEP   12
#define PHI_STEP    6
#define PHI_DIR     5
#define PHI_M0      16
#define PHI_M1      13
#define PHI_MODE    32
#define THETA_SLEEP 22
#define THETA_STEP  27
#define THETA_DIR   18
#define THETA_M0    24
#define THETA_M1    23
#define THETA_MODE  32

int main(int argc,char**argv){
    int i;
    trigger trigger;
    stepper phi,theta;
    verbose_level=255;
//    for(i=0;i<argc;i++)printf("%i: %s\n",i,argv[i]);

    if(!bcm2835_init())return 1;
    trigger=trigger_init(MF,0);
    phi=stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,"φ");
    theta=stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,"θ");
    stepper_mode(phi,PHI_MODE);
    stepper_mode(theta,THETA_MODE);
    stepper_on(phi);
    stepper_on(theta);
//    for(i=0;i<3;i++){
      stepper_walk_sync(phi,4000,0,theta,200*8*32,0);
//      stepper_walk_sync(phi,200*8*32,1,theta,200*8*32,1);
//    }
//    stepper_walk(phi,1,1000);
    stepper_off(phi);
    stepper_off(theta);
    bcm2835_close();
    verbose(1,"Bye.");
    return 0;
}

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
#include "sphere.h"

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
    trigger trigger;
    stepper rho,theta,phi;
    sphere sphere;
    int i;
    verbose_l=L_ALL;
//    for(i=0;i<argc;i++)printf("%i: %s\n",i,argv[i]);
    if(!bcm2835_init())return 1;
    verbose(L_FALL,"α:");alert_led();
    trigger=trigger_init(MF,0,"μ");
    theta=stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,"θ");
    phi=stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,"φ");
    stepper_mode(theta,THETA_MODE);
    stepper_mode(phi,PHI_MODE);
    stepper_on(theta);
    stepper_on(phi);
    sphere=sphere_init(rho,theta,phi,"ο");
    go(sphere,0,0.5,180);
//    trigger_shot(trigger,500000);
//    stepper_walk_sync(phi,200*8*32,0,theta,200*8*32,1);
//    stepper_walk(phi,1,1000);
    stepper_off(phi);
    stepper_off(theta);
    verbose(L_FALL,"ω:");alert_led();
    bcm2835_close();
    return 0;
}

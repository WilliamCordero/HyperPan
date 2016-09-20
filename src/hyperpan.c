/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"
#include "sphere.h"

#define THETA_SLEEP 22
#define THETA_STEP  27
#define THETA_DIR   18
#define THETA_M0    24
#define THETA_M1    23
#define THETA_MODE  32
#define THETA_STEPS 200*8
#define PHI_SLEEP   12
#define PHI_STEP    6
#define PHI_DIR     5
#define PHI_M0      16
#define PHI_M1      13
#define PHI_MODE    32
#define PHI_STEPS   200*8

    

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
    theta=stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,THETA_MODE,THETA_STEPS,"θ");
    phi=stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,PHI_MODE,PHI_STEPS,"φ");  
    sphere=sphere_init(rho,theta,phi,"ο");
    go(&sphere,0,90,270);
    //trigger_shot(trigger,500000);
    go(&sphere,0,180,180);
    //trigger_shot(trigger,500000);
    go(&sphere,0,0,0);
    stepper_off(phi);
    stepper_off(theta);
    verbose(L_FALL,"ω:");alert_led();
    bcm2835_close();
    return 0;
}
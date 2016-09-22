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
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"
#include "sphere.h"
#include "camera.h"

#define RHO_SLEEP   22
#define RHO_STEP    27
#define RHO_DIR     18
#define RHO_M0      24
#define RHO_M1      23
#define RHO_MODE    32
#define RHO_STEPS   200*8
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

int x;
int main(int argc,char**argv){
    sphere sphere;
    camera camera;
    verbose_init(argc,argv);
    if(!bcm2835_init())return 1;
    verbose(L_FALL,"α:");alert_led();
    sphere=sphere_init(
        stepper_init(RHO_SLEEP,RHO_STEP,RHO_DIR,RHO_M0,RHO_M1,RHO_MODE,RHO_STEPS,"ρ"),
        stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,THETA_MODE,THETA_STEPS,"θ"),
        stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,PHI_MODE,PHI_STEPS,"φ"),
        "ο");
    camera=camera_init(&sphere,trigger_init(MF,0,"μ"),"δ");

//ALL READY.    
    v_shot(&camera,35,15.6,23.5,60,60);    
    
//GO OUT.
    camera_off(&camera);
    verbose(L_FALL,"ω:");alert_led();
    bcm2835_close();
    return 0;
}
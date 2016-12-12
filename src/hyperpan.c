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
#define THETA_SLEEP 12
#define THETA_STEP  6
#define THETA_DIR   5
#define THETA_M0    16
#define THETA_M1    13
#define THETA_MODE  32
#define THETA_STEPS 200*8
#define PHI_SLEEP   22
#define PHI_STEP    27
#define PHI_DIR     18
#define PHI_M0      24
#define PHI_M1      23
#define PHI_MODE    32
#define PHI_STEPS   200*8

int x;
int main(int argc,char**argv){
    sphere sphere;
    camera camera;
    if(!bcm2835_init())error("Broadcom BCM 2835");
    verbose_init(argc,argv);
    verbose(L_INFO,"α:");alert_led();
    sphere=sphere_init(
        stepper_init(RHO_SLEEP,RHO_STEP,RHO_DIR,RHO_M0,RHO_M1,RHO_MODE,RHO_STEPS,"ρ"),
        stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,THETA_MODE,THETA_STEPS,"θ"),
        stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,PHI_MODE,PHI_STEPS,"φ"),
        "ο");
    camera=camera_init(&sphere,trigger_init(MF,0,"μ"),"δ");
//ALL READY.
    switch(a->action){
        case      ACT_35:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,24,36);break;
        case    ACT_6x45:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,45);break;
        case    ACT_45x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,45,60);break;
        case     ACT_6x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,60);break;
        case     ACT_6x7:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,70);break;
        case     ACT_7x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,70,60);break;
        case     ACT_6x8:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,80);break;
        case     ACT_8x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,80,60);break;
        case     ACT_6x9:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,90);break;
        case     ACT_9x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,90,60);break;
        case    ACT_6x17:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,60,170);break;
        case    ACT_17x6:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,170,60);break;
        case ACT_VIRTUAL:virtual_shot(&camera,a->focal,a->width,a->height,a->overlap,a->vwidth,a->vheight);break;
        case  ACT_SPHERE:
            verbose(L_INFO,"Not Implemented");
            break;
        case ACT_XXX:
            verbose(L_INFO,"Not Implemented");
            break;
    }
//GO OUT.
    camera_off(&camera);
    verbose(L_INFO,"ω:");alert_led();
    bcm2835_close();
    return 0;
}
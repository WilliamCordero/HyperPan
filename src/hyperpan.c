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
float r2d(float r){return r*(180/M_PI);}
float d2r(float d){return d*(M_PI/180);}
int main(int argc,char**argv){
    trigger trigger;
    stepper rho,theta,phi;
    sphere sphere;
    verbose_init(argc,argv);
    if(!bcm2835_init())return 1;
    verbose(L_FALL,"α:");alert_led();
    trigger=trigger_init(MF,0,"μ");
    rho=stepper_init(RHO_SLEEP,RHO_STEP,RHO_DIR,RHO_M0,RHO_M1,RHO_MODE,RHO_STEPS,"ρ");
    theta=stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,THETA_MODE,THETA_STEPS,"θ");
    phi=stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,PHI_MODE,PHI_STEPS,"φ");  
    sphere=sphere_init(rho,theta,phi,"ο");
//ALL READY.    
#define SS 7500000
/*    
    for(x=3;x>0;x--){
    go(&sphere,0,50,0);
    trigger_shot(trigger,SS);
    go(&sphere,0,70,45);
    trigger_shot(trigger,SS);
    go(&sphere,0,90,90);
    trigger_shot(trigger,SS);
    go(&sphere,0,110,135);
    trigger_shot(trigger,SS);
    go(&sphere,0,120,180);
    trigger_shot(trigger,SS);
    }
*/

    {
        double f=35;
        double v=15.6; //a77ii=23.5x15.6 35mm=36x24
        double h=23.5;
        double d=sqrt((h*h)+(v*v));
        double aov_v=r2d(2*atan(v/(2*f)));
        double aov_h=r2d(2*atan(h/(2*f)));
        double aov_d=r2d(2*atan(d/(2*f)));
        double a_v=360/(1+floor(360/aov_v));
        double a_h=360/(1+floor(360/aov_h));
        printf("\n  f=%fmm\n  v=%fmm\n  d=%fmm\naov_v=%f°\naov_h=%f°\naov_d=%f°\n  a_v=%f°\n  a_h=%f°\n\n",f,v,d,aov_v,aov_h,aov_d,a_v,a_h);
    }
    
//GO OUT.
    go(&sphere,0,0,0);
    stepper_off(phi);
    stepper_off(theta);
    verbose(L_FALL,"ω:");alert_led();
    bcm2835_close();
    return 0;
}
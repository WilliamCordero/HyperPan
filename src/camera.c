/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"
#include "sphere.h"
#include "camera.h"
camera camera_init(sphere *sphere,trigger trigger,char *name){
    camera tmp;char *msj;
    tmp.sphere=sphere;
    tmp.trigger=trigger;
    asprintf(&tmp.name,"%s",name);
    go(sphere,0,90,90);
    pos_reset(sphere);
    asprintf(&msj,"%s: init().",tmp.name);
    verbose(L_FALL,msj);free(msj);
    return tmp;
}
int camera_off(camera *camera){
    go(camera->sphere,0,-90,-90);
    stepper_off(camera->sphere->st_rho);
    stepper_off(camera->sphere->st_theta);
    stepper_off(camera->sphere->st_phi);
}
double r2d(double r){return r*(180/M_PI);}
double d2r(double d){return d*(M_PI/180);}
int test(){
    int x;
    double f=35;
    double v=15.6; //a77ii=23.5x15.6 35mm=36x24
    double h=23.5;
    double d=sqrt((h*h)+(v*v));
    double aov_v=r2d(2*atan(v/(2*f)));
    double aov_h=r2d(2*atan(h/(2*f)));
    double aov_d=r2d(2*atan(d/(2*f)));
    double a_v=360/(1+floor(360/aov_v));
    double a_h=360/(1+floor(360/aov_h));
    double va=180;
    printf("\n  f=%fmm\n  v=%fmm\n  d=%fmm\naov_v=%f°\naov_h=%f°\naov_d=%f°\n  a_v=%f°\n  a_h=%f°\n\n",f,v,d,aov_v,aov_h,aov_d,a_v,a_h);
    for(x=0;x<=floor(va/a_v);x++){
//        double shift=((va-(aov_v*floor(va/aov_v)))/2)-(va/2);
        double shift=((va-(aov_v*floor(va/aov_v)))/2)-(va/2);
        double pos_phi=(aov_v*x)+shift;
        printf(" x=%i>  phi=%f shift=%f\n",x,pos_phi,shift);
    }
    /*
     * 
     * (x*a)+((va-(a*floor(va/a))-va)/2)
     * 
     * (x*a)+((a*floor(va/a))/2)
     * 
     */
}

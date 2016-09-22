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
int v_shot(double f,double v,double h,double vv,double vh){
    int x,y;
    double  a_v=r2d(2*atan( v/(2*f)));
    double  a_h=r2d(2*atan( h/(2*f)));
    double va_v=r2d(2*atan(vv/(2*f)));
    double va_h=r2d(2*atan(vh/(2*f)));    
    printf("\n      f=%fmm\n sensor=%f X %f mm\n    aov=%f X %f °\nvirtual=%fx%f mm\n   vaov=%f X %f °\n\n",f,h,v,a_v,a_h,vh,vv,va_v,va_h);
    for(y=0;y<=floor(va_h/a_h);y++){
        double pos_theta=((a_h*((y*2)-floor(va_h/a_h)))/2);
        for(x=0;x<=floor(va_v/a_v);x++){
            double pos_phi=((a_v*((x*2)-floor(va_v/a_v)))/2);
            printf("go(0,%f,%f)\n",pos_theta,pos_phi);
        }
    }
    printf("\n");
    /*
     * (x*a)+((va-(a*floor(va/a))-va)/2)
     * (x*a)+((a*floor(va/a))/2)
     */
}

/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "config.h"
#include "verbose.h"
#include "trigger.h"
#include "stepper.h"
#include "sphere.h"
#include "camera.h"
double r2d(double r){return r*(180/M_PI);}
double d2r(double d){return d*(M_PI/180);}
int camera_init(char *name){
    cam=(struct camera*)malloc(sizeof(struct camera));
    verbose(L_INFO,"%s: ★",cam->name=name);
}
int camera_on(){
    sphere_init(stepper_init(RHO_SLEEP,RHO_STEP,RHO_DIR,RHO_M0,RHO_M1,RHO_MODE,RHO_STEPS,"ρ"),
                stepper_init(THETA_SLEEP,THETA_STEP,THETA_DIR,THETA_M0,THETA_M1,THETA_MODE,THETA_STEPS,"θ"),
                stepper_init(PHI_SLEEP,PHI_STEP,PHI_DIR,PHI_M0,PHI_M1,PHI_MODE,PHI_STEPS,"φ"),
                "ο");
    trigger_init("μ");
    camera_init("δ");
}
int camera_off(){
    go(0,OFFSET,OFFSET);
    stepper_off(sphere->st_rho);
    stepper_off(sphere->st_theta);
    stepper_off(sphere->st_phi);
    verbose(L_INFO,"ω\n");alert_led();
    bcm2835_close();
}
int camera_action(){
    switch(a->action){
        case      ACT_35:camera_vshot(a->focal,a->width,a->height,a->overlap,24,36);break;
        case    ACT_6x45:camera_vshot(a->focal,a->width,a->height,a->overlap,60,45);break;
        case    ACT_45x6:camera_vshot(a->focal,a->width,a->height,a->overlap,45,60);break;
        case     ACT_6x6:camera_vshot(a->focal,a->width,a->height,a->overlap,60,60);break;
        case     ACT_6x7:camera_vshot(a->focal,a->width,a->height,a->overlap,60,70);break;
        case     ACT_7x6:camera_vshot(a->focal,a->width,a->height,a->overlap,70,60);break;
        case     ACT_6x8:camera_vshot(a->focal,a->width,a->height,a->overlap,60,80);break;
        case     ACT_8x6:camera_vshot(a->focal,a->width,a->height,a->overlap,80,60);break;
        case     ACT_6x9:camera_vshot(a->focal,a->width,a->height,a->overlap,60,90);break;
        case     ACT_9x6:camera_vshot(a->focal,a->width,a->height,a->overlap,90,60);break;
        case    ACT_6x17:camera_vshot(a->focal,a->width,a->height,a->overlap,60,170);break;
        case    ACT_17x6:camera_vshot(a->focal,a->width,a->height,a->overlap,170,60);break;
        case ACT_VIRTUAL:camera_vshot(a->focal,a->width,a->height,a->overlap,a->vwidth,a->vheight);break;
        case  ACT_SPHERE:verbose(L_INFO,"Not Implemented yet");break;
        case     ACT_XXX:verbose(L_INFO,"Not Implemented yet");break;
    }
}
int camera_vshot(double f,double v,double h,double o,double vv,double vh){
    int x,y;
    double  a_v=r2d(2*atan( v/(2*f)));
    double  a_h=r2d(2*atan( h/(2*f)));
    double va_v=r2d(2*atan(vv/(2*f)));
    double va_h=r2d(2*atan(vh/(2*f)));
    verbose(L_INFO,"%s:     focal: %6.2f mm",cam->name,f);
    verbose(L_INFO,"%s: υ: sensor: %6.2f • %6.2f mm",cam->name,h,v);
    verbose(L_INFO,"%s: υ:      α: %6.2f • %6.2f °",cam->name,a_v,a_h);
    a_v=a_v*(1-(o/2));a_h=a_h*(1-(o/2));
    verbose(L_INFO,"%s: υ:     α': %6.2f • %6.2f °",cam->name,a_v,a_h);
    verbose(L_INFO,"%s: υ:      Ξ: %6.3f",cam->name,o);
    verbose(L_INFO,"%s: ν: sensor: %6.2f • %6.2f mm",cam->name,vh,vv);
    verbose(L_INFO,"%s: ν:      α: %6.2f • %6.2f °",cam->name,va_v,va_h);
    for(y=0;y<=floor(va_h/a_h);y++){
        double pos_theta=((a_h*((y*2)-floor(va_h/a_h)))/2); 
        for(x=0;x<=floor(va_v/(a_v/cos(d2r(pos_theta))));x++){
            double pos_phi=(((a_v/cos(d2r(pos_theta)))*((x*2)-floor(va_v/(a_v/cos(d2r(pos_theta))))))/2);
            go(0,pos_theta,(y%2==0?pos_phi:-pos_phi));
            trigger_shot(0);
        }
    }
}
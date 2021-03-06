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
#include "slave.h"
double r2d(double r){return r*(180/M_PI);}
double d2r(double d){return d*(M_PI/180);}
int camera_init(char *name){
    cam=(struct camera*)malloc(sizeof(struct camera));
    verbose(L_CAMR,"%s: ★:",cam->name=name);
}
int camera_on(){
    if(!w_init())error("bcm2835 missing");
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
    w_close();
}
int camera_action(){
    switch(a->action){
        case ACT_SLAVE:break;
        default: camera_on();
    }
    switch(a->action){
        case      ACT_35:camera_vshot(a->focal,a->height,a->width,a->overlap,36,24);break;
        case    ACT_6x45:camera_vshot(a->focal,a->height,a->width,a->overlap,45,60);break;
        case    ACT_45x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,45);break;
        case     ACT_6x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,60);break;
        case     ACT_6x7:camera_vshot(a->focal,a->height,a->width,a->overlap,70,60);break;
        case     ACT_7x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,70);break;
        case     ACT_6x8:camera_vshot(a->focal,a->height,a->width,a->overlap,80,60);break;
        case     ACT_8x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,80);break;
        case     ACT_6x9:camera_vshot(a->focal,a->height,a->width,a->overlap,90,60);break;
        case     ACT_9x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,90);break;
        case    ACT_6x17:camera_vshot(a->focal,a->height,a->width,a->overlap,170,60);break;
        case    ACT_17x6:camera_vshot(a->focal,a->height,a->width,a->overlap,60,170);break;
        case    ACT_TEST:camera_test();break;
        case   ACT_SLAVE:slave_read();break;
        case ACT_VIRTUAL:camera_vshot(a->focal,a->height,a->width,a->overlap,a->vheight,a->vwidth);break;
        case  ACT_SPHERE:camera_sphere(a->focal,a->height,a->width,a->overlap);break;
        case     ACT_XXX:warning("Not Implemented yet");break;
    }
    switch(a->action){
        case ACT_SLAVE:break;
        default: camera_off();
    }
}
int camera_vshot(double f,double v,double h,double o,double vv,double vh){
    int x,y;
    double  a_v=r2d(2*atan( v/(2*f)));
    double  a_h=r2d(2*atan( h/(2*f)));
    double va_v=r2d(2*atan(vv/(2*f)));
    double va_h=r2d(2*atan(vh/(2*f)));
    verbose(L_CAMR,"%s:     focal: %6.2f mm",cam->name,f);
    verbose(L_CAMR,"%s: υ: sensor: %6.2f • %6.2f mm",cam->name,v,h);
    verbose(L_CAMR,"%s: υ:      α: %6.2f • %6.2f °",cam->name,a_v,a_h);
    a_v=a_v*(1-(o/2));a_h=a_h*(1-(o/2));
    verbose(L_CAMR,"%s: υ:     α': %6.2f • %6.2f °",cam->name,a_v,a_h);
    verbose(L_CAMR,"%s: υ:      Ξ: %6.3f",cam->name,o);
    verbose(L_CAMR,"%s: ν: sensor: %6.2f • %6.2f mm",cam->name,vv,vh);
    verbose(L_CAMR,"%s: ν:      α: %6.2f • %6.2f °",cam->name,va_v,va_h);
    for(y=0;y<=floor(va_v/a_v);y++){
        double pos_theta=((a_v*((y*2)-floor(va_v/a_v)))/2); 
        for(x=0;x<=floor(va_h/(a_h/cos(d2r(pos_theta))));x++){
            double pos_phi=(((a_h/cos(d2r(pos_theta)))*((x*2)-floor(va_h/(a_h/cos(d2r(pos_theta))))))/2);
            go(0,pos_theta,(y%2?-pos_phi:pos_phi));
            trigger_shot(0);
        }
    }
}
int camera_sphere(double f,double v,double h,double o){
    int x,y;
    double a_v=r2d(2*atan(v/(2*f)));
    double a_h=r2d(2*atan(h/(2*f)));
    verbose(L_CAMR,"%s:     focal: %6.2f mm",cam->name,f);
    verbose(L_CAMR,"%s: υ: sensor: %6.2f • %6.2f mm",cam->name,v,h);
    verbose(L_CAMR,"%s: υ:      α: %6.2f • %6.2f °",cam->name,a_v,a_h);
    a_v=a_v*(1-(o/2));a_h=a_h*(1-(o/2));
    verbose(L_CAMR,"%s: υ:     α': %6.2f • %6.2f °",cam->name,a_v,a_h);
    verbose(L_CAMR,"%s: υ:      Ξ: %6.3f",cam->name,o);
    for(y=0;y<=ceil(180/a_v);y++){
        double pos_theta=(y*(180/ceil(180/a_v)))-90;
        for(x=0;x<ceil(360/(a_h/cos(d2r(pos_theta))));x++){
            double pos_phi=x*(360/ceil(360/(a_h/cos(d2r(pos_theta)))));
            go(0,pos_theta,pos_phi);
            trigger_shot(0);
        }
    }
}
int camera_test(){
//    go(0,-90,-90);
//    go(0,  0,-90);
//    go(0, 90,-90);
//    go(0,180,-90);
//    go(0,270,-90);

    go(0,0,0);
    w_delayMicroseconds(1*M);
//    go(0,-90,  0);
//    go(0,-90,  0);
//    go(0,-90, 90);
//    go(0,-90,180);
//    go(0,-90,270);
//    go(0,0,0);
}
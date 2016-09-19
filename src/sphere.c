/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stepper.h"
#include "verbose.h"
#include "sphere.h"
sphere sphere_init(stepper rho,stepper theta,stepper phi,char *name){
    sphere tmp;char *msj;
    tmp.rho=tmp.theta=tmp.phi=tmp.s_rho=tmp.s_theta=tmp.s_phi=0;
    tmp.st_rho=rho;tmp.st_theta=theta;tmp.st_phi=phi;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"%s: init().",tmp.name);
    verbose(L_FALL,msj);free(msj);
    return tmp;
}
int go(sphere sphere,double rho,double theta,double phi){
    char *msj;
    double o_phi,o_theta,n_phi,n_theta;
//    o_rho=sphere.rho*(STEPS_LOOP/360.0);    
//    o_theta=sphere.theta*(STEPS_LOOP/360.0);
//    o_phi=sphere.phi*(STEPS_LOOP/360.0);
//    n_rho=rho*(STEPS_LOOP/360.0);    
    n_theta=theta*(STEPS_LOOP/360.0);
    n_phi=phi*(STEPS_LOOP/360.0);
    msj=(char*)malloc(100*sizeof(char));
    sprintf(msj,"%s: old(x,%i,%i) new(x,%f,%f)",sphere.name,sphere.s_theta,sphere.s_phi,n_theta,n_phi);
    verbose(L_POSS,msj);free(msj);    

    
/*
 * if(-180<d=n-o<180)move(d)
 * else move((d<0?1:-1)*(360-d))
 */    
}
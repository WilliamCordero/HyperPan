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
    int n_rho,n_theta,n_phi,d_rho,d_theta,d_phi;
//    n_rho=rho*(STEPS_LOOP/360.0);    
    n_theta=theta*(STEPS_LOOP/360.0);
    n_phi=phi*(STEPS_LOOP/360.0);
    
    msj=(char*)malloc(100*sizeof(char));
    sprintf(msj,"%s: old(f,%f,%f) new(f,%f,%f)",sphere.name,sphere.theta,sphere.phi,theta,phi);
    verbose(L_POSS,msj);
    sprintf(msj,"%s: old(i,%i,%i) new(i,%i,%i)",sphere.name,sphere.s_theta,sphere.s_phi,n_theta,n_phi);
    verbose(L_POSS,msj);
    
    //d_rho=((-180<(d_rho=n_rho-sphere.s_rho))||(d_rho>180)?1:-1)*d_rho;
    d_theta=((-180<(d_theta=n_theta-sphere.s_theta))||(d_theta>180)?1:-1)*d_theta;
    d_phi=((-180<(d_phi=n_phi-sphere.s_phi))||(d_phi>180)?1:-1)*d_phi;
    
    sprintf(msj,"%s: move(i,%i,%i)",sphere.name,d_theta,d_phi);
    verbose(L_POSS,msj);
    free(msj);    
    
    
/*
 * if(-180<d=n-o<180)move(d)
 * else move((d<0?1:-1)*(360-d))
 */    
}
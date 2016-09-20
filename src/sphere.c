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
int go(sphere *sphere,double rho,double theta,double phi){
    char *msj;
    int n_rho,n_theta,n_phi,d_rho,d_theta,d_phi;
//    int md_rho=((sphere->st_rho.mode*sphere->st_rho.steps)/2);
    int md_theta=((sphere->st_theta.mode*sphere->st_theta.steps)/2);
    int md_phi=((sphere->st_phi.mode*sphere->st_phi.steps)/2);
//    n_rho=rho*(STEPS_LOOP/360.0);    
    n_theta=theta*(STEPS_LOOP/360.0);
    n_phi=phi*(STEPS_LOOP/360.0);
//    d_rho=(((-1*md_rho)<(d_rho=n_rho-sphere->s_rho))&&((md_rho)>(d_rho=n_rho-sphere->s_rho)))?d_rho:((d_rho<0?1:-1)*((md_rho*2)-d_rho));
    d_theta=(((-1*md_theta)<(d_theta=n_theta-sphere->s_theta))&&((md_theta)>(d_theta=n_theta-sphere->s_theta)))?d_theta:((d_theta<0?1:-1)*((md_theta*2)-d_theta));
    d_phi=(((-1*md_phi)<(d_phi=n_phi-sphere->s_phi))&&((md_phi)>(d_phi=n_phi-sphere->s_phi)))?d_phi:((d_phi<0?1:-1)*((md_phi*2)-d_phi));
    asprintf(&msj,"%s: (i,%i,%i)<->(i,%i,%i)->(i,%i,%i).",sphere->name,sphere->s_theta,sphere->s_phi,n_theta,n_phi,d_theta,d_phi);
    verbose(L_POSS,msj);free(msj);
//    sphere->rho=rho;sphere->s_rho=n_rho;
    sphere->theta=theta;sphere->s_theta=n_theta;
    sphere->phi=phi;sphere->s_phi=n_phi;
    stepper_walk_sync(sphere->st_theta,d_theta,sphere->st_phi,d_phi);
}
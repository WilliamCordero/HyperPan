/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "config.h"
#include "stepper.h"
#include "verbose.h"
#include "sphere.h"
int sphere_init(stepper rho,stepper theta,stepper phi,char *name){
    sphere=(struct sph*)malloc(sizeof(struct sph));
    sphere->rho=sphere->s_rho=0;
    sphere->theta=sphere->phi=OFFSET;
    sphere->s_theta=sphere->s_phi=OFFSET*(STEPS_LOOP/360.0);
    sphere->st_rho=rho;sphere->st_theta=theta;sphere->st_phi=phi;
    verbose(L_SPHR,"%s: ★:",sphere->name=name);
}
int go(double rho,double theta,double phi){
    int n_rho,n_theta,n_phi,d_rho,d_theta,d_phi;
    int md_rho=((sphere->st_rho.mode*sphere->st_rho.steps)/2);
    int md_theta=((sphere->st_theta.mode*sphere->st_theta.steps)/2);
    int md_phi=((sphere->st_phi.mode*sphere->st_phi.steps)/2);
    n_rho=rho*(STEPS_LOOP/360.0);    
    n_theta=theta*(STEPS_LOOP/360.0);
    n_phi=phi*(STEPS_LOOP/360.0);
    d_rho=(((-1*md_rho)<=(d_rho=n_rho-sphere->s_rho))&&((md_rho)>=(d_rho=n_rho-sphere->s_rho)))?d_rho:((d_rho<0?1:-1)*((md_rho*2)-abs(d_rho)));
    d_theta=(((-1*md_theta)<=(d_theta=n_theta-sphere->s_theta))&&((md_theta)>=(d_theta=n_theta-sphere->s_theta)))?d_theta:((d_theta<0?1:-1)*((md_theta*2)-abs(d_theta)));
    d_phi=(((-1*md_phi)<=(d_phi=n_phi-sphere->s_phi))&&((md_phi)>=(d_phi=n_phi-sphere->s_phi)))?d_phi:((d_phi<0?1:-1)*((md_phi*2)-abs(d_phi)));
    verbose(L_SPHR,"%s: ↝: %4.2f:ρ %7.2f:θ %7.2f:φ",sphere->name,rho,theta,phi);
    sphere->rho=rho;sphere->s_rho=n_rho;
    sphere->theta=theta;sphere->s_theta=n_theta;
    sphere->phi=phi;sphere->s_phi=n_phi;
    stepper_walk(sphere->st_theta,d_theta,sphere->st_phi,d_phi,a->min,a->max,a->border);
}
int pos_reset(){sphere->rho=sphere->theta=sphere->phi=sphere->s_rho=sphere->s_theta=sphere->s_phi=0;}
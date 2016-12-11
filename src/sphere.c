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
    tmp.rho=tmp.s_rho=0;
    tmp.theta=tmp.phi=OFFSET;
    tmp.s_theta=tmp.s_phi=OFFSET*(STEPS_LOOP/360.0);
    tmp.st_rho=rho;tmp.st_theta=theta;tmp.st_phi=phi;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"%s: init()",tmp.name);
    verbose(L_INFO,msj);free(msj);
    return tmp;
}
int go(sphere *sphere,double rho,double theta,double phi){
    char *msj;
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
//    asprintf(&msj,"%s: (%i,%i,%i)<>(%i,%i,%i).",sphere->name,sphere->s_rho,sphere->s_theta,sphere->s_phi,n_rho,n_theta,n_phi);
//    asprintf(&msj,"%s: ( %4.2f, %7.2f,%7.2f )( %4.2f, %7.2f, %7.2f ).",sphere->name,sphere->rho,sphere->theta,sphere->phi,rho,theta,phi);
    asprintf(&msj,"%s: %4.2f, %7.2f,%7.2f",sphere->name,rho,theta,phi);
    verbose(L_POSS,msj);free(msj);
    sphere->rho=rho;sphere->s_rho=n_rho;
    sphere->theta=theta;sphere->s_theta=n_theta;
    sphere->phi=phi;sphere->s_phi=n_phi;
//    printf("pulse=%d\n",args.pulse);
//    stepper_walk(sphere->st_theta,d_theta,sphere->st_phi,d_phi,args->pulse,args->accel,args->border);
    stepper_walk(sphere->st_theta,d_theta,sphere->st_phi,d_phi,pulse,accel,border);
    
}
int pos_reset(sphere *sphere){sphere->rho=sphere->theta=sphere->phi=sphere->s_rho=sphere->s_theta=sphere->s_phi=0;}

/*
int pos_offset(sphere *sphere,double o_rho,double o_theta,double o_phi){
    sphere->rho=sphere->rho+o_rho;
    sphere->theta=sphere->theta+o_theta;
    sphere->phi=sphere->phi+o_phi;
    sphere->s_rho=sphere->s_rho+()
    sphere->s_theta=
    sphere->s_phi=0;
}
 */
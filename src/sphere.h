/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

#ifndef SPHERE_H
#define SPHERE_H

#ifdef __cplusplus
extern "C" {
#endif

#define STEPS_LOOP 51200 //200*8*32
    
typedef struct sphere{
    double rho;
    double theta;
    double phi;
    stepper st_rho;
    stepper st_theta;
    stepper st_phi;
    int s_rho;
    int s_theta;
    int s_phi;
    char *name;
}sphere;

sphere sphere_init(stepper rho,stepper theta,stepper phi,char *name);
int go(sphere sphere,double rho,double theta,double phi);

#ifdef __cplusplus
}
#endif

#endif /* SPHERE_H */


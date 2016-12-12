/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef SPHERE_H
#define SPHERE_H
#ifdef __cplusplus
extern "C" {
#endif
#define STEPS_LOOP 51200 //200*8*32
#define OFFSET     -90
typedef struct sph{
    int s_rho;
    int s_theta;
    int s_phi;  
    double rho;
    double theta;
    double phi;
    struct stepper st_rho;
    struct stepper st_theta;
    struct stepper st_phi;
    char *name;
}sph;
struct sph *sphere;
int sphere_init(stepper rho,stepper theta,stepper phi,char *name);
int go(double rho,double theta,double phi);
int pos_reset();
#ifdef __cplusplus
}
#endif
#endif /* SPHERE_H */


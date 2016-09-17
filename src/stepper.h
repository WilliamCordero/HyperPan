/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef STEPPER_H
#define STEPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#define PULSE  30
#define ACCEL  8
   
typedef struct stepper{
    int sleep;
    int step;
    int dir;    
    int m0;
    int m1;
    char *name;
}stepper;

stepper stepper_init(int sleep,int step,int dir,int m0,int m1,char *name);
int stepper_mode(stepper motor,int mode); /* Valid modes 1,2,4,8,16,32 everything else sets as 1 */
int stepper_on(stepper motor);
int stepper_off(stepper motor);
int stepper_walk(stepper motor,int dir,int steps);
int stepper_walk_sync(stepper phi,int phi_n,int phi_dir,stepper theta,int theta_n,int theta_dir);
int stepper_walk_round(stepper motor,int dir,int n);
    
#ifdef __cplusplus
}
#endif

#endif /* STEPPER_H */


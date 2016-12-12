/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef STEPPER_H
#define STEPPER_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct stepper{
    int sleep;
    int step;
    int dir;    
    int m0;
    int m1;
    int mode;
    int steps;
    char *name;
}stepper;
stepper stepper_init(int sleep,int step,int dir,int m0,int m1,int mode,int steps,char *name);
int stepper_on(stepper motor);
int stepper_off(stepper motor);
int stepper_walk(stepper l_st,int l_n,stepper s_st,int s_n, int pulse, int accel,int border);
#ifdef __cplusplus
}
#endif
#endif /* STEPPER_H */


/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

/* 
 * File:   stepper.h
 * Author: wcordero
 *
 * Created on September 8, 2016, 12:06 AM
 */

#ifndef STEPPER_H
#define STEPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#define PULSE 30
    
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

#ifdef __cplusplus
}
#endif

#endif /* STEPPER_H */


/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

/* 
 * File:   trigger.h
 * Author: wcordero
 *
 * Created on September 7, 2016, 1:22 AM
 */

#ifndef TRIGGER_H
#define TRIGGER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct trigger{
    int shutter;
    int shutter_speed;
    int focus;    
    int focus_mode;
    int focus_delay;
}trigger;

trigger trigger_init(int shutter,int focus,int focus_mode,int focus_delay);
int trigger_shot(trigger trigger,int speed);

#ifdef __cplusplus
}
#endif

#endif /* TRIGGER_H */


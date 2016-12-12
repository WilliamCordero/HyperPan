/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef TRIGGER_H
#define TRIGGER_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct trig{
    int shutter;
    int shutter_speed;
    int focus;    
    int focus_mode;
    int focus_delay;
    char *name;
}trig;
struct trig *trigger;
int trigger_init(int focus_mode,int focus_delay,char *name);
int trigger_shot(int speed);
#ifdef __cplusplus
}
#endif
#endif /* TRIGGER_H */


/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef TRIGGER_H
#define TRIGGER_H
#ifdef __cplusplus
extern "C" {
#endif
#define SHUTTER 17
#define FOCUS   4
#define SPEED   750000
#define AF      1    
#define MF      0    
typedef struct trigger{
    int shutter;
    int shutter_speed;
    int focus;    
    int focus_mode;
    int focus_delay;
    char *name;
}trigger;
trigger trigger_init(int focus_mode,int focus_delay,char *name);
int trigger_shot(trigger trigger,int speed);
#ifdef __cplusplus
}
#endif
#endif /* TRIGGER_H */


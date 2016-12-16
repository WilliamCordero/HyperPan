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
    double shutter_speed;
    double shutter_delay;
    int focus;    
    int focus_mode;
    char *name;
}trig;
struct trig *trigger;
int trigger_init(char *name);
int trigger_shot(double speed);
#ifdef __cplusplus
}
#endif
#endif /* TRIGGER_H */


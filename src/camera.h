/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef CAMERA_H
#define CAMERA_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct camera{
    trigger trigger;
    sphere *sphere;
    char *name;
}camera;
camera camera_init(sphere *sphere,trigger trigger,char *name);
int camera_off(camera *camera);
int virtual_shot(camera *camera,double f,double v,double h,double o,double vv,double vh);
#ifdef __cplusplus
}
#endif
#endif /* CAMERA_H */


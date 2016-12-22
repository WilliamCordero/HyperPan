/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef CAMERA_H
#define CAMERA_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct camera{
    char *name;
}camera;
struct camera *cam;
int camera_on();
int camera_off();
int camera_action();
int camera_vshot(double f,double v,double h,double o,double vv,double vh);
int camera_sphere(double f,double v,double h,double o);
int camera_test();
#ifdef __cplusplus
}
#endif
#endif /* CAMERA_H */
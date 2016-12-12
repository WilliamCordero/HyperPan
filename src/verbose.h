/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef VERBOSE_H
#define VERBOSE_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct args{
    int    level;
    int    action;
    int    dummy;
    int    pulse;
    int    accel;
    int    border;
    double focal;
    double width;
    double height;
    double vwidth;
    double vheight;
    double overlap;
    char  *file;
}args;
struct args *a;
int verbose_init(int argc,char**argv);
int verbose(int level,char *msj);
int warning(char *msj);
int error(char *msj);
int alert_led();
#ifdef __cplusplus
}
#endif
#endif /* VERBOSE_H */


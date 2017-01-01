/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef VERBOSE_H
#define VERBOSE_H
#ifdef __cplusplus
extern "C" {
#endif
typedef struct args{
    int level;
    int action;
    int dummy;
    int min;
    int max;
    int border;
    int focus;
    int shutter;
   char *file;
   char *load;
 double focal;
 double width;
 double height;
 double vwidth;
 double vheight;
 double overlap;
 double speed;
 double delay;
}args;
struct args *a;
int verbose_init(int argc,char**argv);
int verbose(int level,char *str,...);
int save(char *str,...);
int warning(char *str,...);
int error(char *str,...);
int alert_led();
#ifdef __cplusplus
}
#endif
#endif /* VERBOSE_H */
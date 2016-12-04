/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef VERBOSE_H
#define VERBOSE_H
#ifdef __cplusplus
extern "C" {
#endif
#define ALERT_GPIO  21
#define ALERT_BLINK 20000
#define L_NONE 0b00000000
#define L_INFO 0b00000001
#define L_POSS 0b00000010
#define L_ACCT 0b00000100
#define L_TRGR 0b00001000
#define L_ALL  0b00010000
#define D_LEVEL   3
#define D_FOCAL   50.0
#define D_WIDTH   15.6
#define D_HEIGHT  23.5
#define D_OVERLAP 0.375
#define D_VWIDTH  60.0
#define D_VHEIGHT 60.0
#define D_FILE    "out"
#define D_DUMMY   0
#define ACT_VIRTUAL 1
#define ACT_SPHERE  2
#define ACT_XXX     3

#define VERSION  "HyperPan 0.6";
#define BUG_REP  "William Cordero <william.cordero@gmail.com>";
//#define HELP_DOC "\n * HyperPan Control Software.\n\n * William Cordero Photo\n * http://williamcordero.com\n * https://github.com/WilliamCordero/HyperPan";
#define HELP_DOC "\n * HyperPan Control Software.\n\n * William Cordero Photo\n * http://williamcordero.com\n * https://github.com/WilliamCordero/HyperPan\n\nActions:\n\n  virtual\tEmulate a bigger sensor\n  sphere\tCover the entire area\n\nOptions:";
#define ARGS_DOC "virtual|sphere|..."
typedef struct args{
    int    level;
    int    action;
    int    dummy;
    double focal;
    double width;
    double height;
    double vwidth;
    double vheight;
    double overlap;
    char  *file;
}args;
int verbose_l;
args verbose_init(int argc,char**argv);
int verbose(int level,char *msj);
int warning(char *msj);
int error(char *msj);
int alert_led();
#ifdef __cplusplus
}
#endif
#endif /* VERBOSE_H */


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
#define ACT_35      10
#define ACT_6x45    11
#define ACT_45x6    12
#define ACT_6x6     13
#define ACT_6x7     14
#define ACT_7x6     15
#define ACT_6x8     16
#define ACT_8x6     17
#define ACT_6x9     18
#define ACT_9x6     19
#define ACT_6x17    20
#define ACT_17x6    21
#define PULSE_DEF    30
#define ACCEL_DEF    10
#define BORDER_DEF   8
#define PULSE_SLOTH  180
#define ACCEL_SLOTH  4
#define BORDER_SLOTH 2
#define VERSION  "HyperPan 0.6";
#define BUG_REP  "William Cordero <william.cordero@gmail.com>";
//#define HELP_DOC "\n * HyperPan Control Software.\n\n * William Cordero Photo\n * http://williamcordero.com\n * https://github.com/WilliamCordero/HyperPan";
#define HELP_DOC "\n\
 * HyperPan Control Software.\n\
   William Cordero Photo\n\
   http://williamcordero.com\n\
   https://github.com/WilliamCordero/HyperPan\n\n\
Actions:\n\n\
   virtual\tCustom size virtual sensor\n\
   sphere\tCover the entire area\n\
   35\t\tFull Frame    24x36mm\n\
   6x6\t\tMedium Format 60x60mm\n\
   6x45 45x6\tMedium Format 60x45mm\n\
   6x7   7x6\tMedium Format 60x70mm\n\
   6x8   8x6\tMedium Format 60x80mm\n\
   6x9   9x6\tMedium Format 60x90mm\n\
   6x17 17x6\tMedium Format 60x170mm\n\n\
Options:";
#define ARGS_DOC "virtual|sphere|35|6x45|45x6|6x6|6x7|7x6|6x8|8x6|6x9|9x6|6x17|17x6"
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


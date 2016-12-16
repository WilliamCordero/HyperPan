/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef CONFIG_H
#define CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif
#define M 1000000
//STEPPER CONFIGURATION
#define RHO_SLEEP    22    //GPIO 22
#define RHO_STEP     27    //GPIO 27
#define RHO_DIR      18    //GPIO 18
#define RHO_M0       24    //GPIO 24
#define RHO_M1       23    //GPIO 23
#define RHO_MODE     32    //MICROSTEP MODE 1/32
#define RHO_STEPS    200*8 //STEPS PER ROTATION
#define THETA_SLEEP  12    //GPIO 12
#define THETA_STEP   6     //GPIO 6
#define THETA_DIR    5     //GPIO 5
#define THETA_M0     16    //GPIO 16
#define THETA_M1     13    //GPIO 13
#define THETA_MODE   32    //MICROSTEP MODE 1/32
#define THETA_STEPS  200*8 //STEPS PER ROTATION
#define PHI_SLEEP    22    //GPIO 22
#define PHI_STEP     27    //GPIO 27
#define PHI_DIR      18    //GPIO 18
#define PHI_M0       24    //GPIO 24
#define PHI_M1       23    //GPIO 23
#define PHI_MODE     32    //MICROSTEP MODE 1/32
#define PHI_STEPS    200*8 //STEPS PER ROTATION
//ALERT LED
#define ALERT_GPIO   21    //GPIO 21
#define ALERT_BLINK  20000 //MILISEC
//TRIGGER CONFIGURATION
#define SHUTTER      4     //GPIO 17
#define FOCUS        17    //GPIO 4
#define SPEED        0.5   //1/125
#define DELAY        0.0   //DELAY BEFORE SHOT
#define AF           1     //AUTO FOCUS 
#define MF           0     //MANUAL FOCUS 
//VERVOSE LEVELS
#define L_NONE 0b00000000
#define L_INFO 0b00000001
#define L_POSS 0b00000010
#define L_ACCT 0b00000100
#define L_TRGR 0b00001000
#define L_ALL  0b00010000
//DEFAULT ARGS
#define D_LEVEL    3       //DEFAULT VERVOSE LEVEL
#define D_FOCAL    50.0    //DEFAULT FOCAL LENGH
#define D_WIDTH    15.6    //DEFAULT SENSOR WIDTH
#define D_HEIGHT   23.5    //DEFAULT SENSOR HEIGHT 
#define D_OVERLAP  0.375   //DEFAULT OVERLAP
#define D_VWIDTH   60.0    //DEFAULT VIRTUAL WIDTH
#define D_VHEIGHT  60.0    //DEFAULT VIRTUAL HEIGHT
#define D_FILE     "out"   //DEFAULT FILE NAME
#define D_DUMMY    0       //DEFAULT DUMMY
//ACTIONS
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
//MOVEMENT SPEED
#define PULSE_DEF    40
#define ACCEL_DEF    10
#define BORDER_DEF   8
#define PULSE_SLOTH  180
#define ACCEL_SLOTH  4
#define BORDER_SLOTH 2
//ARGP
#define VERSION  "HyperPan 0.61";
#define BUG_REP  "William Cordero <william.cordero@gmail.com>";
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
#ifdef __cplusplus
}
#endif
#endif /* CONFIG_H */


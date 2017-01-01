/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef CONFIG_H
#define CONFIG_H
#ifdef __cplusplus
extern "C" {
#endif
#define      VERSION "HyperPan 0.62";
#define      BUG_REP "William Cordero <william.cordero@gmail.com>";
#define            M 1000000
//STEPPER CONFIGURATION
#define    RHO_SLEEP 22    //GPIO 22
#define     RHO_STEP 27    //GPIO 27
#define      RHO_DIR 18    //GPIO 18
#define       RHO_M0 24    //GPIO 24
#define       RHO_M1 23    //GPIO 23
#define     RHO_MODE 32    //MICROSTEP MODE 1/32
#define    RHO_STEPS 200*8 //STEPS PER ROTATION
#define  THETA_SLEEP 12    //GPIO 12
#define   THETA_STEP 6     //GPIO 6
#define    THETA_DIR 5     //GPIO 5
#define     THETA_M0 16    //GPIO 16
#define     THETA_M1 13    //GPIO 13
#define   THETA_MODE 32    //MICROSTEP MODE 1/32
#define  THETA_STEPS 200*8 //STEPS PER ROTATION
#define    PHI_SLEEP 22    //GPIO 22
#define     PHI_STEP 27    //GPIO 27
#define      PHI_DIR 18    //GPIO 18
#define       PHI_M0 24    //GPIO 24
#define       PHI_M1 23    //GPIO 23
#define     PHI_MODE 32    //MICROSTEP MODE 1/32
#define    PHI_STEPS 200*8 //STEPS PER ROTATION
//ALERT LED
#define   ALERT_GPIO 21    //GPIO 21
#define  ALERT_BLINK 20000 //MILISEC
//TRIGGER CONFIGURATION
#define      SHUTTER 4     //GPIO 17
#define        FOCUS 17    //GPIO 4
#define        SPEED 0.5   //1/125
#define        DELAY 0.0   //DELAY BEFORE SHOT
#define           AF 1     //AUTO FOCUS 
#define           MF 0     //MANUAL FOCUS 
//VERVOSE LEVELS
#define       L_NONE 0b00000000 //0
#define        L_ALL 0b11111111 //X
#define       L_INFO 0b00000001 //1
#define       L_STPR 0b00000010 //2
#define       L_SPHR 0b00000100 //4
#define       L_CAMR 0b00001000 //8
#define       L_TRGR 0b00010000 //16
#define       L_SLVE 0b00100000 //32
#define       L_OUTP 0b01000000 //64
//#define       L_OUTP 0b10000000 //128
#define       L_TEST 0b00000000 //
//DEFAULT ARGS
#define      D_LEVEL 9     //DEFAULT VERVOSE LEVEL
#define      D_FOCAL 50.0  //DEFAULT FOCAL LENGH
#define      D_WIDTH 15.6  //DEFAULT SENSOR WIDTH
#define     D_HEIGHT 23.5  //DEFAULT SENSOR HEIGHT 
#define    D_OVERLAP 0.375 //DEFAULT OVERLAP
#define     D_VWIDTH 60.0  //DEFAULT VIRTUAL WIDTH
#define    D_VHEIGHT 60.0  //DEFAULT VIRTUAL HEIGHT
//#define       D_FILE "out" //DEFAULT FILE NAME
#define      D_DUMMY 0     //DEFAULT DUMMY
//ACTIONS
//SLAVE INSTRUCTIONS
#define      ACT_NOP 0
#define       ACT_ON 1
#define      ACT_OFF 2
#define    ACT_SLEEP 3
#define    ACT_WRITE 4
#define     ACT_FSEL 5
#define   ACT_SETPUD 6
#define     ACT_TEST 10
#define  ACT_VIRTUAL 11
#define   ACT_SPHERE 12
#define    ACT_SLAVE 13
#define      ACT_XXX 99
#define       ACT_35 100
#define     ACT_6x45 101
#define     ACT_45x6 102
#define      ACT_6x6 103
#define      ACT_6x7 104
#define      ACT_7x6 105
#define      ACT_6x8 106
#define      ACT_8x6 107
#define      ACT_6x9 108
#define      ACT_9x6 109
#define     ACT_6x17 110
#define     ACT_17x6 111
//MOVEMENT SPEED
#define      MIN_DEF 40    //40
#define      MAX_DEF 230   //230
#define   BORDER_DEF 14    //14
#define     MIN_SLOW 200
#define     MAX_SLOW 400
#define  BORDER_SLOW 2
#define     MIN_FAST 40
#define     MAX_FAST 40
#define  BORDER_FAST 1000
//ARGP
#define     ARGS_DOC "virtual|sphere|slave|35|6x45|45x6|6x6|6x7|7x6|6x8|8x6|6x9|9x6|6x17|17x6"
#define     HELP_DOC "\n\
 * HyperPan Control Software.\n\
   William Cordero Photo\n\
   http://williamcordero.com\n\
   https://github.com/WilliamCordero/HyperPan\n\n\
Actions:\n\n\
   virtual\tCustom size virtual sensor\n\
   sphere\tCover the entire area\n\
   slave\tSlave mode\n\
   35\t\tFull Frame    24x36mm\n\
   6x6\t\tMedium Format 60x60mm\n\
   6x45 45x6\tMedium Format 60x45mm\n\
   6x7   7x6\tMedium Format 60x70mm\n\
   6x8   8x6\tMedium Format 60x80mm\n\
   6x9   9x6\tMedium Format 60x90mm\n\
   6x17 17x6\tMedium Format 60x170mm\n\n\
Options:";
#ifdef __cplusplus
}
#endif
#endif /* CONFIG_H */


/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <argp.h>
#include "config.h"
#include "slave.h"
#include "verbose.h"
#include "camera.h"
const char *argp_program_version=VERSION;
const char *argp_program_bug_address=BUG_REP;
static char doc[]=HELP_DOC;
static char args_doc[]=ARGS_DOC;
static struct argp_option options[]={
    {"auto",   'a',0,        0,"Auto Focus On"},
    {"delay",  'b',"DELAY",  0,"Shutter delay"},
    {"fast",   'c',0,        0,"High speed"},
    {"dummy",  'd',0,        0,"Dummy mode"},
    {"focal",  'f',"FOCAL",  0,"Focal length(Def:50mm)"},
    {"save",   'g',"FILE",   0,"Save to file"},
    {"height", 'h',"HEIGHT", 0,"Sensor height(Def:23.5mm)"},
    {"load",   'l',"FILE",   0,"Load file"},
    {"motion", 'm',0,        0,"No shutter"},
    {"overlap",'o',"OVERLAP",0,"Overlap area(Def:0.375)"},
    {"quiet",  'q',0,        0,"Quiet output"},
    {"speed",  's',"SPEED",  0,"Shutter speed(Def:0.5s)"},
    {"verbose",'v',"LEVEL",  0,"Verbose level"},
    {"width",  'w',"WIDTH",  0,"Sensor width(Def:15.6mm)"},
    {"vwidth", 'x',"VWIDTH", 0,"Virtual sensor width(Def:60mm)"},
    {"vheight",'y',"VHEIGHT",0,"Virtual sensor height(Def:60mm)"},
    {"slow",   'z',0,        0,"Low speed"},
    {0}
};
static error_t parse_opt(int key,char *arg,struct argp_state *state){
  switch(key){
    case 'a':a->focus=AF;break;
    case 'b':a->delay=atof(arg);break;
    case 'c':a->min=MIN_FAST;
             a->max=MAX_FAST;
             a->border=BORDER_FAST;
             break;
    case 'd':a->dummy=1;break;        
    case 'f':a->focal=atof(arg);break;
    case 'g':a->file=arg;break;
    case 'h':a->height=atof(arg);break;
    case 'l':a->load=arg;break;
    case 'm':a->shutter=0;break;
    case 'o':a->overlap=atof(arg);break;
    case 'q':a->level=L_NONE;break;
    case 's':a->speed=atof(arg);break;
    case 'v':a->level=atoi(arg);break;
    case 'w':a->width=atof(arg);break;
    case 'x':a->vwidth=atof(arg);break;
    case 'y':a->vheight=atof(arg);break;
    case 'z':a->min=MIN_SLOW;
             a->max=MAX_SLOW;
             a->border=BORDER_SLOW;
             break;
    case ARGP_KEY_ARG:
        if(state->arg_num==0){
                 if(!strcmp(arg,"test"))   a->action=ACT_TEST;
            else if(!strcmp(arg,"virtual"))a->action=ACT_VIRTUAL;
            else if(!strcmp(arg,"sphere")) a->action=ACT_SPHERE;
            else if(!strcmp(arg,"slave"))  a->action=ACT_SLAVE;
            else if(!strcmp(arg,"35"))     a->action=ACT_35;
            else if(!strcmp(arg,"6x45"))   a->action=ACT_6x45;
            else if(!strcmp(arg,"45x6"))   a->action=ACT_45x6;
            else if(!strcmp(arg,"6x6"))    a->action=ACT_6x6;
            else if(!strcmp(arg,"6x7"))    a->action=ACT_6x7;
            else if(!strcmp(arg,"7x6"))    a->action=ACT_7x6;
            else if(!strcmp(arg,"6x8"))    a->action=ACT_6x8;
            else if(!strcmp(arg,"8x6"))    a->action=ACT_8x6;
            else if(!strcmp(arg,"6x9"))    a->action=ACT_6x9;
            else if(!strcmp(arg,"9x6"))    a->action=ACT_9x6;
            else if(!strcmp(arg,"6x17"))   a->action=ACT_6x17;
            else if(!strcmp(arg,"17x6"))   a->action=ACT_17x6;
            else if(!strcmp(arg,"xxx"))    a->action=ACT_XXX;
            else argp_usage(state);//error("Invalid Action.");
        }
        if(state->arg_num>0)argp_usage(state);break;
    case ARGP_KEY_END:
        if(state->arg_num<1)argp_usage(state);break;
    default:
        return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
static struct argp argp={options,parse_opt,args_doc,doc};
int verbose_init(int argc,char**argv){
    a=(struct args*)malloc(sizeof(struct args));
    a->focus=MF;
    a->speed=SPEED;
    a->delay=DELAY;
    a->level=D_LEVEL;
    a->focal=D_FOCAL;
    a->file=0;
    a->load=0;
    a->width=D_WIDTH;
    a->height=D_HEIGHT;
    a->overlap=D_OVERLAP;
    a->vwidth=D_VWIDTH;
    a->vheight=D_VHEIGHT;
    a->dummy=D_DUMMY;
    a->shutter=1;
    a->min=MIN_DEF;
    a->max=MAX_DEF;
    a->border=BORDER_DEF;
    argp_parse(&argp,argc,argv,0,0,a);
    slave_init("λ");
    verbose(L_INFO,"α: %s",a->dummy?"dummy mode":"");
    camera_action();
    verbose(L_INFO,"ω:");
    slave_stop();
}
int verbose(int level,char *str,...){
    va_list args;
    if(level&a->level){
        if(level!=L_OUTP)printf("# ");
        va_start(args,str);
        vprintf(str,args);
        va_end(args);
        printf("\n");
    }
}
int save(char *str,...){
    va_list args;
    if(a->file){
        va_start(args,str);
        vfprintf(out,str,args);
        va_end(args);
        fprintf(out,"\n");
    }
}
int warning(char *str,...){
    va_list args;
    alert_led();alert_led();
    fprintf(stderr,"# χ: ");
    va_start(args,str);
    vfprintf(stderr,str,args);
    va_end(args);
    fprintf(stderr,"\n");
}
int error(char *str,...){
    va_list args;
    fprintf(stderr,"# χχ: ");
    va_start(args,str);
    vfprintf(stderr,str,args);printf("\n");
    va_end(args);
    fprintf(stderr,"\n");
    exit(1);
}
int alert_led(){
    int i;
    w_gpio_fsel(ALERT_GPIO,GPIO_FSEL_OUTP);
    for(i=0;i<3;i++){
        w_gpio_write(ALERT_GPIO,HIGH);
        w_delayMicroseconds(ALERT_BLINK);
        w_gpio_write(ALERT_GPIO,LOW);
        w_delayMicroseconds(ALERT_BLINK);
    }
}
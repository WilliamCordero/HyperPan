/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <argp.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "verbose.h"
const char *argp_program_version="HyperPan 0.6";
const char *argp_program_bug_address="William Cordero <william.cordero@gmail.com>";
static char doc[]="\n * HyperPan Control Software.\n\n * William Cordero Photo\n * http://williamcordero.com\n * https://github.com/WilliamCordero/HyperPan";
static char args_doc[]="ACTION";
static struct argp_option options[]={
  {"quiet",'q',0,0,"Quiet verbose"},
  {"verbose",'v',"LEVEL",0,"Verbose level"},
  {"focal",'f',"FOCAL",0,"Focal length(Def:50mm)"},
  {"width",'w',"WIDTH",0,"Sensor width(Def:15.6mm)"},
  {"height",'h',"HEIGHT",0,"Sensor height(Def:23.5mm)"},
  {"overlap",'o',"OVERLAP",0,"Overlap area(Def:0.375)"},
  {"v_width",'x',"V_WIDTH",0,"Virtual sensor width(Def:60mm)"},
  {"v_height",'y',"V_HEIGHT",0,"Virtual sensor height(Def:60mm)"},
  //  {"dummy",'d',0,0,"Mock-up behaviour"},
  {"save",'s',"FILE",0,"Save to file"},
  {0}
};
typedef struct args{
    char *file;
    char *level;
    char *focal;
    char *width;
    char *height;
    char *vwidth;
    char *vheight;
    char *overlap;
    char *action;
}args;
static error_t parse_opt(int key,char *arg,struct argp_state *state){
  struct args *args=state->input;
  switch(key){
    case 'q':
      strcpy(args->level,"0");break;
    case 'v':
      args->level=arg;break;
    case 'f':
      args->focal=arg;break;
    case 'w':
      args->width=arg;break;
    case 'h':
      args->height=arg;break;
    case 'o':
      args->overlap=arg;break;
    case 'x':
      args->vwidth=arg;break;
    case 'y':
      args->vheight=arg;break;
    case 's':
      args->file=arg;break;
    case 'd':
      dummy=1;break;        
    case ARGP_KEY_ARG:
      if(state->arg_num==0)args->action=arg;
      if(state->arg_num>0)argp_usage(state);
      break;
    case ARGP_KEY_END:
      if (state->arg_num<1)argp_usage(state);
      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
static struct argp argp={options,parse_opt,args_doc,doc};
int verbose_init(int argc,char**argv){
    args args;
    asprintf(&args.level,"%d",D_LEVEL);
    asprintf(&args.focal,"%f",D_FOCAL);
    asprintf(&args.width,"%f",D_WIDTH);
    asprintf(&args.height,"%f",D_HEIGHT);
    asprintf(&args.overlap,"%f",D_OVERLAP);
    asprintf(&args.vwidth,"%f",D_VWIDTH);
    asprintf(&args.vheight,"%f",D_VHEIGHT);
    asprintf(&args.file,"%s",D_FILE);
    dummy=0;
    argp_parse(&argp,argc,argv,0,0,&args);
    verbose_l=atoi(args.level);
    focal=atof(args.focal);
    width=atof(args.width);
    height=atof(args.height);
    overlap=atof(args.overlap);
    vwidth=atof(args.vwidth);
    vheight=atof(args.vheight);
    asprintf(&file,"%s",args.file);
         if(!strcmp(args.action,"virtual"))action=ACT_VIRTUAL;
    else if(!strcmp(args.action,"xxx"))    action=ACT_XXX;
    else error("Invalid Action.");
}
int verbose(int level,char *msj){
    if(level<=verbose_l)printf("|> %s\n",msj);
}
int warning(char *msj){
    alert_led();alert_led();
    fprintf(stderr,"|> χ: %s\n",msj);
}
int error(char *msj){
    alert_led();alert_led();
    fprintf(stderr,"|> χχ: %s\n",msj);
    exit(1);
}
int alert_led(){
    int i;
    bcm2835_gpio_fsel(ALERT_GPIO,BCM2835_GPIO_FSEL_OUTP);
    for(i=0;i<3;i++){
        bcm2835_gpio_write(ALERT_GPIO,HIGH);
        bcm2835_delayMicroseconds(ALERT_BLINK);
        bcm2835_gpio_write(ALERT_GPIO,LOW);
        bcm2835_delayMicroseconds(ALERT_BLINK);
    }
}
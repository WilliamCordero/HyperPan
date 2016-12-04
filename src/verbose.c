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
const char *argp_program_version=VERSION;
const char *argp_program_bug_address=BUG_REP;
static char doc[]=HELP_DOC;
static char args_doc[]=ARGS_DOC;
static struct argp_option options[]={
  {"quiet",'q',0,0,"Quiet verbose"},
  {"verbose",'v',"LEVEL",0,"Verbose level"},
  {"focal",'f',"FOCAL",0,"Focal length(Def:50mm)"},
  {"width",'w',"WIDTH",0,"Sensor width(Def:15.6mm)"},
  {"height",'h',"HEIGHT",0,"Sensor height(Def:23.5mm)"},
  {"overlap",'o',"OVERLAP",0,"Overlap area(Def:0.375)"},
  {"vwidth",'x',"VWIDTH",0,"Virtual sensor width(Def:60mm)"},
  {"vheight",'y',"VHEIGHT",0,"Virtual sensor height(Def:60mm)"},
  {"dummy",'d',0,0,"Mock-up behaviour"},
  {"save",'s',"FILE",0,"Save to file"},
  {0}
};
static error_t parse_opt(int key,char *arg,struct argp_state *state){
  struct args *args=state->input;
  switch(key){
    case 'q':
      args->level=L_NONE;break;
    case 'v':
      args->level=atoi(arg);break;
    case 'f':
      args->focal=atof(arg);break;
    case 'w':
      args->width=atof(arg);break;
    case 'h':
      args->height=atof(arg);break;
    case 'o':
      args->overlap=atof(arg);break;
    case 'x':
      args->vwidth=atof(arg);break;
    case 'y':
      args->vheight=atof(arg);break;
    case 's':
      args->file=arg;break;
    case 'd':
      args->dummy=1;break;        
    case ARGP_KEY_ARG:
      if(state->arg_num==0){
          args->action=arg;
               if(!strcmp(arg,"virtual"))args->action=ACT_VIRTUAL;
          else if(!strcmp(arg,"sphere")) args->action=ACT_SPHERE;
          else if(!strcmp(arg,"xxx"))    args->action=ACT_XXX;
          else argp_usage(state);//error("Invalid Action.");
     }if(state->arg_num>0)argp_usage(state);
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
args verbose_init(int argc,char**argv){
    args args;
    args.level=D_LEVEL;
    args.focal=D_FOCAL;
    args.width=D_WIDTH;
    args.height=D_HEIGHT;
    args.overlap=D_OVERLAP;
    args.vwidth=D_VWIDTH;
    args.vheight=D_VHEIGHT;
    args.dummy=D_DUMMY;
    asprintf(&args.file,"%s",D_FILE);
    argp_parse(&argp,argc,argv,0,0,&args);
    verbose_l=args.level;
     return args;
}
int verbose(int level,char *msj){
    if(level&verbose_l)printf("|> %s\n",msj);
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
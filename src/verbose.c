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
static char args_doc[]="ACTION ACTION_ARG";
static struct argp_option options[]={
  {"quiet",'q',0,0,"Quiet verbose"},
  {"verbose",'v',"LEVEL",0,"Verbose level"},
  {"focal",'f',"FOCAL",0,"Lens focal distance"},
  {"width",'w',"WIDTH",0,"Sensor width(Def.15.6mm)"},
  {"height",'h',"HEIGHT",0,"Sensor height(Def.23.5mm)"},
  {"overlap",'o',"OVERLAP",0,"Overlap area(Def.0.375)"},
  {"dummy",'d',0,0,"Mock-up behaviour"},
  {"save",'s',"FILE",0,"Save to file"},
  {0}
};
typedef struct args{
    char    file[MAX_ARGL];
    char   level[MAX_ARGL];
    char   focal[MAX_ARGL];
    char   width[MAX_ARGL];
    char  height[MAX_ARGL];
    char overlap[MAX_ARGL];    
}args;
static error_t parse_opt(int key,char *arg,struct argp_state *state){
  struct args *args=state->input;
  switch(key){
    case 'q':
      strcpy(args->level,"0");break;
    case 'v':
      strcpy(args->level,arg);break;        
    case 'f':
      strcpy(args->focal,arg);break;
    case 'w':
      strcpy(args->width,arg);break;
    case 'h':
      strcpy(args->height,arg);break;        
    case 'o':
      strcpy(args->overlap,arg);break;
    case 's':
      strcpy(args->file,arg);break;
    case 'd':
      ;break;        
//    case ARGP_KEY_ARG:
//      if (state->arg_num >= 2)/* Too many arguments. */
//        argp_usage (state);
//      args->args[state->arg_num] = arg;
//      break;
//    case ARGP_KEY_END:
//      if (state->arg_num < 2)/* Not enough arguments. */
//        argp_usage (state);
//      break;
    default:
      return ARGP_ERR_UNKNOWN;
    }
  return 0;
}
static struct argp argp={options,parse_opt,args_doc,doc};
int verbose_init(int argc,char**argv){
    args args;
    strncpy(args.level,  D_LEVEL,  MAX_ARGL);
    strncpy(args.focal,  D_FOCAL,  MAX_ARGL);
    strncpy(args.width,  D_WIDTH,  MAX_ARGL);
    strncpy(args.height, D_HEIGHT, MAX_ARGL);
    strncpy(args.overlap,D_OVERLAP,MAX_ARGL);
    strncpy(args.file,   D_FILE   ,MAX_ARGL);
    argp_parse(&argp,argc,argv,0,0,&args);
    verbose_l=atoi(args.level);
    focal=atof(args.focal);
    width=atof(args.width);
    height=atof(args.height);
    overlap=atof(args.overlap);
    asprintf(&file,"%s",args.file);    
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
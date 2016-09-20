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
const char *argp_program_bug_address="William Cordero<william.cordero@gmail.com>";
static char doc[]="\n * HyperPan Control Software.\n\n * William Cordero Photo\n * http://williamcordero.com/";
static char args_doc[]="ARG1 ARG2";
static struct argp_option options[]={
  {"quiet",'q',0,0,"Quiet verbose"},
  {"silent",'s',0,0,"Silent verbose"},
  {"verbose",'v',0,0,"Verbose"},
  {"level",'l',"LEVEL",0,"Set verbose level"},
  {0}
};
typedef struct args{int level;}args;
static error_t parse_opt(int key,char *arg,struct argp_state *state){
  struct args *args=state->input;
  switch(key){
    case 'q':case 's':
      args->level=0;break;
    case 'v':
      args->level=10;break;
    case 'l':
      args->level=atoi(arg);break;
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
    args.level=L_POSS;
    argp_parse(&argp,argc,argv,0,0,&args);
    verbose_l=args.level;    
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
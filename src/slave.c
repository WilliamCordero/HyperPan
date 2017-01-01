/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef  BCM_DUMMY
#  include <bcm2835.h>
#else  //BCM_DUMMY
#  include "dummy/bcm_dummy.h"
#endif //BCM_DUMMY
#include "config.h"
#include "verbose.h"
#include "slave.h"
int slave_init(char *name){
    slv_name=name;
    if(a->file){
        out=fopen(a->file,"w+");
        verbose(L_SLVE,"%s: »: %s",slv_name,a->file);
    }
    if(a->load){
        in=fopen(a->load,"r");
        verbose(L_SLVE,"%s: «: %s",slv_name,a->load);
    }else in=stdin;
}
int slave_stop(){
    if(a->file)fclose(out);
    if(a->load)fclose(in);
}
long get_long(FILE *src){
    int c,i;
    char s[32];
    while(((c=getc(src))!=EOF)&&(c!=' ')&&(c!='\n'))s[i++]=c;
    s[i]=0;
    if(c==EOF)return -1;
    return atol(s);
}
int slave_read(){
    int i;
    verbose(L_SLVE,"%s:",slv_name);
    while((i=get_long(in))>=0){
        switch(i){
            case    ACT_NOP:break;
            case     ACT_ON:w_init();break;
            case    ACT_OFF:w_close();break;
            case  ACT_SLEEP:w_delayMicroseconds(get_long(in));break;
            case  ACT_WRITE:w_gpio_write(get_long(in),get_long(in));break;
            case   ACT_FSEL:w_gpio_fsel(get_long(in),get_long(in));break;
            case ACT_SETPUD:w_gpio_set_pud(get_long(in),get_long(in));break;
        }
    }
}
int w_init(){
    save("%u",ACT_ON);
    if(!a->dummy)return bcm2835_init();
    else return 1;
}
int w_close(){
    save("%u",ACT_OFF);
    if(!a->dummy)return bcm2835_close();
    else return 1;
}
int w_delayMicroseconds(uint64_t micros){
    save("%u %u",ACT_SLEEP,micros);
    if(!a->dummy)bcm2835_delayMicroseconds(micros);
}
int w_gpio_write(uint8_t pin,uint8_t on){
    save("%u %u %u",ACT_WRITE,pin,on);
    if(!a->dummy)bcm2835_gpio_write(pin,on);
}
int w_gpio_fsel(uint8_t pin,uint8_t mode){
    save("%u %u %u",ACT_FSEL,pin,mode);
    if(!a->dummy)bcm2835_gpio_fsel(pin,mode);
}
int w_gpio_set_pud(uint8_t pin,uint8_t pud){
    save("%u %u %u",ACT_SETPUD,pin,pud);
    if(!a->dummy)bcm2835_gpio_set_pud(pin,pud);
}


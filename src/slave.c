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
int get_int(FILE *src){
    char c,s[255];
    int i=-1;
    do{
        s[++i]=getc(src);
        if(s[i]=='#')while(getc(src)!='\n');
    }while(s[i]!=' '&&s[i]!='\n');
    s[i]=0;
    verbose(L_SLVE," -->%s<--",s);
}
int slave_read(){
    verbose(L_INFO,"hola mundo");
    get_int(in);
}
int w_init(){
    verbose(L_SLVE,"%u",I_ON);
    return bcm2835_init();
}
int w_close(){
    verbose(L_OUTP,"%u",I_OFF);
    return bcm2835_close();
}
int w_delayMicroseconds(uint64_t micros){
    verbose(L_OUTP,"%u %u",I_SLEEP,micros);
    bcm2835_delayMicroseconds(micros);
}
int w_gpio_write(uint8_t pin,uint8_t on){
    verbose(L_OUTP,"%u %u %u",I_WRITE,pin,on);
    bcm2835_gpio_write(pin,on);
}
int w_gpio_fsel(uint8_t pin,uint8_t mode){
    verbose(L_OUTP,"%u %u %u",I_FSEL,pin,mode);
    bcm2835_gpio_fsel(pin,mode);
}
int w_gpio_set_pud(uint8_t pin,uint8_t pud){
    verbose(L_OUTP,"%u %u %u",I_SETPUD,pin,pud);
    bcm2835_gpio_set_pud(pin,pud);
}


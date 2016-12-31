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
        verbose(L_SLVE,"%s: %s",slv_name,a->file);
    }
}
int slave_stop(){
    if(a->file)
        fclose(out);
}

/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include "verbose.h"
#include "camera.h"
int main(int argc,char**argv){
    verbose_init(argc,argv);
    camera_on();
    camera_action();
    camera_off();
    return 0;
}
/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bcm2835.h>
#include "stepper.h"
#include "verbose.h"
stepper stepper_init(int sleep,int step,int dir,int m0,int m1,char *name){
    char *msj;
    stepper tmp;
    bcm2835_gpio_fsel(sleep,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(sleep,LOW);
    tmp.sleep=sleep;
    bcm2835_gpio_fsel(step,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(step,LOW);
    tmp.step=step;
    bcm2835_gpio_fsel(dir,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(dir,LOW);
    tmp.dir=dir;    
//    bcm2835_gpio_fsel(m0,BCM2835_GPIO_FSEL_OUTP);
//    bcm2835_gpio_write(m0,LOW);
    tmp.m0=m0;    
    bcm2835_gpio_fsel(m1,BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(m1,LOW);
    tmp.m1=m1;
    asprintf(&tmp.name,"%s",name);
    asprintf(&msj,"Initializing stepper %s.",tmp.name);
    verbose(3,msj);free(msj);
    alert_led();
    return tmp;
}
int stepper_mode(stepper motor,int mode){
    char *msj;
    switch(mode){ //M0
        case 2:case 16:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(motor.m0,HIGH);break;
        case 4:case 32:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_INPT);
            bcm2835_gpio_set_pud(motor.m0,BCM2835_GPIO_PUD_OFF);break;
        default:
            bcm2835_gpio_fsel(motor.m0,BCM2835_GPIO_FSEL_OUTP);
            bcm2835_gpio_write(motor.m0,LOW);
    }
    switch(mode){ //M1
        case 8:case 16:case 32:
            bcm2835_gpio_write(motor.m1,HIGH);break;
        default:
            bcm2835_gpio_write(motor.m1,LOW);
    }
    switch(mode){
        case 1:case 2:case 4:case 8:case 16:case 32:
            asprintf(&msj,"%s: set mode 1/%i.",motor.name,mode);
            verbose(3,msj);free(msj);
            break;
        default:
            asprintf(&msj,"%s: invalid mode 1/%i, using mode 1/1.",motor.name,mode);
            warning(msj);free(msj);
    }
}
int stepper_on(stepper motor){
    bcm2835_gpio_write(motor.sleep,HIGH);
}
int stepper_off(stepper motor){
    bcm2835_gpio_write(motor.sleep,LOW);
}
int stepper_walk(stepper motor,int dir,int n){
    int i,ii,t=0;
    double iii=0,e=150.0,x=1.0,ret;
    char *msj;
//    double pi=acos(-1);
    for(i=e;0<i;i--){
        t++;
        bcm2835_gpio_write(motor.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        bcm2835_gpio_write(motor.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
    x=1.0;
    iii=(double)90.0+x/e;
    printf("sin(90.0*i) = %f i=%i\n",sin((double)(iii*M_PI/180)),i);
//    x=0.0;
//    printf("sin(0) = %f\n",sin(x*M_PI/180));
//    x=45.0;
//    printf("sin(45) = %f\n",sin(x*M_PI/180));
//    printf("sin(-3*pi/4) = %f\n", sin(-3*pi/4));
    // special values
//    printf("sin(+0) = %f\n", sin(0.0));
//    printf("sin(-0) = %f\n", sin(-0.0));
        
//        ret=sin(((90.0*ii)/e)*(PI/180));
//        ret=sin((90.0*ii)*(PI/180));        
//        x=((90*i)/e);
//        x=90.0*i;
//        printf("The sine of %lf\n",x);
//        ret=sin(x*(pi/180.0));
//        printf("The sine of %lf is %lf degrees\n",x,ret);
//        for(ii=iii;0<ii;ii--){                    
//         for(ii=i;0<ii;ii=ii-ret){            
//            bcm2835_delayMicroseconds(PULSE*2);            
//        }
    } 
/*    asprintf(&msj,"%s: t=%i",motor.name,t);
    verbose(3,msj);free(msj);
    for(i=(n-(t*2));0<i;i--,t++){
        bcm2835_gpio_write(motor.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        bcm2835_gpio_write(motor.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
    }
    asprintf(&msj,"%s: t=%i",motor.name,t);
    verbose(3,msj);free(msj);
    for(i=0;i<e;i++,t++){
        for(ii=0;ii<i;ii++){            
            bcm2835_delayMicroseconds(PULSE*2);            
        }
        bcm2835_gpio_write(motor.step,HIGH);
        bcm2835_delayMicroseconds(PULSE);
        bcm2835_gpio_write(motor.step,LOW);
        bcm2835_delayMicroseconds(PULSE);
    } 
    asprintf(&msj,"%s: t=%i",motor.name,t);
    verbose(3,msj);free(msj);
*/
  
//    ret=sin(x*(PI/180));
//    printf("The sine of %lf is %lf degrees\n",x,ret);
    
/*
    asprintf(&msj,"%s: sin(1)=%lf",motor.name,sin(0.0*(PI/180)));
    verbose(3,msj);free(msj);
    asprintf(&msj,"%s: sin(0.5)=%lf",motor.name,sin(45.0*(PI/180)));
    verbose(3,msj);free(msj);
    asprintf(&msj,"%s: sin(0)=%lf",motor.name,sin(90.0*(PI/180)));
    verbose(3,msj);free(msj);
*/
    
//            asprintf(&msj,"%s: i=%i\t ii=%i\t iii=%i",motor.name,i,ii,iii);
//            verbose(3,msj);free(msj);

}
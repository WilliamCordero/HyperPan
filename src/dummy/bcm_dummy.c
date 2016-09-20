/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifdef  BCM_DUMMY
#include <time.h>
#include "bcm_dummy.h"

extern  int bcm2835_init(void){return 1;}
extern  int bcm2835_close(void){return 1;}
extern void bcm2835_gpio_fsel(uint8_t pin,uint8_t mode){}
extern void bcm2835_gpio_write(uint8_t pin,uint8_t on){
    //printf("%i:%s\n",pin,on?"HIGH":"LOW");
}
extern void bcm2835_gpio_set_pud(uint8_t pin,uint8_t pud){}
extern void bcm2835_delayMicroseconds(uint64_t micros){usleep(micros);}

#endif //BCM_DUMMY
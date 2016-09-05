/*
 * 
 * William Cordero (2016)
 * <william.cordero@gmail.com>
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bcm2835.h>

int main(int argc,char**argv){
    int i;
    printf("Debug:>>\n");
    for(i=0;i<argc;i++)printf("%i: %s\n", i, argv[i]);

/*    
    if(!bcm2835_init())return 1;
    bcm2835_gpio_fsel(RPI_GPIO_P1_21,BCM2835_GPIO_FSEL_OUTP);
    while(1){
        bcm2835_gpio_write(RPI_GPIO_P1_21, HIGH);
        bcm2835_delay(500);
        bcm2835_gpio_write(RPI_GPIO_P1_21, LOW);
        bcm2835_delay(500);
    }
    bcm2835_close();
 */
 
    printf("Bye\n");
    return 0;
}

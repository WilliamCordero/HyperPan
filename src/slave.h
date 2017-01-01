/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef SLAVE_H
#define SLAVE_H
#ifdef __cplusplus
extern "C" {
#endif
#define HIGH 0x1
#define LOW  0x0
typedef enum{
    GPIO_FSEL_INPT=0x00,/*!< Input 0b000 */
    GPIO_FSEL_OUTP=0x01,/*!< Output 0b001 */
}FunctionSelect;
typedef enum{
    GPIO_PUD_OFF =0x00,/*!< Off ? disable pull-up/down 0b00 */
    GPIO_PUD_DOWN=0x01,/*!< Enable Pull Down control 0b01 */
    GPIO_PUD_UP  =0x02 /*!< Enable Pull Up control 0b10  */
}PUDControl;
FILE *out;
FILE *in;
int slave_init(char *name);
int slave_stop();
int slave_read();
int w_init();
int w_close();
int w_gpio_fsel(unsigned char pin,unsigned char mode);
int w_gpio_write(unsigned char pin,unsigned char on);
int w_gpio_set_pud(unsigned char pin,unsigned char pud);
int w_delayMicroseconds(unsigned long long micros);
#ifdef __cplusplus
}
#endif
#endif /* SLAVE_H */


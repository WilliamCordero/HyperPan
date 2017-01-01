/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef SLAVE_H
#define SLAVE_H
#ifdef __cplusplus
extern "C" {
#endif

FILE *out;
FILE *in;
char *slv_name;
int slave_init(char *name);
int slave_stop();
int slave_read();
int w_init();
int w_close();
int w_gpio_fsel(uint8_t pin,uint8_t mode);
int w_gpio_write(uint8_t pin,uint8_t on);
int w_gpio_set_pud(uint8_t pin,uint8_t pud);
int w_delayMicroseconds(uint64_t micros);
#ifdef __cplusplus
}
#endif
#endif /* SLAVE_H */


/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef VERBOSE_H
#define VERBOSE_H

#ifdef __cplusplus
extern "C" {
#endif

#define ALERT_GPIO  21
#define ALERT_BLINK 20000
    
int verbose_level;

int verbose(int level, char *msj);
int warning(char *msj);
int error(char *msj);
int alert_led();

#ifdef __cplusplus
}
#endif

#endif /* VERBOSE_H */


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
#define L_NONE 0
#define L_FALL 1
#define L_TRGR 2
#define L_POSS 3
#define L_ACCT 4
#define L_ALL 10    
int verbose_l;
int verbose(int level,char *msj);
int warning(char *msj);
int error(char *msj);
int alert_led();
#ifdef __cplusplus
}
#endif
#endif /* VERBOSE_H */


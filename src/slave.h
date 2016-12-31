/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */
#ifndef SLAVE_H
#define SLAVE_H
#ifdef __cplusplus
extern "C" {
#endif

FILE *out;
char *slv_name;
int slave_init(char *name);
int slave_stop();
#ifdef __cplusplus
}
#endif
#endif /* SLAVE_H */


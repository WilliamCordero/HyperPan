/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

/* 
 * File:   verbose.h
 * Author: wcordero
 *
 * Created on September 7, 2016, 3:16 AM
 */

#ifndef VERBOSE_H
#define VERBOSE_H

#ifdef __cplusplus
extern "C" {
#endif

#define ALERT_GPIO  21
#define ALERT_BLINK 20000
    
int verbose_level;
int verbose(int level, char msj[]);

#ifdef __cplusplus
}
#endif

#endif /* VERBOSE_H */


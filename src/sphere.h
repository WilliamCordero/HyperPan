/*
 * William Cordero (2016) <william.cordero@gmail.com>
 */

#ifndef SPHERE_H
#define SPHERE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct sphere{
    int rho;
    int theta;
    int phi;    
}sphere;

sphere sphere_init();

#ifdef __cplusplus
}
#endif

#endif /* SPHERE_H */


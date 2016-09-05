/*
 * 
 * William Cordero (2016)
 * <william.cordero@gmail.com>
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char**argv){
    int i;
    printf("Debug:\n");
    for(i=0;i<argc;i++)printf("%i: %s\n", i, argv[i]);
    return 0;
}

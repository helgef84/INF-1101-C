#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include <string.h>


int sort(void *data, int left, int right, cmpfunc_t cmpfunc, exchfunc_t exchfunc){
    int i, j;
    int min;

    for(i = left; i < right; i ++){
        min = i;

        for(j = i + 1; j <= right; j++){
            if(cmpfunc(data, j, min) < 0){
                min = j;
            }
        }
        exchfunc(data, i, min);
    }
    
    return 0;
}
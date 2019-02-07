#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include <string.h>


int sort(void *data, int left, int right, cmpfunc_t cmpfunc, exchfunc_t exchfunc){
    int i, j;

    for(i = left + 1; i <= right; i ++){
        for(j = i; j > left; j --){
            if(cmpfunc(data, j -1 , j) > 0){
                exchfunc(data, j - 1, j);
            }else{
                break;
            }
        }
    }

    return 0;
}
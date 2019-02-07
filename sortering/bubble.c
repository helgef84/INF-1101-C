#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include <string.h>


int sort(void *data, int left, int right, cmpfunc_t cmpfunc, exchfunc_t exchfunc){
    
    int i, j;

    for(i = left; i < right; i++){
        for(j = right; j > i; j --){
            if(cmpfunc(data, j-1, j) > 0){
                exchfunc(data, j-1, j);
            }
        }
    }
}







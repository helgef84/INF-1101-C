#include <stdlib.h>
#include <stdio.h>
#include "sort.h"
#include <string.h>
#include "timer.h"

#define MAXNUM (16 * 1024)


typedef struct data{
    int key;
    char *name;
    char phone[10];

} data_t;

int compare_data(void *d, int a, int b){
    data_t *data = (data_t*) d;

    if(data[a].key < data[b].key){
        return -1;
    }
    if(data[a].key > data[b].key){
        return 1;
    }
    return 0;
}

int exchange_data(void *d, int a, int b){
    data_t tmp;
    data_t *data = (data_t*) d;
    memcpy(&tmp, data + a, sizeof(data_t));
    memcpy(data + a, data + b, sizeof(data_t));
    memcpy(data + b, &tmp, sizeof(data_t));

    return 0;
}


int main( int argc, char ** argv){

    int i, cursize;
    unsigned long long t1, t2;

    FILE *fil;

    if(argc != 2){
        printf("%s <logfile>\n", argv[0]);
        exit(0);
    }
    fil = fopen(argv[1], "w");
    if(fil == NULL){
        printf("Kunne ikke åpne %s\n", argv[1]);
    }
    data_t *data = malloc(sizeof(data_t) * MAXNUM);
    if(data == NULL){
        printf("Fritt for minne\n");
        exit(0);
    }
    for(cursize = 2048; cursize <= MAXNUM; cursize += 2048){
        for(i = 0; i < cursize; i ++){
            data[i].key = rand();
        }
        printf("sorting %d elements\n", cursize);
        t1 = gettime();
        sort(data, 0, cursize - 1, compare_data, exchange_data);
        t2 = gettime();

        fprintf(fil, "%d %dllu\n", cursize, (t2 - t1));
    }
    fclose(fil);
/*
    for(i = 0; i < 8; i++){
        data[i].key = rand();
        printf("data[%d] = %d\n", i, data[i].key);
    }
    sort(data, 0, 7, compare_data, exchange_data);

    printf("Sorted : \n");
    for(i = 0; i < 8; i++){
        printf("data[%d] = %d\n", i, data[i].key);
        
    }
*/
}
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

#define NUM_ITEMS 150


typedef struct data{
    int id;
    char name[128];

}data_t;


int datacompare(void *a, void *b){
    long aVal = (long)a;
    long bVal = (long)b;

    return bVal - aVal;
}

void dataToStr(char *buf, int bufSize, void *key, void *item){
    snprintf(buf, bufSize, "%ld", (long)key);
}

int main(void){
    int i;

    data_t **data = malloc(sizeof(data_t) * NUM_ITEMS);
    if(data == NULL){
        printf("Fri for minne\n");
        exit(0);
    }
    bst_t *bst = bst_create(datacompare, dataToStr);
    if(bst == NULL){
        printf("FRITT FOR MINNE !\n");
        exit(0);
    }
    for(i = 0; i < NUM_ITEMS; i ++){
        data[i] = malloc(sizeof(data_t));
        if(data[i] == NULL){
            printf("FRI FOR MINNE!\n");
            exit(0);
        }
        data[i]->id = rand() % 9999;

        bst_insert(bst, (void*) data[i]->id, data[i]);
    }
    data_t *test = bst_search(bst, (void*) 352);
    if(test != NULL){
        printf("Fant id 352\n");
    }
    test = bst_search(bst, (void*) 25);
    if(test == NULL){
        printf("Fant ikke id 25\n");
    }
    bst_print(bst, "BST");

    bst_destroy(bst);

    return 0;
}
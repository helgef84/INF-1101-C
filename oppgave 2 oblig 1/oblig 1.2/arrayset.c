#include "set.h"
#include <stdlib.h>
#include <stdio.h>


#define MAX_ITEMS 100

struct set {
	void **items;
	int maxitems;
	int size;
};



set_t *set_create(cmpfunc_t cmpfunc) {
	set_t *set;
	set = calloc(1, sizeof(set_t));
	if(set == NULL){
		fatal_error("Could not create set\n");
		free(set);
	}
	set->items = malloc(sizeof(void*) * MAX_ITEMS);
	if(set->items == NULL){
		fatal_error("could not create set\n");
		free(set);
	}
	set->size = 0;
	set->maxitems = MAX_ITEMS;
	
	return set;
}



void set_destroy(set_t *set) {
	free(set->items);
	free(set);
}

int set_size(set_t *set) {
	return set->size;
}

void set_add(set_t *set, void *elem) {
	int new_max;
	void **elems;

	if(set->size >= set->maxitems){
		new_max = set->maxitems * 2;
		elems = realloc(set->items, sizeof(void*) * new_max);
		if(elems == NULL){
			fatal_error("Could not reallocate\n");
		}
	set->maxitems = new_max;
	set->items = elems; 
	}
	set->items[set->size] = elem;
	set->size += 1;
	
}

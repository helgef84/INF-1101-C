#include <stdlib.h>
#include <stdio.h>

#include "set.h"
#include "list.h"



struct set{
	list_t *list
};

set_t *set_create(cmpfunc_t cmpfunc){
	set_t *set = malloc(sizeof(set_t));
	if(set == NULL){
		fatal_error("Could not create set\n");
	}	
	set->list = list_create(cmpfunc);
}

void set_destroy(set_t *set){
	if(set == NULL){
		fatal_error("set does not exist\n");
	}
	if(set->list != NULL){
		list_destroy(set->list);
	}
	free(set);
}

int set_size(set_t *set){
	return list_size(set->list);
}

void set_add(set_t *set, void *elem){
	if(!list_cointains(set->list, elem)){
		list_addfirst(set->list, elem);
	}
}

int set_contains(set_t *set, void *elem){
	if(list_cointains(set->list, elem)){
		return 1;
	}else{
		return 0;
	}
}


set_t *set_union(set_t *a, set_t *b){
	
	set_t *unionset = set_create(getfunc(a->list));

}

//set_t *set_difference(set_t *a, set_t *b){

//}

//set_t *set_copy(set_t *set){

//}

/*
*		Set iterator
*/

struct set_iter{
	list_iter_t *list_iter;
};

set_iter_t *set_createiter(set_t *set){
	set_iter_t *set_iterator = malloc(sizeof(set_iter_t));
	if(set_iterator == NULL){
		fatal_error("could not create iterator\n");
	}
	set_iterator = list_createiter(set->list);
	return set_iterator;
} 

int set_hasnext(set_iter_t *iter){
	return list_hasnext(iter->list_iter);
}

void set_destroyiter(set_iter_t *iter){
	if(iter->list_iter != NULL){
		list_destroyiter(iter->list_iter);
	}
	free(iter);
}

void *set_next(set_iter_t *iter){
	*list_next(iter->list_iter);
}





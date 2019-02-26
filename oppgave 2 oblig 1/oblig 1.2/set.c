#include <stdlib.h>
#include <stdio.h>

#include "set.h"
#include "list.h"
#include "common.h"



struct set{
	list_t *list;
};

struct set_iter{
	list_iter_t *list_iter;
};

set_t *set_create(cmpfunc_t cmpfunc) {
	set_t *set = malloc(sizeof(set_t));
	if (set == NULL) {
		fatal_error("could not create set\n");
	}
	set->list = list_create(cmpfunc);
}

void set_destroy(set_t *set) {
	if (set == NULL) {
		fatal_error("no list here\n");
	}
	if (set->list != NULL) {
		list_destroy(set->list);
	}
	free(set);
}

int set_size(set_t *set) {
	return list_size(set->list);
}


void set_add(set_t *set, void *elem) {
	if (!list_contains(set->list, elem)) {

		list_addfirst(set->list, elem);
		//list_sort(set->list);
	}
}

int set_contains(set_t *set, void *elem) {
	return list_contains(set->list, elem);

}

set_t *set_union(set_t *a, set_t *b) {
	set_iter_t *itera = set_createiter(a);
	set_iter_t *iterb = set_createiter(b);	

	set_t *unionset = set_create(getfunc(a->list));

	while(set_hasnext(itera)){
		set_add(unionset, set_next(itera));
		//list_sort(unionset->list);
	}
	while(set_hasnext(iterb)){
		set_add(unionset, set_next(iterb));
		//list_sort(unionset->list);
	}
	return unionset;
}

set_t *set_intersection(set_t *a, set_t *b){
	set_iter_t *itera = set_createiter(a);

	set_t *intersectset = set_create(getfunc(a->list));
	void *elem;
	while(set_hasnext(itera)){
		elem = set_next(itera);
		if(set_contains(b, elem)){
			set_add(intersectset, elem);
			//list_sort(intersectset->list);
		}
	}
	
	set_destroyiter(itera);
	return intersectset;
}

set_t *set_difference(set_t *a, set_t *b){
	set_iter_t *itera = set_createiter(a);
	

	set_t *diffset = set_create(getfunc(a->list));
	void *elem;

	while(set_hasnext(itera)){
		elem = set_next(itera);
		if(!set_contains(b, elem)){
			set_add(diffset, elem);
			//list_sort(diffset->list);
		}
	}
	set_destroyiter(itera);	
	return diffset;
}

set_t *set_copy(set_t *set) {
	set_iter_t *iter = set_createiter(set);

	set_t *copyset = set_create(getfunc(set->list));
	while(set_hasnext(iter)){
		set_add(copyset, set_next(iter));
		//list_sort(copyset->list);
	}
	set_destroyiter(iter);
	return copyset;
}

set_iter_t *set_createiter(set_t *set) {
	set_iter_t *iter = malloc(sizeof(set_iter_t));
	if (iter == NULL) {
		fatal_error("could not create iterator\n");
	}
	list_sort(set->list);
	iter->list_iter = list_createiter(set->list);
	return iter;
}

void set_destroyiter(set_iter_t *iter) {
	if (iter->list_iter != NULL) {
		list_destroyiter(iter->list_iter);
	}
	free(iter);
}


int set_hasnext(set_iter_t *iter) {
	return list_hasnext(iter->list_iter);
}


void *set_next(set_iter_t *iter) {
	list_next(iter->list_iter);
}

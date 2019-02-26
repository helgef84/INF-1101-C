#include <stdlib.h>
#include <stdio.h>


#include "set.h"
#include "list.h"
#include "common.h"


int compare_values(int a, int b) {
	if (a < b) {
		return 1;
	}
	else if (a > b) {
		return -1;
	}
	else {
		return 0;
	}
}


int main() {
	
	set_t *new_set = set_create((cmpfunc_t)compare_values);
	
	int i;
	int value;
	for(i = 0; i < 11; i ++){
		set_add(new_set, rand() % 25);
	}
	
	
	int size = set_size(new_set);
	printf("set has %d elements\n", size);

	set_iter_t *set_iter = set_createiter(new_set);
	
	
	while (set_hasnext(set_iter)) {
		value = set_next(set_iter);
		printf("number = %d \n", value);
	}
	set_destroyiter(set_iter);
	
	set_destroy(new_set);
	return 0;
}
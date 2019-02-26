#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include "common.h"


static int compare(int a, int b) {
	if (a > b) {
		return 1;
	}else if (a < b) {
		return -1;
	}
	return 0;
}



int main(int argc, char **argv) {
	int i, size, size2;
	set_t *test;
	
	test = set_create((cmpfunc_t)compare);
	
	size = set_size(test);
	printf("size before add: %d \n", size);
	
	for (i = 0; i < 5; i++) {
		set_add(test, i);
	}
	size2 = set_size(test);



	printf("size after add: %d\n", size);
	set_destroy(test);
	
}
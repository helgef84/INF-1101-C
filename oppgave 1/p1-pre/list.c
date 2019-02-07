#include <stdlib.h>
#include "list.h"

/*
* 			DEFINITIONS
*/
typedef struct listnode listnode_t;

struct listnode{
	void *word;
	listnode_t *prev;
	listnode_t *next;
};

struct list{
	listnode_t *head;
	listnode_t *tail;
	cmpfunc_t cmpfunc;
	int size;
};

list_t *list_create(cmpfunc_t cmpfunc){

	list_t *list = malloc(sizeof(list_t));
	if(list == NULL){
		fatal_error("Could not create list");
	}
	list->head = NULL;
	list->tail = NULL;
	list->cmpfunc = cmpfunc;
	list->size = 0;

}
	
void list_addfirst(list_t *list, void *elem){
	listnode_t *node = malloc(sizeof(listnode_t));
	if(node == NULL){
		fatal_error("Could not create node");
	}
	node->prev = NULL;
	node->word = elem;

	if(list->head == NULL){
		list->head = node;
		list->tail = node;
	}
	else{
		list->head->prev = node;
		node->next = list->head;
		list->head = node;
		
	}
	list->size += 1;
}

void list_addlast(list_t *list, void *elem){
	listnode_t *node = malloc(sizeof(listnode_t));
	if(node == NULL){
		fatal_error("could not create node");
	}
	node->next = NULL;
	node->word = elem;
	if(list->head == NULL){
		node->prev = NULL;
		list->head = node;
		list->tail = node;
	}
	else{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
	list->size += 1;
}


void list_destroy(list_t *list){
	listnode_t *current, *next;

	current = list->head;
	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
}


int list_size(list_t *list){
	return list->size;
}

void *list_popfirst(list_t *list){
	if(list->head == NULL){
		fatal_error("could not remove item");
	}
	void *word = list->head->word;
	listnode_t *new_head = list->head->next;

	free(list->head);
	list->head = new_head;
	list->size -= 1;

	return word;
}

void *list_poplast(list_t *list){
	if(list->tail == NULL){
		fatal_error("could not remove item");
	}

	void *word = list->tail->word;
	listnode_t *new_tail = list->tail->prev;

	free(list->tail);
	list->tail = new_tail;
	list->size -= 1;

	return word;
}


int list_contains(list_t *list, void *elem){
	if(list->head == NULL){
		fatal_error("List is empty");
	}	
	
	void *word = list->head->next->word;
	if(word == elem){
		return 1;
	}
	return 0;
}

void list_sort(list_t *list){
	list_iter_t *outeriter = list_createiter(list);
	list_iter_t *inneriter = list_createiter(list);

	//inneriter->node = outeriter->node->next;
	listnode_t *tmp;
	
	while (list_hasnext(outeriter) != 0){
		while(list_hasnext(inneriter) != 0){
			if(strcmp(outeriter->node->word, inneriter->node->word) > 0){
				tmp = outeriter->node->word;
				outeriter->node->word = inneriter->node->word;
				inneriter->node->word = tmp;
			}
		}
	}
}


//#############################  LIST ITERATOR  ##########################################

struct list_iter{
	listnode_t *node;
};


list_iter_t *list_createiter(list_t *list){
	list_iter_t *iter = malloc(sizeof(list_iter_t));
	if(iter == NULL){
	fatal_error("could not create iterator");
	}
	iter->node = list->head;
	return iter;
}


void list_destroyiter(list_iter_t *iter){
	free(iter);
}

int list_hasnext(list_iter_t *iter){
	if(iter->node == NULL){
		return 0;
	}
	return 1;

}

void *list_next(list_iter_t *iter){
	 
	void * element = iter->node->word;
	iter->node = iter->node->next;
	return element;
}

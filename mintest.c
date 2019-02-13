#include <stdio.h>

#include <stdlib.h>

typedef struct node node_t;
struct node{
node_t *next;  
node_t *prev;
  
void *elem;

};

typedef struct list list_t;


struct list{
  
node_t *head;
  
node_t *tail;
  
int size;

};

list_t *list_create(){
    
list_t *list = malloc(sizeof(list_t));
    
if(list == NULL){
        
printf("No list created\n");
   
}
    
   
 list->head = NULL;
    
list->tail = NULL;
    
    
list->size = 0;
    
return list;

}

void list_add(list_t *list, void *elem){
    
node_t *node = malloc(sizeof(node_t));
    
if(node == NULL){
        
printf("no node created\n");
    
}
    
    
node->elem = elem;
    
if(list->head == NULL){
        
list->head = node;
        
list->tail = node;
    
}else{
        
list->head->prev = node;
        
node->next = list->head;
        
list->head = node;
    
}
    
list->size += 1;

}

typedef struct list_iter list_iter_t;


struct list_iter{
    
node_t *node;

};


list_iter_t *create_iter(list_t *list){
    
list_iter_t *iter = malloc(sizeof(iter));
    
if(iter == NULL){
       
 printf("could not create iter\n");
    
}
    
iter->node = list->head;
    
return iter;

}


int list_hasnext(list_iter_t *iter){
    
if(iter->node == NULL){
        
return 0;
    
}
    
return 1;

}

void *list_next(list_iter_t *iter){
    
void *element = iter->node->elem;
    
iter->node = iter->node->next;
    
return element;

}

int main()
{
    
    
int i;
    
    
list_t *new_list = list_create();
    
    
for(i = 0; i < 20; i++){
        
list_add(new_list, i);
   
 }
    
list_iter_t *iter = create_iter(new_list);
    
    
while(list_hasnext(iter)){
        
int number = list_next(iter);
       
 printf("number = %d\n", number);
    
}
  
    
return 0;

}








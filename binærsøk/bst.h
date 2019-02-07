#ifndef __BST_H_
#define __BST_H_

typedef struct bst bst_t;
typedef int (*cmpfunc_t)(void *a, void *b);

typedef void( *strfunc_t)(char *buf, int bufSize, void *key, void *item);

bst_t *bst_create(cmpfunc_t cmpfunc, strfunc_t strfunc);

void bst_destroy(bst_t *bst);

int bst_insert(bst_t *bst, void *key, void *item);

void *bst_search(bst_t *bst, void *key);

void bst_print(bst_t *bst, char *name);

#endif

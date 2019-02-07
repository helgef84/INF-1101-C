#include <stdlib.h>
#include <stdio.h>

#include "bst.h"
#include "plot.h"

typedef struct node node_t;

struct node{
    void *key;
    void *item;
    node_t *left;
    node_t *right;
};

struct bst{
    node_t *root;
    cmpfunc_t cmpfunc;
    strfunc_t strfunc;
};


bst_t *bst_create(cmpfunc_t cmpfunc, strfunc_t strfunc){
    bst_t *bst = malloc(sizeof(bst_t));
    if(bst == NULL){
        goto error;
    }
    bst->root = NULL;
    bst->cmpfunc = cmpfunc;
    bst->strfunc = strfunc;
    return bst;

    
error:
    if (bst != NULL)
        free(bst);

}   


static node_t *node_new(void * key, void *item){
    node_t *node = malloc(sizeof(node_t));
    if(node == NULL){
        return NULL;
    }
    node->key = key;
    node->item = item;
    node->left = NULL;
    node->right = NULL;
    
    return node;
}


static node_t *_bst_insert(bst_t *bst, node_t *node, node_t *new, int *error){
    int cmpres;

    if (node == NULL){
        return new;
    }

    cmpres = bst->cmpfunc(node->key, new->key);

    if(cmpres == 0){
        *error = -1;
    }
    else if (cmpres < 0){
        node->left = _bst_insert(bst, node->left, new, error);
    }
    else{
        node->right = _bst_insert(bst, node->right, new, error);
    }

    return node;
}

int bst_insert(bst_t *bst, void *key, void *item){

    node_t *node;
    int error = 0;

    node = node_new(key, item);
    if(node == NULL){
        goto error;
    }

    bst->root = _bst_insert(bst, bst->root, node, &error);
    if(error != 0){
        goto error;
    }

    return 0;

error:
    if(node == NULL){
        printf("shit hit the fan fam!\n");
        free(node);
    }
    return -1;
}

static void _bst_destroy(node_t *node){

    if(node == NULL){
        return;
    }

    _bst_destroy(node->left);
    _bst_destroy(node->right);

    free(node);
}

void bst_destroy(bst_t *bst){
    if(bst->root != NULL){
        _bst_destroy(bst->root);
    }
    free(bst);
}


static void *_bst_search(bst_t *bst, node_t *node, void *key){
    int cmpres;
    if(node == NULL){
        return NULL;
    }

    cmpres = bst->cmpfunc(node->key, key);
    if (cmpres == 0){
        return node->item;
    }
    else if(cmpres < 0){
        return _bst_search(bst, node->left, key);
    }
    else{
        return _bst_search(bst, node->right, key);
    }
}


void *bst_search(bst_t *bst, void *key){

    return _bst_search(bst, bst->root, key);
}


static void _bst_print(bst_t *bst, plot_t *plot, node_t *node){
    char from[250];
    char to [250];  
    
    if(node == NULL){
        return;
    }
    bst->strfunc(from, 250, node->key, node->item);

    if(node->left != NULL){
        bst->strfunc(to, 250, node->left->key, node->left->item);
        plot_addlink(plot, from, to);
    }
    if (node->right != NULL){
        bst->strfunc(to, 250, node->right->key, node->right->item);
        plot_addlink(plot, from, to);
    }

    _bst_print(bst, plot, node->left);
    _bst_print(bst, plot, node->right);

}


void bst_print(bst_t *bst, char *name){
    plot_t *plot;
    plot = plot_newplot(name);

    _bst_print(bst, plot, bst->root);
    plot_print(plot);
}




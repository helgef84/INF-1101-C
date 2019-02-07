
#include <stdio.h>
#include <stdlib.h>
#include "plot.h"


struct plot {
    FILE *fp;
    char name[250];
};

plot_t *plot_newplot(char *name){
    plot_t *plot = malloc(sizeof(plot_t));
    if(plot == NULL){
        return NULL;
    }
    sprintf(plot->name, "%s.dot", name);
    plot->fp = fopen(plot->name, "w");
    if(plot->fp == NULL){
        free(plot);
        return NULL;
    }

    fprintf(plot->fp, "digraph structs {\n");
    fprintf(plot->fp, "rankdir=TB;\n");
    fprintf(plot->fp, "size=\"7.5,10\";\n");
    return plot;
}

void plot_addlink(plot_t *plot, char *a, char *b){
    fprintf(plot->fp, "%s->%s;\n", a , b);
    fflush(plot->fp);
}

void plot_print(plot_t *plot){
    char cmd[256];
    fprintf(plot->fp, "}\n");
    fflush(plot->fp);
    sprintf(cmd, "dot -Tpdf %s -o %s.pdf", plot->name, plot->name);
    system(cmd);
}
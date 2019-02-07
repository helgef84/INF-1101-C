#ifndef __PLOT_H_
#define __PLOT_H_

typedef struct plot plot_t;

plot_t *plot_newplot(char *name);
void plot_addlink(plot_t *plot, char *a, char *b);
void plot_print(plot_t *plot);


#endif

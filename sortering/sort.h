#ifndef __SORT_H_
#define __SORT_H_

// returnerer -1 hvis a er størst
// 0 hvis de er lik
// 1 hvis b er størst

typedef int (*cmpfunc_t)(void *, int a , int b);

typedef int (*exchfunc_t)(void *, int a, int b);

int sort(void *, int left, int right, 
        cmpfunc_t cmpfunc, exchfunc_t exchfunc);

#endif


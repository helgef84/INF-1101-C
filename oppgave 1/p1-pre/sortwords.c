#include "list.h"
#include "common.h"
#include <string.h>


/*
*           MAIN FUNCTION
*/

int main(int argc, char **argv)
{  

    FILE *fil;
    if(argc < 2){
        fatal_error("no file given\n");
    }

    list_t *new_words = list_create((cmpfunc_t) strcmp);
    list_t *sorted_words;

    for(int i = 1; i < argc; i ++){
        FILE *fil = fopen(argv[i], "r");

        tokenize_file(fil, new_words);
        fclose(fil);
    }
    list_sort(new_words);
    list_iter_t *iter = list_createiter(new_words);
    
    while(list_hasnext(iter) != 0){
       //list_sort(new_words);
        

        char *word = list_next(iter);
        printf("%s\n", word);
    }
    list_destroyiter(iter);

    return 0;
}

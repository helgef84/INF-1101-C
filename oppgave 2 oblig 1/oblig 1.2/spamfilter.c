/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include <string.h>
#include "list.h"
#include "set.h"
#include "common.h"

/*
 * Case-insensitive comparison function for strings.
 */
static int compare_words(void *a, void *b)
{
    return strcasecmp(a, b);
}

/*
 * Returns the set of (unique) words found in the given file.
 */
static set_t *tokenize(char *filename)
{
	set_t *wordset = set_create(compare_words);
	list_t *wordlist = list_create(compare_words);
	list_iter_t *it;
	FILE *f;
	
	f = fopen(filename, "r");
	if (f == NULL) {
		perror("fopen");
		fatal_error("fopen() failed");
	}
	tokenize_file(f, wordlist);
	
	it = list_createiter(wordlist);
	while (list_hasnext(it)) {
		set_add(wordset, list_next(it));		
	}
	list_destroyiter(it);
	list_destroy(wordlist);
	return wordset;
}

/*
 * Prints a set of words.
 */
static void printwords(char *prefix, set_t *words)
{
	set_iter_t *it;
	
	it = set_createiter(words);
	printf("%s: ", prefix);
	while (set_hasnext(it)) {
		printf(" %s", set_next(it));
	}
	printf("\n");
	set_destroyiter(it);
}



/*
 * Main entry point.
 */
int main(int argc, char **argv)
{
	char *spamdir, *nonspamdir, *maildir;

	list_t *spamfiles, *nonspamfiles, *mailfiles;

	if (argc != 4) {
		fprintf(stderr, "usage: %s <spamdir> <nonspamdir> <maildir>\n",
				argv[0]);
		return 1;
	}
	spamdir = argv[1];
	nonspamdir = argv[2];
	maildir = argv[3];

/*
*	List files in spam directory
*/
	spamfiles = find_files(spamdir);
	
/*
*	find intersection of all spam mails
*/
	list_iter_t *spamit = list_createiter(spamfiles);
	set_t *spamintersect = tokenize(list_next(spamit));
	while (list_hasnext(spamit)) {
		spamintersect = set_intersection(spamintersect, tokenize(list_next(spamit)));
		
	}
/*
*	List all files in  nonspam directory
*/
	nonspamfiles = find_files(nonspamdir);
/*
*	Find union of all nonspam mails
*/
	list_iter_t *nonspamit = list_createiter(nonspamfiles);
	set_t *nonspamunion = tokenize(list_next(nonspamit));
	while(list_hasnext(nonspamit)){
		nonspamunion = set_union(nonspamunion, tokenize(list_next(nonspamit)));
	}

/*
*	Find spam key as difference of spam-intersection and nonspam-union
*/
	set_t *spamkey = set_difference(spamintersect, nonspamunion);

/*
*	Find files in mail directory
*/
	mailfiles = find_files(maildir);
	
/*
*	Check if mail contains words in spamkey with intersection of mail and spamkey
*	if yes mail is spam
*/

	list_iter_t *mailit = list_createiter(mailfiles);
	char *dir = list_next(mailit);
	set_t *mailasspam = set_intersection(spamkey, tokenize(dir));
	int size = set_size(mailasspam);
	if(size > 0){
		printf("%s : %d -> SPAM\n", dir,size);
	}else{
		printf("%s : %d -> not spam\n",dir , size);
	}
	while(list_hasnext(mailit)){
		dir = list_next(mailit);
		mailasspam = set_intersection(spamkey, tokenize(dir));
		size = set_size(mailasspam);
		if(size > 0){
			printf("%s : %d -> SPAM\n", dir ,size);
		}
		else{
			printf("%s : %d -> not spam\n", dir , size);
		}
	}
/*
*	Destroy all lists, sets, and iterators
*/

	list_destroy(spamfiles);
	list_destroy(nonspamfiles);
	list_destroy(mailfiles);
	
	list_destroyiter(spamit);
	list_destroyiter(nonspamit);
	list_destroyiter(mailit);

	set_destroy(spamintersect);
	set_destroy(nonspamunion);
	set_destroy(spamkey);
	set_destroy(mailasspam);

	return 0;
}

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

set_t *token_set(char *path, char *filename) {
	
	FILE *fp;
	
	char filepath[50] = "";
	char file[20] = "";


	strcpy(filepath, path);
	strcpy(file, filename);

	strcat(filepath, file);

	//fp = fopen(filepath, "r");

	set_t *set = tokenize(filepath);

	return set;


}



/*
 * Main entry point.
 */
int main(int argc, char **argv)
{
	char *spamdir, *nonspamdir, *maildir;
	char *spam1, *spam2, *spam3, *spam4;
	char *nonspam1, *nonspam2, *nonspam3, *nonspam4;
	char *mail1, *mail2, *mail3, *mail4, *mail5;

	if (argc != 4) {
		fprintf(stderr, "usage: %s <spamdir> <nonspamdir> <maildir>\n",
				argv[0]);
		return 1;
	}
	spamdir = argv[1];
	nonspamdir = argv[2];
	maildir = argv[3];

	spam1 = token_set(spamdir, "/spam1.txt");
	spam2 = token_set(spamdir, "/spam2.txt");
	spam3 = token_set(spamdir, "/spam3.txt");
	spam4 = token_set(spamdir, "/spam4.txt");
	
	nonspam1 = token_set(nonspamdir, "/nonspam1.txt");
	nonspam2 = token_set(nonspamdir, "/nonspam2.txt");
	nonspam3 = token_set(nonspamdir, "/nonspam3.txt");
	nonspam4 = token_set(nonspamdir, "/nonspam4.txt");
	
	mail1 = token_set(maildir, "/mail1.txt");
	mail2 = token_set(maildir, "/mail2.txt");
	mail3 = token_set(maildir, "/mail3.txt");
	mail4 = token_set(maildir, "/mail4.txt");
	mail5 = token_set(maildir, "/mail5.txt");
	
	set_t *spamintersect = set_intersection(set_intersection(spam1, spam2), set_intersection(spam3, spam4));
	set_t *nonspamunion = set_union(set_union(nonspam1, nonspam2), set_union(nonspam3, nonspam4));
	set_t *spamkey = set_difference(spamintersect, nonspamunion);

	set_t *mail1intersect = set_intersection(mail1, spamkey);
	set_t *mail2intersect = set_intersection(mail2, spamkey);
	set_t *mail3intersect = set_intersection(mail3, spamkey);
	set_t *mail4intersect = set_intersection(mail4, spamkey);
	set_t *mail5intersect = set_intersection(mail5, spamkey);

	if (mail3intersect == NULL){
		printf("its null\n");
	}else{
		printf("its not null\n");
	}
	

	printwords("Mail 1 vs key", mail1intersect);
	printwords("Mail 2 vs key", mail2intersect);
	printwords("Mail 3 vs key", mail3intersect);
	printwords("Mail 4 vs key", mail4intersect);
	printwords("Mail 5 vs key", mail5intersect);
	
	//printwords("intersecting words in spam mails : \n", spamintersect);
	//printwords("All words in nonspam: \n", nonspamunion);
	//printwords("Spamkey: \n", spamkey);


	return 0;
}

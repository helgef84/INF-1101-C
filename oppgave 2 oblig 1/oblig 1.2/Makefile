## Author: Steffen Viken Valvaag <steffenv@cs.uit.no> 
LIST_SRC=linkedlist.c
SET_SRC=   set.c # Insert the file name of your set implementation here
SPAMFILTER_SRC=spamfilter.c common.c time.c $(LIST_SRC) $(SET_SRC)
NUMBERS_SRC=numbers.c common.c time.c $(LIST_SRC) $(SET_SRC)
ASSERT_SRC=assert_set.c common.c time.c $(LIST_SRC) $(SET_SRC)
HEADERS=common.h list.h set.h time.h

all: spamfilter numbers assert

spamfilter: $(SPAMFILTER_SRC) $(HEADERS) Makefile
	gcc -o $@ $(SPAMFILTER_SRC) -g

numbers: $(NUMBERS_SRC) $(HEADERS) Makefile
	gcc -o $@ $(NUMBERS_SRC) -g

assert: $(ASSERT_SRC) $(HEADERS) Makefile
	gcc -o $@ $(ASSERT_SRC) -g

clean:
	rm -f *~ *.o *.exe spamfilter numbers assert

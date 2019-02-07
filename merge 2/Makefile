## Author: Aage Kvalnes <aage@cs.uit.no>
all: compile random sorted reversed plot plot_compare

random:
	./mergesort_random 262144 mergesort_random.data

sorted:
	./mergesort_sorted 262144 mergesort_sorted.data

reversed:
	./mergesort_reversed 262144 mergesort_reversed.data

	
compile:
	@echo Compiling...
	@gcc -o mergesort_random testsort.c mergesort_array.c time.c
	@gcc -o mergesort_sorted testsort_sorted.c mergesort_array.c time.c
	@gcc -o mergesort_reversed testsort_reversed.c mergesort_array.c time.c
	@gcc -o mergesort_list mergesort_list.c
	@echo Done!

plot_compare:
	gnuplot sortperf_compare.plot
#acrobat sortperf_compare.pdf

plot:
	gnuplot sortperf_mergesort.plot
#acrobat sortperf_mergesort.pdf

clean:
	rm -f *.o
	rm -f *~
	rm -f ./mergesort_random ./mergesort_sorted ./mergesort_reversed ./mergesort_list
	rm -f ./mergesort_random.data ./mergesort_sorted.data ./mergesort_reversed.data
	rm -f *.ps *.pdf *.exe *.stackdump

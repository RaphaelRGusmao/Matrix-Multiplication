################################################################################
#                                IME-USP (2018)                                #
#              MAC0219 - Programacao Concorrente e Paralela - EP1              #
#                                                                              #
#                                   Makefile                                   #
#                                                                              #
#                       Marcelo Schmitt   - NUSP 9297641                       #
#                       Raphael R. Gusmao - NUSP 9778561                       #
################################################################################

.PHONY: clean
CC = g++
CFLAGS = -Wall -O0 -g
OBJS = \
	block_matrix.o \
	matrix.o \
	main.o

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread -fopenmp
	make clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~

run:
	./main s "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"

mar_test:
	./main o "matrix/test5.txt" "matrix/test6.txt" "matrix/result_test.txt"
#	./main o "matrix/test1.txt" "matrix/test3.txt" "matrix/result_test.txt"
#	./main o "matrix/test4.txt" "matrix/test3.txt" "matrix/result_test.txt"
################################################################################

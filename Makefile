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
CFLAGS = -Wall -O2 -g
OBJS = \
	util.o \
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
	clear
	make
	clear
	./main p "matrix/A_python.txt" "matrix/B_python.txt" "matrix/C.txt"

mar_test:
	./main o "matrix/test5.txt" "matrix/test6.txt" "matrix/result_test.txt"
#pequeno teste de corretude
#	./main o "matrix/test1.txt" "matrix/test2.txt" "matrix/result_test.txt"
#	./main o "matrix/test1.txt" "matrix/test3.txt" "matrix/result_test.txt"
#teste de compatibilidade das dimensoes das matrizes
#	./main o "matrix/test3.txt" "matrix/test4.txt" "matrix/result_test.txt"
################################################################################

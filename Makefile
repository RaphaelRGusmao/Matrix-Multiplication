################################################################################
#                                IME-USP (2018)                                #
#           MAC0219 - Programacao Concorrente e Paralela - Desafio2            #
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
	matrix_reader.o \
	mult_openmp.o \
	mult_pthread.o \
	main.o

all: ep1

ep1: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ -lpthread
	make clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *~

run:
	./ep1 p "matrizExemplo.txt" "matrizExemplo.txt" "matrizSaidaExemplo.txt"

################################################################################

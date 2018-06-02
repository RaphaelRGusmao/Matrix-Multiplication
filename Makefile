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
CXXFLAGS = -fopenmp
OBJS = \
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
	./main p "matrix/A.txt" "matrix/B.txt" "matrix/C.txt"

################################################################################

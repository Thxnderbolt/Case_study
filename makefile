CC=gcc
CFLAGS=-Wall -Wextra -std=c99

all: CaseStudy

CaseStudy: CaseStudy.o functions.o
	$(CC) $(CFLAGS) -o CaseStudy CaseStudy.o functions.o

CaseStudy.o: CaseStudy.c functions.h 
	$(CC) $(CFLAGS) -c CaseStudy.c
functions.o: functions.c functions.h 
	$(CC) $(CFLAGS) -c functions.c
clean: 
	rm -f CaseStudy *.o

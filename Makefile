all: NumericalAnalyzer

NumericalAnalyzer: NumericalAnalyzer.c libinfi.a
		gcc -Wall -Wextra -Wvla -std=c99 -lm NumericalAnalyzer.c libinfi.a -o NumericalAnalyzer

libinfi.a: infi.o #let's link library files into a static library
		ar rcs libinfi.a infi.o

infi.o: infi.c infi.h
		gcc -Wall -Wextra -Wvla -std=c99 -lm -c infi.c

PHONY: clean
clean:
		rm -f NumericalAnalyzer *.o *.a *.gch
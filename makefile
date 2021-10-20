all: tests/maptel_test1 tests/maptel_test2

tests/maptel_test1: tests/maptel_test1.o maptel.o
	g++ tests/maptel_test1.o maptel.o -o tests/maptel_test1

tests/maptel_test1.o: tests/maptel_test1.c maptel.h
	gcc -Wall -Wextra -std=c11 -c tests/maptel_test1.c -o tests/maptel_test1.o

tests/maptel_test2: tests/maptel_test2.o maptel.o
	g++ tests/maptel_test2.o maptel.o -o tests/maptel_test2

tests/maptel_test2.o: tests/maptel_test2.cc maptel.h
	g++ -Wall -Wextra -std=c++17 -c tests/maptel_test2.cc -o tests/maptel_test2.o

maptel.o: maptel.cc maptel.h
	g++ -Wall -Wextra -std=c++17 -c maptel.cc

test: tests/maptel_test1 tests/maptel_test2 
	./tests/maptel_test1
	./tests/maptel_test2

clean:
	rm tests/maptel_test1 tests/maptel_test1.o tests/maptel_test2 tests/maptel_test2.o maptel.o

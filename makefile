all: test test

tests/maptel_test1: test maptel.o
	g++ tests/maptel_test1.o maptel.o -o tests/maptel_test1

tests/maptel_test1.o: test src/maptel.h
	gcc -Wall -Wextra -std=c11 -c tests/maptel_test1.c -o tests/maptel_test1.o

tests/maptel_test2: test maptel.o
	g++ tests/maptel_test2.o maptel.o -o tests/maptel_test2

tests/maptel_test2.o: test src/maptel.h
	g++ -Wall -Wextra -std=c++17 -c tests/maptel_test2.cc -o tests/maptel_test2.o

maptel.o: src/maptel.cc src/maptel.h
	g++ -Wall -Wextra -std=c++17 -c maptel.cc

test: test test
	./tests/maptel_test1
	./tests/maptel_test2

clean:
	rm tests/maptel_test1 tests/maptel_test1.o tests/maptel_test2 tests/maptel_test2.o maptel.o

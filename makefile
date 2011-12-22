CC=g++
#CXXFLAGS=-I ~/include -Werror -Wall -Wextra
CXXFLAGS=-I ~/include

compile: card.o player.o console.o game.o cpphead.o
	$(CC) -o cpphead card.o player.o console.o game.o cpphead.o

install: compile
	cp cpphead ~/bin/cpphead

compile-tests: testsuite.o test_card.o card.o test_player.o player.o
	$(CC) testsuite.o test_card.o card.o test_player.o player.o -I ~/include -L ~/lib -o testsuite -l headunitcpp

test: compile-tests
	./testsuite

clean:
	rm -f *.o
	rm -f cpphead
	rm -f ~/bin/cpphead
	rm -f testsuite

run: clean install
	cpphead

memcheck: clean install
	valgrind --leak-check=full cpphead


CC=g++
#CXXFLAGS=-I ~/include -Werror -Wall -Wextra
CXXFLAGS=-I ~/include -Wno-write-strings

compile: card.o player.o human_player.o computer_player.o console.o game.o cpphead.o
	$(CC) -o cpphead card.o player.o human_player.o computer_player.o console.o game.o cpphead.o

install: compile
	cp cpphead ~/bin/cpphead

compile-tests: testsuite.o test_card.o card.o test_player.o test_computer_player.o test_human_player.o player.o human_player.o computer_player.o
	$(CC) -Wno-write-strings testsuite.o test_card.o card.o test_player.o test_computer_player.o test_human_player.o player.o human_player.o computer_player.o -I ~/include -L ~/lib -o testsuite -l headunit

test: compile-tests
	./testsuite

clean:
	rm -f *.o
	rm -f cpphead
	rm -f testsuite

run: clean install
	cpphead

memcheck: clean install
	valgrind --leak-check=full cpphead


CC = g++
CXXFLAGS = -I ~/include -Wno-write-strings
TESTLIB = -L ~/lib -l headunit
OBJS = card.o player.o human_player.o computer_player.o console.o \
	   game.o player_factory.o cpphead.o
TESTOBJS = test_card.o card.o \
		   test_player.o player.o \
		   test_computer_player.o computer_player.o \
		   test_human_player.o human_player.o

cpphead: $(OBJS)
	$(CC) -o cpphead $(OBJS)

card.o: card.hpp
player.o: player.hpp card.hpp
human_player.o: human_player.hpp shithead_exception.hpp
computer_player.o: computer_player.hpp
player_factory.o: player_factory.hpp player.hpp human_player.hpp \
                  computer_player.hpp shithead_exception.hpp
console.o: console.hpp player.hpp
game.o: game.hpp console.hpp player.hpp player_factory.hpp card.hpp
cpphead.o: console.hpp card.hpp player.hpp game.hpp shithead_exception.hpp

test_card.o: card.hpp
test_player.o: human_player.hpp
test_human_player.o: player.hpp human_player.hpp shithead_exception.hpp
test_computer_player.o: computer_player.hpp

testsuite: testsuite.hpp $(TESTOBJS)
	$(CC) $(CXXFLAGS) testsuite.cpp  $(TESTOBJS) -o testsuite $(TESTLIB)

.PHONY: install
install: cpphead
	cp cpphead ~/bin/cpphead

.PHONY: test
test: testsuite
	./testsuite

.PHONY: clean
clean:
	rm -f *.o
	rm -f cpphead
	rm -f testsuite

.PHONY: run
run: clean install
	cpphead

.PHONY: memcheck
memcheck: clean install
	valgrind --leak-check=full cpphead


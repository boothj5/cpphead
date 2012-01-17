CC = g++
CXXFLAGS = -std=c++0x -O3 -I ~/include -Wno-write-strings
TESTLIB = -L ~/lib -l headunit
OBJS = card.o player.o human_player.o computer_player.o console.o \
	   simple_player.o lowcard_player.o game.o player_interaction.o \
       player_helper.o highcard_player.o pyromaniac.o player_factory.o \
       util.o
TESTOBJS = test_card.o card.o \
		   test_player.o player.o \
           highcard_player.o lowcard_player.o pyromaniac.o computer_player.o \
		   test_simple_player.o simple_player.o player_factory.o \
		   test_human_player.o human_player.o \
           player_helper.o game.o util.o

cpphead: $(OBJS) cpphead.o
	$(CC) -o cpphead $(OBJS) cpphead.o

battle: $(OBJS) battle.o
	$(CC) -o battle $(OBJS) battle.o

card.o: card.hpp
player.o: player.hpp human_player.hpp card.hpp shithead_exception.hpp util.hpp
player_factory.o: player_factory.hpp player.hpp human_player.hpp \
				  computer_players.hpp
computer_player.o: player.hpp computer_players.hpp
human_player.o: human_player.hpp player.hpp player_helper.hpp shithead_exception.hpp
simple_player.o: computer_players.hpp player_helper.hpp card.hpp \
                 game.hpp util.hpp
lowcard_player.o: computer_players.hpp player_helper.hpp \
				  card.hpp game.hpp
highcard_player.o: card.hpp computer_players.hpp \
				   player_helper.hpp game.hpp
pyromaniac.o: card.hpp computer_players.hpp \
              player_helper.hpp game.hpp
player_interaction.o: player_interaction.hpp player.hpp game.hpp \
                      console.hpp player_helper.hpp shithead_exception.hpp
player_helper.o: player_helper.hpp card.hpp
console.o: console.hpp player.hpp
game.o: game.hpp console.hpp player.hpp card.hpp player_helper.hpp util.hpp
util.o: util.hpp
cpphead.o: console.hpp card.hpp player.hpp game.hpp shithead_exception.hpp \
           player_interaction.hpp
battle.o: player_factory.hpp player.hpp game.hpp player_interaction.hpp \
		  shithead_exception.hpp util.hpp

test_card.o: card.hpp
test_player.o: human_player.hpp
test_human_player.o: player.hpp human_player.hpp shithead_exception.hpp
test_simple_player.o: computer_players.hpp

testsuite: testsuite.hpp $(TESTOBJS)
	$(CC) $(CXXFLAGS) -std=c++0x testsuite.cpp  $(TESTOBJS) -o testsuite $(TESTLIB)

.PHONY: install
install: cpphead battle
	cp cpphead ~/bin/cpphead
	cp battle ~/bin/battle

.PHONY: test
test: testsuite
	./testsuite

.PHONY: clean
clean:
	rm -f *.o
	rm -f cpphead
	rm -f battle
	rm -f testsuite

.PHONY: run
run: clean install
	cpphead

.PHONY: memcheck
memcheck: clean install
	valgrind --leak-check=full cpphead


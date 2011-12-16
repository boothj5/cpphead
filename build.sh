#!/bin/sh

rm -f ./bin/*

g++ -c player.cpp
g++ -c game.cpp
g++ player.o game.o cpphead.cpp -o ./bin/cpphead


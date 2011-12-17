#!/bin/sh

rm -f ./bin/*

g++ -c player.cpp
g++ -c console.cpp
g++ -c game.cpp
g++ console.o player.o game.o cpphead.cpp -o ./bin/cpphead


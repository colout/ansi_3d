#!/bin/bash
clang++ -c ./src/main.cpp -o ./src/main.o -std=gnu++11 -g -O2 -I./include
clang++ ./src/main.o -o ./bin/ansi_3d -L./lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
./bin/ansi_3d

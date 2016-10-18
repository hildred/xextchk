#!/usr/bin/make -f

xextchk: xextchk.c
	gcc -O3 -g3 -W -Wall -Wextra -o $@ $< `pkg-config --cflags --libs x11`

#!/usr/bin/make -f

xextchk: xextchk.c
	gcc -O3 -g3  -W -Wall -Wextra  $<  $(pkg-config --cflags --libs x11)  -o $@

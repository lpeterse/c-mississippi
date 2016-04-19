.PHONY: all

all: mississippi
	sh -c 'time ./mississippi'

mississippi: mississippi.c
	gcc mississippi.c -O2 -Wall -o mississippi

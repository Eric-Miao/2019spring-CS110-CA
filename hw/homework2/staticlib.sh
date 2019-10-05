#!/bin/bash
gcc -c doubll.c -o doubll.o

ar rcs liblist.a doubll.o
gcc -o staticlist test.c -L. -llist

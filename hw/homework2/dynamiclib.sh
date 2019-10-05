#! /bin/bash
gcc -shared -fPIC -o liblist.so doubll.c
gcc test.c -L. -llist -o dynamiclist -Wl,-rpath=.

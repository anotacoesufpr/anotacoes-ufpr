#!/bin/bash
gcc -c a.c -o a.o
gcc -c main.c -o main.o
gcc -o main main.o a.o

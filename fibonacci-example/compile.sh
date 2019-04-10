#!/bin/sh


# The compiler creates an assembly file out of a C source file
../tokenize-and-compile fibonacci.c

# gcc is used to compile special main function and for turning the previously
# generated assembly file into an executable
gcc main.c fibonacci.c.s -o program


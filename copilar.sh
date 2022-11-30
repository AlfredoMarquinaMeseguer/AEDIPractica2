#!/bin/bash

make
./a.out < Entrada/$1.in > SalidaPrueba/$1.out
meld Salida/$1.out SalidaPrueba/$1.out
tar -cf archivo.tar Makefile *.cpp *.h

# Ejercicio 005
a.out: MapaLugares.o Lugar.o Principal.o
	g++ MapaLugares.o Lugar.o Principal.o

MapaLugares.o: MapaLugares.cpp MapaLugares.h Lugar.h
	g++ -c MapaLugares.cpp

Lugar.o: Lugar.cpp Lugar.h
	g++ -c Lugar.cpp

Principal.o: Principal.cpp Lugar.h MapaLugares.h 
	g++ -c Principal.cpp


# Ejercicio 005
a.out: MapaLugares.o Lugar.o Carretera.o Principal.o
	g++ MapaLugares.o Lugar.o Carretera.o Principal.o

MapaLugares.o: MapaLugares.cpp MapaLugares.h Lugar.h Carretera.h
	g++ -c MapaLugares.cpp

Lugar.o: Lugar.cpp Lugar.h Carretera.h
	g++ -c Lugar.cpp

Carretera.o: Carretera.cpp Carretera.h
	g++ -c Carretera.cpp

Principal.o: Principal.cpp Lugar.h MapaLugares.h 
	g++ -c Principal.cpp


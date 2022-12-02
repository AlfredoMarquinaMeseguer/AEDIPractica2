# Ejercicio 005
a.out:  funcionesArbol.o MapaLugares.o Lugar.o Carretera.o Principal.o
	g++ funcionesArbol.o MapaLugares.o Lugar.o Carretera.o Principal.o


Carretera.o: Carretera.cpp Carretera.h 
	g++ -c Carretera.cpp

MapaLugares.o: MapaLugares.cpp MapaLugares.h Lugar.h Carretera.h funcionesArbol.h Carretera.o
	g++ -c MapaLugares.cpp

Lugar.o: Lugar.cpp Lugar.h Carretera.h
	g++ -c Lugar.cpp

funcionesArbol.o: funcionesArbol.cpp funcionesArbol.h Carretera.h
	g++ -c funcionesArbol.cpp

Principal.o: Principal.cpp Lugar.h MapaLugares.h Carretera.h funcionesArbol.h 
	g++ -c Principal.cpp


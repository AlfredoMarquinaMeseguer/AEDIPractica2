#ifndef MAPALUGARES_H
#define MAPALUGARES_H

#include <string>
#include <list>
#include "Lugar.h"

using namespace std;
class MapaLugares{  
  private:
    Lugar **mapa;
    int numeroLugares;
    int capacidad;

    unsigned long funcionHash(string clave);
    void reestructuracion();
  public:

    MapaLugares();
    ~MapaLugares();
    int getNumeroLugares();
    int getCapacidad();
   
    bool insertar(string nombre, string informacion);
    Lugar  consultar(string nombre);
    void vaciar(void);
};
#endif

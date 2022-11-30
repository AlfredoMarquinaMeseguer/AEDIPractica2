#ifndef MAPALUGARES_H
#define MAPALUGARES_H

#include <string>
#include <list>
#include "Lugar.h"

using namespace std;
class MapaLugares{  
  private:
    Lugar **mapa;
    unsigned long numeroLugares;
    unsigned long capacidad;

    unsigned long funcionHash(string clave);
    void reestructuracion();
  public:

    MapaLugares();
    ~MapaLugares();
    int getNumeroLugares(){ return numeroLugares; }
    int getCapacidad(){ return capacidad; }
   
    bool insertar(Lugar * lugar);
    Lugar consultar(string nombre);
    void eliminar(string nombre);
    void vaciar(void);
};
#endif

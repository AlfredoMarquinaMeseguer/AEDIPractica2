#ifndef MAPALUGARES_H
#define MAPALUGARES_H

#include <string>
#include <list>
#include "Lugar.h"
#include "Carretera.h"

using namespace std;
class MapaLugares{  
  private:
    list<Lugar> *mapa;
    unsigned long numeroLugares;
    unsigned long capacidad;

    unsigned long funcionHash(string clave);
    void reestructuracion();  
  public:
    
    MapaLugares();
    ~MapaLugares();
    int getNumeroLugares(){ return numeroLugares; }
    int getCapacidad(){ return capacidad; }
   
    void insertar(Lugar * lugar);
    Lugar * consultar(string nombre);
    void eliminar(string nombre);
    void vaciar(void);

    bool annadirCarretera(string origen, Carretera * carretera);
    Carretera * consultarCarretera(string origen, string destino);

    //Listar adyacente como lista de carreteras al implementarlo en el siguiente ejercicio 302
    list<Carretera *> listarAdyacentes(string origen);
};
#endif

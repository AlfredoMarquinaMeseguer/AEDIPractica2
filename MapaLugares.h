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
    unsigned long numeroCarreteras;
    unsigned long capacidad;

    unsigned long funcionHash(string clave);
    void reestructuracion();  
  public:
    
    MapaLugares();
    ~MapaLugares();
    int getNumeroLugares(){ return numeroLugares; }
    int getCapacidad(){ return capacidad; }
    int getNumeroCarreteras(){ return numeroCarreteras; }
   
    void insertar(Lugar * lugar);
    Lugar * consultar(string nombre);
    void eliminar(string nombre);
    void vaciar(void);

    bool annadirCarretera(string origen, string destino, unsigned int coste,string informacion);
    bool annadirCarretera(string origen, Carretera * carreteraAnnadir);
    Carretera * consultarCarretera(string origen, string destino);

    //Listar adyacente como lista de carreteras al implementarlo en el siguiente ejercicio 302
    list<Carretera *> listarAdyacentes(string origen);
};
#endif


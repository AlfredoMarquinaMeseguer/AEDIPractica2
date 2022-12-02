#ifndef MAPALUGARES_H
#define MAPALUGARES_H

#include <string>
#include <list>
#include "Lugar.h"
#include "Carretera.h"

using namespace std;
class MapaLugares
{
private:
  list<Lugar> *mapa;
  unsigned long numeroLugares;
  unsigned long numeroCarreteras;
  unsigned long capacidad;

  // Algoritmo de dispersion sdbm
  unsigned long funcionHash(string clave);
  // Reestrutucracion del mapaLugares
  void reestructuracion();

public:
  // Constructor y Destructor
  MapaLugares();
  ~MapaLugares();

  // Getters de variables
  int getNumeroLugares() { return numeroLugares; }
  int getCapacidad() { return capacidad; }
  int getNumeroCarreteras() { return numeroCarreteras; }

  //************************Operaciones que editan lugares************************

  /*
     Inserta un lugar en el mapa o lo actualiza si el lugar ya existe.
     Actualiza numeroLugares.*/
  void insertar(Lugar *lugar);
  /*
    Elimina un lugar del mapaLugares si su clave nombre coincide con el parametro nombre.
    Actualiza numeroLugares.*/
  void eliminar(string nombre);

  //************************Operacion que consulta lugares************************

  /*
    Consulta si un lugar se encuentra en el mapaLugares por clave.
    Devuelve nullptr si no se encuentra.*/
  Lugar *consultar(string nombre);

  //************************Operaciones que editan carreteras************************

  /*
    Devuelve true si se insertar o actualiza una carretera en el arbol de carreteras 
    del lugar con clave origen. Sino, devuelve false*/
  bool annadirCarretera(string origen, string destino, unsigned int coste, string informacion);

  //************************Operaciones que consultan carrerteras************************

  /*
    Devuelve una carretera perteneciente a un lugar con clave origen con carretera en direccion destino.
    Devuelve nullptr si no se encuentra la carretera.*/
  Carretera *consultarCarretera(string origen, string destino);

  /*
    Lista el arbol completo de carreteras del lugar a consultar. El orden es alfabetico distinguiendo
    mayúsculas y minúsculas.*/
  list<Carretera *> listarAdyacentes(string origen);

  //************************Operaciones que editan lugares y carreteras************************

  /*
    Vacia por completo el mapaLugares.
    Actualiza numeroLugares y numeroCarreteras.*/
  void vaciar(void);
};
#endif

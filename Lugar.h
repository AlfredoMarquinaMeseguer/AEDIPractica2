// Definición de la clase persona -> archivo "Persona.h"
// siempre es buena idea usar macros del preprocesador para evitar compilar varias veces el mismo archivo
#ifndef LUGAR_H
#define LUGAR_H

#include <string>
using namespace std;
class Lugar
{
private:
  // Clave
  string nombre;
  // Valor
  string informacion;
  // siguiente nodo
  Lugar * siguiente;
public:
  Lugar(){this->nombre = ""; this->informacion = "";};
  Lugar(string &nombre){this->nombre = nombre; this->informacion = "";};
  Lugar(string &nombre, string &informacion) :
   nombre(nombre), informacion(informacion), siguiente(NULL){    
   }

  
  
  // nombre
  string getNombre(){ return nombre; }
  void setNombre(string nombre){ this->nombre = nombre; }

// informacion
  string getInformacion() { return informacion; }
  void setInformacion(string informacion){ this->informacion = informacion;}

// siguiente
  Lugar * getSiguiente(){ return siguiente; }
  void setSiguiente(Lugar * siguiente) { Lugar::siguiente = siguiente;}
  
  string toString();
  int compareTo(Lugar otro);
};
#endif


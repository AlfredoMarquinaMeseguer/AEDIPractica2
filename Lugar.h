// Definición de la clase persona -> archivo "Persona.h"
// siempre es buena idea usar macros del preprocesador para evitar compilar varias veces el mismo archivo
#ifndef LUGAR_H
#define LUGAR_H

#include <string>
#include "Carretera.h"
using namespace std;

class Lugar
{
private:
  // Clave
  string nombre;
  // Valor
  string informacion;
  // Carreteras que sale del lugar
  Carretera * carretera;
  // 
public:
  Lugar(){this->nombre = ""; this->informacion = "";};
  Lugar(string &nombre){this->nombre = nombre; this->informacion = "";};
  Lugar(string &nombre, string &informacion) :
   nombre(nombre), informacion(informacion){    
  } 
  
  // nombre
  std::string getNombre(){ return nombre; }
  void setNombre(string nombre){ this->nombre = nombre; }

  // informacion
  std::string getInformacion() { return informacion; }
  void setInformacion(string informacion){ this->informacion = informacion;}

  // carretera
  Carretera * getCarretera() { return carretera; }
  void setCarretera(Carretera * carretera){ this->carretera = carretera;}
  
  std::string toString();
  int compareTo(Lugar otro);

  std::string nombreCarretera();
};
#endif


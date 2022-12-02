#ifndef LUGAR_H
#define LUGAR_H

#include <iostream>
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
  // Arbol de carreteras que salen del lugar
  Carretera *carretera;

public:
  //************************Constructores y destructor************************

  Lugar()
  {
    this->nombre = "";
    this->informacion = "";
    this->carretera = nullptr;
  };
  Lugar(string &nombre)
  {
    this->nombre = nombre;
    this->informacion = "";
    this->carretera = nullptr;
  };
  Lugar(string &nombre, string &informacion) : nombre(nombre), informacion(informacion), carretera(nullptr)
  {
  }
  ~Lugar() { delete carretera; };

  //************************Setters y getters************************

  // nombre
  std::string getNombre() { return nombre; }
  void setNombre(string nombre) { this->nombre = nombre; }

  // informacion
  std::string getInformacion() { return informacion; }
  void setInformacion(string informacion) { this->informacion = informacion; }

  // carretera
  Carretera *getCarretera() { return carretera; }
  void setCarretera(Carretera *carretera) { this->carretera = carretera; }

  //************************Métodos************************

  /*
    Pasa la informacion del lugar a string*/
  std::string toString();

  /*
    Compara Lugares segun el nombre*/
  int compareTo(Lugar otro);

  /*
    Nombre completo de la carretera*/
  std::string nombreCarretera();
};
#endif

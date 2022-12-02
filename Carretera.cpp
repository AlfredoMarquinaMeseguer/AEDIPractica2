// Archivo fuente de implementación de la clase Persona
#include "Lugar.h"  // Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>

// Public

// Destructor
Carretera::~Carretera()
{
  if (this != nullptr)
  {

    if (this->getHijoIzquierdo() != nullptr)
    {
      delete this->getHijoIzquierdo();
    }

    if (this->getHijoDerecho() != nullptr)
    {
      delete this->getHijoDerecho();
    }
  }
}

/*
Escribe en un array la informacion de la carretera*/
string Carretera::toString()
{
  return "Destino: " + this->destino + ". Informacion: " + this->informacion +
         ". Coste: " + to_string(this->coste);
}

// Archivo fuente de implementación de la clase Persona
#include "Lugar.h"  // Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>

// Public

string Carretera::toString()
{
  return "Destino: " + this->destino + ". Informacion: " + this->informacion + 
         ". Coste: " + to_string(this->coste);
}
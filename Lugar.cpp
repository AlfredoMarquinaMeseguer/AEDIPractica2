// Archivo fuente de implementación de la clase Persona
#include "Lugar.h"  // Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>
#include <bits/stdc++.h>

// Public

string Lugar::toString()
{
  return "Nombre: " + this->nombre + ". Informacion: " + this->informacion;
}

int Lugar::compareTo(Lugar otro)
{
  int comparador = 0;

  string nombre1 = this->nombre;
	transform(nombre1.begin(), nombre1.end(), nombre1.begin(), ::tolower);
    
  string nombre2 = otro.getNombre();
  transform(nombre2.begin(), nombre2.end(), nombre2.begin(), ::tolower);

  if (this->nombre < otro.getNombre())
  {
    comparador = -1;
  }
  else if (this->nombre < otro.getNombre())
  {
    comparador = 1;
  }

  return comparador;
}
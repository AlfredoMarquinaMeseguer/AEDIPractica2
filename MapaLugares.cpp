// Archivo fuente de implementación de la clase Persona
#include "MapaLugares.h"
#include "Lugar.h"
// Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>

using namespace std; // utilizaremos el espacio de nombres std para cout y string

MapaLugares::MapaLugares()
{
  this->mapa = new Lugar *[100]();
  this->capacidad = 100;
  this->numeroLugares = 0;
}

MapaLugares::~MapaLugares()
{
  for (int i = 0; i < this->capacidad; ++i)
  {
    Lugar *entrada = mapa[i];
    while (entrada != NULL)
    {
      Lugar *previo = entrada;
      entrada = entrada->getSiguiente();
      delete previo;
    }
    mapa[i] = NULL;
  }
  // destroy the hash mapa
  delete[] mapa;
}

int MapaLugares::getNumeroLugares()
{
  return this->numeroLugares;
}

void MapaLugares::vaciar(void)
{
}

bool MapaLugares::insertar(string nombre, string informacion)
{
  unsigned long valorHash = funcionHash(nombre);
  Lugar *previo = NULL;
  Lugar *entrada = mapa[valorHash];

  while (entrada != NULL && entrada->getNombre() != nombre)
  {
    previo = entrada;
    entrada = entrada->getSiguiente();
  }

  if (entrada == NULL)
  {
    entrada = new Lugar(nombre, informacion);
    if (previo == NULL)
    {
      // insert as first bucket
      mapa[valorHash] = entrada;
    }
    else
    {
      previo->setSiguiente(entrada);
    }
  }
  else
  {
    // just update the informacion
    entrada->setInformacion(informacion);
  }
}

Lugar MapaLugares::consultar(string nombre)
{
  unsigned long hashValue = funcionHash(nombre);
  Lugar *entrada = mapa[hashValue];

  while (entrada != NULL && entrada->getNombre() != nombre)
  {
    entrada = entrada->getSiguiente();
  }

  return (entrada != NULL) ? *(entrada) : Lugar();
}
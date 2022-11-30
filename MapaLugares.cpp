// Archivo fuente de implementación de la clase Persona
#include "MapaLugares.h"
#include "Lugar.h"
// Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>

using namespace std; // utilizaremos el espacio de nombres std para cout y string

// Private methods

// Algotimo de dispersion sdbm
unsigned long MapaLugares::funcionHash(string clave)
{
  unsigned char *str = new unsigned char[clave.length() + 1];
  unsigned char *borrarDespues = str;
  std::copy(clave.data(), clave.data() + clave.length() + 1, str);

  unsigned long hash = 0;
  int c;

  while (c = *str++)
    hash = c + (hash << 6) + (hash << 16) - hash;

  delete borrarDespues;

  return (hash % this->capacidad);
}

void MapaLugares::reestructuracion()
{
  unsigned long hash;
  unsigned long antiguaCapacidad = this->capacidad;  
  Lugar **nuevoMapa = this->mapa;

  this->capacidad = this->capacidad ^ 2;
  this->mapa = new Lugar *[this->capacidad];

  for (int i = 0; i < antiguaCapacidad; i++)
  {
    if (this->mapa[i] != NULL)
    {
      // Se coge el primer elemento de la cubeta
      Lugar *entrada = mapa[i];
      while (entrada != NULL)
      {
        // Se inserta en el nuevo mapa
        this->insertar(entrada);
        // Se pasa al siguiente lugar en la cubeta
        entrada = entrada->getSiguiente();
      }
    }
  }
}

// Public methods
MapaLugares::MapaLugares()
{
  this->mapa = new Lugar *[1000]();
  this->capacidad = 1000;
  this->numeroLugares = 0;
}

MapaLugares::~MapaLugares()
{
  // destruir objetos contenidos en el mapa
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
    //mensaje
  }
  // destruir mapa 
  delete[] mapa;
}

bool MapaLugares::insertar(Lugar * lugar)
{
  std::string nombre = lugar->getNombre();
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
    if (previo == NULL)
    {
      // Insertar como primera cubeta
      mapa[valorHash] = lugar;
    }
    else
    {
      previo->setSiguiente(lugar);
    }
  }
  else
  {
    // Si existe uno con la misma clave se edita info
    entrada->setInformacion(lugar->getInformacion());
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

void MapaLugares::eliminar(string nombre)
{
  unsigned long hashValue = funcionHash(nombre);
  Lugar *previo = NULL;
  Lugar *entrada = mapa[hashValue];

  while (entrada != NULL && entrada->getNombre() != nombre)
  {
    previo = entrada;
    entrada = entrada->getSiguiente();
  }

  // Si entrada no es nulo, es porque se ha encontrado el objeto
  if (entrada != NULL)
  {
    if (previo == NULL)
    {
      // eliminar primer nodo cubeta
      mapa[hashValue] = entrada->getSiguiente();
    }
    else
    {
      // eliminar otro nodo cubeta
      previo->setSiguiente(entrada->getSiguiente());
    }
    delete entrada;
  }
}

void MapaLugares::vaciar(void)
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
}
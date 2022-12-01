// Archivo fuente de implementación de la clase Persona
#include "MapaLugares.h"
#include "Lugar.h"
// Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>
#include <list>

using namespace std; // utilizaremos el espacio de nombres std para cout y string

// Private methods

// Algotimo de dispersion sdbm
unsigned long MapaLugares::funcionHash(string clave)
{
  unsigned char str[clave.length() + 1];
  unsigned char *borrarDespues = str;
  std::copy(clave.data(), clave.data() + clave.length() + 1, str);

  unsigned long hash = 0;
  int c;

  while (c = *borrarDespues++)
    hash = c + (hash << 6) + (hash << 16) - hash;  

  return (hash % this->capacidad);
}

void MapaLugares::reestructuracion()
{
  unsigned long hash;
  unsigned long antiguaCapacidad = this->capacidad;
  list<Lugar> *antiguoMapa = this->mapa;

  list<Lugar>::iterator finCubeta;
  list<Lugar>::iterator recorreCubetas;
  list<Lugar> cubeta;

  this->capacidad *= 2;
  this->mapa = new list<Lugar>[this->capacidad];
  this->numeroLugares = 0;

  for (unsigned long i = 0; i < antiguaCapacidad; i++)
  {
    recorreCubetas = antiguoMapa[i].begin();
    finCubeta = antiguoMapa[i].end();
    // Se coge el primer elemento de la cubeta
    while (recorreCubetas != finCubeta)
    {
      // Se inserta en el nuevo mapa
      this->insertar(&(*recorreCubetas));
      // Se pasa al siguiente lugar en la cubeta
      recorreCubetas++;
    }
    antiguoMapa[i].clear();
  }
  delete[] antiguoMapa;
}

// Public methods
MapaLugares::MapaLugares()
{
  this->capacidad = 1000;
  this->mapa = new list<Lugar>[this->capacidad];  
  this->numeroLugares = 0;
}

MapaLugares::~MapaLugares()
{
  // destruir cubeta a cubeta
  for (int i = 0; i < this->capacidad; ++i)
	{
		this->mapa[i].clear();
	}
	delete[] mapa;
}

void MapaLugares::insertar(Lugar *lugar)
{
  std::string nombre = lugar->getNombre();
  unsigned long hashValue = funcionHash(nombre);
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();

  while (posicionCubeta != mapa[hashValue].end() && (*posicionCubeta).getNombre() != nombre)
  {
    posicionCubeta++;
  }

  // No ha llegado al final de la lista, es porque se ha encontrado el objeto
  if (posicionCubeta != mapa[hashValue].end())
  {
    (*posicionCubeta).setInformacion(lugar->getInformacion());    
  }else{
    mapa[hashValue].push_back(*lugar);
    this->numeroLugares++;
  }
}

Lugar *MapaLugares::consultar(string nombre)
{
  unsigned long hashValue = funcionHash(nombre);
  std::list<Lugar>::iterator finCubeta = mapa[hashValue].end();
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();

  while (posicionCubeta != finCubeta && (*posicionCubeta).getNombre() != nombre)
  {
    posicionCubeta++;
  }

  // No ha llegado al final de la lista, es porque se ha encontrado el objeto
  return (posicionCubeta != finCubeta) ? &(*posicionCubeta) : nullptr;  
}

void MapaLugares::eliminar(string nombre)
{
  unsigned long hashValue = funcionHash(nombre);
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();

  while (posicionCubeta != mapa[hashValue].end() && (*posicionCubeta).getNombre() != nombre)
  {
    posicionCubeta++;
  }

  // No ha llegado al final de la lista, es porque se ha encontrado el objeto
  if (posicionCubeta != mapa[hashValue].end())
  {
    mapa[hashValue].erase(posicionCubeta);
    this->numeroLugares--;
  }
}

void MapaLugares::vaciar(void)
{
  // Vaciar mapa cubeta a cubeta
  for (int i = 0; i < this->capacidad; ++i)
	{
		this->mapa[i].clear();
	}
  // Resetear numeroLugares
  this->numeroLugares = 0;
}
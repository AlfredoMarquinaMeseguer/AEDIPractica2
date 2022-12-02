// Archivo fuente de implementación de la clase Persona
#include "Carretera.h"
#include "MapaLugares.h"
#include "Lugar.h"
#include "funcionesArbol.h"
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

  while ((c = *borrarDespues++))
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
  this->numeroCarreteras = 0;
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
  }
  else
  {
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
  // Si no lo encuentra devuele nulo
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
  std::list<Lugar>::iterator posicionCubeta;
  // Vaciar mapa cubeta a cubeta
  for (int i = 0; i < this->capacidad; ++i)
  { /*
     std::cout << "En bucle " << i << " de vaciar" << std::endl;
     posicionCubeta = mapa[i].begin();
     std::cout << "  Antes bucle iterador." << std::endl;
     while (posicionCubeta != mapa[i].end())
     {
       std::cout << "    En bucle iterador. Lugar: "<< (*posicionCubeta).getNombre() << std::endl;
       //delete (*posicionCubeta).getCarretera();
       Carretera::destruirRecursivamente((*posicionCubeta).getCarretera());
       std::cout << "    Carretera eliminada " << std::endl;
       posicionCubeta++;
     }
     std::cout << "  Despues bucle iterador." << std::endl;*/
    this->mapa[i].clear();
  }
  // std::cout << "Fin bucle." << std::endl;
  //  Resetear numeroLugares
  this->numeroLugares = 0;
  this->numeroCarreteras = 0;
}

bool MapaLugares::annadirCarretera(string origen, string destino, unsigned int coste, string informacion)
{
  bool devolver = false;
  int numNodosAntesInserccion, numNodosDespuesInserccion;
  unsigned long hashValue = funcionHash(origen);
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();

  // std::cout << "Inicio: Bucle"<< std::endl;
  while (posicionCubeta != mapa[hashValue].end() &&
         (*posicionCubeta).getNombre() != origen)
  {
    posicionCubeta++;
  }
  // std::cout << "Fin: Bucle"<< std::endl;

  // No ha llegado al final de la lista, es porque se ha encontrado el objeto
  if (posicionCubeta != mapa[hashValue].end() && origen != destino &&  consultar(destino) != nullptr)
  {
    // std::cout <<"Dentro if: " <<  posicionCubeta->getCarretera() << std::endl;
    //  Se mide el numero de nodos antes de insertar
    numNodosAntesInserccion = funcionesArbol::numNodos(posicionCubeta->getCarretera());
    // Se inserta el nodo en el arbol
    // std::cout << "  Numero de nodos antes de insertar: " << numNodosAntesInserccion << std::endl;
    posicionCubeta->setCarretera(funcionesArbol::insertar(posicionCubeta->getCarretera(),
                                                          destino, coste, informacion));
    // std::cout << "  Carretera setteada " << std::endl;
    //  Se mide el numero de nodos despues de insertar
    numNodosDespuesInserccion = funcionesArbol::numNodos(posicionCubeta->getCarretera());
    // std::cout << "Nuumeros de nodos: "<< std::endl;

    // std::cout << "  Numero de nodos despues de insertar: " << numNodosDespuesInserccion << std::endl;
    //  Si el numero de antes es menor al posterior, es porque se ha añadido el nodo
    if (numNodosAntesInserccion < numNodosDespuesInserccion)
    {
      this->numeroCarreteras++;
      // std::cout << "    Nuevo numero carreteras: " << this->numeroCarreteras<< std::endl;
    }
    devolver = true;
  }

  return devolver;
}

Carretera *MapaLugares::consultarCarretera(string origen, string destino)
{
  unsigned long hashValue = funcionHash(origen);
  std::list<Lugar>::iterator finCubeta = mapa[hashValue].end();
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();
  Carretera *consulta;

  while (posicionCubeta != finCubeta && (*posicionCubeta).getNombre() != origen)
  {
    posicionCubeta++;
  }

  /*
   1. Si no se llega al final de la cubeta es porque ha encontrado el objeto.
   2. El puntero carretera no es nulo
   3. El destino de la carretera y el pasado por parametro son iguales
  */
  // (*posicionCubeta).getCarretera()->getDestino() == destino
  if (posicionCubeta != mapa[hashValue].end() &&
      (*posicionCubeta).getCarretera() != nullptr)
  {
    int diferencia = funcionesArbol::comparadorCadenas(destino, (*posicionCubeta).getCarretera()->getDestino());
    if (diferencia == 0)
    {
      consulta = (*posicionCubeta).getCarretera();
    }
    else if (diferencia < 0)
    {
      consulta = funcionesArbol::buscar(posicionCubeta->getCarretera()->getLeftChild(), destino);
    }
    else
    {
      consulta = funcionesArbol::buscar(posicionCubeta->getCarretera()->getRigthChild(), destino);
    }
  }
  else
  {
    // Si no se encuentra devuelve un puntero nulo
    consulta = nullptr;
  }

  return consulta;
}

std::list<Carretera *> MapaLugares::listarAdyacentes(string origen)
{
  unsigned long hashValue = funcionHash(origen);
  std::list<Lugar>::iterator finCubeta = mapa[hashValue].end();
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();
  std::list<Carretera *> consulta;

  while (posicionCubeta != finCubeta && (*posicionCubeta).getNombre() != origen)
  {
    posicionCubeta++;
  }

  /*
  Si no se llega al final de la cubeta es porque ha encontrado el objeto.
  */
  if (posicionCubeta != finCubeta)
  {
    consulta = funcionesArbol::inOrden((*posicionCubeta).getCarretera());
    if (consulta.empty())
    {
      consulta = {nullptr};
    }
  }
  else
  {
    consulta = {};
  }

  return consulta;
}
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

// Algoritmo de dispersion sdbm
unsigned long MapaLugares::funcionHash(string clave)
{
  // Se pasa el string clave a un array de char y se pone un apuntado al principio
  unsigned char str[clave.length() + 1];
  unsigned char *auxiliar = str;
  std::copy(clave.data(), clave.data() + clave.length() + 1, str);

  unsigned long hash = 0;
  int c;

  //Se recorre todo el array teniendo en cuenta el asccii de cada letra
  while ((c = *auxiliar++))
    hash = c + (hash << 6) + (hash << 16) - hash;//Se acumula la funcion de dispersion

  return (hash % this->capacidad); //Se hace el modulo para que apunte a una casilla del mapaLugares
}

// Reestrutucracion del mapaLugares
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

// Constructor
MapaLugares::MapaLugares()
{
  this->capacidad = 1000;
  this->mapa = new list<Lugar>[this->capacidad];
  this->numeroLugares = 0;
  this->numeroCarreteras = 0;
}

// Destructor
MapaLugares::~MapaLugares()
{
  // destruir cubeta a cubeta
  for (int i = 0; i < this->capacidad; ++i)
  {
    this->mapa[i].clear();
  }
  delete[] mapa;
}

//************************Operaciones que editan lugares************************
/*
  Inserta un lugar en el mapa o lo actualiza si el lugar ya existe.
  Actualiza numeroLugares.*/
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

/*
  Elimina un lugar del mapaLugares si su clave nombre coincide con el parametro nombre.
  Actualiza numeroLugares.*/
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

//************************Operacion que consulta lugares************************

/*
  Consulta si un lugar se encuentra en el mapaLugares por clave.
  Devuelve nullptr si no se encuentra.*/
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

//************************Operaciones que editan carreteras************************

/*
Devuelve true si añade un objeto carretera a un lugar si el origen y el destino estan
contenidos en el mapaLugares y origen y destino son diferentes. Si la carretera ya existe
la actualiza.Actuliza numeroCarreteras.*/
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
  if (posicionCubeta != mapa[hashValue].end() && origen != destino && consultar(destino) != nullptr)
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

//************************Operaciones que consultan carrerteras************************

/*
Devuelve una carretera perteneciente a un lugar con clave origen con carretera en direccion destino.
Devuelve nullptr si no se encuentra la carretera.*/
Carretera *MapaLugares::consultarCarretera(string origen, string destino)
{
  unsigned long hashValue = funcionHash(origen);
  std::list<Lugar>::iterator finCubeta = mapa[hashValue].end();
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();
  Carretera *consulta;

  // Primero se encuentra el lugar con clave origen en el mapaLugares
  while (posicionCubeta != finCubeta && (*posicionCubeta).getNombre() != origen)
  {
    posicionCubeta++;
  }

  /*
   1. Si no se llega al final de la cubeta es porque ha encontrado el objeto.
   2. El puntero carretera no es nulo
  */
  if (posicionCubeta != mapa[hashValue].end() &&
      (*posicionCubeta).getCarretera() != nullptr)
  {
    //Calcula direfecrencia entre las claves del nodo y la del objeto a buscar
    int diferencia = funcionesArbol::comparadorCadenas(destino, (*posicionCubeta).getCarretera()->getDestino());
    if (diferencia == 0)//Si la diferencia es cero, la raiz es la carretera a buscar
    {
      consulta = (*posicionCubeta).getCarretera();
    }
    else if (diferencia < 0)//Si la diferencia menor a cero, se encuentra en el subarbol izquierdo
    {
      consulta = funcionesArbol::buscar(posicionCubeta->getCarretera()->getHijoIzquierdo(), destino);
    }
    else //Si la diferencia mayor a cero, se encuentra en el subarbol izquierdo
    {
      consulta = funcionesArbol::buscar(posicionCubeta->getCarretera()->getHijoDerecho(), destino);
    }
  }
  else
  {
    // Si no se encuentra devuelve un puntero nulo
    consulta = nullptr;
  }

  return consulta;
}

/*
Lista el arbol completo de carreteras del lugar a consultar. El orden es alfabetico distinguiendo 
mayúsculas y minúsculas.*/
std::list<Carretera *> MapaLugares::listarAdyacentes(string origen)
{
  unsigned long hashValue = funcionHash(origen);
  std::list<Lugar>::iterator finCubeta = mapa[hashValue].end();
  std::list<Lugar>::iterator posicionCubeta = mapa[hashValue].begin();
  std::list<Carretera *> consulta;

  // Buscar objeto lugar con clave origen
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

    //Si esta vacia es porque el lugar no tiene carreteras
    if (consulta.empty())
    {
      // Le insertarmos un puntero nulo para diferenciarlo de no encontrado
      consulta = {nullptr};
    }
  }
  else
  {
    //No a sido encontrado, devolver lista vacia
    consulta = {};
  }

  return consulta;
}

//************************Operaciones que editan lugares y carreteras************************

/*
  Vacia por completo el mapaLugares.
  Actualiza numeroLugares y numeroCarreteras.*/
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
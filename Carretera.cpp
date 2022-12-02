// Archivo fuente de implementación de la clase Persona
#include "Lugar.h"  // Incluimos la definición (declaración) de la clase
#include <iostream> // Incluimos iostream para usar std::cout
#include <string>

// Public

Carretera::~Carretera()
{
  if (this != nullptr)
  {

    if (this->getLeftChild() != nullptr)
    {
      delete this->getLeftChild();
    }

    if (this->getRigthChild() != nullptr)
    {
      delete this->getRigthChild();
    }
  }
  // Carretera::destruirRecursivamente(this);
}
string Carretera::toString()
{
  return "Destino: " + this->destino + ". Informacion: " + this->informacion +
         ". Coste: " + to_string(this->coste);
}

void Carretera::destruirRecursivamente(Carretera *nodo)
{
  Carretera *derecha;

  do
  {
    std::cout << "    Destruida Carretera Izquierda" << std::endl;
    derecha = nodo->getRigthChild();
    while (nodo != nullptr)
    {
      Carretera *left = nodo->getLeftChild();
      std::cout << "    Destruida Carretera derecha" << std::endl;
      delete nodo;
      std::cout << "    Destruida esta Carretera" << std::endl;
      nodo = left;
    }
    nodo = derecha;
  } while (nodo != nullptr);
  /*
      if (nodo != nullptr)
      {
          destruirRecursivamente(nodo->getLeftChild());
          std::cout << "    Destruida Carretera Izquierda"<< std::endl;
          destruirRecursivamente(nodo->getRigthChild());
          std::cout << "    Destruida Carretera derecha"<< std::endl;
          delete nodo;
          std::cout << "    Destruida esta Carretera"<< std::endl;
      }    */
  /*
      TreeNode* right;
      do {
          right = node->right;
          while(node) {
              TreeNode* left = node->left;
              delete node;
              node = left;
          }
      } while(node = right);*/
}
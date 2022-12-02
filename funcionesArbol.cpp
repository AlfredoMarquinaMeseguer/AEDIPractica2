#include <iostream>
#include <list>
#include <string>
#include <math.h>
#include <algorithm>
#include "Carretera.h"
#include "funcionesArbol.h"

int funcionesArbol::altura(Carretera *arbol)
{
    int altura = 0;
    int alturaIzquierda;
    int alturaDerecha;
    if (arbol != nullptr)
    {
        alturaIzquierda = funcionesArbol::altura(arbol->getLeftChild());
        alturaDerecha = funcionesArbol::altura(arbol->getRigthChild());
        int max_height = std::max(alturaIzquierda, alturaDerecha);
        altura = max_height + 1;
    }
    return altura;
}

int funcionesArbol::numNodos(Carretera *arbol)
{
    int numeroDeNodos = 0;
    if (arbol != nullptr)
    {
        numeroDeNodos = 1 + numNodos(arbol->getLeftChild()) + numNodos(arbol->getRigthChild());
    }
    return numeroDeNodos;
}

int funcionesArbol::diferencia(Carretera *arbol)
{
    int alturaIzquierda = funcionesArbol::altura(arbol->getLeftChild());
    int alturaDerecha = funcionesArbol::altura(arbol->getRigthChild());
    return alturaIzquierda - alturaDerecha;
}

Carretera *funcionesArbol::rotacionSimpleDerecha(Carretera *arbol)
{
    // No se como llamar a t
    Carretera *t = arbol->getRigthChild();
    arbol->setRigthChild(t->getLeftChild());
    t->setLeftChild(arbol);
    return t;
}

Carretera *funcionesArbol::rotacionSimpleIzquierda(Carretera *arbol)
{
    // No se como llamar a t
    Carretera *t = arbol->getLeftChild();
    arbol->setLeftChild(t->getRigthChild());
    t->setRigthChild(arbol);
    return t;
}

Carretera *funcionesArbol::rotacionDobleIzquierdaDerecha(Carretera *arbol)
{
    Carretera *t;
    t = arbol->getLeftChild();
    arbol->setLeftChild(funcionesArbol::rotacionSimpleDerecha(t));
    return funcionesArbol::rotacionSimpleIzquierda(arbol);
}

Carretera *funcionesArbol::rotacionDobleDerechaIzquierda(Carretera *arbol)
{
    Carretera *t;
    t = arbol->getRigthChild();
    arbol->setRigthChild(funcionesArbol::rotacionSimpleIzquierda(t));
    return funcionesArbol::rotacionSimpleDerecha(arbol);
}

Carretera *funcionesArbol::balancear(Carretera *nodo)
{
    int factorDeBalanceo = funcionesArbol::diferencia(nodo);
    if (factorDeBalanceo > 1)
    {
        if (funcionesArbol::diferencia(nodo->getLeftChild()) > 0)
            nodo = funcionesArbol::rotacionSimpleIzquierda(nodo);
        else
            nodo = funcionesArbol::rotacionDobleIzquierdaDerecha(nodo);
    }
    else if (factorDeBalanceo < -1)
    {
        if (funcionesArbol::diferencia(nodo->getRigthChild()) > 0)
            nodo = funcionesArbol::rotacionDobleDerechaIzquierda(nodo);
        else
            nodo = funcionesArbol::rotacionSimpleDerecha(nodo);
    }
    return nodo;
}

Carretera *funcionesArbol::insertar(Carretera *esteNodo, std::string destino, unsigned int coste,
                                    std::string informacion)
{
    int diferencia;
    if (esteNodo == nullptr)
    {
        //std::cout << "Crear Nodo" << destino << std::endl;
        esteNodo = new Carretera(destino, coste, informacion);
        /*
        r->d = v;
        r->l = NULL;
        r->r = NULL;*/
    }
    else
    {
        diferencia = funcionesArbol::comparadorCadenas(destino, esteNodo->getDestino());
        if (diferencia < 0) // Valores menores a la izquierda
        {
            //std::cout << "Insertar en izquierda " << destino << std::endl;
            if (esteNodo->getLeftChild() == nullptr)
            {
                esteNodo->setLeftChild(new Carretera(destino, coste, informacion)); /* code */
            }
            else
            {
                esteNodo->setLeftChild(insertar(esteNodo->getLeftChild(), destino,
                                                coste, informacion));
            }

            /*
            if (esteNodo->getLeftChild() != nullptr){
                esteNodo->setLeftChild(insertar(esteNodo->getLeftChild(), valor));
            }
            else{
                esteNodo->setLeftChild(new Carretera(valor));
            }*/
            esteNodo = balancear(esteNodo);
        }
        else if (diferencia > 0) // Valores mayores a la derecha
        {
            //std::cout << "Insertar en derecha " << destino << std::endl;

             if (esteNodo->getRigthChild() == nullptr)
            {
                esteNodo->setRigthChild(new Carretera(destino, coste, informacion)); /* code */
            }
            else
            {
                esteNodo->setRigthChild(insertar(esteNodo->getRigthChild(), destino,
                                                coste, informacion));
            }
            /*
            if (esteNodo->getRigthChild() != nullptr)

            else
                esteNodo->setRigthChild(new Carretera(valor));*/
            esteNodo = balancear(esteNodo);
        }
        // Si el nodo es de valor igual al existente, no se inserta
        // Excepto si estamos hablando de una carretera tenemos que actualizar la info y el coste

        else
        {
            //std::cout << "Actualizar" << destino << std::endl;
            esteNodo->setInformacion(informacion);
            esteNodo->setCoste(coste);
        }
    }

    return esteNodo;
}

void funcionesArbol::show(Carretera *imprimir, int valorAImprimir)
{
    int i;
    if (imprimir != NULL)
    {
        show(imprimir->getRigthChild(), valorAImprimir + 1);
        std::cout << " ";
        for (i = 0; i < valorAImprimir; i++)
            std::cout << " ";
        std::cout << imprimir->getDestino();
        show(imprimir->getLeftChild(), valorAImprimir + 1);
    }
}

void funcionesArbol::inorder(Carretera *t)
{
    if (t != NULL)
    {
        inorder(t->getLeftChild());
        std::cout << t->getDestino() << " ";
        inorder(t->getRigthChild());
    }
}

std::list<Carretera *> funcionesArbol::inOrden(Carretera *t)
{
    std::list<Carretera *> devolver;
    std::list<Carretera *> aux;
    if (t != NULL)
    {
        // Asignar lista de rama izquierda a actual
        devolver = inOrden(t->getLeftChild());
        // Insertar valor actual en lista
        devolver.push_back(t);
        // Fusionar lista de rama derecha a actual
        aux = inOrden(t->getRigthChild());
        for (Carretera *i : aux)
        {
            devolver.push_back(i);
        }
        // devolver.merge(postOrden(t->getRigthChild()));
        /*
                std::cout << "Nodo: " << t->getValue() << std::endl;
                if (t->getLeftChild() != nullptr)
                {
                    std::cout << "Hijo Izquierdo: " << t->getLeftChild()->getValue() << std::endl;
                }
                if (t->getRigthChild() != nullptr)
                {
                    std::cout << "Hijo Derecho: " << t->getRigthChild()->getValue() << std::endl;
                }
                std::cout << "***************************************************" << std::endl;*/
    }

    return devolver;
}

Carretera *funcionesArbol::buscar(Carretera *esteNodo, std::string destino)
{
    Carretera *devolver;
    int diferencia;
    if (esteNodo != nullptr) // Si el nodo es nulo entonces
    {
        diferencia = funcionesArbol::comparadorCadenas(esteNodo->getDestino(), destino);
        if (diferencia == 0) // Valor igual es el consultado
        {
            devolver = esteNodo;
        }
        else if (diferencia < 0) // Valores menores a la izquierda
        {
            devolver = funcionesArbol::buscar(esteNodo->getLeftChild(), destino);
        }
        else // Valores mayores a la derecha
        {
            devolver = funcionesArbol::buscar(esteNodo->getRigthChild(), destino);
        }
    }
    else
    {
        devolver = nullptr;
    }

    return devolver;
}

/*
    Devuelve un numero n segun el orden alfabetico:
        - numero < 0 -> la primera cadena es menor que la segunda
        - numero == 0 -> la primera cadena es igual a la segunda
        - numero > 0 -> la primera cadena es mayor que la segunda
*/
int funcionesArbol::comparadorCadenas(std::string primero, std::string segundo)
{
    int diferenciaLongitud = primero.length() - segundo.length();
    int longitudTextoCorto = (diferenciaLongitud < 0) ? primero.length() : segundo.length();
    int devolver = 0;

    /*Convertir ambas cadena a compara a minusculas para no diferciar
      entre mayusculas y minusculas*/
    transform(primero.begin(), primero.end(), primero.begin(), ::tolower);
    transform(segundo.begin(), segundo.end(), segundo.begin(), ::tolower);

    // Comparamos letra a letra has que encontremos una diferente
    for (int i = 0; i < longitudTextoCorto && devolver == 0; i++)
    {
        devolver = int(tolower(primero[i])) - tolower(segundo[i]);
    }

    /* En caso de que los caracteres comparados sean iguales es posible que uno
       sea prefijo del otro. Por lo que  comprobamos la diferencia de longitud.
       Esto tendrá los mismos efectos que la original.
    */
    if (devolver == 0)
    {
        devolver = diferenciaLongitud;
    }

    return devolver;
}
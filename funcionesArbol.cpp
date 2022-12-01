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
    std::string copiaValor;
    std::string copiaValorEsteNodo;
    if (esteNodo == NULL)
    {
        esteNodo = new Carretera(destino, coste, informacion);
        /*
        r->d = v;
        r->l = NULL;
        r->r = NULL;*/
    }
    else
    {
        copiaValor = destino;
        copiaValorEsteNodo = esteNodo->getDestino();
        transform(copiaValor.begin(), copiaValor.end(), copiaValor.begin(), ::tolower);
        transform(copiaValorEsteNodo.begin(), copiaValorEsteNodo.end(), copiaValorEsteNodo.begin(), ::tolower);

        if (copiaValor < copiaValorEsteNodo) // Valores menores a la izquierda
        {
            esteNodo->setLeftChild(insertar(esteNodo->getLeftChild(), destino,
                                            coste, informacion));
            /*
            if (esteNodo->getLeftChild() != nullptr){
                esteNodo->setLeftChild(insertar(esteNodo->getLeftChild(), valor));
            }
            else{
                esteNodo->setLeftChild(new Carretera(valor));
            }*/
            esteNodo = balancear(esteNodo);
        }
        else if (copiaValor > copiaValorEsteNodo) // Valores mayores a la derecha
        {
            esteNodo->setRigthChild(insertar(esteNodo->getRigthChild(), destino,
                                             coste, informacion));
            /*
            if (esteNodo->getRigthChild() != nullptr)

            else
                esteNodo->setRigthChild(new Carretera(valor));*/
            esteNodo = balancear(esteNodo);
        }
        // Si el nodo es de valor igual al existente, no se inserta
        // Excepto si estamos hablando de una carretera tenemos que actualizar la info y el coste

        else if (copiaValor == copiaValorEsteNodo)
        {
            std::cout << "Has estado aquí" << copiaValor << " : " << copiaValorEsteNodo << std::endl;
            /*r.setInformacion(informacion);
            r.setCoste(coste);*/
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

std::list<Carretera *> funcionesArbol::postOrden(Carretera *t)
{
    std::list<Carretera *> devolver;
    if (t != NULL)
    {
        // Asignar lista de rama izquierda a actual
        devolver = postOrden(t->getLeftChild());
        // Insertar valor actual en lista
        devolver.push_back(t);
        // Fusionar lista de rama derecha a actual
        devolver.merge(postOrden(t->getRigthChild()));
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
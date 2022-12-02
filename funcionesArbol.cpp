#include <iostream>
#include <list>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include "Carretera.h"
#include "funcionesArbol.h"

//************************Operaciones sobre altura y numero Nodos************************

/*
    Calcula la altura del arbol de carreteras con raiz param arbol.*/
int funcionesArbol::altura(Carretera *arbol)
{

    /// @brief Calcula la altura del arbol de carreteras con raiz param arbol
    /// @param arbol raiz del arbol
    /// @return altura del arbol

    int altura = 0;      // Altura del arbol, se inicializa en cero
                         // por si el arbol es nulo
    int alturaIzquierda; // Altura del subarbol izquierdo
    int alturaDerecha;   // Altura del subarbol derecho
    if (arbol != nullptr)
    {
        /* Si el nodo no es nulo, la altura del arbol es la altura maxima
           entre sus sub-arboles derecho e izquierdo, más la suya propia.
        */
        // Obtener altura sub-arbol izquierdo
        alturaIzquierda = funcionesArbol::altura(arbol->getHijoIzquierdo());
        // Obtener altura sub-arbol derecho
        alturaDerecha = funcionesArbol::altura(arbol->getHijoDerecho());
        // Calcular altura
        altura = std::max(alturaIzquierda, alturaDerecha) + 1;
    }
    return altura;
}

/*
    Calcula el numero de nodos del arbol de carreteas con raiz  param arbol*/
int funcionesArbol::numNodos(Carretera *arbol)
{
    /// @brief Calcula el numero de nodos del arbol de carreteas con raiz  param arbol
    /// @param arbol  raiz deñ arbol de carreteras
    /// @return numero de nodos del arbol

    int numeroDeNodos = 0;
    if (arbol != nullptr)
    {
        /*  Si el nodo no es nulo, el total de nodos es la suma
            del número de nodos de sus subarboles más el mismo.
        */
        numeroDeNodos = 1;

        // Se suma el sub arbol izquierdo si no es nulo
        if (arbol->getHijoIzquierdo() != nullptr)
        {
            numeroDeNodos += numNodos(arbol->getHijoIzquierdo());
        }

        // Se suma el sub arbol derecho si no es nulo
        if (arbol->getHijoDerecho() != nullptr)
        {
            numeroDeNodos += numNodos(arbol->getHijoDerecho());
        }
    }
    return numeroDeNodos;
}

/*
Calcula diferencia de altura entre sub arboles izquierdo y derecho*/
int funcionesArbol::diferencia(Carretera *arbol)
{
    /// @brief calcula diferencia de altura entre sub arboles izquierdo y derecho
    /// @param arbol  raiz del arbol a consultar
    /// @return diferencia de altura entre sub arboles izquierdo y derecho
    int alturaIzquierda = funcionesArbol::altura(arbol->getHijoIzquierdo());
    int alturaDerecha = funcionesArbol::altura(arbol->getHijoDerecho());
    return alturaIzquierda - alturaDerecha;
}

//************************Rotaciones y balanceo************************

/*
Rotacion simple derecha o rotacion derecha-derecha*/
Carretera *funcionesArbol::rotacionSimpleDerecha(Carretera *arbol)
{

    /*Puntero auxiliar, ayuda a la rotatacion si que se pierda
    ningún puntero*/
    Carretera *nodo = arbol->getHijoDerecho();
    arbol->setHijoDerecho(nodo->getHijoIzquierdo());
    nodo->setHijoIzquierdo(arbol);
    return nodo;
}

/*
Rotacion simple izquierda o rotacion izquierda-izquierda*/
Carretera *funcionesArbol::rotacionSimpleIzquierda(Carretera *arbol)
{
    /*Puntero auxiliar, ayuda a la rotatacion si que se pierda
    ningún puntero*/
    Carretera *nodo = arbol->getHijoIzquierdo();
    arbol->setHijoIzquierdo(nodo->getHijoDerecho());
    nodo->setHijoDerecho(arbol);
    return nodo;
}

/*
Rotacion doble derecha o rotacion derecha-izquierda*/
Carretera *funcionesArbol::rotacionDobleDerechaIzquierda(Carretera *arbol)
{
    Carretera *t;
    t = arbol->getHijoDerecho();
    arbol->setHijoDerecho(funcionesArbol::rotacionSimpleIzquierda(t));
    return funcionesArbol::rotacionSimpleDerecha(arbol);
}

/*
Rotacion doble izquierda o rotacion izquierda-derecha*/
Carretera *funcionesArbol::rotacionDobleIzquierdaDerecha(Carretera *arbol)
{
    Carretera *t;
    t = arbol->getHijoIzquierdo();
    arbol->setHijoIzquierdo(funcionesArbol::rotacionSimpleDerecha(t));
    return funcionesArbol::rotacionSimpleIzquierda(arbol);
}

/*
Comprueba si el árbol cumple la condicion de balanceo y la actuliza sino lo hace*/
Carretera *funcionesArbol::balancear(Carretera *nodo)
{
    int factorDeBalanceo = funcionesArbol::diferencia(nodo);
    if (factorDeBalanceo > 1)
    {
        if (funcionesArbol::diferencia(nodo->getHijoIzquierdo()) > 0)
            nodo = funcionesArbol::rotacionSimpleIzquierda(nodo);
        else
            nodo = funcionesArbol::rotacionDobleIzquierdaDerecha(nodo);
    }
    else if (factorDeBalanceo < -1)
    {
        if (funcionesArbol::diferencia(nodo->getHijoDerecho()) > 0)
            nodo = funcionesArbol::rotacionDobleDerechaIzquierda(nodo);
        else
            nodo = funcionesArbol::rotacionSimpleDerecha(nodo);
    }
    return nodo;
}

//************************Edición************************

/*
    Devuelve la raiz del árbol de carreteras después de insertar o actualizar 
    el nodo con clave destino.
*/
Carretera *funcionesArbol::insertar(Carretera *esteNodo, std::string destino, unsigned int coste,
                                    std::string informacion)
{
    int diferencia;
    if (esteNodo == nullptr)
    {
        // std::cout << "Crear Nodo" << destino << std::endl;
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
            // std::cout << "Insertar en izquierda " << destino << std::endl;
            if (esteNodo->getHijoIzquierdo() == nullptr)
            {
                esteNodo->setHijoIzquierdo(new Carretera(destino, coste, informacion)); /* code */
            }
            else
            {
                esteNodo->setHijoIzquierdo(insertar(esteNodo->getHijoIzquierdo(), destino,
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
            // std::cout << "Insertar en derecha " << destino << std::endl;

            if (esteNodo->getHijoDerecho() == nullptr)
            {
                esteNodo->setHijoDerecho(new Carretera(destino, coste, informacion)); /* code */
            }
            else
            {
                esteNodo->setHijoDerecho(insertar(esteNodo->getHijoDerecho(), destino,
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
            // std::cout << "Actualizar" << destino << std::endl;
            esteNodo->setInformacion(informacion);
            esteNodo->setCoste(coste);
        }
    }

    return esteNodo;
}

//************************Consulta************************

/*
    Devuelve la direccion de carretera con clave destino. Sino se encuentra en el
    árbol, devuelve nullptr.
*/
Carretera *funcionesArbol::buscar(Carretera *esteNodo, std::string destino)
{
    /// @brief busca en el arbol de carreteas esteNodo el nodo con getDestino() igual a param destino
    /// @param esteNodo raiz del arbol a consultar
    /// @param destino clave del objeto carretera buscado
    /// @return Puntero al lugar buscado o nullptr ni no se encuentra en el arbol
    Carretera *devolver;
    int diferencia;
    if (esteNodo != nullptr) // Si el nodo no es nulo sigue buscando
    {
        diferencia = funcionesArbol::comparadorCadenas(destino, esteNodo->getDestino());
        if (diferencia == 0) // Valor igual es el consultado
        {
            devolver = esteNodo;
        }
        else if (diferencia < 0) // Valores menores a la izquierda
        {
            // Se consulta si la carretera se encuentra en el subarbol izquierdo
            devolver = funcionesArbol::buscar(esteNodo->getHijoIzquierdo(), destino);
        }
        else // Valores mayores a la derecha
        {
            // Se consulta si la carretera se encuentra en el subarbol derecho
            devolver = funcionesArbol::buscar(esteNodo->getHijoDerecho(), destino);
        }
    }
    else
    { // Si el nodo es nulo, la carretera consultada no se encuentra en el arbol
        devolver = nullptr;
    }

    return devolver;
}

//************************Operacion mostrar************************

/*
    Devuelve una lista de direcciones de las carreteras del arbol ordenadas
    alfabeticamente de menor a mayor según sus claves.
*/
std::list<Carretera *> funcionesArbol::inOrden(Carretera *raiz)
{
    std::list<Carretera *> devolver;
    std::list<Carretera *> aux;
    if (raiz != NULL)
    {
        // Asignar lista de rama izquierda a actual
        devolver = inOrden(raiz->getHijoIzquierdo());
        // Insertar valor actual en lista
        devolver.push_back(raiz);
        // Fusionar lista de rama derecha a actual
        aux = inOrden(raiz->getHijoDerecho());
        for (Carretera *i : aux)
        {
            devolver.push_back(i);
        }
    }

    return devolver;
}

//************************Comparar claves************************

/*
    Devuelve un numero n segun el orden alfabetico:
        - numero < 0 -> la primera cadena es menor que la segunda
        - numero == 0 -> la primera cadena es igual a la segunda
        - numero > 0 -> la primera cadena es mayor que la segunda
*/
int funcionesArbol::comparadorCadenas(std::string primero, std::string segundo)
{
    // Convertir los string a arrays de carcateres

    /* Declarar arrays de caracteres del mismo tamaño que sus strings
       correspondientes, más el caracter de fin.
    */
    char primero_array[primero.length() + 1];
    char segundo_array[segundo.length() + 1];

    /* Copiar el contenido de los strings a las cadenas de caracteres */
    strcpy(primero_array, primero.c_str());
    strcpy(segundo_array, segundo.c_str());

    // llamar a la funcion que compara las cadenas de caracteres
    return strcmp(primero_array, segundo_array);
}
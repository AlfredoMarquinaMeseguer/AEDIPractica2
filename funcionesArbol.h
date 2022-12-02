#ifndef FUNCIONES_ARBOL_C_H
#define FUNCIONES_ARBOL_C_H

#include "Carretera.h"

class funcionesArbol
{
public:
    //************************Operaciones sobre altura y numero Nodos************************

    /*
        Calcula la altura del arbol de carreteras con raiz param arbol.*/
    static int altura(Carretera *arbol);

    /*
        Calcula el numero de nodos del arbol de carreteas con raiz  param arbol*/
    static int numNodos(Carretera *arbol);

    /*
        Calcula diferencia de altura entre sub arboles izquierdo y derecho*/
    static int diferencia(Carretera *arbol);

    //************************Rotaciones y balanceo************************

    /*
        Rotacion simple derecha o rotacion derecha-derecha*/
    static Carretera *rotacionSimpleIzquierda(Carretera *arbol);

    /*
        Rotacion simple izquierda o rotacion izquierda-izquierda*/
    static Carretera *rotacionSimpleDerecha(Carretera *arbol);

    /*
        Rotacion doble derecha o rotacion derecha-izquierda*/
    static Carretera *rotacionDobleIzquierdaDerecha(Carretera *arbol);

    /*
        Rotacion doble izquierda o rotacion izquierda-derecha*/
    static Carretera *rotacionDobleDerechaIzquierda(Carretera *arbol);

    /*
        Comprueba si el árbol cumple la condicion de balanceo y la actuliza
        sino la cumple*/
    static Carretera *balancear(Carretera *t);

    //************************Edición************************

    /*
        Devuelve la raiz del árbol de carreteras después de insertar o actualizar
        el nodo con clave destino.
    */
    static Carretera *insertar(Carretera *esteNodo, std::string destino,
                               unsigned int coste, std::string informacion);

    //************************Consulta************************

    /*
        Devuelve la direccion de carretera con clave destino. Sino se encuentra en el
        árbol, devuelve nullptr.
    */
    static Carretera *buscar(Carretera *esteNodo, std::string destino);

    //************************Operacion mostrar************************

    /*
        Devuelve una lista de direcciones de las carreteras del arbol ordenadas
        alfabeticamente de menor a mayor según sus claves.
    */
    static std::list<Carretera *> inOrden(Carretera *t);

    //************************Comparar claves************************

    /*
        Devuelve un numero n segun el orden alfabetico:
            - numero < 0 -> la primera cadena es menor que la segunda
            - numero == 0 -> la primera cadena es igual a la segunda
            - numero > 0 -> la primera cadena es mayor que la segunda
    */
    static int comparadorCadenas(std::string primero, std::string segundo);
};

#endif
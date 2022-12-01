#ifndef FUNCIONES_ARBOL_C_H
#define FUNCIONES_ARBOL_C_H

#include "Carretera.h"

class funcionesArbol
{
public:
    static Carretera *rotacionSimpleIzquierda(Carretera *arbol);
    static Carretera *rotacionSimpleDerecha(Carretera *arbol);

    static Carretera *rotate_RightLeft(Carretera *X, Carretera *Z);
    static Carretera *rotate_LeftRight(Carretera *X, Carretera *Z);

    static Carretera *rotacionDobleIzquierdaDerecha(Carretera *arbol);
    static Carretera *rotacionDobleDerechaIzquierda(Carretera *arbol);

    static Carretera *balancear(Carretera *t);
    static Carretera *insertar(Carretera *esteNodo, std::string destino,
                               unsigned int coste, std::string informacion);
    static int compareTo(Carretera *Z);

    static int altura(Carretera *arbol);
    static int diferencia(Carretera *arbol);

    static void show(Carretera *, int);
    static void inorder(Carretera *);
    // Cuando sena carretera esta funcion devuelve strings de nombre carretera
    static std::list<Carretera *> postOrden(Carretera *t);
    static void preorder(Carretera *);
    static void postorder(Carretera *);

    static int comparadorCadenas(std::string primero, std::string segundo);
};

#endif
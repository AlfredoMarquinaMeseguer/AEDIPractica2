#ifndef CARRETERA_H
#define CARRETERA_H

#include <string>

class Lugar;

class Carretera
{
private:
    // Lugar de origen viene dado por el lugar que lo contiene que salen
    // Lugar del que salen
    // Lugar *origen;

    // Lugar al que llegan
    std::string destino;

    // Coste de recorrer carretera
    unsigned int coste;

    // Informacion
    std::string informacion;

    // Nodos hijo
    Carretera *hijo_izquierdo;
    Carretera *hijo_derecho;

public:
    Carretera(std::string destino, unsigned int coste, std::string informacion)
        : destino(destino), coste(coste), informacion(informacion),
          hijo_izquierdo(nullptr), hijo_derecho(nullptr) {}

    ~Carretera();

    // destino
    std::string getDestino() { return this->destino; }
    void setDestino(std::string destino) { this->destino = destino; }

    // coste
    unsigned int getCoste() { return this->coste; }
    void setCoste(unsigned int coste) { this->coste = coste; }

    // informacion
    std::string getInformacion() { return informacion; }
    void setInformacion(std::string informacion) { this->informacion = informacion; }

    // hijo_izquierdo
    Carretera *getHijoIzquierdo() { return hijo_izquierdo; }
    void setHijoIzquierdo(Carretera *hijo_izquierdo) { this->hijo_izquierdo = hijo_izquierdo; }

    // hijo_derecho
    Carretera *getHijoDerecho() { return hijo_derecho; }
    void setHijoDerecho(Carretera *hijo_derecho) { this->hijo_derecho = hijo_derecho; }

    /*
      Escribe en un array la informacion sobre esta carretera*/
    std::string toString();
};
#endif
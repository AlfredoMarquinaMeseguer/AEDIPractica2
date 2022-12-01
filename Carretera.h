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

    //Nodos hijo
    Carretera *left_child;
    Carretera *rigth_child;

public:
    Carretera(std::string destino,unsigned int coste, std::string informacion)
     : destino(destino), coste(coste), informacion(informacion), 
     left_child(nullptr), rigth_child(nullptr) {}

    ~Carretera();
    //Descomentar si la idea sale mal
    /*
        Carretera( Lugar * &origen, Lugar * &destino,
                   unsigned int coste, std::string informacion) :
        origen(origen), destino(destino), coste(coste),
        informacion(informacion) { }

        Carretera( Lugar * &origen, Lugar * &destino,
                   unsigned int coste) :
        origen(origen), destino(destino), coste(coste),
        informacion("") { }

        // origen
        Lugar *getOrigen() { return this->origen; }
        void setOrigen(Lugar *origen) { this->origen = origen; }*/


    // destino
    std::string getDestino() { return this->destino; }
    void setDestino(std::string destino) { this->destino = destino; }

    // coste
    unsigned int getCoste() { return this->coste; }
    void setCoste(unsigned int coste) { this->coste = coste; }

    // informacion
    std::string getInformacion() { return informacion; }
    void setInformacion(std::string informacion) { this->informacion = informacion; }

    std::string toString();
    
    Carretera *getLeftChild() { return left_child; }
    void setLeftChild(Carretera *left_child) { this->left_child = left_child; }

    Carretera *getRigthChild() { return rigth_child; }
    void setRigthChild(Carretera *rigth_child) { this->rigth_child = rigth_child; }

    static void destruirRecursivamente(Carretera *Carretera);
};
#endif
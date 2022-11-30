#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <string>

#include "Lugar.h"
#include "MapaLugares.h"

using namespace std;

Lugar *lugarActual;
MapaLugares *lugares = new MapaLugares();
/*Separa los argumentos del comando, normalmente separados por comas*/
vector<string> separarParametros(string linea, char sep = ',')
{
	vector<string> resultado;
	if (linea == "")
		return resultado;
	istringstream iss(linea);
	string parametro;

	while (getline(iss, parametro, sep))
		resultado.push_back(parametro);

	if (linea[linea.length() - 1] == ',')
		resultado.push_back("");

	return resultado;
}

void escribirParametros(vector<string> params)
{
	int contador = 1;
	for (auto parametro : params)
		cout << "Parámetro " << contador++ << ": [" << parametro << "]" << endl;
}

string inicializar()
{
	lugares->vaciar();
	return "Mapa inicializado";
}

int main()
{
	// int cont = 1; // Contador actualmente obsoleto
	/*comando -> albergará los nombres de los comandos llamados
	  parametros -> alberga todos los parámetros antes de ser separados
	  totalLugares -> total de lugares añadido en el mapa de lugares*/
	string comando, parametros;
	// paramSeparados -> alberga los parámetros recibidos de la funcionSeparadora
	vector<string> paramSeparados;
	

	bool imprimir;

	// Bucle se ejecuta hasta que deje de recibir texto por consola
	while (cin >> comando)
	{

		char c = std::cin.get(); // Recibe caracter

		if (c == '\n')
		{							// Si c es /n, el comando no tiene parametros
			parametros = "";		// Se evita que las variable
			paramSeparados.clear(); // tengan parametros del comando anterior
		}
		else
		{													// Sino se reciben y separan los parametros
			getline(cin, parametros);						// Recibir
			paramSeparados = separarParametros(parametros); // Separar
		}

		// Identificacion y tratamiento de comando
		imprimir = false;
		if (comando == "Inicializar")
		{
			std::cout << inicializar() << std::endl;
		}
		else if (comando == "AñadirLugar")
		{
			lugares->insertar(paramSeparados[0], paramSeparados[1]);
			std::cout <<"Añadido: " << paramSeparados[0] << ". Total: " << lugares->getTotalLugares() << " lugares" << std::endl;	
		}
		else if (comando == "AL")
		{
			lugares->insertar(paramSeparados[0],"");
		}
		else if (comando == "ConsultarLugar")
		{
			lugarActual = lugares->consultar(paramSeparados[0]);
			if (lugarActual != nullptr)
			{
				/*Encontrado: nombre
				  Información: informacion*/
				cout << "Encontrado: "  << lugarActual->getNombre()      << endl 
				     << "Información: " << lugarActual->getInformacion() << endl;
			}else{
				//No encontrado: nombre
				cout << "No encontrado: " << paramSeparados[0] << endl;
			}
			
		}
		// Aquí anteriormente se encontraba aumento varible cont
	}

	return 0;
}
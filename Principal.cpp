#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>

#include "Carretera.h"
#include "Lugar.h"
#include "MapaLugares.h"
#include "funcionesArbol.h"

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

//Metodo utilizado en ejercicios anteriores
void escribirParametros(vector<string> params)
{
	int contador = 1;
	for (auto parametro : params)
		cout << "Parámetro " << contador++ << ": [" << parametro << "]" << endl;
}

int main()
{
	/*
		comando -> albergará los nombres de los comandos llamados
		parametros -> alberga todos los parámetros antes de ser separados*/
	string comando, parametros;
	// paramSeparados -> alberga los parámetros recibidos de la funcionSeparadora
	vector<string> paramSeparados;
	// Carretera consultada en el comando ConsultarCarretera
	Carretera *consultada;
	/*
		Booleano utilizado en el comando AñadirCarretera, indica si se añadido o actulizado 
		una carretera.*/
	bool carreteraAnnadida;
	std::string imprimir;

	std::list<Carretera *>::iterator itrAdyacentes;

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
		if (comando == "Inicializar")
		{
			// Se vacia el mapa de Lugares con el método vaciar()
			lugares->vaciar();
			// Se imprime mensaje
			std::cout << "Mapa inicializado" << std::endl;
		}
		else if (comando == "AñadirLugar")
		{
			/*
				Se inserta el lugar en el mapa de lugares:
					paramSeparados[0] -> nombre del lugar
					paramSeparados[1] -> informacion del lugar
			*/
			lugares->insertar(new Lugar(paramSeparados[0], paramSeparados[1]));
			//Imprimir mensaje;
			std::cout << "Añadido: " << paramSeparados[0] << ". Total: " << lugares->getNumeroLugares()
					  << " lugares" << std::endl;
		}
		else if (comando == "AL")
		{
			/*
				Similar al anterior, pero sin informacion del lugar ni mensaje.
				Se inserta el lugar en el mapa de lugares:
					paramSeparados[0] -> nombre del lugar
			*/
			lugares->insertar(new Lugar(paramSeparados[0]));
		}
		else if (comando == "ConsultarLugar")
		{
			/*				
				Se consulta el lugar en el mapa de lugares:
					paramSeparados[0] -> nombre del lugar, clave

				Esta funcion devuelve el puntero al lugar o nullptr si
				no se encuentra.
			*/
			lugarActual = lugares->consultar(paramSeparados[0]);

			if (lugarActual != nullptr)//Si se ha encontrado el lugar
			{
				
				// Se imprime mensaje:					
				cout << "Encontrado: " << lugarActual->getNombre() << endl
					 << "Información: " << lugarActual->getInformacion() << endl;
			}
			else // Si no se encuentra
			{
				// Se imprime mensaje:	
				cout << "No encontrado: " << paramSeparados[0] << endl;
				delete lugarActual;
			}
		}
		else if (comando == "AñadirCarretera")
		{
			/*				
				Se añade carreter al árbol del lugar si se encuentra en el mapa:
					paramSeparados[0] -> nombre del lugar (clave lugar)
					paramSeparados[1] -> nombre del destino (clave carretera)
					paramSeparados[2] -> coste de la carretera
						Se convierte de string a unsigned int 
					paramSeparados[3] -> informacion de la carretera

				Esta funcion devuelve un booleano segun si ha podido añadir la 
				carretera.
			*/
			carreteraAnnadida = lugares->annadirCarretera(paramSeparados[0], paramSeparados[1],
														  (unsigned int)stoi(paramSeparados[2]),
														  paramSeparados[3]);
			if (carreteraAnnadida) //Si se ha añadido o actualizado imprime mensaje
			{
				std::cout << "Añadido: " << paramSeparados[0] << "-" << paramSeparados[1] << ". Total: "
						  << lugares->getNumeroCarreteras() << " carreteras" << std::endl;
			}
		}
		else if (comando == "AC")
		{
			/*				
				Se añade carreter al árbol del lugar si se encuentra en el mapa:
					paramSeparados[0] -> nombre del lugar (clave lugar)
					paramSeparados[1] -> nombre del destino (clave carretera)
					paramSeparados[2] -> coste de la carretera
						Se convierte de string a unsigned int 
				
				AC no tiene paramSeparados[3] por lo que tenemos que pasarle la
				informacion vacia.
			*/
			lugares->annadirCarretera(paramSeparados[0], paramSeparados[1],
									  (unsigned int)stoi(paramSeparados[2]),
									  "");
		}
		else if (comando == "ConsultarCarretera")
		{
			/*				
				Se consulta si existe una carretera en el árbol de un lugar:
					paramSeparados[0] -> nombre del lugar (clave lugar)
					paramSeparados[1] -> nombre del destino (clave carretera)					
				
				Esta funcion devuelve un puntero a Carretera, si no se encuentra
				devuelve un puntero nullptr.
			*/
			consultada = lugares->consultarCarretera(paramSeparados[0], paramSeparados[1]);

			if (consultada != nullptr) //Si se ha encontrado
			{
				//Imprime mensaje, nombre carretera = origen-destino
				std::cout << "Encontrado: " << paramSeparados[0] << "-" << paramSeparados[1] << std::endl
						  << "Coste: " << consultada->getCoste() << std::endl
						  << "Información: " << consultada->getInformacion() << std::endl;
			}
			else //Si no se ha encontrado
			{
				std::cout << "No encontrado: " << paramSeparados[0] << "-" << paramSeparados[1] << std::endl;
			}
		}
		else if (comando == "ListarAdyacentes")
		{
			/*				
				Se listan todos las carreteras del árbol del lugar:
					paramSeparados[0] -> nombre del lugar (clave lugar)
				
				Esta funcion devuelve una lista de punteros.
				Si la lista está vacia, el lugar no existe.
				Si la lista tiene un solo elemento y es nullptr, es porque no
				tiene carreteras.
			*/
			std::list<Carretera *> consultada = lugares->listarAdyacentes(paramSeparados[0]);

			if (!consultada.empty())// Si el lugar existe
			{
				imprimir = "";// Aquí parasemos a string la lista para imprimir por pantalla

				if (consultada.front() != nullptr)//Si el lugar tiene alguna carretera
				{	
					/* 
						Iteramos por la lista para obtener los valores de destino y pasarlos
						a string.
					*/
					itrAdyacentes = consultada.begin();
					while (itrAdyacentes != consultada.end())
					{
						// Además de los destinos se añaden separadores ", " al string
						imprimir += (*itrAdyacentes)->getDestino() + ", ";
						itrAdyacentes++;
					}
					/* 
						Se eliminan ", " del final del string, añadidos por el 
						último ciclo del bucle.
					*/
					imprimir.pop_back();
					imprimir.pop_back();
				}

				//Imprime mensaje
				std::cout << "Encontrado: " << paramSeparados[0] << std::endl
						  << "Adyacentes: " << imprimir << std::endl;
			}
			else //Si el lugar no existe
			{
				//Imprime mensaje
				std::cout << "No encontrado: " << paramSeparados[0] << std::endl;
			}
		}
	}

	return 0;
}

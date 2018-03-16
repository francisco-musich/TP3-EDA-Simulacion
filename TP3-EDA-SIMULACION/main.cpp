#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;

//INCLUIR LIBRERIAS ALLEGRO

//INCLUIR HEADERS
#include "simulacion.h"
#include"robot.h"
#include"piso.h"

//INCLUIR PARSER Y CALLBACK

#include"callback.h"
#include"parseCmdLine.h"


int main()
{
	//INICIALIZAR ALLEGRO

	userParams userData; //crear estructura para el parser
	parseCmdline(argc, argv, callback, &userData); //Llamo al parser(hay que hacerlo)  
	srand(time(NULL));

	if (userData.modo == MODO1)
	{
		simulacion simu(userData.cant_robots, userData.filas, userData.columnas, userData.modo); //Creo objeto simulacion

		simu.run();	//corro simulacion
		simu.~simulacion(); //destruyo simulacion
	}
	else
	{
		double ticks_promedio[MAX_SIMS]; //arreglo donde guardo todos los promedios
		for (int i = 2; i < MAX_ROBOTS; i++)	//falta agregar condicional s(n-1)-s(n)<1
		{
			double sum = 0.0;
			for (int cant_sim = 0; cant_sim < MAX_SIMS; cant_sim++)
			{
				simulacion simu(parametros);
				sum +=simu.run();
				simu.~simulacion();
			}
			ticks_promedio[i] = sum / 1000;
			// funcion_grafica_analitica();  //falta implementar
		}
	}

}
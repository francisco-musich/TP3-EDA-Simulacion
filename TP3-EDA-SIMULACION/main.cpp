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

int main()
{
	//INICIALIZAR ALLEGRO

	userParams userData; //crear estructura para el parser
	parseCmdline(argc, argv, callback, &userData); //Llamo al parser
	srand(time(NULL));

	if (userData.modo == MODO1)
	{
		simulacion simu(userData.cant_robots, userData.filas, userData.columnas, usearData.modo); //Creo objeto simulacion

		simu.run();
		simu.destroy();
	}
	else
	{
		double ticks_promedio[MAX_SIMS]; //arreglo donde guardo todos los promedios
		for (int i = 2; i < MAX_ROBOTS; i++)
		{
			double sum = 0.0;
			for (int cant_sim = 0; cant_sim < MAX_SIMS; cant_sim++)
			{
				simulacion simu(parametros);
				sum +=simu.run();
				simu.destroy();
			}
			ticks_promedio[i] = sum / 1000;
		}
	}

}
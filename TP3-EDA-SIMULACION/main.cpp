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
#include "estructura.h"

int main(int argc, char *argv[])
{
	//INICIALIZAR ALLEGRO

	userInput_t userData; //crear estructura para el parser
	switch (parseCmdLine(argc, argv, &organizeInfo, &userData))
	{
	case ERRORTYPE1:
		printf("Error type 1\n");

		break;
	case ERRORTYPE2:
		printf("Error type 2\n");

		break;

	case ERRORTYPE3:
		printf("Error type 3\n");

		break;
	}
	srand(time(NULL));

	if (userData.modo == MODO1)
	{
		simulacion simu(userData.cant_robots, userData.width, userData.height, userData.modo); //Creo objeto simulacion

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
				simulacion simu(userData.cant_robots, userData.width, userData.height, userData.modo);
				sum +=simu.run();
				simu.~simulacion();
			}
			ticks_promedio[i] = sum / 1000;
			// funcion_grafica_analitica();  //falta implementar
		}
	}

}
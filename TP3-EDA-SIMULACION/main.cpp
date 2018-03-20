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
	unsigned int test;
	userInput_t userData; //crear estructura para el parser
	switch (parseCmdLine(argc, argv, &organizeInfo, &userData))
	{
	case ERRORTYPE1:
		printf("Error type 1\n");
		while (getchar() != '\n');	//Afrefo asi no desaparece la consola
		break;
	case ERRORTYPE2:
		printf("Error type 2\n");
		while (getchar() != '\n');
		break;

	case ERRORTYPE3:
		printf("Error type 3\n");
		while (getchar() != '\n');
		break;
	}
	srand(time(NULL));

	if (userData.modo == MODO1)
	{
		simulacion simu(userData.cant_robots, userData.height, userData.width, userData.modo); //Creo objeto simulacion

		test = simu.run();	//corro simulacion
		simu.~simulacion(); //destruyo simulacion
	}
	else if (userData.modo == MODO2)
	{
		double ticks_promedio[MAX_SIMS]; //arreglo donde guardo todos los promedios
		for (int i = 2; i < MAX_ROBOTS; i++)	//falta agregar condicional s(n-1)-s(n)<1
		{
			double sum = 0.0;
			for (int cant_sim = 0; cant_sim < MAX_SIMS; cant_sim++)
			{
				simulacion simu(userData.cant_robots, userData.width, userData.height, userData.modo);
				sum += simu.run();
				simu.~simulacion();
			}
			ticks_promedio[i] = sum / 1000;
			// funcion_grafica_analitica();  //falta implementar
		}
	}
	printf("TEST = %d", test);
	while (getchar() != '\n');
}
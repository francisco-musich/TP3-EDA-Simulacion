#include<stdlib.h>
#include<iostream>
#include<time.h>

using namespace std;

//INCLUIR LIBRERIAS ALLEGRO

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

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

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_BITMAP *piso_sucio = NULL;
	ALLEGRO_BITMAP *piso_limpio = NULL;
	ALLEGRO_BITMAP *robot = NULL;

	if (!al_init()) {
		fprintf(stderr, "Couldn't initialize allegro!\n");
		return -1;
	}

	if (!al_init_image_addon()) {
		printf( "Failed to initialize al_init_image_addon! \n");
		return 0;
	}

	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Couldn't initialize primitives addon!\n");
		return -1;
	}
	display = al_create_display(H, W);
	if (!display) {
		fprintf(stderr, "Couldn't create allegro display!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

	//ALLEGRO INICIALIZADO
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
		printf("");
	}
	else if (userData.modo == MODO2)
	{
		double ticks_promedio[MAX_SIMS]; //arreglo donde guardo todos los promedios
		for (int i = 2; i < MAX_ROBOTS; i++)	//falta agregar condicional s(n-1)-s(n)<1
		{
			double sum = 0.0;
		
			for (int cant_sim = 0; cant_sim < MAX_SIMS; cant_sim++)
			{
				simulacion simu(i, userData.width, userData.height, userData.modo);
				sum += simu.run();			
				simu.~simulacion();
				
			}
			ticks_promedio[i] = sum / MAX_SIMS;
			printf("ticks promedio = %f, cantidad robots = %d", (sum / MAX_SIMS),i);
			while (getchar() != '\n');
			// funcion_grafica_analitica();  //falta implementar
		}
		printf("hola");
	}
	
	while (getchar() != '\n');
}
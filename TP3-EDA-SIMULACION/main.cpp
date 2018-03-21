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
#include "robot.h"
#include "piso.h"
#include "display.h"

//INCLUIR PARSER Y CALLBACK

#include"callback.h"
#include"parseCmdLine.h"
#include "estructura.h"

//PROTOTIPOS FUNCIONES INTERNAS
bool are_parametres_ok(userInput_t userData);


int main(int argc, char *argv[])
{
	//INICIALIZAR ALLEGRO

	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_BITMAP *piso_sucio = NULL;
	ALLEGRO_BITMAP *piso_limpio = NULL;
	ALLEGRO_BITMAP *robot_imagen = NULL;

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
	//Cargo Imagenes

	piso_limpio = al_load_bitmap("piso_limpio.jpg");	
	if (!piso_limpio)
	{
		printf("Error piso limpio");
		while (getchar() != '\n');
		return 0;
	}
	piso_sucio = al_load_bitmap("piso_sucio.jpg");
	if (!piso_sucio)
	{
		printf("Error piso sucio");
		while (getchar() != '\n');
		return 0;
	}
	robot_imagen = al_load_bitmap("rooma.jpg");
	if (!robot_imagen)
	{
		printf("Error robot");
		while (getchar() != '\n');
		return 0;
	}



	//ALLEGRO INICIALIZADO
	unsigned int test;
	userInput_t userData = { 0,0,0,0 }; //crear estructura para el parser


	switch (parseCmdLine(argc, argv, &organizeInfo, &userData))
	{
	case ERRORTYPE1:
		printf("Error type 1\n");
		while (getchar() != '\n');	//Afrefo asi no desaparece la consola
		return 0;
	case ERRORTYPE2:
		printf("Error type 2\n");
		while (getchar() != '\n');
		return 0;

	case ERRORTYPE3:
		printf("Error type 3\n");
		while (getchar() != '\n');
		return 0;
	}
	
	srand(time(NULL));

	double  valori = LADO_BALDOSA_MAX; //valor inicial del lado de baldosa
	while (userData.height*valori > TAM_MAX_DISPLAY || userData.width * valori >TAM_MAX_DISPLAY) //si el largo total o altura total superior es mayor a 1000, se divide valori por 2
	{
		valori = valori / 2;
	}

	double H = userData.height * valori;
	double W = userData.width * valori;

	if (are_parametres_ok(userData))
	{
		if (userData.modo == MODO_A)
		{
			double valor_ticks;
			display = al_create_display(H, W);
			if (!display) {
				fprintf(stderr, "Couldn't create allegro display!\n");
				return -1;
			}

			al_clear_to_color(al_map_rgb(0, 0, 0));

			simulacion simu(userData.cant_robots, userData.height, userData.width, userData.modo, H, W); //Creo objeto simulacion

			valor_ticks = simu.run(valori, robot_imagen, piso_sucio, piso_limpio);	//corro simulacion
			///simu.~simulacion(); //destruyo simulacion
			printf("La simulacion termino correctamente\n Los %d robots hand terminado en %5.0f ticks \n", userData.cant_robots, valor_ticks);
		}
		else if (userData.modo == MODO_B)
		{
			double ticks_promedio[MAX_SIMS]; //arreglo donde guardo todos los promedios

			int count_zer_Arr = 0;
			while (count_zer_Arr < MAX_SIMS)
			{
				ticks_promedio[count_zer_Arr++] = 0;
			}

			display = al_create_display(TAM_DISPLAY, TAM_DISPLAY);
			if (!display) {
				fprintf(stderr, "Couldn't create allegro display!\n");
				return -1;
			}

			al_clear_to_color(al_map_rgb(0, 0, 0));
			int j;
			for (int i = 2, j = 0; i < MAX_ROBOTS; i++, j++)	//falta agregar condicional s(n-1)-s(n)<1
			{

				double sum = 0.0;

				for (int cant_sim = 0; ((cant_sim < MAX_SIMS)/*&&( (ticks_promedio[i-2]-ticks_promedio[i-3]) > 0,1) )*/); cant_sim++)
				{
					/*if((ticks_promedio[i - 1] - ticks_promedio[i - 2]) <=  1)
					{
					break;
					}*/
					simulacion simu(i, userData.width, userData.height, userData.modo, H, W);
					sum += simu.run(valori, robot_imagen, piso_sucio, piso_limpio);
					simu.~simulacion();

				}
				ticks_promedio[j] = sum / MAX_SIMS;
				if (abs(ticks_promedio[j - 1] - ticks_promedio[j]) <= 0.1)
				{
					break;
				}
				//printf("ticks promedio = %f, cantidad robots = %d", (sum / MAX_SIMS),i);
				//while (getchar() != '\n');
				diagramabarras(i, ticks_promedio);
				al_rest(0.05);
				al_clear_to_color(al_map_rgb(0, 0, 0));
			}
			printf("Modo analitico finalizado. Se muestra el grafico con los ticks promedio en funcion de la cantidad de robots.\n");
		}
	}
	else
	{
		printf("Parametros incorrectos, por favor revise su entrada \n");
	}
	al_destroy_bitmap(piso_limpio);
	al_destroy_bitmap(piso_sucio);
	al_destroy_bitmap(robot_imagen);
	
	printf("Oprima enter para salir \n");
	//al_destroy_display(display);
	while (getchar() != '\n');
	al_destroy_display(display);
}


bool are_parametres_ok(userInput_t userData)
{
	bool ret_value = false;
	if ((userData.modo == 1) && ((userData.height) && (userData.width)) && (userData.cant_robots))
		ret_value = true;
	else if ((userData.modo == 2) && ((userData.height) && (userData.width)))
		ret_value = true;
	return ret_value;
}
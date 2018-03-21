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
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

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
bool init_al(ALLEGRO_DISPLAY ** display, ALLEGRO_BITMAP **piso_sucio, ALLEGRO_BITMAP **piso_limpio, ALLEGRO_BITMAP **robot_imagen, ALLEGRO_SAMPLE ** musica1, ALLEGRO_SAMPLE ** musica2);


int main(int argc, char *argv[])
{
	//INICIALIZAR ALLEGRO

	ALLEGRO_DISPLAY *display = NULL;

	ALLEGRO_BITMAP *piso_sucio = NULL;
	ALLEGRO_BITMAP *piso_limpio = NULL;
	ALLEGRO_BITMAP *robot_imagen = NULL;
	ALLEGRO_SAMPLE * musiquita = NULL;
	ALLEGRO_SAMPLE * sonido_robot = NULL;


	if (!init_al(&display, &piso_sucio, &piso_limpio, &robot_imagen, &musiquita, &sonido_robot))
		return -1;

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

		valor_ticks = simu.run(valori,robot_imagen, piso_sucio, piso_limpio, sonido_robot);	//corro simulacion
		///simu.~simulacion(); //destruyo simulacion
		printf("La simulacion termino correctamente\n Los %d robots hand terminado en %5.0f ticks \n",userData.cant_robots,valor_ticks);
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
					sum += simu.run(valori, robot_imagen, piso_sucio, piso_limpio, sonido_robot);
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
	ALLEGRO_SAMPLE_ID musica_id;
	al_play_sample(musiquita, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &musica_id);
	while (getchar() != '\n');
	al_stop_sample(&musica_id);
	al_destroy_sample(musiquita);
	al_destroy_sample(sonido_robot);
	al_destroy_display(display);
	al_uninstall_audio();
}

bool init_al(ALLEGRO_DISPLAY ** display, ALLEGRO_BITMAP **piso_sucio, ALLEGRO_BITMAP **piso_limpio, ALLEGRO_BITMAP **robot_imagen, ALLEGRO_SAMPLE ** musica1, ALLEGRO_SAMPLE ** musica2) {

	if (!al_init()) {
		fprintf(stderr, "Couldn't initialize allegro!\n");
		return false;
	}

	if (!al_init_image_addon()) {
		printf("Failed to initialize al_init_image_addon! \n");
		return false;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Couldn't initialize primitives addon!\n");
		return false;
	}
	//Cargo Imagenes

	*piso_limpio = al_load_bitmap("piso_limpio.jpg");
	if (!piso_limpio)
	{
		printf("Error piso limpio");
		while (getchar() != '\n');
		return false;
	}
	*piso_sucio = al_load_bitmap("piso_sucio.jpg");
	if (!piso_sucio)
	{
		printf("Error piso sucio");
		while (getchar() != '\n');
		return false;
	}
	*robot_imagen = al_load_bitmap("rooma.jpg");
	if (!robot_imagen)
	{
		printf("Error robot");
		while (getchar() != '\n');
		return false;
	}
	if ( !al_install_audio())
	{
		printf("Error audio");
		while (getchar() != '\n');
		return false;
	}
	if( !al_init_acodec_addon())
	{
		printf("Error audio codec");
		while (getchar() != '\n');
		return false;
	}
	if( !al_reserve_samples(2))
	{
		printf("Error al cargar los samples");
		while (getchar() != '\n');
		return false;
	}

	*musica1 = al_load_sample("piano.wav");
	*musica2 = al_load_sample("aspiradora.wav");

	return true;
}
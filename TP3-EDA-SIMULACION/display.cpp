#include "display.h"
#include"robot.h"
#include<cstdlib>

#define PI 3.14159265

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <math.h>


double maximo(double * arregloR, int cantidad_robots);
/*
	double  valori = 200; //valor inicial del lado de baldosa
	while (FIL*valori > 2000 || COL * valori >2000) //si el largo total o altura total superior es mayor a 1000, se divide valori por 2
	{
		valori = valori / 2;
	}
	double H = FIL * valori;
	double W = COL * valori;

	ALLEGRO_DISPLAY *display = NULL;
	if (!al_init()) {
		fprintf(stderr, "Couldn't initialize allegro!\n");
		return -1;
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Couldn't initialize primitives addon!\n");
		return -1;
	}
	display = al_create_display(H2, W2);
	if (!display) {
		fprintf(stderr, "Couldn't create allegro display!\n");
		return -1;
	}
	al_clear_to_color(al_map_rgb(0, 0, 0));

		//* Ejemplo de uso 2 - variables que use para simular un arreglo de robots con distintos promedios de ticks


		const unsigned int Nrobots = 21;
		double arregloR[Nrobots];
		arregloR[0] = 3438.30;
		arregloR[1] = 931.56;
		arregloR[2] = 543.1;
		arregloR[3] = 321.9;
		arregloR[4] = 45.9;
		arregloR[5] = 35.9;
		arregloR[6] = 35.9;	
		arregloR[7] = 35.9;		
		arregloR[8] = 350.9; 
		arregloR[9] = 35.9; 
		arregloR[10] = 35.9; 
		arregloR[11] = 931.56;
		arregloR[12] = 543.1;
		arregloR[13] = 321.9;
		arregloR[14] = 45.9;
		arregloR[15] = 35.9;
		arregloR[16] = 35.9;
		arregloR[17] = 35.9;
		arregloR[18] = 350.9;
		arregloR[19] = 35.9;
		arregloR[20] = 35.9;


		diagramabarras(Nrobots, arregloR);

		al_rest(15.0);
		
		//int arreglo[FIL][COL];
		

		arreglo[3][1] = 1;
		displaypiso(FIL, COL, arreglo, H, W);
		al_flip_display();
		al_rest(15.0);

}

*/

void diagramabarras(int cantidad_robots, double * arregloR)
{
	
	double easyx = H2 / 8.0;
	double easyy = W2 / 8.0;
	double maximoticks = maximo(arregloR, cantidad_robots); 	//funcion que da el maximoticks
	double x1 = easyx * 6 / (double) cantidad_robots; //constante para escalar el eje 
	unsigned int c = 255 / cantidad_robots; //constante que escala cambio de color

	ALLEGRO_FONT* font = al_create_builtin_font();


	al_draw_line(easyx, easyy*7, easyx, easyy, al_map_rgb(255, 0, 255), 1); //carga los 2 ejes
	al_draw_line(easyx, easyy*7, easyx*7, easyy*7, al_map_rgb(255, 0, 255), 1);

	for (int i = 1; i <= cantidad_robots; i++) //Carga los numeros de los robots en el display
	{
		al_draw_textf(font, al_map_rgb(255, 0, 255), easyx + (i*x1), easyy*7, ALLEGRO_ALIGN_LEFT, "%d",i);
	}

	int cap = 0;
	int div = 100;
	int j = 0; //cantidad de divisiones del eje
	while (maximoticks > cap)
	{
		cap += div;
		j++;
	}
	while (j > 10)	//reduce la cantidad de divisiones para que no sean mas de 10
	{
		j = (j / 2);
		div = div * 2;
	}

	for (int i = 1; i <= j; i++) //Carga los ticks en el display
	{
		int m = div * (easyy * 6) / cap;
		al_draw_textf(font, al_map_rgb(255, 0, 255), easyx, easyy * 7 - (m*i), ALLEGRO_ALIGN_LEFT, "%d", i*div);
	}

	for (int i = 0; i < cantidad_robots; i++) //carga los cuadrados en el display
	{
		double h = arregloR[i] * (easyy * 6) / maximoticks; //constante que escala los ticks
		al_draw_filled_rectangle((easyx - (x1 / 3)) + ((i + 1)*x1), easyy * 7, (easyx + (x1 / 3)) + ((i + 1)*x1), easyy * 7 - h, al_map_rgb(150, 255 - i * c, 150));
	}


	al_flip_display();
}



void displaypiso(piso &floor, ALLEGRO_BITMAP * piso_sucio, ALLEGRO_BITMAP * piso_limpio, double valori)
{
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for (int i = 0; i < floor.get_filas(); i++)
	{
		for (int j = 0; j < floor.get_columnas(); j++)
		{
			if(floor.state_tile(i, j))
					//al_draw_filled_rectangle(i * (H / cantidad_filas), j * (W / cantidad_columnas), i * (H / cantidad_filas) + ((H / cantidad_filas) - 1), j * (W / cantidad_columnas) + ((W / cantidad_columnas) - 1), al_map_rgb(155, 50, 155));
					al_draw_scaled_bitmap(piso_limpio, 0, 0, al_get_bitmap_width(piso_limpio), al_get_bitmap_height(piso_limpio), i * (floor.get_H() /floor.get_filas()), j * (floor.get_W() / floor.get_columnas()), valori - 1, valori - 1, 0);
				else
					//al_draw_filled_rectangle(i * (H / cantidad_filas), j * (W / cantidad_columnas), i * (H / cantidad_filas) + ((H / cantidad_filas) - 1), j * (W / cantidad_columnas) + ((W / cantidad_columnas) - 1), al_map_rgb(255, 0, 255));
					al_draw_scaled_bitmap(piso_sucio, 0, 0, al_get_bitmap_width(piso_sucio), al_get_bitmap_height(piso_sucio), i * (floor.get_H() / floor.get_filas()), j * (floor.get_W() / floor.get_columnas()), valori - 1, valori - 1, 0);


		}
	}
	
}

double maximo(double * arregloR, int cantidad_robots)
{
	double h = 0;

	for (int i = 0; i < cantidad_robots; i++)
	{

		if (h <= arregloR[i])
			h = arregloR[i];

	}

	return h;
}

void displayR(robot * rob_handler ,unsigned int cantidad_robots, double valori, ALLEGRO_BITMAP * bitmap)
{
	for (int i = 0; i < cantidad_robots; i++)
	{
		int x = floor(rob_handler[i].get_posicion_x());
		int y = floor(rob_handler[i].get_posicion_y());
		
		//al_draw_filled_rectangle(y*valori + (valori / 5),  (x*valori) + (valori / 5), (y + 1)*valori - (valori / 5),  ((x + 1) * valori) - (valori / 5), (al_map_rgb(0, 0, 255)));
		al_draw_scaled_bitmap(bitmap, 0, 0, al_get_bitmap_width(bitmap), al_get_bitmap_height(bitmap), y*valori + (valori / 10), (x*valori) + (valori / 10), valori * 5 /6 , valori * 5 / 6, 0);

	}
	
}
#include "display.h"
#include<cstdlib>

#define PI 3.14159265

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdio.h>
#include <math.h>

/*cosas que hay que meter en el main
ALLEGRO_DISPLAY *display = NULL;
if(!al_init()) {
fprintf(stderr, "Couldn't initialize allegro!\n");
return -1;
}
if(!al_init_primitives_addon()) {
fprintf(stderr, "Couldn't initialize primitives addon!\n");
return -1;
}
display = al_create_display(H,W);
if(!display) {
fprintf(stderr, "Couldn't create allegro display!\n");
return -1;
}
al_clear_to_color(al_map_rgb(0, 0, 0));
*/

/* Ejemplo de uso 2 - variables que use para simular un arreglo de robots con distintos promedios de ticks

const unsigned int Nrobots = 6;
double arregloR[Nrobots];
arregloR[0] = 1438.30;
arregloR[1] = 931.56;
arregloR[2] = 543.1;
arregloR[3] = 321.9;
arregloR[4] = 45.9;
arregloR[5] = 35.9;
diagramabarras(Nrobots, arregloR);
*/

/* Ejemplo de uso 1 -
inicializarpiso(FIL,COL,arreglo);
al_flip_display();
al_rest(5.0);
arreglo[3][1] = 1;
displaypiso(FIL, COL, arreglo);
al_flip_display();
al_rest(15.0);
*/


void diagramabarras(unsigned int cantidad_robots, double * arregloR)
{
	double easyx = H / 8.0;
	double easyy = W / 8.0;
	double maximoticks = maximo(arregloR, cantidad_robots); 	//funcion que da el maximoticks
	double x1 = easyx * 6 / cantidad_robots; //constante para escalar el eje 
	unsigned int c = 255 / cantidad_robots; //constante que escala cambio de color

	ALLEGRO_FONT* font = al_create_builtin_font();


	al_draw_line(easyx, easyy * 7, easyx, easyy, al_map_rgb(255, 0, 255), 1); //carga los 2 ejes
	al_draw_line(easyx, easyy * 7, easyx * 7, easyy * 7, al_map_rgb(255, 0, 255), 1);

	for (int i = 1; i <= cantidad_robots; i++) //Carga los numeros de los robots en el display
	{
		al_draw_textf(font, al_map_rgb(255, 0, 255), easyx + (i*x1), easyy * 7, ALLEGRO_ALIGN_LEFT, "%d", i);
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

void inicializarpiso(unsigned int cantidad_filas, unsigned int cantidad_columnas, int arreglo[FIL][COL])
{

	for (int i = 0; i < cantidad_filas; i++)
	{
		for (int j = 0; j < cantidad_columnas; j++)
		{
			arreglo[i][j] = 0; //esto puede ya estar en el main
			al_draw_filled_rectangle(i * (H / cantidad_filas), j * (W / cantidad_columnas), i * (H / cantidad_filas) + ((H / cantidad_filas) - 1), j * (W / cantidad_columnas) + ((W / cantidad_columnas) - 1), al_map_rgb(255, 0, 255));
		}
	}

}

void displaypiso(unsigned int cantidad_filas, unsigned int cantidad_columnas, int arreglo[FIL][COL])
{
	for (int i = 0; i < cantidad_filas; i++)
	{
		for (int j = 0; j < cantidad_columnas; j++)
		{
			if (arreglo[i][j] == 1)
				al_draw_filled_rectangle(i * (H / cantidad_filas), j * (W / cantidad_columnas), i * (H / cantidad_filas) + ((H / cantidad_filas) - 1), j * (W / cantidad_columnas) + ((W / cantidad_columnas) - 1), al_map_rgb(155, 50, 155));
			else
				al_draw_filled_rectangle(i * (H / cantidad_filas), j * (W / cantidad_columnas), i * (H / cantidad_filas) + ((H / cantidad_filas) - 1), j * (W / cantidad_columnas) + ((W / cantidad_columnas) - 1), al_map_rgb(255, 0, 255));
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
#pragma once
#include "robot.h"
#include"piso.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define TIMER_TICK (1/24)

class simulacion
{
public:
	//////////////////////////
	///////simulacion/////////
	//////////////////////////
	/*
	Constructor.

	INPUT:
			1) cant_robots : cantidad de robots con los cuales se correrá la simulación
			2) filas : cantidad de filas con las que se maneja el piso para la simulación
			3) columnas : cantidad de columnas con las que se maneja el piso para la simulación
			4) H : altura del display a utilizar en la simulación
			5) W : ancho del display a utilizar en la simulación
	OUTPUT:
			void.
	*/
	simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, int modo,double H, double W);
	~simulacion();

	//////////////////////////
	///////////run////////////
	//////////////////////////
	/*
	Se corre la simulacion con display grafico.

	INPUT:
	1) valori : 
	2) bitmap_robot : foto que se utilizara para mostrar la posicion del robot durante la simulacion.
	3) piso_sucio : foto que se utilizara para mostrar la baldosa de piso sucio durante la simulacion.
	4) piso_limpio : foto que se utilizara para mostrar la baldosa de piso limpio durante la simulacion.
	5) musica : musica de fondo que se correra con la simulacion.

	OUTPUT:
			void.
	*/
	unsigned int run(double valori, ALLEGRO_BITMAP * robot_image, ALLEGRO_BITMAP * piso_sucio, ALLEGRO_BITMAP * piso_limpio, ALLEGRO_SAMPLE * sonido_move);

private:

	piso f;						//piso donde se correra la simulacion
	robot * rob_handler;		//nose
	unsigned int ticks;
	int mode;					//modo en que se eligio correr la simulacion
	unsigned int nro_robots;	//numero de robots con los que se corre la simulacion
};
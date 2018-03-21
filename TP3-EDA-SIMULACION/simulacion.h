#pragma once
#include "robot.h"
#include"piso.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>


#define TIMER_TICK (1/24)

class simulacion
{
public:
	simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, int modo,double H, double W);
	~simulacion();
	unsigned int run(double valori, ALLEGRO_BITMAP * bitmap_robot,ALLEGRO_BITMAP * piso_sucio, ALLEGRO_BITMAP*piso_limpio);


private:

	piso f;						//piso donde se correra la simulacion
	robot * rob_handler;		//nose
	unsigned int ticks;
	int mode;					//modo en que se eligio correr la simulacion
	unsigned int nro_robots;	//numero de robots con los que se corre la simulacion
};
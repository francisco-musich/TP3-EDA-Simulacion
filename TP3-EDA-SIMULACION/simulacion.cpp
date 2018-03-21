#include "simulacion.h"
#include "estructura.h"
#include "display.h"
#include<stdlib.h>
#include<cstdio>
#include<cmath>
#include <Windows.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

simulacion::simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, int modo,double H,double W)
	:f(filas, columnas,H,W)
{
	//f.iniciar(filas, columnas);
	rob_handler = (robot*)calloc(cant_robots, sizeof(robot));  //Creo malloc con cantidad de robots necesarios para crear
	if (rob_handler == NULL)
	{
		//ERROR AL ALOCAR LA MEMORIA!
		f.~piso();				//destruyo el piso porque no lo utilizare mas.
	}
	else
	{
		for (int i = 0; i < cant_robots; i++)
		{
			rob_handler[i] = robot(f.get_filas(), f.get_columnas());  //nose como usar el constructor explicitamente, ni si se usa asi
		}
		nro_robots = cant_robots;
		mode = modo;
	}
	//return (rob_handler == NULL);
}

unsigned int simulacion::run(double valori, ALLEGRO_BITMAP * robot_image, ALLEGRO_BITMAP * piso_sucio, ALLEGRO_BITMAP * piso_limpio)
{
	unsigned int nro_ticks = 0;
	if (mode == MODO_A)		//Decido modo 1 i modo 2
	{
		while (f.isDirty()) //Modo SImulacion
		{
			/*
			displaypiso(f,piso_sucio,piso_limpio,valori); //Funcion grafica
			displayR(rob_handler, nro_robots, valori,robot_image);
			al_flip_display();
			//Sleep(TIMER_TICK * 1000); //Hay que verlo a ojo.
			al_rest(0.2);*/
			for (int i = 0; i < nro_robots; i++)	//muevo todos los robots a su nueva direccion
			{
				rob_handler[i].mover(f.get_filas(), f.get_columnas()); //muevo el robot
				f.clean(floor(rob_handler[i].get_posicion_x()), floor(rob_handler[i].get_posicion_y()));	//limpio la baldosa corrspondiente
			}
			al_rest(0.3);
			displaypiso(f, piso_sucio, piso_limpio, valori); //Funcion grafica
			displayR(rob_handler, nro_robots, valori, robot_image);
			al_flip_display();
			
			nro_ticks++;
		}
		
		
	}
	else if(mode == MODO_B)
	{
		while (f.isDirty()) //Modo analitico
		{
			for (int i = 0; i < nro_robots; i++)	//muevo todos los robots a su nueva direccion
			{
				rob_handler[i].mover(f.get_filas(), f.get_columnas());
				f.clean(floor(rob_handler[i].get_posicion_x()), floor(rob_handler[i].get_posicion_y()));	//limpio la baldosa corrspondiente
			}
			nro_ticks++;
		}
	}
	return nro_ticks;
	free(rob_handler);
}

simulacion::~simulacion() {}
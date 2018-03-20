#pragma once
#include "robot.h"
#include"piso.h"

#define TIMER_TICK (1/24)
class simulacion
{
public:
	simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, int modo);
	~simulacion();
	unsigned int run();


private:

	piso f;						//piso donde se correra la simulacion
	robot * rob_handler;		//nose
	unsigned int ticks;
	int mode;					//modo en que se eligio correr la simulacion
	unsigned int nro_robots;	//numero de robots con los que se corre la simulacion
};
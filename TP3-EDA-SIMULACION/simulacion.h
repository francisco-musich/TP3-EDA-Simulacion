#pragma once
#include "robot.h"
#include"piso.h"

#define TIMER_TICK (1/24)
class simulacion
{
public:
	simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, bool modo);
	~simulacion();
	unsigned int run();



private:

	piso f;
	robot * rob_handler; //nose
	unsigned int ticks;
	bool mode;
	unsigned int nro_robots;
};


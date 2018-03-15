#pragma once
#include "robot.h"
#include"piso.h"

class simulacion
{
public:
	simulacion(unsigned int cant_robots, unsigned int filas, unsigned int columnas, bool modo);
	~simulacion();
	unsigned int run();



private:

	piso f;
	robot * rob_handler;
	unsigned int ticks;
	bool mode;
	unsigned int nro_robots;
};


#include "robot.h"
#include<cstdlib>
#include <math.h>

#define PI 3.14159265


robot::robot(unsigned int cantidad_filas, unsigned int cantidad_columnas)
{
	posicion_x = (rand() % (cantidad_columnas - 1)); //asigno posicion al azar en x.(resto 1 asi no me voy de las baldosas)
	posicion_y = (rand() % (cantidad_filas/* - 1*/)); //asigno posicion al azar en y
	direccion = (2.0*randZeroToOne()) * PI; //Asigno angulo al azar
}

void robot::mover(unsigned int cantidad_filas, unsigned int cant_columnas)
{
	double temp_x = posicion_x;
	double temp_y = posicion_y;
	posicion_x += (cos(direccion)); //Asigno nueva posicion al robot. La unidad(hipotenusa) es de 1.
	posicion_y += (sin(direccion));
	if ((posicion_x >= cant_columnas) || (posicion_y >= cantidad_filas) || (posicion_x < 0) || (posicion_y < 0))  //Chequeo que la nueva posicion no salga de los parametros
	{
		posicion_x = temp_x;	//mantengo la posicion en la que estaba antes
		posicion_y = temp_y;
		direccion = (2.0*randZeroToOne()) * PI; //Asigno angulo al azar
	}
	return;

}

double robot::get_posicion_x()
{
	double res;
	res = posicion_x;

	return res;
}

double robot::get_posicion_y()
{
	double res;
	res = posicion_y;

	return res;
}



robot::~robot()
{
}

double randZeroToOne()
{
	return rand() / (RAND_MAX + 1.);
}
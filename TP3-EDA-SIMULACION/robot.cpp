#include "robot.h"
#include<cstdlib>

#define PI 3.14159265


robot::robot(unsigned int cantidad_filas, unsigned int cantidad_columnas)
{
	posicion.x = (rand() % (cantidad_columnas - 1)); //asigno posicion al azar en x.(resto 1 asi no me voy de las baldosas)
	posicion.y = (rand() % (cantidad_filas - 1)); //asigno posicion al azar en y
	direccion = (rand() % (2.0 * PI)); //Asigno angulo al azar
}

void robot::mover(unsigned int cantidad_filas,unsigned int cant_columnas )
{
	double temp_x = posicion.x;
	double temp_y = posicion.y;
	posicion.x += (cos(direccion)); //Asigno nueva posicion al robot. La unidad(hipotenusa) es de 1.
	posicion.y += (sin(direccion));
	if ((posicion.x > cant_columnas) || (posicion.y > cantidad_filas) || (posicion.x < 0) || (posicion.y < 0))  //Chequeo que la nueva posicion no salga de los parametros
	{
		posicion.x = temp_x;
		posicion.y = temp_y;
		direccion = (rand() % (2.0 * PI)); //Asigno angulo al azar
	}
	return;

}

punto_t robot::get_posicion()
{
	punto_t res;
	res.x = posicion.x;
	res.y = posicion.y;
	return res;
}

robot::~robot()
{
}

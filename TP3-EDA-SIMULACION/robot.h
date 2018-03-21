#pragma once
class robot
{
public:
	//////////////////////////
	///////////robot////////////
	//////////////////////////
	/*
	constructor

	INPUT:
	1) cantidad_filas : cantidad de filas maximas para la posicion del robot al azar
	2) cantidad_columnas : cantidad de columnas maximas para la posicion del robot al azar

	OUTPUT:
	void.
	*/
	robot(unsigned int cantidad_filas, unsigned int cantidad_columnas); //Funcion constructora
	~robot();

	//////////////////////////
	///////////mover////////////
	//////////////////////////
	/*
		mueve al robot aleatriamente
		
	INPUT:
	1) cantidad_filas : cantidad de filas maximas del piso.
	2) cantidad_columnas : cantidad de columnas maximas del piso.

	OUTPUT:
	void.
	*/
	void mover(unsigned int cantidad_filas, unsigned int cant_columnas);
	//getters para las coordenas actuales del robot
	double get_posicion_x();
	double get_posicion_y();	

private:
	//posicion del robot en el piso, coordenadas
	double posicion_x;			
	double posicion_y;
	double direccion;		//angulo con el que se movera respecto de su posicion actual el robot en el siguiente tick.
};
double randZeroToOne();
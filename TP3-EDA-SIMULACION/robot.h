#pragma once
class robot
{
public:
	robot(unsigned int cantidad_filas, unsigned int cantidad_columnas); //Funcion constructora
	~robot();
	void mover(unsigned int cantidad_filas, unsigned int cant_columnas);
	double get_posicion_x();
	double get_posicion_y();

private:
	double posicion_x;
	double posicion_y;
	double direccion;
};
double randZeroToOne();
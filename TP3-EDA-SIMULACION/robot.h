#pragma once
class robot
{
public:
	robot(unsigned int cantidad_filas,unsigned int cantidad_columnas); //Funcion constructora
	~robot();
	void mover(unsigned int cantidad_filas, unsigned int cant_columnas);
	punto_t get_posicion();

private:
	punto_t posicion;
	double direccion;
};

typedef struct
{
	double x;
	double y;
}punto_t;


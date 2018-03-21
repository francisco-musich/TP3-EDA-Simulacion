#pragma once
class piso
{
public:

	piso(unsigned int cantidad_filas2, unsigned int cantidad_columnas2,double H, double W);//constructora de piso
	~piso();
	bool clean(int x, int y);  //Usada para limpiar baldosas
	bool isDirty();	//funcion que te devuelve si todo el piso esta limpio
	bool state_tile(int x, int y); //FALTA HACERLA DEVUELVE EL ESTADO DE LA BALDOSA
	unsigned int get_filas();	//getter cantidad de filas
	unsigned int get_columnas();	//getter cantidad de columnas
	double get_H();	//getter alto display segun cantidad de filas
	double get_W();	//getter width display segun cantidad de columnas

private:
	bool ** tiles; //puntero para apuntar al futuro piso. true-> tile limpia false-> tile sucia
	unsigned int cantidad_filas;
	unsigned int cantidad_columnas;
	double H; //height display segun cantidad de filas
	double W; //width display segun cantidad de columnas

};
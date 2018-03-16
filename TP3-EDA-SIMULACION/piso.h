#pragma once
class piso
{
public:
	piso(unsigned int cantidad_filas, unsigned int cantidad_columnas);//constructora de piso
	~piso();
	bool clean(int x,int y);  //Usada para limpiar baldosas
	bool isDirty();	//funcion que te devuelve si todo el piso esta limpio
	bool state_tile(int x, int y); //FALTA HACERLA DEVUELVE EL ESTADO DE LA BALDOSA
	unsigned int get_filas();	//getter cantidad de filas
	unsigned int get_columnas();	//getter cantidad de columnas


private:
	bool ** tiles; //puntero para apuntar al futuro piso
	unsigned int cantidad_filas; 
	unsigned int cantidad_columnas; 

};


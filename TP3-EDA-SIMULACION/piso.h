#pragma once
class piso
{
public:
	piso(unsigned int cantidad_filas, unsigned int cantidad_columnas);
	~piso();
	bool clean();  //Usada para limpiar baldosas
	bool isDirty();	//funcion que te devuelve si todo el piso esta limpio
	unsigned int get_filas();	//getter cantidad de filas
	unsigned int get_columnas();	//getter cantidad de columnas


private:
	bool * tiles; //puntero para apuntar al futuro piso
	unsigned int cantidad_filas; //Nose para que estan, pero el pibe las agrego
	unsigned int cantidad_columnas; 

};


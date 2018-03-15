#pragma once
class piso
{
public:
	piso();
	~piso();
	bool clean();
	bool isDirty();
	unsigned int get_filas();
	unsigned int get_columnas();


private:
	bool * tiles; //puntero para apuntar al futuro piso
	unsigned int cantidad_filas; //Nose para que estan, pero el pibe las agrego
	unsigned int cantidad_columnas; 

};


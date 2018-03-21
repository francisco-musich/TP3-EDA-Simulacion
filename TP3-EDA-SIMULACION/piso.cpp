#include<cstdlib>
#include<cstdio>
#include "piso.h"


piso::piso(unsigned int cantidad_filas2, unsigned int cantidad_columnas2,double H2,double W2)
{	//creo matriz dinamica que contiene bools 1(limpio) 0 (sucio)
	tiles = (bool**)calloc(cantidad_filas2, sizeof(bool*));		//Primero creo un arreglo que contiene punteros a punteros a bool
	for (int i = 0; i < cantidad_filas2; i++)
	{
		tiles[i] = (bool*)calloc(cantidad_filas2, sizeof(bool));	// lleno ese arreglo con punteros a arreglos de memoria dinamicos
	}//para acceder a un valor usar tiles[i][j] MUCHISIMO CUIDADO QUE COMO ES UN MALLOC SI SE ME PASAN LOS I Y J HAGO QUILOMBO
	cantidad_columnas = cantidad_columnas2;
	cantidad_filas = cantidad_filas2;
	H = H2;
	W = W2;
}


bool piso::clean(int x, int y)
{
	bool validez = true;
	if ((x > cantidad_columnas) || (y > cantidad_filas) || (x < 0) || (y < 0))	//chequeo parametros
	{
		validez = false;
	}
	else
	{
		tiles[y][x] = true; //pongo en verdad(limpio) esa baldosa
		//printf("baldosa y=%d, x=%d limpia \n", y, x);

	}
	return validez;
}

bool piso::isDirty()
{
	bool sucio= false;
	for (int i = 0; i < cantidad_filas; i++)	//loopeo toda la matriz del piso a ver si esta sucio
	{
		for (int j = 0; j < cantidad_columnas; j++)
		{
			if (!tiles[i][j])	//si se encuentra un false(sucio) se pierde la validez
				sucio = true;
		}
	}
	if (!sucio)
	{
		free(tiles);
	}
	return sucio;
}


unsigned int piso::get_filas()
{
	return cantidad_filas;
}

unsigned int piso::get_columnas()
{
	return cantidad_columnas;
}

double piso::get_H()
{
	return H;
}
double piso::get_W()
{
	return W;
}

bool piso::state_tile(int x, int y)	//Devuelve el estado de la baldosa, true(limpia)  false (sucia)
{
	return tiles[x][y];
}

piso::~piso()
{
	//free(tiles); //nose si tengo que liberar los otros mallocs apuntados por este malloc
}
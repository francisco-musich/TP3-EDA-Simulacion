#include<cstdlib>
#include "piso.h"

//hola

piso::piso(unsigned int cantidad_filas, unsigned int cantidad_columnas)
{	//creo matriz dinamica que contiene bools 1(limpio) 0 (sucio)
	tiles = (bool**)calloc(cantidad_filas, sizeof(bool*));		//Primero creo un arreglo que contiene punteros a punteros a bool
	for (int i = 0; i < cantidad_filas;i++)
	{
		tiles[i] = (bool*)calloc(cantidad_filas, sizeof(bool));	// lleno ese arreglo con punteros a arreglos de memoria dinamicos
	}//para acceder a un valor usar tiles[i][j] MUCHISIMO CUIDADO QUE COMO ES UN MALLOC SI SE ME PASAN LOS I Y J HAGO QUILOMBO
}

bool piso::clean(int x, int y)
{
	bool validez = true;
	if ((x > cantidad_filas) || (y > cantidad_columnas) || (x < 0) || (y < 0))	//chequeo parametros
	{
		validez = false;
	}
	else
	{
	tiles[x][y] = true; //pongo en verdad(limpio) esa baldosa
	}
	return validez;
}

bool piso::isDirty()
{
	bool validez;
	for (int i = 0; i < cantidad_filas; i++)	//loopeo toda la matriz del piso a ver si esta sucio
	{
		for (j = 0; j < cantidad_columnas; j++)
		{
			if (!tiles[i][j])	//si se encuentra un false(sucio) se pierde la validez
				validez = false;
		}
	}
	return validez;
}


unsigned int piso::get_filas()
{
	return cantidad_filas;
}

unsigned int piso::get_columnas()
{
	return cantidad_columnas;
}

piso::~piso()
{
}

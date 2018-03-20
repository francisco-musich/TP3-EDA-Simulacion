#include<cstdlib>
#include "piso.h"


piso::piso(unsigned int cantidad_filas, unsigned int cantidad_columnas)
{	//creo matriz dinamica que contiene bools 1(limpio) 0 (sucio)
	tiles = (bool**)calloc(cantidad_filas, sizeof(bool*));		//Primero creo un arreglo que contiene punteros a punteros a bool
	for (int i = 0; i < cantidad_filas; i++)
	{
		tiles[i] = (bool*)calloc(cantidad_filas, sizeof(bool));	// lleno ese arreglo con punteros a arreglos de memoria dinamicos
	}//para acceder a un valor usar tiles[i][j] MUCHISIMO CUIDADO QUE COMO ES UN MALLOC SI SE ME PASAN LOS I Y J HAGO QUILOMBO
}

bool piso::iniciar(unsigned int cantidad_fila, unsigned int cantidad_columna)
{
	bool ret = true;
	tiles = (bool**)calloc(cantidad_fila, sizeof(bool*));		//Primero creo un arreglo que contiene punteros a punteros a bool
	if (tiles)
	{
		for (int i = 0; i < cantidad_fila; i++)
		{
			tiles[i] = (bool*)calloc(cantidad_columna, sizeof(bool));	// lleno ese arreglo con punteros a arreglos de memoria dinamicos
		}
		cantidad_columnas = cantidad_columna;	//cambiar nombre de variables!!!
		cantidad_filas = cantidad_fila;
	}
	else
	{
		ret = false;
	}
	return ret;
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

bool piso::state_tile(int x, int y)	//Devuelve el estado de la baldosa, true(limpia)  false (sucia)
{
	return tiles[x][y];
}

piso::~piso()
{
	//free(tiles); //nose si tengo que liberar los otros mallocs apuntados por este malloc
}
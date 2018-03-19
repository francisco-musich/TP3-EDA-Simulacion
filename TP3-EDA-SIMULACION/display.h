#pragma once

#define MAX_ROBOTS 1

#define COL 5 //despues ver si son fijas y no las cambian los profes, porque si metes 2 numeros distintos no son cuadradas
#define FIL 5
#define H 1000
#define W 1000


void inicializarpiso(unsigned int cantidad_filas, unsigned int cantidad_columnas, int arreglo[FIL][COL]); //carga 0 en cada valor del arreglo y carga en el display el piso

void displaypiso(unsigned int cantidad_filas, unsigned int cantidad_columnas, int arreglo[FIL][COL]); //funcion para actualizar el display del piso
//OJO, el arreglo fila 1 columna 3 va a ser simetricamente opuesto diagonalmente, ya que el 0,0 esta en la esquina superior izquiera, sin embargo no lo altere porque no importa como estan ordenadas las filas y columnas mientras se tengan las cordenadas

void diagramabarras(unsigned int cantidad_robots, double * arregloR);

double maximo(double * arregloR, int cantidad_robots); //devuelve el mayor numero de ticks que hizo un robot
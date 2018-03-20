#pragma once

#define MAX_ROBOTS 1

#define H2 1000
#define W2 1000

#define FIL 120
#define COL 70




void displaypiso(unsigned int cantidad_filas, unsigned int cantidad_columnas, int arreglo[FIL][COL]); //funcion para actualizar el display del piso
//OJO, el arreglo fila 1 columna 3 va a ser simetricamente opuesto diagonalmente, ya que el 0,0 esta en la esquina superior izquiera, sin embargo no lo altere porque no importa como estan ordenadas las filas y columnas mientras se tengan las cordenadas

void diagramabarras(unsigned int cantidad_robots, double * arregloR, double H, double W);

double maximo(double * arregloR, int cantidad_robots); //devuelve el mayor numero de ticks que hizo un robot
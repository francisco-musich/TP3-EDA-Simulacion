#pragma once
#include"piso.h"
#include "robot.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>

#define H2 1000
#define W2 1000

#define FIL 120
#define COL 70




void displaypiso(piso &floor,ALLEGRO_BITMAP * piso_sucio, ALLEGRO_BITMAP * piso_limpio, double valori); //funcion para actualizar el display del piso
//OJO, el arreglo fila 1 columna 3 va a ser simetricamente opuesto diagonalmente, ya que el 0,0 esta en la esquina superior izquiera, sin embargo no lo altere porque no importa como estan ordenadas las filas y columnas mientras se tengan las cordenadas

void diagramabarras(int cantidad_robots,double * arregloR);

double maximo(double * arregloR, int cantidad_robots); //devuelve el mayor numero de ticks que hizo un robot

void displayR(robot * rob_handler, unsigned int cantidad_robots,double valori,ALLEGRO_BITMAP *bitmap);
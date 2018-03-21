#pragma once

typedef struct {
	int height ;
	int width;
	int cant_robots;
	int modo;
}userInput_t;

enum modos {MODO_A=1, MODO_B};

#define ERRORTYPE1 1
#define ERRORTYPE2 2
#define ERRORTYPE3 3
#define myNOERROR 4

#define MAX_SIMS 1000
#define MAX_ROBOTS 1000

#define LADO_BALDOSA_MAX 200
#define TAM_MAX_DISPLAY 1200

#define TAM_DISPLAY 1200
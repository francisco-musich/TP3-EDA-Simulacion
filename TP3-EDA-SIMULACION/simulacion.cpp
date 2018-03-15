#include "simulacion.h"
#include<stdlib.h>


simulacion::simulacion(unsigned int cant_robots,unsigned int filas,unsigned int columnas, bool modo)
{
	// f.create();  //Creo que se hace implicitamente
	rob_handler =(robot*) calloc(cant_robots * sizeof(robot));
	if (!rob_handler)
	{
		for (int i = 0; i < cant_robots; i++)
		{
			rob_handler[i].create();
		}
		nro_robots = cant_robots;
	}
	else
	{
		piso();
	}
	return (rob_handler == NULL);
}

unsigned int simulacion::run()
{
	unsigned int nro_ticks = 0;
	while (f.isDirty())
	{
		for (int i = 0; i < nro_robots; i++)	//muevo todos los robots a su nueva direccion
		{
			rob_handler[i].mover(f.get_filas(),f.get_columnas());
		}
		sleep(TIEMPO_TICK); //Hay que verlo a ojo
		imprimir_piso(rob_handler, nro_robots, f); //Funcion grafica. Mando puntero asi sacas la informacion directo de ahi, nose si se puede. 
		nro_ticks++;
	}
	return nro_ticks;
}


simulacion::~simulacion()
{
}

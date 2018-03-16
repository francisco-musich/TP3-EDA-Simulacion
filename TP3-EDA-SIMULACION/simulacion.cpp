#include "simulacion.h"
#include<stdlib.h>


simulacion::simulacion(unsigned int cant_robots,unsigned int filas,unsigned int columnas, bool modo)
{
	// f.create();  //Creo que se hace implicitamente
	rob_handler =(robot*) calloc(cant_robots * sizeof(robot));  //Creo malloc con cantidad de robots necesarios para crear
	if (!rob_handler)
	{
		for (int i = 0; i < cant_robots; i++)
		{
			rob_handler[i].create();  //nose como usar el constructor explicitamente, ni si se usa asi
		}
		nro_robots = cant_robots;
		mode = modo;
	}
	else
	{
		 f.~piso();	//creo que es el destructor
	}
	return (rob_handler == NULL);
}

unsigned int simulacion::run()
{
	unsigned int nro_ticks = 0;
	if (mode)
	{	
		while (f.isDirty()) //Modo SImulacion
		{
			for (int i = 0; i < nro_robots; i++)	//muevo todos los robots a su nueva direccion
			{
				rob_handler[i].mover(f.get_filas(), f.get_columnas());
			}
			sleep(TIEMPO_TICK); //Hay que verlo a ojo
			imprimir_piso(rob_handler, nro_robots, f); //Funcion grafica. Mando puntero asi sacas la informacion directo de ahi, nose si se puede. 
			nro_ticks++;
		}
	}
	else
	{
		while (f.isDirty()) //Modo analitico
		{
			for (int i = 0; i < nro_robots; i++)	//muevo todos los robots a su nueva direccion
			{
				rob_handler[i].mover(f.get_filas(), f.get_columnas());
			}
			nro_ticks++;
		}
	}
	return nro_ticks;
}


simulacion::~simulacion()
{
}

#include "simulacion.h"
#include<stdlib.h>
#include<cmath>


simulacion::simulacion(unsigned int cant_robots,unsigned int filas,unsigned int columnas, bool modo)
{
	// f.create();  //Creo que se hace implicitamente
	rob_handler =(robot*) calloc(cant_robots * sizeof(robot));  //Creo malloc con cantidad de robots necesarios para crear
	if (!rob_handler)
	{
		for (int i = 0; i < cant_robots; i++)
		{
			rob_handler[i]=robot(f.get_filas,f.get_columnas);  //nose como usar el constructor explicitamente, ni si se usa asi
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
				rob_handler[i].mover(f.get_filas(), f.get_columnas()); //muevo el robot
				f.clean(floor(rob_handler[i].get_posicion_x()),floor(rob_handler[i].get_posicion_y()));	//limpio la baldosa corrspondiente
			}
			
			sleep(TIEMPO_TICK); //Hay que verlo a ojo
			//imprimir_piso( f); //Funcion grafica.
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
	free(rob_handler);
}

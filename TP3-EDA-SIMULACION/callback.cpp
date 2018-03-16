#include "callback.h"
#include "estructura.h"

int organizeInfo(char * pass, char * value, void * userData)
{
	userInput_t * usr = (userInput_t *)userData;
	bool retValue = true;
	if (pass)
	{
		if ((!usr->modo) && !strcmp(_strlwr((char *)pass), "modo"))
		{
			if (!strcmp(_strlwr((char *)value), "1") || !strcmp(_strlwr((char *)value), "2"))
				usr->modo = atoi(value);
	
			else
				retValue = ERRORTYPE3;
		}
		else if (!(usr->height) && !strcmp(_strlwr((char *)pass), "height"))
		{
			if ((atoi(value) <= 100) && (atoi(value) >= 0))
				usr->height = atoi(value);
			else
				retValue = ERRORTYPE3;
		}
		else if (!(usr->width) && !strcmp(_strlwr((char *)pass), "width"))
		{
			if ((atoi(value) <= 70) && (atof(value) > 0))
				usr->width = atoi(value);
			else
				retValue = ERRORTYPE3;
		}
		else if (!(usr->cant_robots) && !strcmp(_strlwr((char *)pass), "n"))
		{
			if (atoi(value) > 0)
				usr->cant_robots = atoi(value);
			else
				retValue = ERRORTYPE3;
		}
		
		else
			retValue = ERRORTYPE3;  // This error means that the user used an incorrect keyword
	}
	else
		retValue = ERRORTYPE3;

	return  retValue;
}

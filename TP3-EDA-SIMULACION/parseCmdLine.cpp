#include "parseCmdLine.h"
#include "estructura.h"

int parseCmdLine(int argc, char * argv[], pCallback p, void * userData)
{
	int retValue = myNOERROR;
	char * keyword = NULL;
	int ammountOptions = 0;
	for (int i = 1; (retValue == myNOERROR) && (i < argc); i = i + 2)
	{
		if (argv[i][0] == '-')			// This part handles the input of the keyword. If there is no keyword it will 
			if (argv[i][1] != 0)					// set the keyword value to NULL or if it is just a '-' it will return error type 2
				keyword = (char *)argv[i] + 1;
			else
				retValue = ERRORTYPE2;

		if (keyword && ((i + 1) == argc))	// This parts verifies that the last word isn't a keyword. If it is, it will
			retValue = ERRORTYPE1;			// return error type 1

		if (retValue == myNOERROR)
		{
			retValue = (*p)(keyword, (char *)(i + 1 == argc ? argv[i] : argv[i + 1]), userData);
			if (keyword)
				ammountOptions += 1;
			keyword = NULL;
		}
	}
	if (argc == 1)
		retValue = ERRORTYPE3;

	return (retValue == myNOERROR ? ammountOptions : retValue);
}
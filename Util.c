#include "Util.h"
#include <stdio.h>
#include <stdlib.h>

void fail(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(-1);
}

void trim(char *string)
{
	char *s = string;

	while(*s) s++;

	s--;

	while(*s == '\n' || *s == ' ') 
	{
		*s-- = '\0';
	}
}

#include <Grammar.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		puts("Invalid number of arguments, must be one");
		return 0;
	}
		
	Symbol* symbols = tokenizeString(argv[1]);
	
	printf("Parsing result : \n");
	
	while(*symbols)
	{
		printf("%s\n", *symbols);
		symbols++;
	}
}

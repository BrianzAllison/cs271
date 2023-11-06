/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{		

	if(argc < 2){
		printf("Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	FILE *fin = fopen(argv[1], "r");

	if (fin == NULL){
		perror("Cannot open the file!");
		exit(EXIT_FAILURE);
	}
	parse(fin);
	fclose(fin);
	
	return 0;
			
}



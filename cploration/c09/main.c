/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include "error.h"
#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, const char *argv[])
{		

	if(argc != 2){
		// incorrect number of arguemnts
		exit_program(EXIT_INCORRECT_ARGUMENTS, argv[0]);
	}

	FILE *fin = fopen(argv[1], "r");

	if (fin == NULL){
		exit_program(EXIT_CANNOT_OPEN_FILE, argv[1]);
	}
	parse(fin);
	symtable_display_table();
	symtable_print_labels();
	fclose(fin);
	
	return 0;
			
}



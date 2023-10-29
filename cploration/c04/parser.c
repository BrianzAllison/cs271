/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"

/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */

line[MAX_LINE_LENGTH] = {0};

char *strip(char *s){	
	char s_new[sizeof(s)+1];
	i = 0;
	for (char *s2 = s, *s2; s2++){
		
	}
	
	
    return s;	
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
void parse(FILE * file){
	while (fgets(line, sizeof(line), file)){
		strip(line);
		if(*line == NULL){
			continue;
		}
		printf("%s\n", line);
	}
}
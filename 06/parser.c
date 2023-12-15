/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


/* Function: strip
 * -------------
 * remove whitespace and comments from a line
 *
 * s: the char* string to strip
 *
 * returns: the stripped char* string
 */



char *strip(char *s){	
	char s_new[strlen(s) + 1];
	int i = 0;
	for (char *s2 = s; *s2; s2++){
		if((*s2 == '/') && (*(s2 + 1) == '/')){
			break;
		} else if (!isspace(*s2)){
			s_new[i++] = *s2;
		}
	}
	s_new[i] = '\0';
	
	strcpy(s,s_new);
    return s;	
}

bool is_Atype(const char *line){
	return line[0] == '@';
}
bool is_label(const char *line){
	int size = strlen(line);
	return (line[0] == '(') && (line[size - 1] == ')');
}
bool is_Ctype(const char *line){
	return !(is_Atype(line) || is_label(line));
}
char *extract_label(const char *line, char* label){
	int i = 0;
	for(const char *s = line; *s; s++){
		if(*s=='(' || *s==')'){
			continue;
		} else{
			label[i++] = *s;
		}
	}
	return label;

}

void add_predefined_symbols(){
		for(int i = 0; i < NUM_PREDEFINED_SYMBOLS; i++){
			predefined_symbol symbol = predefined_symbols[i];
			symtable_insert(symbol.name, symbol.address);
		}
	}

bool parse_A_instruction(const char *line, a_instruction *instr){
		char *s = (char*) malloc(strlen(line));
		strcpy(s, line + 1);
		char *s_end = NULL;
		long result = strtol(s, &s_end, 10);

		if(s == s_end){
			instr -> operand.label = (char*) malloc(strlen(line));
			strcpy(instr->operand.label, s);
			instr->is_addr = false;
		} else if(*s_end != 0){
			return false;
		} else{
			instr->operand.address = result;
			instr->is_addr = true;
		}
		return true;
	}
void parse_C_instruction(char *line, c_instruction *instr){
	char *temp = strtok(line, ";");

	char *jump = strtok(NULL, ";");

	char *dest = strtok(NULL, "=");
	char *comp = strtok(NULL, "=");

	if(comp == NULL){
		comp = dest;
		dest = NULL;
	}
	int *a = 0;
	instr->comp = str_to_compid(comp, a);
	instr->jump = str_to_jumpid(jump);
	instr->dest = str_to_destid(dest);
	instr->a = (*a = 0) ? 0x1 : 0x0;
}

/* Function: parse
 * -------------
 * iterate each line in the file and strip whitespace and comments. 
 *
 * file: pointer to FILE to parse
 *
 * returns: nothing
 */
 int parse(FILE * file, instruction *instructions){
	char line[MAX_LINE_LENGTH] = {0};
	instruction instr;
	unsigned int line_num = 0;
	unsigned int instr_num = 0;
	add_predefined_symbols();
	while(fgets(line, sizeof(line), file)){
		line_num = line_num + 1;
		if(instr_num > MAX_INSTRUCTIONS){
			exit_program(EXIT_TOO_MANY_INSTRUCTIONS, MAX_INSTRUCTIONS + 1);
		}
		strip(line);
		
		if(!*line){
			continue;
		}

		char inst_type = ' ';

		if(is_Atype(line)){
			inst_type = 'A';
			if (!parse_A_instruction(line, &instr.instr.a_instr)){
    			exit_program(EXIT_INVALID_A_INSTR, line_num, line);
 			}
 			instr.itype = A_Type;
		} else if(is_Ctype(line)){
			inst_type = 'C';
			char tmp_line[MAX_LINE_LENGTH] = {0};
			strcpy(tmp_line, line);
			parse_C_instruction(tmp_line, &instr.instr.c_instr);
			if(instr.instr.c_instr.comp == COMP_INVALID){
				exit_program(EXIT_INVALID_C_COMP);
			} else if (instr.instr.c_instr.dest == DEST_INVALID){
				exit_program(EXIT_INVALID_C_DEST);
			} else if (instr.instr.c_instr.jump == JMP_INVALID){
				exit_program(EXIT_INVALID_C_JUMP);
			}
			instr.itype = C_Type;
		} else if(is_label(line)){
			inst_type = 'L';
			char label[MAX_LABEL_LENGTH] = {0};
			strcpy(line, extract_label(line, label));
			//printf("%c  %s\n", inst_type, label);
			if(!isalpha(label[0])){
				exit_program(EXIT_INVALID_LABEL, line_num, line);
			} else if(symtable_find(label) != NULL){
				exit_program(EXIT_SYMBOL_ALREADY_EXISTS, line_num, line);
			}
				symtable_insert(label, instr_num);
				continue;

		}
		
		//printf("%c  %s\n", inst_type, line);
		instructions[instr_num++] = instr;
	}
	return instr_num;


}

void assemble(const char * file_name, instruction* instructions, int num_instructions){
	char * file_name_hack = "";
	strcpy(file_name_hack, file_name);
	strcat(file_name_hack, ".hack");
	FILE *ba = fopen(file_name_hack, "w");
	for(int i = 0; i < num_instructions; i++){
		instruction confirm = instruction[i];
		opcode confirm_code = 0;

		if(confirm.a_instr.label){
			Symbol* entry = symtable_find(confirm.a_instr.label);
			if(entry == NULL){
				int16_t numbers = 16;
				symtable_insert(confirm.a_instr.label, numbers);
				confirm_code = numbers;
			} else{
				confirm_code = entry->address;
			}
			free(confirm.a_instr.label);
		} else if (confirm.a_instr.is_addr){
			confirm_code = confirm.a_instr.address;
		} else if (confirm.instr_type == C_Type){
			confirm_code = instruction_to_opcode(instructions->c_instr);
		}
		fclose(ba);
	}
}
opcode instruction_to_opcode(c_instruction instr){
	opcode op = 0;
	op |= (7 << 13);
	op |= (a_instr << 12);
	op |= (instr.comp << 7)
	op |= (instr.dest << 4)
	op |= (instr.jump);
	return op;
}
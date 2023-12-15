/****************************************
 * C-ploration 4 for CS 271
 * 
 * [NAME] $Brian Allison$
 * [TERM] FALL $2023$
 * 
 ****************************************/
#ifndef __PARSER_H__
#define __PARSER_H__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include "symtable.h"
#include "hack.h"
#include "error.h"

#define MAX_LINE_LENGTH  200
#define MAX_LABEL_LENGTH MAX_LINE_LENGTH - 2
#define MAX_HACK_ADDRESS INT16_MAX
#define MAX_INSTRUCTIONS MAX_HACK_ADDRESS

typedef int16_t hack_addr;
typedef int16_t opcode;

typedef enum instr_type{
    Invalid = -1,
    A_Type,
    C_Type,
} instr_type;
typedef struct c_instruction{
    opcode a:1;
    opcode comp:7;
    opcode dest:4;
    opcode jump:4;
} c_instruction;

typedef struct a_instruction{
    union{
        hack_addr address;
        char * label;
    } operand;
    bool is_addr;
} a_instruction;

typedef struct instruction{
    union{
        a_instruction a_instr;
        c_instruction c_instr;
    } instr;
    instr_type itype;
} instruction;

/** function prototypes

    needing more work.

 **/
char *strip(char *s);

int parse(FILE * file, instruction *instructions);

bool is_Atype(const char*);
bool is_label(const char*);
bool is_Ctype(const char*);
char *extract_label(const char *line, char* label);

//void add_predefined_symbols();
bool parse_A_instruction(const char *line, a_instruction *instr);
void parse_C_instruction(char *line, c_instruction *instr);

#endif
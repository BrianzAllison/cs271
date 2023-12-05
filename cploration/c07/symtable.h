#ifndef __SYMTABLE_H__
#define __SYMTABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include "error.h"
#include "parser.h"

#define SYMBOL_TABLE_SIZE 1000

typedef int16_t hack_addr;


typedef struct Symbol{
    char *name;
    hack_addr address;
};

int hash(char *str);
struct Symbol *symtable_find(char *key);
void symtable_insert(char *key, hack_addr addr);
void symtable_display_table();
void symtable_print_labels();

#endif




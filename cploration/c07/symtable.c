#include "symtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>


struct Symbol* hashArray[SYMBOL_TABLE_SIZE];
struct Symbol* item;

void symtable_display_table(){
    int i = 0;
    for (i = 0; i<SYMBOL_TABLE_SIZE; i++){
        if(hashArray[i] != NULL){
            printf(" (%s,%d)", hashArray[i]->name, hashArray[i]->address);
        else
            printf(" ~~ ");
        
        }
        printf("\n");

}
}

void symtable_insert(char *key, hack_addr addr) {

   struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
   item->address = addr;  
   item->name = key;

   //get the hash 
   int hashIndex = hashCode(key);

   //move in array until an empty or deleted cell
   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->name != NULL) {
      //go to next cell
      ++hashIndex;
		
      //wrap around the table
      hashIndex %= SYMBOL_TABLE_SIZE;
   }
   hashArray[hashIndex] = item;
}

struct Symbol *find(char *str){
    int hashIndex = hashCode(str);

    while(hashArray[hashIndex] != NULL){
        if(hashArray[hashIndex] ->name == str)
        return hashArray[hashIndex];

        ++hashIndex;

        hashIndex %= SYMBOL_TABLE_SIZE;
    }
    return NULL;
}

 unsigned int hashCode(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *key++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash % SYMBOL_TABLE_SIZE;
    }

void symtable_print_table() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->address);
        }
   }
} 


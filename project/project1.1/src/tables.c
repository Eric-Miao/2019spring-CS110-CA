
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "tables.h"

const int SYMBOLTBL_NON_UNIQUE = 0;
const int SYMBOLTBL_UNIQUE_NAME = 1;

/*******************************
 * Helper Functions
 *******************************/

void allocation_failed() {
    write_to_log("Error: allocation failed\n");
    exit(1);
}

void addr_alignment_incorrect() {
    write_to_log("Error: address is not a multiple of 4.\n");
}

void name_already_exists(const char* name) {
    write_to_log("Error: name '%s' already exists in table.\n", name);
}

void write_sym(FILE* output, uint32_t addr, const char* name) {
    fprintf(output, "%u\t%s\n", addr, name);
}

/*******************************
 * Symbol Table Functions
 *******************************/

/* Creates a new SymbolTable containg 0 elements and returns a pointer to that
   table. Multiple SymbolTables may exist at the same time. 
   If memory allocation fails, you should call allocation_failed(). 
   Mode will be either SYMBOLTBL_NON_UNIQUE or SYMBOLTBL_UNIQUE_NAME. You will need
   to store this value for use during add_to_table().
 */
SymbolTable* create_table(int mode) {
  SymbolTable *t=malloc(sizeof(SymbolTable));
  /*exit when allocation_failed*/
  if(t==NULL)allocation_failed();

  /*default*/
  t->len=0;
  t->mode=mode;
  t->head=NULL;
  return t;
}

/* Frees the given SymbolTable and all associated memory. */
void free_table(SymbolTable* table) {
  Symbol *nt,*tp;
  if(table==NULL)return;
  /*free from last of the label*/
  if(table->head!=NULL){
    for(nt=table->head;nt!=NULL;nt=tp){
      tp=nt->next;
      free(nt->name);
      free(nt);
    }
  }
  free(table);
}

/* Adds a new symbol and its address to the SymbolTable pointed to by TABLE. 
   1. ADDR is given as the byte offset from the first instruction. 
   2. The SymbolTable must be able to resize itself as more elements are added. 

   3. Note that NAME may point to a temporary array, so it is not safe to simply
   store the NAME pointer. You must store a copy of the given string.

   4. If ADDR is not word-aligned, you should call addr_alignment_incorrect() 
   and return -1. 

   5. If the table's mode is SYMTBL_UNIQUE_NAME and NAME already exists 
   in the table, you should call name_already_exists() and return -1. 

   6.If memory allocation fails, you should call allocation_failed(). 

   Otherwise, you should store the symbol name and address and return 0.
 */
int add_to_table(SymbolTable* table, const char* name, uint32_t addr) {
  if(table==NULL){
    write_to_log("Error: input table is NULL.\n");
  }

  Symbol* nsym=malloc(sizeof(Symbol));
  if(nsym==NULL)allocation_failed();

  /*addr not aligned*/
  if(addr%4!=0){
    addr_alignment_incorrect();
    free(nsym);
    return -1;
  }

  /*insert to the last of labels*/
  if(table->mode==SYMBOLTBL_UNIQUE_NAME){
    if(get_addr_for_symbol(table,name)!=-1){
      /*exsit when repeated*/
      free(nsym);
      name_already_exists(name);
      return -1;
    }
  }

  /*copy a piece of name*/
  char *n_name=malloc(strlen(name)+5);
  strcpy(n_name,name);
  
  if(table->head!=NULL){
    table->head->prev=nsym;
  }

  /*set new symbol correct*/
  nsym->next=table->head;
  nsym->prev=NULL;
  nsym->addr=addr;
  nsym->name=n_name;

  /*insert to the table tail*/
  table->head=nsym;
  table->len++;
  return 0;
}

/* Returns the address (byte offset) of the given symbol. If a symbol with name
   NAME is not present in TABLE, return -1.
 */
int64_t get_addr_for_symbol(SymbolTable* table, const char* name) {
  if(table==NULL||name==NULL)return -1;
  Symbol* n;
  /*search from back of the labels*/
  for(n=table->head;n!=NULL;n=n->next){
    if(strcmp(name,n->name)==0){
      return n->addr;
    }
  }
  return -1;
}

/* Writes the SymbolTable TABLE to OUTPUT. You should use write_sym() to
   perform the write. Do not print any additional whitespace or characters.
 */
void write_table(SymbolTable* table, FILE* output) {
  Symbol* n;
  if(table==NULL||output==NULL)return;

  /*get the first label addr*/
  if(table->head==NULL)return;
  for(n=table->head;n->next!=NULL;n=n->next){
  }

  /*output in order*/
  for(;n!=NULL;n=n->prev){
    write_sym(output,n->addr,n->name);
  }
  
}

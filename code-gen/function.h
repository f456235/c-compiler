#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOL_TABLE_SIZE 5000
#define MAX_ARGUMNETS 5
#define MAX_LOCAL 50
#define FRAME_SIZE (2 + MAX_ARGUMNETS + MAX_LOCAL) *4

#define TYPE_FUNCTION 1
#define TYPE_POINTER 2
#define TYPE_INT 3

#define GLOBAL_MODE 4
#define LOCAL_MODE 5
#define ARGUMENT_MODE 6

struct symbol_entry{
    char *name;
    int scope;
    int type;
    int mode;
    int offset;
    int total_arguments;
    int total_locals;
};

extern struct symbol_entry symbol_table[MAX_SYMBOL_TABLE_SIZE];
extern int cur_counter;
extern int cur_scope;
extern int if_counter;
extern int for_counter;
extern int nested_if;
extern char *cur_function_name;
extern FILE *codegen;

void init();
void install_symbol(char *name);
void pop_symbol(int scope);
int lookup_symbol(char *name);
void set_type(char *name, int type);
void set_global_variable(char *name);
void set_local_variable(char *mame);
void set_parameter(char *func_name, int total_arguments);
int get_offset(char *name); 

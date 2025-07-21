#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "function.h"

struct symbol_entry symbol_table[MAX_SYMBOL_TABLE_SIZE];
int cur_counter = 0;
int cur_scope = 0;
int if_counter = 0;
int for_counter = 0;
int nested_if = 0;
char *cur_function_name = NULL;
FILE *codegen = NULL;

void init(){
    memset(symbol_table, 0, sizeof(struct  symbol_entry) * MAX_SYMBOL_TABLE_SIZE);
    
}

void install_symbol(char *name){
    int flag = cur_counter >= MAX_SYMBOL_TABLE_SIZE ? 1 : 0;
    if (!flag) {
        symbol_table[cur_counter].scope = cur_scope;
        symbol_table[cur_counter].name = strdup(name);
        cur_counter++;
    }else{
        
        printf("Symbol_table Full!\n");
        return;
    }
    

}

void pop_symbol(int scope){
    int i = cur_counter;
    if (cur_counter == 0) return;
    do{
        i--;
    }while(i >= 0 && symbol_table[i].scope == scope);
    for (i = cur_counter - 1; i >= 0; i--) {
        if (symbol_table[i].scope != scope)
            break;
    }
    if (i < 0) cur_counter = 0;
    else cur_counter = i + 1;
}

int lookup_symbol(char *name){
    if (cur_counter == 0) return -1;
    int i = cur_counter - 1;
    while(i >= 0){
        if (strcmp(symbol_table[i].name, name) == 0)
            return i;
        i--;
    }
    return -1;
}

void set_type(char *name, int type){
    int idx = lookup_symbol(name);

    if (idx < 0){ 
        printf("Error in look up\n");
        return;
    }
    else symbol_table[idx].type = type;
}

void set_global_variable(char *name){
    int idx = lookup_symbol(name);

    if(idx < 0){

        printf("Error in look up\n");
        return;
    }

    symbol_table[idx].mode = GLOBAL_MODE;

}

void set_local_variable(char *name){
    int idx = lookup_symbol(name);
    int func_idx = lookup_symbol(cur_function_name);
    if (idx < 0 || func_idx < 0) {
        printf("Error in look up\n");
        return;
    }else{
        
        symbol_table[idx].mode = LOCAL_MODE;
        symbol_table[idx].offset = ++symbol_table[func_idx].total_locals;
    }
}

void set_parameter(char *func_name, int total_arguments){
    int idx = lookup_symbol(func_name);
    if (idx < 0) printf("Error in function header\n");
    else {
        symbol_table[idx].type = TYPE_FUNCTION;
        symbol_table[idx].total_arguments = total_arguments;
        for (int i = cur_counter - 1, j = total_arguments; j > 0; i--, j--) {
            symbol_table[i].scope = cur_scope;
            symbol_table[i].offset = j;
            symbol_table[i].mode = ARGUMENT_MODE;
        }
    }
}

int get_offset(char *name){
    int idx = lookup_symbol(name);
    if(idx < 0) return -1;
    else{
        if (symbol_table[idx].mode == ARGUMENT_MODE)
            return (-4) * (2 + symbol_table[idx].offset);
        else
            return (-4) * (2 + MAX_ARGUMNETS+ symbol_table[idx].offset);
    }
    
}
    

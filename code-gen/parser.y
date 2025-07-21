%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

char* copy(char *str){

    char *s = (char *)malloc(strlen(str) + 1);
    strcpy(s, str);
    return s;

}

void move_reg_before_jump(char *label){ // move sp, save ra, save old fp, move fp

    fprintf(codegen, "addi sp, sp, %d\n", -FRAME_SIZE);
    fprintf(codegen, "sw ra, %d(sp)\n", FRAME_SIZE-4);
    fprintf(codegen, "sw fp, %d(sp)\n", FRAME_SIZE-8);
    fprintf(codegen, "addi fp, sp, %d\n", FRAME_SIZE);
    
}

void restore_reg(){
    fprintf(codegen, "lw ra, %d(sp)\n", FRAME_SIZE-4);
    fprintf(codegen, "lw fp, %d(sp)\n", FRAME_SIZE-8);
    fprintf(codegen, "addi sp, sp, %d\n", FRAME_SIZE);
    fprintf(codegen, "jr ra\n");
    fprintf(codegen, "\n");

}

void changeLine(){
    fprintf(codegen, "\n");
}

void message(char *str){
    fprintf(codegen, "%s\n", str);
}

void pop_stack(char* rd , char *sd, int offset){
    fprintf(codegen, "lw %s, %d(%s)\n", rd, offset, sd);
    fprintf(codegen, "addi %s, %s, 4\n", sd, sd);
}
void pop_stack_pt(char* rd , char *sd, int offset){
    fprintf(codegen, "lw %s, %d(%s)\n", rd, offset, sd);
    fprintf(codegen, "addi %s, %s, 4\n", sd, sd);
    fprintf(codegen, "slli %s, %s, 2\n", rd, rd);
}

void push_stack(char* rd , char *sd, int offset){
    fprintf(codegen, "addi %s, %s, -4\n", sd, sd);
    fprintf(codegen, "sw %s, %d(%s)\n", rd, offset, sd);
}

void store_reg(char* rd , char *sd, int offset){
    fprintf(codegen, "sw %s, %d(%s)\n", rd, offset, sd);
    fprintf(codegen, "\n");
} 

void push_args(){
    fprintf(codegen, "sw a0, %d(fp)\n", -12);
    fprintf(codegen, "sw a1, %d(fp)\n", -16);

}

%}



%union {
    int intVal;
    char* str;
}

%start S

%type<str> S programs program
%type<str> function_decl function_decfinition codegen_decl codegen_decfinition
%type<str> stmt_or_decls stmt_or_decl scalar_decl array_decl
%type<str> stmt if_stmt if_else_stmt while_stmt for_stmt jump_stmt compound_stmt digital_write_stmt delay_stmt
%type<intVal> type variable expr

%token<intVal> INTEGER
%token<str> ';' ',' '=' '&' '<' '>' '+' '-' '*' '/' '(' ')' '[' ']' '{' '}'
%token<str> IDENTIFIER EQ NE UMINUS DEREF ADDR
%token<str> FOR DO WHILE BREAK IF ELSE RETURN VOID INT CONST
%token<str> CODEGEN DIGITALWRITE DELAY HIGH LOW
%token <str> EXTDSPCODEGEN TYPEUINT32 __RV__UKADD8 __RV__CMPEQ8 __RV__UCMPLT8 __RV__UKSUB8

%left ';'
%left ','
%right '='
%left '&'
%left EQ NE
%left '<' '>'
%left '+' '-'
%left '*' '/'
%right UMINUS DEREF ADDR
%left '(' ')' '[' ']'

%%

S   : programs;

programs: programs program
    | program
    ;

program: codegen_decl
       | codegen_decfinition
       | function_decl
       | function_decfinition
       ;

stmt_or_decl
    : stmt
    | scalar_decl
    | array_decl
;

stmt_or_decls
    : stmt_or_decl
    | stmt_or_decls stmt_or_decl
;

type
    : INT { $$ = TYPE_INT; }
    | CONST INT { $$ = TYPE_INT; }
    | INT '*' { $$ = TYPE_POINTER; }
    | CONST INT '*' { $$ = TYPE_POINTER; }
    | TYPEUINT32 { $$ = TYPE_INT; }
;

codegen_decl
    : VOID CODEGEN '(' ')' ';' {
        install_symbol($2);
        set_global_variable($2);
        $$ = $2;
    }
    | type EXTDSPCODEGEN '(' type IDENTIFIER ',' type IDENTIFIER ')' ';' {
        install_symbol($2);
        set_global_variable($2);
        $$ = $2;
    }
;

codegen_decfinition
    : VOID CODEGEN '(' ')' '{' {
        cur_function_name = copy($2);
        cur_scope++;
        set_parameter($2, 0);
        /* Section A */
        fprintf(codegen, ".global %s\n", $2);
        fprintf(codegen, "%s:\n", $2);
        move_reg_before_jump($2);
        changeLine();
    }
    stmt_or_decls {
        /* Section B */
        // restore ra, restore old fp, remove the frame
        restore_reg();
        
        pop_symbol(cur_scope);
        cur_scope--;
    }'}'
    | type EXTDSPCODEGEN '(' type IDENTIFIER ',' type IDENTIFIER ')' '{' {
        cur_function_name = copy($2);
        cur_scope++;
        install_symbol($5); set_type($5, $4);
        install_symbol($8); set_type($8, $7);
        set_parameter($2, 2);
        /* Section A */
        fprintf(codegen, ".global %s\n", $2);
        fprintf(codegen, "%s:\n", $2);
        move_reg_before_jump($2);
        push_args();
        changeLine();
    } stmt_or_decls {
        /* Section B */
        pop_symbol(cur_scope);
        cur_scope--;
    }'}' {$$ = $2;}
;

function_decl
    : type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' ';' {
        install_symbol($2);
        set_global_variable($2);
        $$ = $2;
    }
;

function_decfinition
    : type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' '{' {
        cur_function_name = copy($2);
        cur_scope++;
        install_symbol($5); set_type($5, $4);
        install_symbol($8); set_type($8, $7);
        set_parameter($2, 2);
        /* Section A */
        fprintf(codegen, ".global %s\n", $2);
        fprintf(codegen, "%s:\n", $2);
        // move sp, save ra, save old fp, move fp
        move_reg_before_jump($2);
        // push the arguments onto the stack
        fprintf(codegen, "sw a0, %d(fp)\n", -12);
        fprintf(codegen, "sw a1, %d(fp)\n", -16);
        changeLine();
    }
    stmt_or_decls {
        pop_symbol(cur_scope);
        cur_scope--;
    }
    '}' { $$ = $2; }
;

scalar_decl
    : type IDENTIFIER ';' {
        install_symbol($2);
        set_local_variable($2);
        set_type($2, $1);
    }
    | type IDENTIFIER '=' expr ';' {
        install_symbol($2);
        set_local_variable($2);
        set_type($2, $1);
        pop_stack("t0", "sp", 0);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($2));
    }
    | type IDENTIFIER '=' expr ',' {
        install_symbol($2);
        set_local_variable($2);
        set_type($2, $1);
        pop_stack("t0", "sp", 0);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($2));
    }
    IDENTIFIER '=' expr ';' {
        install_symbol($7);
        set_local_variable($7);
        set_type($7, $1);
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($7));
    }
    | type IDENTIFIER '=' expr ',' {
        install_symbol($2);
        set_local_variable($2);
        set_type($2, $1);
        pop_stack("t0", "sp", 0);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($2));
    }
    '*' IDENTIFIER '=' expr ';' {
        install_symbol($8);
        set_local_variable($8);
        set_type($8, $1);
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($8));
    }
;

array_decl
    : type IDENTIFIER '[' INTEGER ']' ';' {
        install_symbol($2);
        set_local_variable($2);
        set_type($2, TYPE_POINTER);
        for (int i = 0; i < $4; i++) {
            install_symbol("");
            set_local_variable("");
            set_type("", $1);
        }
        // t0 = IDENTIFIER[0]'s address
        fprintf(codegen, "addi t0, fp, %d\n", get_offset($2) - 4);
        // IDENTIFIER = t0
        store_reg("t0", "fp", get_offset($2));
    }
;

expr
    : expr '+' expr {
        if ($1 == TYPE_POINTER) {
            // t0 = expr2 * 4 (pop)
            pop_stack_pt("t0", "sp", 0);
            // t1 = expr1 (pop)
            pop_stack("t1", "sp", 0);
            // t0 = t1 - t0
            fprintf(codegen, "sub t0, t1, t0\n");
            // push t0
            push_stack("t0", "sp", 0);
            
        } else {
            // t0 = expr2 (pop)
            pop_stack("t0", "sp", 0);
            // t1 = expr1 (pop)
            pop_stack("t1", "sp", 0);
            // t0 = t1 + t0
            fprintf(codegen, "add t0, t1, t0\n");
            // push t0
            push_stack("t0", "sp", 0);
            changeLine();
        }
        $$ = $1;
    }
    | expr '-' expr {
        if ($1 == TYPE_POINTER) {
            // t0 = expr2 * 4 (pop)
            pop_stack_pt("t0", "sp", 0);
            // t1 = expr1 (pop)
            pop_stack("t1", "sp", 0);
            // t0 = t1 + t0
            fprintf(codegen, "add t0, t1, t0\n");
            // push t0
            push_stack("t0", "sp", 0);
            changeLine();
        } else {
            // t0 = expr2 (pop)
            pop_stack("t0", "sp", 0);
            // t1 = expr1 (pop)
            pop_stack("t1", "sp", 0);
            // t0 = t1 - t0
            fprintf(codegen, "sub t0, t1, t0\n");
            // push t0
            push_stack("t0", "sp", 0);
            changeLine();
        }
        $$ = $1;
    }
    | expr '*' expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = t1 * t0
        fprintf(codegen, "mul t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = $1;
    }
    | expr '/' expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = t1 / t0
        fprintf(codegen, "div t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = $1;
    }
    | expr '<' expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t2 = (t1 < t0) ? 1 : 0
        fprintf(codegen, "slt t2, t1, t0\n");
        // push t2
        push_stack("t2", "sp", 0);
        $$ = $1;
    }
    | expr '>' expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t2 = (t1 > t0) ? 1 : 0
        fprintf(codegen, "slt t2, t0, t1\n");
        // push t2
        push_stack("t2", "sp", 0);
        $$ = $1;
    }
    | expr EQ expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t2 = (t1 == t0) ? 1 : 0
        fprintf(codegen, "xor t2, t1, t0\n");
        fprintf(codegen, "sltu t2, zero, t2\n");
        fprintf(codegen, "xori t2, t2, 1\n");
        // push t2
        push_stack("t2", "sp", 0);
        $$ = $1;
    }
    | expr NE expr {
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t2 = (t1 != t0) ? 1 : 0
        fprintf(codegen, "xor t2, t1, t0\n");
        fprintf(codegen, "sltu t2, zero, t2\n");
        // push t2
        push_stack("t2", "sp", 0);
        $$ = $1;
    }
    | '-' expr %prec UMINUS {
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t0 = -t0
        fprintf(codegen, "sub t0, zero, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = $2;
    }
    | '&' variable %prec ADDR { $$ = $2; }
    | '(' expr ')' { $$ = $2; }
    | IDENTIFIER '(' expr ',' expr ')' {
        /* Section C */
        // a1 = expr2 (pop)
        pop_stack("a1", "sp", 0);
        // a0 = expr1 (pop)
        pop_stack("a0", "sp", 0);
        // call IDENTIFIER()
        fprintf(codegen, "jal ra, %s\n", $1);
        fprintf(codegen, "\n");
        /* Section D */
        // push the function return value onto stack
        push_stack("a0", "sp", 0);
        $$ = TYPE_INT;
    }
    | __RV__UKADD8 '(' expr ',' expr ')'{
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = t1 + t0
        fprintf(codegen, "ukadd8 t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | __RV__CMPEQ8 '(' expr ',' expr ')'{
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = (t1 == t0) ? 1 : 0
        fprintf(codegen, "cmpeq8 t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | __RV__UCMPLT8 '(' expr ',' expr ')'{
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = (t1 < t0) ? 1 : 0
        fprintf(codegen, "ucmplt8 t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | __RV__UKSUB8 '(' expr ',' expr ')'{
        // t0 = expr2 (pop)
        pop_stack("t0", "sp", 0);
        // t1 = expr1 (pop)
        pop_stack("t1", "sp", 0);
        // t0 = t1 - t0
        fprintf(codegen, "uksub8 t0, t1, t0\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | variable '=' expr {
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t1 = variable (pop)
        pop_stack("t1", "sp", 0);
        // *variable = t0
        fprintf(codegen, "sw t0, 0(t1)\n");
        fprintf(codegen, "\n");
        $$ = $1;
    }
    | variable {
        // t0 = variable (pop)
        pop_stack("t0", "sp", 0);
        // t1 = *variable
        fprintf(codegen, "lw t1, 0(t0)\n");
        // push t1
        push_stack("t1", "sp", 0);
        changeLine();
        $$ = $1;
    }
    | INTEGER {
        // t0 = INTEGER
        fprintf(codegen, "li t0, %d\n", $1);
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = $1;
    }
;

variable
    : IDENTIFIER {
        int idx = lookup_symbol($1);
        // t0 = IDENTIFIER's address
        fprintf(codegen, "addi t0, fp, %d\n", get_offset($1));
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = symbol_table[idx].type;
    }
    | IDENTIFIER '[' expr ']' {
        // IDENTIFIER is a pointer
        // t0 = IDENTIFIER's value (IDENTIFIER[0]'s address)
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset($1));
        // t1 = expr * 4 (pop)
        pop_stack_pt("t1", "sp", 0);
        // t0 = IDENTIFIER[expr]'s address
        fprintf(codegen, "sub t0, t0, t1\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | '*' IDENTIFIER %prec DEREF {
        // IDENTIFIER is a pointer
        // t0 = IDENTIFIER's value (an address)
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset($2));
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
    | '*' '(' IDENTIFIER '+' expr ')' %prec DEREF {
        // IDENTIFIER is a pointer
        // t0 = IDENTIFIER's value (IDENTIFIER[0]'s address)
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset($3));
        // t1 = expr * 4 (pop)
        pop_stack_pt("t1", "sp", 0);
        // t0 = IDENTIFIER[expr]'s address
        fprintf(codegen, "sub t0, t0, t1\n");
        // push t0
        push_stack("t0", "sp", 0);
        changeLine();
        $$ = TYPE_INT;
    }
;

stmt
	: expr ';' { $$ = "expr"; }
	| if_stmt {
        // end_if
        fprintf(codegen, ".IF%d0:\n", if_counter);
    }
    | if_else_stmt
    | while_stmt
    | for_stmt
    | jump_stmt
    | compound_stmt
    | digital_write_stmt
    | delay_stmt
;

if_stmt
	: IF '(' expr ')' {
        if_counter++;
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t0 == 0: jump to .IF10 (end_if / else)
        // t0 == 1: continue to do
        fprintf(codegen, "beq t0, zero, .IF%d0\n", if_counter);
        changeLine();
    }
    compound_stmt
;

if_else_stmt: if_stmt ELSE {
                // finish if part, jump to .IF11 (end_if)
                fprintf(codegen, "j .IF%d1\n", if_counter);
                // else
                fprintf(codegen, ".IF%d0:\n", if_counter);
            }
            compound_stmt {
                // end_if
                if(!nested_if){
                    fprintf(codegen, ".IF%d1:\n", if_counter);
                    nested_if = 1;
                }else
                    fprintf(codegen, ".IF11: \n");
                    
            }
            ;

while_stmt
	: WHILE '(' {
        fprintf(codegen, ".WHILE:\n");
    }
    expr ')' {
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t0 == 0: jump to .END_WHILE
        // t0 == 1: continue to do
        fprintf(codegen, "beq t0, zero, .END_WHILE\n");
        changeLine();
    }
    compound_stmt {
        fprintf(codegen, "j .WHILE\n");
        changeLine();
        fprintf(codegen, ".END_WHILE:\n");
    }
    | DO {
        fprintf(codegen, ".DOWHILE:\n");
    }
    compound_stmt WHILE '(' expr ')' ';' {
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t0 == 0: jump to .END_DOWHILE
        // t0 == 1: continue to do
        fprintf(codegen, "beq t0, zero, .END_DOWHILE\n");
        changeLine();
        fprintf(codegen, "j .DOWHILE\n");
        changeLine();
        fprintf(codegen, ".END_DOWHILE:\n");
    }
;

for_stmt
    : FOR '(' expr ';' {
        for_counter++;
        fprintf(codegen, ".FOR%d:\n", for_counter);
    }
    expr ';' {
        // t0 = expr (pop)
        pop_stack("t0", "sp", 0);
        // t0 == 0: jump to .END_FOR
        // t0 == 1: jump to .FOR_STMT
        fprintf(codegen, "beq t0, zero, .END_FOR%d\n", for_counter);
        changeLine();
        fprintf(codegen, "j .FOR%d_STMT\n", for_counter);
        changeLine();
        fprintf(codegen, ".FOR%d_UPDATE:\n", for_counter);
    }
    expr ')' {
        fprintf(codegen, "j .FOR%d\n", for_counter);
        changeLine();
        fprintf(codegen, ".FOR%d_STMT:\n", for_counter);
    }
    compound_stmt {
        fprintf(codegen, "j .FOR%d_UPDATE\n" , for_counter);
        changeLine();
        fprintf(codegen, ".END_FOR%d:\n" , for_counter);
    }
;

jump_stmt
	: RETURN expr ';' {
        /* Section B */
        // a0 = function return value (pop)
        pop_stack("a0", "sp", 0);
        // restore ra, restore old fp, remove the frame
        restore_reg();
    }
    | BREAK ';' {
        fprintf(codegen, "j .END_WHILE\n");
    }
;

compound_stmt
	: '{' { cur_scope++; }
    stmt_or_decls {
        pop_symbol(cur_scope);
        cur_scope--;
    }
    '}'
;

digital_write_stmt
    : DIGITALWRITE '(' expr ',' HIGH ')' ';' {
        // a0 = expr (pop)
        pop_stack("a0", "sp", 0);
        // a1 = 1
        fprintf(codegen, "li a1, 1\n");
        // call digitalWrite()
        fprintf(codegen, "jal ra, digitalWrite\n");
        changeLine();
    }
    | DIGITALWRITE '(' expr ',' LOW ')' ';' {
        // a0 = expr (pop)
        pop_stack("a0", "sp", 0);
        // a1 = 0
        fprintf(codegen, "li a1, 0\n");
        // call digitalWrite()
        fprintf(codegen, "jal ra, digitalWrite\n");
        changeLine();
    }
;

delay_stmt
    : DELAY '(' expr ')' ';' {
        // a0 = expr (pop)
        pop_stack("a0", "sp", 0);
        // call delay()
        fprintf(codegen, "jal ra, delay\n");
        changeLine();
    }
;

%%

int main(void) {
    init();
    codegen = fopen("codegen.S", "w");
    yyparse();
    fclose(codegen);
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    return 0;
}

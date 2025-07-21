%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>    
    #include "codegen.h"

    char *copy(char *str){
        char *new_str = (char *)malloc(strlen(str) + 1);
        strcpy(new_str, str);
        return new_str;
    }

%}


%union {
    int intVal;
    char *str;
}

//define terminal tokens
%token <str> T_CONST T_INT T_FLOAT T_CHAR T_VOID T_SIGNED T_UNSIGNED T_SHORT T_LONG T_DOUBLE 
%token <str> IF ELSE SWITCH CASE DEFAULT WHILE DO FOR RETURN BREAK CONTINUE KEY_NULL
%token <str> IDENTIFIER
%token <intVal> INTEGER
%token <str> CHAR STRING
%token <str> '+' '-' '*' '/' '%' '=' '!' '~' '^' '&' '|' ':' ';' ',' '.' '[' ']' '(' ')' '{' '}'
%token <str> INC DEC LT LE GT GE EQ NE AND OR LSHIFT RSHIFT
%token <str> CODEGEN DIGITALWRITE DELAY HIGH LOW

%left ';'
%left ','
%right '='
%left '&'
%left EQ NE
%left LE GE
%left '+' '-'
%left '*' '/'
%right UMINUS DEREF ADDR
%left '(' ')' '[' ']'

// define non terminal and its type

%start S
%type <str> S programs program type variable
%type <str> function_decl function_definition codegen_decl codegen_definition
%type <str> scalar_decl array_decl
%type <str> expr expr_assign expr_OR expr_bitwiseOR expr_XOR expr_bitwiseAND expr_equality expr_inequality 
%type <str> expr_bitSHIFT expr_ADDSUB expr_MULDIVMOD expr_UNARYFRONT expr_UNARYBACK 
%type <str> statement if_stmt if_else_stmt switch_stmt while_stmt for_stmt return_break_continue_stmt compound_stmt jump_stmt digitalWrite_stmt delay_stmt
%type <str> stmt_declarations stmt_declaration 
%type <str> for_con

%%

S: programs;

programs: program
        | programs program
        ;   

program: codegen_decl
        | function_decl
        | codegen_definition
        | function_definition
        ;

stmt_declarations: stmt_declarations statement
                 | stmt_declaration
                 ;
                
stmt_declaration: statement
                | scalar_decl
                | array_decl
                ;
/* start of grammar type*/
type: T_INT {$$ = TYPE_INT;}
    | T_CONST T_INT {$$ = TYPE_INT;}
    | T_INT '*' {$$ = TYPE_POINTER;}
    | T_CONST T_INT '*' {$$ = TYPE_POINTER;}
    ;

/*grammar for codegen delcaration*/
codegen_decl: T_VOID CODEGEN '(' ')' ';'{

                install_symbol($2);
                set_global_variable($2);
                $$ = $2;

            }
            ;
        
/*grammar for codegen definition*/

codegen_definition: T_VOID CODEGEN '(' ')' '{'{

                cur_function_name = copy($2);
                cur_scope++;
                set_parameter($2,0);
                /*section A*/
                fprintf(codegen, "global %s\n", $2);
                fprintf(codegen, "%s:\n", $2);
                /*move sp, save ra, save old fp, move fp*/
                fprintf(codegen, "addi sp, sp, %d\n", FRAME_SIZE);
                fprintf(codegen, "sw ra, %d(sp)\n" , FRAME_SIZE-4);
                fprintf(codegen, "sw fp, %d(sp)\n" , FRAME_SIZE-8);
                fprintf(codegen, "addi fp, sp, %d\n", FRAME_SIZE);
                fprintf(codegen, "\n");
            }
            stmt_declarations{
                /*section B: restore ra, restore old fp , remove frame*/
                fprintf(codegen, "lw ra, %d(fp)\n", FRAME_SIZE-4);
                fprintf(codegen, "lw fp, %d(fp)\n", FRAME_SIZE-8);
                fprintf(codegen, "addi sp, sp, -%d\n", FRAME_SIZE);
                fprintf(codegen, "jr ra\n");
                fprintf(codegen, "\n");
                pop_symbol(cur_scope);
                cur_scope--;
            }
            '}'
            ;
/*grammar for function decalration*/
function_decl: type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' ';'{
                        install_symbol($2);
                        set_global_variable($2);
                        $$ = $2;
                    }
                    ;


/*grammar for function definition*/

function_definition: type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' '{'{

                cur_scope++;
                cur_function_name = copy($2);
                install_symbol($5);
                install_symbol($8);
                set_type($5, $4);
                set_type($8, $7);    
                set_parameter($2,2);

                /*section A, move sp, save ra, save old fp, move fp , then push arguments on stack*/
                fprintf(codegen, "global %s\n", $2);
                fprintf(codegen, "%s:\n", $2);
                fprintf(codegen, "addi sp, sp, %d\n", FRAME_SIZE);
                fprintf(codegen, "sw ra, %d(sp)\n" , FRAME_SIZE-4);
                fprintf(codegen, "sw fp, %d(sp)\n" , FRAME_SIZE-8);
                fprintf(codegen, "addi fp, sp, %d\n", FRAME_SIZE);
                fprintf(codegen, "sw a0, %d(fp)\n" ,-12);
                fprintf(codegen, "sw a1, %d(fp)\n" ,-16);
                fprintf(codegen, "\n");
            }
            stmt_declarations{
                pop_symbol(cur_scope);
                cur_scope--;
            }
            '}' {$$ = $2;}
            ;

scalar_decl: type IDENTIFIER ';'{

                install_symbol($2);
                set_local_variable($2);
                set_type($2, $1);
            }
            | type IDENTIFIER '=' expr ';' {
                
                install_symbol($2);
                set_local_variable($2);
                set_type($2, $1);
                /*t0 = expr , ID = t0*/
                fprintf(codegen, "lw t0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "sw t0, %d(fp)\n", get_offset($2));
                fprintf(codegen, "\n");
            }
            | type IDENTIFIER '=' expr ','{
                install_symbol($2);
                set_local_variable($2);
                set_type($2, $1);
                /*t0 = expr , ID = t0*/
                fprintf(codegen, "lw t0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "sw t0, %d(fp)\n", get_offset($2));
                fprintf(codegen, "\n");
            }
            IDENTIFIER '=' expr ';'{
                install_symbol($7);
                set_local_variable($7);
                set_type($7, $1);
                /*t0 = expr , ID = t0*/
                fprintf(codegen, "lw t0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "sw t0, %d(fp)\n", get_offset($7));
                fprintf(codegen, "\n");
            }
            ;
            
array_decl: type IDENTIFIER '[' INTEGER ']' ';'{
                install_symbol($2);
                set_local_variable($2);
                set_type($2, TYPE_POINTER);
                for(int i=0; i<$4 ; i++){
                    install_symbol("");
                    set_local_variable("");
                    set_type("", $1);
                }
                /*set t0 as array's address , and store ID = t0*/
                fprintf(codegen, "addi t0, fp, %d\n", get_offset($2)-4);
                fprintf(codegen, "sw t0, %d(fp)\n", get_offset($2));
            }


expr: expr_assign '=' expr {}
    | expr_assign {}
    ;

expr_assign: expr_assign OR expr_OR {}
    | expr_OR {}
    ;

expr_OR: expr_OR AND expr_bitwiseOR {}
    | expr_bitwiseOR {}
    ;
expr_bitwiseOR: expr_bitwiseOR '|' expr_XOR {}
    | expr_XOR {}
    ;

expr_XOR: expr_XOR '^' expr_bitwiseAND {}
    | expr_bitwiseAND {}

expr_bitwiseAND: expr_bitwiseAND '&' expr_equality {} 
    | expr_equality {}

expr_equality: expr_equality EQ expr_inequality {
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t2 = t1 == t0
            fprintf(codegen, "xor t2, t1, t0\n");
            fprintf(codegen, "seqz t2, t2\n");
            //push t2
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t2, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
    }
    | expr_equality NE expr_inequality {
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t2 = t1 != t0
            fprintf(codegen, "xor t2, t1, t0\n");
            fprintf(codegen, "snez t2, t2\n");
            //push t2
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t2, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
    }
    | expr_inequality {}
    ;

expr_inequality: expr_inequality LT expr_bitSHIFT {
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t2 = t1 < t0
            fprintf(codegen, "slt t2, t1, t0\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t2, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
    }
    | expr_inequality GT expr_bitSHIFT {
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t2 = t1 > t0
            fprintf(codegen, "slt t2, t0, t1\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t2, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
    }

    | expr_bitSHIFT {}

expr_bitSHIFT: expr_bitSHIFT LSHIFT expr_ADDSUB {}
    | expr_bitSHIFT RSHIFT expr_ADDSUB {}
    | expr_ADDSUB {}
    ;

expr: expr '+' expr {

        if ($1 == TYPE_POINTER){
            /*t0 = expr2*4 , t1 = expr1, t0 = t1 -t0 , push t0*/
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "slli t0, t0, 2\n");
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "sub t0, t1, t0\n");
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
        }else{
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t0 = t1 + t0
            fprintf(codegen, "add t0, t1, t0\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
        }
        $$ = $1;
     }
     | expr '-' expr {
        if ($1 == TYPE_POINTER){
            /*t0 = expr2 *4  , t1 = expr1, t0 = t1 + t0 , push t0*/
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "slli t0, t0, 2\n");
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "add t0, t1, t0\n");
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
        }else{
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t0 = t1 - t0
            fprintf(codegen, "sub t0, t1, t0\n");
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
        }
        $$ = $1;
     }
     | expr_MULDIVMOD {}
     ;

expr_MULDIVMOD: expr_MULDIVMOD '*' expr_UNARYFRONT {

            //t0    
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t0 = t1 * t0
            fprintf(codegen, "mul t0, t1, t0\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
     }
     | expr_MULDIVMOD '/' expr_UNARYFRONT {
        //t0    
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t1
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t0 = t1 * t0
            fprintf(codegen, "div t0, t1, t0\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
     }
     | expr_UNARYFRONT {}
     ;

expr_UNARYFRONT: '-' expr_UNARYFRONT %prec UMINUS{
            //t0
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //t0 = -t0
            fprintf(codegen, "neg t0, t0\n");
            //push t0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $2;
     }
     | '!' expr_UNARYFRONT {}
     | '~' expr_UNARYFRONT {}
     | '(' expr_UNARYFRONT ')' {$$ = $2;}
     |IDENTIFIER '(' expr_UNARYFRONT ',' expr_UNARYFRONT ')' expr_UNARYFRONT {
          //t0 = expr2, t1 = expr1
            fprintf(codegen, "lw a1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "lw a0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");

            //call ID
            fprintf(codegen, "jal ra, %s\n", $1);
            fprintf(codegen, "\n");
            //push a0
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw a0, 0(sp)\n");
           
            $$ = TYPE_INT;
     }
     | variable '=' expr{
            //t0 = expr, t1 = variable
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //variable = expr
            fprintf(codegen, "sw t0, 0(t1)\n");
            $$ = $1;
     }
     | '&' variable %prec ADDR{
            $$ = $2;
     }
     | expr_UNARYBACK {}
     ;

expr_UNARYBACK: INTEGER{
            
            fprintf(codegen, "li t0, %d\n", $1);
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = $1;
     }
     |variable {
        fprintf(codegen, "lw t0, 0(sp)\n");
        fprintf(codegen, "addi sp, sp, 4\n");
        fprintf(codegen, "lw t1, 0(t0)\n");
        fprintf(codegen, "addi sp, sp, -4\n");
        fprintf(codegen, "sw t1, 0(sp)\n");
        fprintf(codegen, "\n");
        $$ = $1;
     }
     ;

variable: IDENTIFIER{
            int idx = lookup_symbol($1);
            fprintf(codegen, "addi t0, fp, %d\n", get_offset($1));
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = symbol_table[idx].type;
        }
        | IDENTIFIER '[' expr ']'{
            fprintf(codegen, "lw t0, %d(fp)\n", get_offset($1));
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "slli t1, t1, 2\n");
            fprintf(codegen, "sub t0, t0, t1\n");
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = TYPE_INT;
        }
        | '*' IDENTIFIER %prec DEREF{
            fprintf(codegen, "lw t0, %d(fp)\n", get_offset($2));
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t0, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = TYPE_INT;
        }
        | '*' '(' IDENTIFIER '+' expr ')' %prec DEREF{
            fprintf(codegen, "lw t0, %d(fp)\n", get_offset($3));
            fprintf(codegen, "lw t1, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            fprintf(codegen, "slli t1, t1, 2\n");
            fprintf(codegen, "sub t0, t0, t1\n");
            fprintf(codegen, "addi sp, sp, -4\n");
            fprintf(codegen, "sw t1, 0(sp)\n");
            fprintf(codegen, "\n");
            $$ = TYPE_INT;
        }

statement: expr ';' {$$ = "expr";}
         | if_stmt {fprintf(codegen, ".IF%d0\n",if_counter);}
         | if_else_stmt
         | while_stmt 
         | for_stmt 
         | delay_stmt
         | compound_stmt
         |jump_stmt
         | digitalWrite_stmt 
         ;

if_stmt: IF '(' expr ')'{
            if_counter++;
            //t0 = expr
            fprintf(codegen, "lw t0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //if t0 == 0, jump to .IF%d0
            //if t0 == 1, continue
            fprintf(codegen, "beqz t0, zero , .IF%d0\n", if_counter);\
            fprintf(codegen, "\n");

        }
        compound_stmt
        ;
if_else_stmt : if_stmt ELSE {
                //jump to .IF%d1
                fprintf(codegen, "j .IF%d1\n", if_counter);
                //else
                fprintf(codegen, ".IF%d0:\n", if_counter);
             }
             compound_stmt{
                //end of if_else
                fprintf(codegen, ".IF%d1:\n", if_counter);
             }
             ;



while_stmt: WHILE '(' {
                fprintf(codegen, ".WHILE:\n");
          }
          expr ')'{
                //t0 = expr
                fprintf(codegen, "lw t0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                //if t0 == 0, jump to .WHILE_END
                //if t0 == 1, continue
                fprintf(codegen, "beqz t0, zero, .END_WHILE\n");
                fprintf(codegen, "\n");
          }
          compound_stmt{
                //jump to .WHILE
                fprintf(codegen, "j .WHILE\n");
                fprintf(codegen, "\n");
                //end of while
                fprintf(codegen, ".END_WHILE:\n");
          }
          | DO{
                fprintf(codegen, ".DOWHILE:\n");
          }
            compound_stmt WHILE '(' expr ')'{
                    //t0 = expr
                    fprintf(codegen, "lw t0, 0(sp)\n");
                    fprintf(codegen, "addi sp, sp, 4\n");
                    //if t0 == 0, jump to .DOWHILE_END
                    //if t0 == 1, continue
                    fprintf(codegen, "beqz t0, zero, .END_DOWHILE\n");
                    fprintf(codegen, "\n");
                    fprintf(codegen, "j .DOWHILE\n");
                    fprintf(codegen, "\n");
                    fprintf(codegen, ".END_DOWHILE:\n");
            }
          ;

for_stmt: FOR '(' for_con ';'{
                fprintf(codegen, ".FOR:\n");
            }
            for_con ';'{
                //t0 = for_con
                fprintf(codegen, "lw t0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                //if t0 == 0, jump to .FOR_END
                //if t0 == 1, continue
                fprintf(codegen, "beqz t0, zero, .END_FOR\n");
                fprintf(codegen, "\n");
                fprintf(codegen, "j .FOR_STMT\n");
                fprintf(codegen, "\n");
                fprintf(codegen, ".FOR_UPDATE:\n");
            } for_con ')'{
                fprintf(codegen, "j .FOR\n");
                fprintf(codegen, "\n");
                fprintf(codegen, ".FOR_STMT:\n");
            } compound_stmt{
                fprintf(codegen, "j .FOR_UPDATE\n");
                fprintf(codegen, "\n");
                
            }
            ;

for_con: expr{}

jump_stmt: RETURN expr ';'{
            //a0 is function return value
            fprintf(codegen, "lw a0, 0(sp)\n");
            fprintf(codegen, "addi sp, sp, 4\n");
            //restire ra, old fp, remove frame
            fprintf(codegen, "lw ra, %d(fp)\n", FRAME_SIZE-4);
            fprintf(codegen, "lw fp, %d(fp)\n", FRAME_SIZE-8);
            fprintf(codegen, "addi sp, sp, -%d\n", FRAME_SIZE);
            fprintf(codegen, "jr ra\n");
            fprintf(codegen, "\n");
        }
        | BREAK ';' {
            fprintf(codegen, "j .END_WHILE\n");
            //fprintf(codegen, "\n");
        }
        ;

compound_stmt: '{' { cur_scope++; }
             stmt_declarations {
                pop_symbol(cur_scope);
                cur_scope--;
             }
             '}' 
             ;

digitalWrite_stmt: DIGITALWRITE '(' expr ',' HIGH ')' ';'{
                fprintf(codegen, "lw a0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "li a1, 1\n");
                fprintf(codegen, "jal ra, digitalWrite\n");
                fprintf(codegen, "\n");
            }
            | DIGITALWRITE '(' expr ',' LOW ')' ';'{
                fprintf(codegen, "lw a0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "li a1, 0\n");
                fprintf(codegen, "jal ra, digitalWrite\n");
                fprintf(codegen, "\n");
            }
            ;

delay_stmt: DELAY '(' expr ')' ';'{
                fprintf(codegen, "lw a0, 0(sp)\n");
                fprintf(codegen, "addi sp, sp, 4\n");
                fprintf(codegen, "jal ra, delay\n");
                fprintf(codegen, "\n");
            }
            ;
%%

int main(){

    yyparse();
    return 0;

}

void yyerror(char *msg){
    fprintf(stderr, "%s\n", msg);
    return;
}
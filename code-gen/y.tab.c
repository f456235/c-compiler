/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 2
#define YYMINOR 0
#define YYPATCH 20220114

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#undef YYBTYACC
#define YYBTYACC 0
#define YYDEBUGSTR YYPREFIX "debug"
#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

char* copy(char *str){

    char *s = (char *)malloc(strlen(str) + 1);
    strcpy(s, str);
    return s;

}

void move_reg_before_jump(char *label){ /* move sp, save ra, save old fp, move fp*/

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

#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#line 72 "parser.y"
typedef union YYSTYPE {
    int intVal;
    char* str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 103 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INTEGER 257
#define IDENTIFIER 258
#define EQ 259
#define NE 260
#define UMINUS 261
#define DEREF 262
#define ADDR 263
#define FOR 264
#define DO 265
#define WHILE 266
#define BREAK 267
#define IF 268
#define ELSE 269
#define RETURN 270
#define VOID 271
#define INT 272
#define CONST 273
#define CODEGEN 274
#define DIGITALWRITE 275
#define DELAY 276
#define HIGH 277
#define LOW 278
#define EXTDSPCODEGEN 279
#define TYPEUINT32 280
#define __RV__UKADD8 281
#define __RV__CMPEQ8 282
#define __RV__UCMPLT8 283
#define __RV__UKSUB8 284
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    1,    1,    2,    2,    2,    2,    8,    8,    8,
    7,    7,   20,   20,   20,   20,   20,    5,    5,   23,
   24,    6,   25,   26,    6,    3,   27,   28,    4,    9,
    9,   29,    9,   30,    9,   10,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   22,   22,   22,   22,   22,
   22,   22,   22,   22,   22,   21,   21,   21,   21,   11,
   11,   11,   11,   11,   11,   11,   11,   11,   31,   12,
   32,   13,   33,   34,   14,   35,   14,   36,   37,   38,
   15,   16,   16,   39,   40,   17,   18,   18,   19,
};
static const YYINT yylen[] = {                            2,
    1,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    2,    1,    2,    2,    3,    1,    5,   10,    0,
    0,    9,    0,    0,   14,   10,    0,    0,   14,    3,
    5,    0,   10,    0,   11,    6,    3,    3,    3,    3,
    3,    3,    3,    3,    2,    2,    3,    6,    6,    6,
    6,    6,    3,    1,    1,    1,    4,    2,    6,    2,
    1,    1,    1,    1,    1,    1,    1,    1,    0,    6,
    0,    4,    0,    0,    7,    0,    8,    0,    0,    0,
   12,    3,    2,    0,    0,    5,    7,    7,    5,
};
static const YYINT yydefred[] = {                         0,
    0,    0,    0,   17,    0,    0,    3,    6,    7,    4,
    5,    0,    0,   15,    0,    2,    0,    0,    0,   16,
    0,    0,    0,    0,    0,   18,   20,    0,    0,    0,
    0,    0,   55,    0,    0,    0,    0,   84,    0,    0,
   76,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   11,    9,   10,    8,    0,   62,   63,   64,
   65,   66,   67,   68,    0,    0,    0,    0,    0,    0,
   46,   45,    0,   58,    0,    0,    0,    0,    0,    0,
   73,   83,    0,    0,    0,    0,    0,    0,    0,    0,
   12,    0,   71,    0,    0,   60,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   47,    0,    0,
    0,    0,    0,    0,    0,   82,    0,    0,    0,    0,
    0,    0,   22,    0,   30,    0,    0,    0,    0,    0,
    0,    0,   39,   40,    0,    0,    0,    0,    0,    0,
    0,   57,   78,    0,    0,   69,    0,    0,    0,    0,
    0,    0,   72,    0,    0,   26,   27,   19,   23,    0,
   86,    0,    0,    0,   74,    0,    0,    0,   89,    0,
    0,    0,    0,   31,    0,    0,    0,    0,   59,   48,
    0,    0,    0,   70,    0,    0,   49,   50,   51,   52,
    0,    0,   36,    0,    0,   79,    0,   75,   87,   88,
    0,    0,    0,    0,    0,   77,    0,    0,   29,   25,
    0,    0,    0,   80,   33,    0,    0,   35,   81,
};
#if defined(YYDESTRUCT_CALL) || defined(YYSTYPE_TOSTRING)
static const YYINT yystos[] = {                           0,
  271,  272,  273,  280,  286,  287,  288,  289,  290,  291,
  292,  306,  274,   42,  272,  288,  258,  279,   40,   42,
   40,   40,   41,  306,  306,   59,  123,  258,  258,  309,
   44,   44,  257,   38,   45,   42,   40,  123,  258,  264,
  265,  266,  267,  268,  270,  275,  276,  281,  282,  283,
  284,  293,  294,  295,  296,  297,  298,  299,  300,  301,
  302,  303,  304,  305,  306,  307,  308,  306,  306,  258,
  307,  308,   40,  258,  308,  325,   40,   91,   40,  321,
   40,   59,   40,  308,   40,   40,   40,   40,   40,   40,
  294,  310,  269,  258,   61,   59,   60,   62,   43,   45,
   42,   47,  259,  260,  258,  258,  258,   41,  293,  308,
  308,  308,  303,  319,  308,   59,  308,  308,  308,  308,
  308,  308,  125,  318,   59,   61,   91,  308,  308,  308,
  308,  308,  308,  308,  308,  308,   41,   41,   43,  326,
   44,   93,   59,  266,  308,   41,   44,   41,   44,   44,
   44,   44,  303,  308,  257,   59,  123,   59,  123,  308,
  125,  308,  322,   40,   41,  317,  277,  278,   59,  308,
  308,  308,  308,   59,   44,   93,  313,  311,   41,   41,
  308,  308,  320,  303,   41,   41,   41,   41,   41,   41,
  315,  316,   59,  293,  293,   59,   41,  303,   59,   59,
  258,   42,  314,  312,  323,   59,   61,  258,  125,  125,
  308,  308,   61,   41,   59,  308,  324,   59,  303,
};
#endif /* YYDESTRUCT_CALL || YYSTYPE_TOSTRING */
static const YYINT yydgoto[] = {                          5,
    6,    7,    8,    9,   10,   11,   52,   53,   54,   55,
   56,   57,   58,   59,   60,   61,   62,   63,   64,   65,
   66,   67,   30,   92,  178,  204,  177,  203,  191,  192,
  166,  124,  114,  183,   80,  163,  205,  217,   76,  140,
};
static const YYINT yysindex[] = {                      -177,
 -258,  -22, -250,    0,    0, -177,    0,    0,    0,    0,
    0, -240,   -7,    0,   -4,    0,   -5,    2,   -1,    0,
  -62,  -62,  -51, -214, -211,    0,    0,   18,   22,  -17,
  -62,  -62,    0,  -41,    3,  -34,    3,    0,  -26,   33,
    0,   50,   20,   57,    3,   60,   73,   80,   86,   88,
  100,  -17,    0,    0,    0,    0, -181,    0,    0,    0,
    0,    0,    0,    0, -147,   61,  311, -113, -111,   68,
    0,    0,  -76,    0,   76,  -17,    3,    3,    3,   64,
    0,    0,    3,  357,    3,    3,    3,    3,    3,    3,
    0,   87,    0,  -42,    3,    0,    3,    3,    3,    3,
    3,    3,    3,    3,  164,  172,  179,    0,  -17,  380,
  386,  402,  -35,    3,  101,    0,  423,  108,  429,  455,
  469,  490,    0,   64,    0,    3,  -24,  396,   82,   82,
  -18,  -18,    0,    0,   92,   92,  -49,  -46,    3,   90,
    3,    0,    0,  212,  115,    0, -246,  198,    3,    3,
    3,    3,    0,  304,  169,    0,    0,    0,    0,  124,
    0,  131,    3,    3,    0,   64,  229,  230,    0,  138,
  147,  154,  161,    0,    0,  213,  -17,  -17,    0,    0,
  445,  249,   64,    0,  214,  215,    0,    0,    0,    0,
   21,  239,    0,  -17,  -17,    0,  219,    0,    0,    0,
  221,   25,  178,  180,    3,    0,    3,  228,    0,    0,
  259,  506,    3,    0,    0,  513,   64,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0, -224,    0,    0,    0,  297,    0,    0,    0,    0,
    0,    0,    0,    0, -212,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    9,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  185,    0,    0,    0,    0,  -38,    0,    0,    0,
    0,    0,    0,    0,    0,   16,    0,    0,    0,   39,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  187,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -29,  279,  283,
   48,   71,    0,    0,  195,  236,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -33,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  188,  189,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#if YYBTYACC
static const YYINT yycindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#endif
static const YYINT yygindex[] = {                         0,
    0,  310,    0,    0,    0,    0,  -73,  241,    0,    0,
    0,    0,    0,    0,    0,    0,  235,    0,    0,    5,
  284,  656,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
};
#define YYTABLESIZE 869
static const YYINT yytable[] = {                         61,
   36,   61,  109,   61,   12,   73,   61,   26,   34,  156,
   12,   53,  158,   77,   53,   13,  125,   17,  126,   14,
   34,   15,   37,  101,   36,   24,   25,   35,  102,   53,
  167,  168,   19,   13,   21,   68,   69,   20,   18,   23,
   34,   22,   37,   28,   36,   14,   29,   35,  127,   56,
   56,   56,   56,   56,   13,   56,   54,   54,   54,   54,
   54,   31,   54,   53,   78,   32,   14,   56,   56,   56,
   56,   27,   79,  157,   54,   54,  159,   54,   82,   56,
   56,   56,   56,   56,   61,   56,   61,   93,   37,   81,
   37,   37,   37,    1,    2,    3,   83,   56,   56,   85,
   56,   56,    4,  194,  195,   38,   37,   37,   54,   37,
   94,   38,   86,   38,   38,   38,  108,  101,   99,   87,
  100,   95,  102,  101,   99,   88,  100,   89,  102,   38,
   38,   56,   38,  101,   99,   97,  100,   98,  102,   90,
   37,  146,  101,   99,  105,  100,  106,  102,  148,  101,
   99,   97,  100,   98,  102,  165,  101,   99,   78,  100,
   97,  102,   98,   38,  179,  101,   99,   97,  100,   98,
  102,  180,  101,   99,   97,  100,   98,  102,  187,  101,
   99,  107,  100,   97,  102,   98,   38,  188,  101,   99,
   97,  100,   98,  102,  189,  101,   99,   97,  100,   98,
  102,  190,  101,   99,  137,  100,   97,  102,   98,    2,
    3,  123,  138,   97,  161,   98,   70,    4,   61,   61,
   97,  139,   98,   74,   32,   61,   61,   61,   61,   61,
  144,   61,  155,   61,   61,   43,   61,   61,   43,   33,
   39,   61,   61,   61,   61,   61,   40,   41,   42,   43,
   44,  164,   45,   43,    2,    3,  169,   46,   47,   33,
   39,  176,    4,   48,   49,   50,   51,   56,   56,  185,
  186,  193,  199,  200,   54,   54,   44,  206,  201,   44,
  202,  207,  208,   48,   49,   50,   51,   43,  213,  197,
  101,   99,   91,  100,   44,  102,    1,   56,   56,  214,
  101,   99,  209,  100,  210,  102,   37,   37,   97,   21,
   98,   85,   28,   24,  113,   16,    0,   71,   97,   41,
   98,    0,   41,   42,    0,    0,   42,    0,   44,   38,
   38,    0,    0,    0,  103,  104,    0,   41,   41,    0,
   41,   42,   42,    0,   42,  101,   99,  175,  100,   91,
  102,    0,  101,   99,    0,  100,    0,  102,  153,  103,
  104,    0,  174,   97,    0,   98,  103,  104,    0,   96,
   97,   41,   98,  103,  104,   42,    0,    0,    0,    0,
    0,    0,  103,  104,    0,    0,    0,    0,    0,  103,
  104,    0,    0,    0,    0,    0,  103,  104,  101,   99,
  184,  100,    0,  102,    0,  103,  104,    0,    0,    0,
    0,    0,  103,  104,    0,  116,   97,  198,   98,  103,
  104,  101,   99,  141,  100,    0,  102,  101,   99,    0,
  100,    0,  102,    0,   91,   91,    0,  101,   99,   97,
  100,   98,  102,  101,   99,   97,  100,   98,  102,    0,
    0,  219,    0,   43,   43,   97,    0,   98,    0,    0,
  143,   97,    0,   98,  101,   99,  147,  100,    0,  102,
  101,   99,  149,  100,    0,  102,    0,    0,  142,    0,
    0,    0,   97,    0,   98,    0,  101,   99,   97,  100,
   98,  102,    0,    0,   44,   44,  101,   99,  150,  100,
    0,  102,    0,  196,   97,    0,   98,  103,  104,    0,
  101,   99,  151,  100,   97,  102,   98,  103,  104,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   97,    0,
   98,  101,   99,  152,  100,    0,  102,   41,   41,    0,
    0,   42,   42,    0,    0,    0,    0,  101,   99,   97,
  100,   98,  102,    0,  101,   99,    0,  100,    0,  102,
    0,    0,  103,  104,  215,   97,    0,   98,    0,  103,
  104,  218,   97,    0,   98,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  103,  104,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  103,  104,
    0,    0,    0,    0,  103,  104,    0,    0,    0,    0,
    0,    0,    0,    0,  103,  104,    0,    0,    0,    0,
  103,  104,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  103,  104,    0,    0,    0,    0,  103,  104,    0,
   72,    0,   75,    0,    0,    0,    0,    0,    0,    0,
   84,    0,    0,  103,  104,    0,    0,    0,    0,    0,
    0,    0,    0,  103,  104,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  103,  104,    0,
    0,    0,  110,  111,  112,    0,    0,    0,  115,    0,
  117,  118,  119,  120,  121,  122,    0,    0,  103,  104,
  128,    0,  129,  130,  131,  132,  133,  134,  135,  136,
    0,    0,    0,    0,  103,  104,    0,    0,    0,  145,
    0,  103,  104,    0,    0,    0,    0,    0,    0,    0,
    0,  154,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  160,    0,  162,    0,    0,    0,
    0,    0,    0,    0,  170,  171,  172,  173,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  181,  182,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  211,    0,  212,    0,    0,    0,    0,    0,  216,
};
static const YYINT yycheck[] = {                         38,
   42,   40,   76,   42,    0,   40,   45,   59,   42,   59,
    6,   41,   59,   40,   44,  274,   59,  258,   61,   42,
   38,  272,   40,   42,   42,   21,   22,   45,   47,   59,
  277,  278,   40,  258,   40,   31,   32,   42,  279,   41,
   38,   40,   40,  258,   42,  258,  258,   45,   91,   41,
   42,   43,   44,   45,  279,   47,   41,   42,   43,   44,
   45,   44,   47,   93,   91,   44,  279,   59,   60,   61,
   62,  123,   40,  123,   59,   60,  123,   62,   59,   41,
   42,   43,   44,   45,  123,   47,  125,  269,   41,   40,
   43,   44,   45,  271,  272,  273,   40,   59,   60,   40,
   62,   93,  280,  177,  178,  123,   59,   60,   93,   62,
  258,   41,   40,   43,   44,   45,   41,   42,   43,   40,
   45,   61,   47,   42,   43,   40,   45,   40,   47,   59,
   60,   93,   62,   42,   43,   60,   45,   62,   47,   40,
   93,   41,   42,   43,  258,   45,  258,   47,   41,   42,
   43,   60,   45,   62,   47,   41,   42,   43,   91,   45,
   60,   47,   62,   93,   41,   42,   43,   60,   45,   62,
   47,   41,   42,   43,   60,   45,   62,   47,   41,   42,
   43,  258,   45,   60,   47,   62,  123,   41,   42,   43,
   60,   45,   62,   47,   41,   42,   43,   60,   45,   62,
   47,   41,   42,   43,   41,   45,   60,   47,   62,  272,
  273,  125,   41,   60,  125,   62,  258,  280,  257,  258,
   60,   43,   62,  258,  258,  264,  265,  266,  267,  268,
  266,  270,  257,  272,  273,   41,  275,  276,   44,  257,
  258,  280,  281,  282,  283,  284,  264,  265,  266,  267,
  268,   40,  270,   59,  272,  273,   59,  275,  276,  257,
  258,   93,  280,  281,  282,  283,  284,  259,  260,   41,
   41,   59,   59,   59,  259,  260,   41,   59,  258,   44,
   42,   61,  258,  281,  282,  283,  284,   93,   61,   41,
   42,   43,   52,   45,   59,   47,    0,  259,  260,   41,
   42,   43,  125,   45,  125,   47,  259,  260,   60,  125,
   62,  125,  125,  125,   80,    6,   -1,   34,   60,   41,
   62,   -1,   44,   41,   -1,   -1,   44,   -1,   93,  259,
  260,   -1,   -1,   -1,  259,  260,   -1,   59,   60,   -1,
   62,   59,   60,   -1,   62,   42,   43,   44,   45,  109,
   47,   -1,   42,   43,   -1,   45,   -1,   47,  124,  259,
  260,   -1,   59,   60,   -1,   62,  259,  260,   -1,   59,
   60,   93,   62,  259,  260,   93,   -1,   -1,   -1,   -1,
   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,   -1,  259,
  260,   -1,   -1,   -1,   -1,   -1,  259,  260,   42,   43,
  166,   45,   -1,   47,   -1,  259,  260,   -1,   -1,   -1,
   -1,   -1,  259,  260,   -1,   59,   60,  183,   62,  259,
  260,   42,   43,   44,   45,   -1,   47,   42,   43,   -1,
   45,   -1,   47,   -1,  194,  195,   -1,   42,   43,   60,
   45,   62,   47,   42,   43,   60,   45,   62,   47,   -1,
   -1,  217,   -1,  259,  260,   60,   -1,   62,   -1,   -1,
   59,   60,   -1,   62,   42,   43,   44,   45,   -1,   47,
   42,   43,   44,   45,   -1,   47,   -1,   -1,   93,   -1,
   -1,   -1,   60,   -1,   62,   -1,   42,   43,   60,   45,
   62,   47,   -1,   -1,  259,  260,   42,   43,   44,   45,
   -1,   47,   -1,   59,   60,   -1,   62,  259,  260,   -1,
   42,   43,   44,   45,   60,   47,   62,  259,  260,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   60,   -1,
   62,   42,   43,   44,   45,   -1,   47,  259,  260,   -1,
   -1,  259,  260,   -1,   -1,   -1,   -1,   42,   43,   60,
   45,   62,   47,   -1,   42,   43,   -1,   45,   -1,   47,
   -1,   -1,  259,  260,   59,   60,   -1,   62,   -1,  259,
  260,   59,   60,   -1,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  259,  260,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,  260,
   -1,   -1,   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,
  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  259,  260,   -1,   -1,   -1,   -1,  259,  260,   -1,
   35,   -1,   37,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   45,   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  259,  260,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  259,  260,   -1,
   -1,   -1,   77,   78,   79,   -1,   -1,   -1,   83,   -1,
   85,   86,   87,   88,   89,   90,   -1,   -1,  259,  260,
   95,   -1,   97,   98,   99,  100,  101,  102,  103,  104,
   -1,   -1,   -1,   -1,  259,  260,   -1,   -1,   -1,  114,
   -1,  259,  260,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  126,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  139,   -1,  141,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  149,  150,  151,  152,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  163,  164,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  205,   -1,  207,   -1,   -1,   -1,   -1,   -1,  213,
};
#if YYBTYACC
static const YYINT yyctable[] = {                        -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
};
#endif
#define YYFINAL 5
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 284
#define YYUNDFTOKEN 327
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"$end",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,
"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,"error","INTEGER","IDENTIFIER","EQ","NE","UMINUS",
"DEREF","ADDR","FOR","DO","WHILE","BREAK","IF","ELSE","RETURN","VOID","INT",
"CONST","CODEGEN","DIGITALWRITE","DELAY","HIGH","LOW","EXTDSPCODEGEN",
"TYPEUINT32","__RV__UKADD8","__RV__CMPEQ8","__RV__UCMPLT8","__RV__UKSUB8",
"$accept","S","programs","program","function_decl","function_decfinition",
"codegen_decl","codegen_decfinition","stmt_or_decls","stmt_or_decl",
"scalar_decl","array_decl","stmt","if_stmt","if_else_stmt","while_stmt",
"for_stmt","jump_stmt","compound_stmt","digital_write_stmt","delay_stmt","type",
"variable","expr","$$1","$$2","$$3","$$4","$$5","$$6","$$7","$$8","$$9","$$10",
"$$11","$$12","$$13","$$14","$$15","$$16","$$17","$$18","illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : S",
"S : programs",
"programs : programs program",
"programs : program",
"program : codegen_decl",
"program : codegen_decfinition",
"program : function_decl",
"program : function_decfinition",
"stmt_or_decl : stmt",
"stmt_or_decl : scalar_decl",
"stmt_or_decl : array_decl",
"stmt_or_decls : stmt_or_decl",
"stmt_or_decls : stmt_or_decls stmt_or_decl",
"type : INT",
"type : CONST INT",
"type : INT '*'",
"type : CONST INT '*'",
"type : TYPEUINT32",
"codegen_decl : VOID CODEGEN '(' ')' ';'",
"codegen_decl : type EXTDSPCODEGEN '(' type IDENTIFIER ',' type IDENTIFIER ')' ';'",
"$$1 :",
"$$2 :",
"codegen_decfinition : VOID CODEGEN '(' ')' '{' $$1 stmt_or_decls $$2 '}'",
"$$3 :",
"$$4 :",
"codegen_decfinition : type EXTDSPCODEGEN '(' type IDENTIFIER ',' type IDENTIFIER ')' '{' $$3 stmt_or_decls $$4 '}'",
"function_decl : type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' ';'",
"$$5 :",
"$$6 :",
"function_decfinition : type IDENTIFIER '(' type IDENTIFIER ',' type IDENTIFIER ')' '{' $$5 stmt_or_decls $$6 '}'",
"scalar_decl : type IDENTIFIER ';'",
"scalar_decl : type IDENTIFIER '=' expr ';'",
"$$7 :",
"scalar_decl : type IDENTIFIER '=' expr ',' $$7 IDENTIFIER '=' expr ';'",
"$$8 :",
"scalar_decl : type IDENTIFIER '=' expr ',' $$8 '*' IDENTIFIER '=' expr ';'",
"array_decl : type IDENTIFIER '[' INTEGER ']' ';'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr EQ expr",
"expr : expr NE expr",
"expr : '-' expr",
"expr : '&' variable",
"expr : '(' expr ')'",
"expr : IDENTIFIER '(' expr ',' expr ')'",
"expr : __RV__UKADD8 '(' expr ',' expr ')'",
"expr : __RV__CMPEQ8 '(' expr ',' expr ')'",
"expr : __RV__UCMPLT8 '(' expr ',' expr ')'",
"expr : __RV__UKSUB8 '(' expr ',' expr ')'",
"expr : variable '=' expr",
"expr : variable",
"expr : INTEGER",
"variable : IDENTIFIER",
"variable : IDENTIFIER '[' expr ']'",
"variable : '*' IDENTIFIER",
"variable : '*' '(' IDENTIFIER '+' expr ')'",
"stmt : expr ';'",
"stmt : if_stmt",
"stmt : if_else_stmt",
"stmt : while_stmt",
"stmt : for_stmt",
"stmt : jump_stmt",
"stmt : compound_stmt",
"stmt : digital_write_stmt",
"stmt : delay_stmt",
"$$9 :",
"if_stmt : IF '(' expr ')' $$9 compound_stmt",
"$$10 :",
"if_else_stmt : if_stmt ELSE $$10 compound_stmt",
"$$11 :",
"$$12 :",
"while_stmt : WHILE '(' $$11 expr ')' $$12 compound_stmt",
"$$13 :",
"while_stmt : DO $$13 compound_stmt WHILE '(' expr ')' ';'",
"$$14 :",
"$$15 :",
"$$16 :",
"for_stmt : FOR '(' expr ';' $$14 expr ';' $$15 expr ')' $$16 compound_stmt",
"jump_stmt : RETURN expr ';'",
"jump_stmt : BREAK ';'",
"$$17 :",
"$$18 :",
"compound_stmt : '{' $$17 stmt_or_decls $$18 '}'",
"digital_write_stmt : DIGITALWRITE '(' expr ',' HIGH ')' ';'",
"digital_write_stmt : DIGITALWRITE '(' expr ',' LOW ')' ';'",
"delay_stmt : DELAY '(' expr ')' ';'",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
YYLTYPE  yyloc; /* position returned by actions */
YYLTYPE  yylloc; /* position from the lexer */
#endif

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT(loc, rhs, n) \
do \
{ \
    if (n == 0) \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 0).last_line; \
        (loc).first_column = YYRHSLOC(rhs, 0).last_column; \
        (loc).last_line    = YYRHSLOC(rhs, 0).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, 0).last_column; \
    } \
    else \
    { \
        (loc).first_line   = YYRHSLOC(rhs, 1).first_line; \
        (loc).first_column = YYRHSLOC(rhs, 1).first_column; \
        (loc).last_line    = YYRHSLOC(rhs, n).last_line; \
        (loc).last_column  = YYRHSLOC(rhs, n).last_column; \
    } \
} while (0)
#endif /* YYLLOC_DEFAULT */
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#if YYBTYACC

#ifndef YYLVQUEUEGROWTH
#define YYLVQUEUEGROWTH 32
#endif
#endif /* YYBTYACC */

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#ifndef YYINITSTACKSIZE
#define YYINITSTACKSIZE 200
#endif

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  *p_base;
    YYLTYPE  *p_mark;
#endif
} YYSTACKDATA;
#if YYBTYACC

struct YYParseState_s
{
    struct YYParseState_s *save;    /* Previously saved parser state */
    YYSTACKDATA            yystack; /* saved parser stack */
    int                    state;   /* saved parser state */
    int                    errflag; /* saved error recovery status */
    int                    lexeme;  /* saved index of the conflict lexeme in the lexical queue */
    YYINT                  ctry;    /* saved index in yyctable[] for this conflict */
};
typedef struct YYParseState_s YYParseState;
#endif /* YYBTYACC */
/* variables for the parser stack */
static YYSTACKDATA yystack;
#if YYBTYACC

/* Current parser state */
static YYParseState *yyps = 0;

/* yypath != NULL: do the full parse, starting at *yypath parser state. */
static YYParseState *yypath = 0;

/* Base of the lexical value queue */
static YYSTYPE *yylvals = 0;

/* Current position at lexical value queue */
static YYSTYPE *yylvp = 0;

/* End position of lexical value queue */
static YYSTYPE *yylve = 0;

/* The last allocated position at the lexical value queue */
static YYSTYPE *yylvlim = 0;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
/* Base of the lexical position queue */
static YYLTYPE *yylpsns = 0;

/* Current position at lexical position queue */
static YYLTYPE *yylpp = 0;

/* End position of lexical position queue */
static YYLTYPE *yylpe = 0;

/* The last allocated position at the lexical position queue */
static YYLTYPE *yylplim = 0;
#endif

/* Current position at lexical token queue */
static YYINT  *yylexp = 0;

static YYINT  *yylexemes = 0;
#endif /* YYBTYACC */
#line 717 "parser.y"

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
#line 862 "y.tab.c"

/* For use in generated program */
#define yydepth (int)(yystack.s_mark - yystack.s_base)
#if YYBTYACC
#define yytrial (yyps->save)
#endif /* YYBTYACC */

#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE *newps;
#endif

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    newps = (YYLTYPE *)realloc(data->p_base, newsize * sizeof(*newps));
    if (newps == 0)
        return YYENOMEM;

    data->p_base = newps;
    data->p_mark = newps + i;
#endif

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;

#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%sdebug: stack size increased to %d\n", YYPREFIX, newsize);
#endif
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    free(data->p_base);
#endif
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif /* YYPURE || defined(YY_NO_LEAKS) */
#if YYBTYACC

static YYParseState *
yyNewState(unsigned size)
{
    YYParseState *p = (YYParseState *) malloc(sizeof(YYParseState));
    if (p == NULL) return NULL;

    p->yystack.stacksize = size;
    if (size == 0)
    {
        p->yystack.s_base = NULL;
        p->yystack.l_base = NULL;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        p->yystack.p_base = NULL;
#endif
        return p;
    }
    p->yystack.s_base    = (YYINT *) malloc(size * sizeof(YYINT));
    if (p->yystack.s_base == NULL) return NULL;
    p->yystack.l_base    = (YYSTYPE *) malloc(size * sizeof(YYSTYPE));
    if (p->yystack.l_base == NULL) return NULL;
    memset(p->yystack.l_base, 0, size * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    p->yystack.p_base    = (YYLTYPE *) malloc(size * sizeof(YYLTYPE));
    if (p->yystack.p_base == NULL) return NULL;
    memset(p->yystack.p_base, 0, size * sizeof(YYLTYPE));
#endif

    return p;
}

static void
yyFreeState(YYParseState *p)
{
    yyfreestack(&p->yystack);
    free(p);
}
#endif /* YYBTYACC */

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab
#if YYBTYACC
#define YYVALID        do { if (yyps->save)            goto yyvalid; } while(0)
#define YYVALID_NESTED do { if (yyps->save && \
                                yyps->save->save == 0) goto yyvalid; } while(0)
#endif /* YYBTYACC */

int
YYPARSE_DECL()
{
    int yym, yyn, yystate, yyresult;
#if YYBTYACC
    int yynewerrflag;
    YYParseState *yyerrctx = NULL;
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    YYLTYPE  yyerror_loc_range[3]; /* position of error start/end (0 unused) */
#endif
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
    if (yydebug)
        fprintf(stderr, "%sdebug[<# of symbols on state stack>]\n", YYPREFIX);
#endif
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    memset(yyerror_loc_range, 0, sizeof(yyerror_loc_range));
#endif

#if YYBTYACC
    yyps = yyNewState(0); if (yyps == 0) goto yyenomem;
    yyps->save = 0;
#endif /* YYBTYACC */
    yym = 0;
    /* yyn is set below */
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base;
#endif
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
#if YYBTYACC
        do {
        if (yylvp < yylve)
        {
            /* we're currently re-reading tokens */
            yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc = *yylpp++;
#endif
            yychar = *yylexp++;
            break;
        }
        if (yyps->save)
        {
            /* in trial mode; save scanner results for future parse attempts */
            if (yylvp == yylvlim)
            {   /* Enlarge lexical value queue */
                size_t p = (size_t) (yylvp - yylvals);
                size_t s = (size_t) (yylvlim - yylvals);

                s += YYLVQUEUEGROWTH;
                if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL) goto yyenomem;
                if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL) goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL) goto yyenomem;
#endif
                yylvp   = yylve = yylvals + p;
                yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp   = yylpe = yylpsns + p;
                yylplim = yylpsns + s;
#endif
                yylexp  = yylexemes + p;
            }
            *yylexp = (YYINT) YYLEX;
            *yylvp++ = yylval;
            yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *yylpp++ = yylloc;
            yylpe++;
#endif
            yychar = *yylexp++;
            break;
        }
        /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
        yychar = YYLEX;
#if YYBTYACC
        } while (0);
#endif /* YYBTYACC */
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, " <%s>", YYSTYPE_TOSTRING(yychar, yylval));
#endif
            fputc('\n', stderr);
        }
#endif
    }
#if YYBTYACC

    /* Do we have a conflict? */
    if (((yyn = yycindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
        yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        YYINT ctry;

        if (yypath)
        {
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: CONFLICT in state %d: following successful trial parse\n",
                                YYDEBUGSTR, yydepth, yystate);
#endif
            /* Switch to the next conflict context */
            save = yypath;
            yypath = save->save;
            save->save = NULL;
            ctry = save->ctry;
            if (save->state != yystate) YYABORT;
            yyFreeState(save);

        }
        else
        {

            /* Unresolved conflict - start/continue trial parse */
            YYParseState *save;
#if YYDEBUG
            if (yydebug)
            {
                fprintf(stderr, "%s[%d]: CONFLICT in state %d. ", YYDEBUGSTR, yydepth, yystate);
                if (yyps->save)
                    fputs("ALREADY in conflict, continuing trial parse.\n", stderr);
                else
                    fputs("Starting trial parse.\n", stderr);
            }
#endif
            save                  = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (save == NULL) goto yyenomem;
            save->save            = yyps->save;
            save->state           = yystate;
            save->errflag         = yyerrflag;
            save->yystack.s_mark  = save->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (save->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            save->yystack.l_mark  = save->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (save->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            save->yystack.p_mark  = save->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (save->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            ctry                  = yytable[yyn];
            if (yyctable[ctry] == -1)
            {
#if YYDEBUG
                if (yydebug && yychar >= YYEOF)
                    fprintf(stderr, "%s[%d]: backtracking 1 token\n", YYDEBUGSTR, yydepth);
#endif
                ctry++;
            }
            save->ctry = ctry;
            if (yyps->save == NULL)
            {
                /* If this is a first conflict in the stack, start saving lexemes */
                if (!yylexemes)
                {
                    yylexemes = (YYINT *) malloc((YYLVQUEUEGROWTH) * sizeof(YYINT));
                    if (yylexemes == NULL) goto yyenomem;
                    yylvals   = (YYSTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYSTYPE));
                    if (yylvals == NULL) goto yyenomem;
                    yylvlim   = yylvals + YYLVQUEUEGROWTH;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpsns   = (YYLTYPE *) malloc((YYLVQUEUEGROWTH) * sizeof(YYLTYPE));
                    if (yylpsns == NULL) goto yyenomem;
                    yylplim   = yylpsns + YYLVQUEUEGROWTH;
#endif
                }
                if (yylvp == yylve)
                {
                    yylvp  = yylve = yylvals;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp  = yylpe = yylpsns;
#endif
                    yylexp = yylexemes;
                    if (yychar >= YYEOF)
                    {
                        *yylve++ = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                        *yylpe++ = yylloc;
#endif
                        *yylexp  = (YYINT) yychar;
                        yychar   = YYEMPTY;
                    }
                }
            }
            if (yychar >= YYEOF)
            {
                yylvp--;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp--;
#endif
                yylexp--;
                yychar = YYEMPTY;
            }
            save->lexeme = (int) (yylvp - yylvals);
            yyps->save   = save;
        }
        if (yytable[yyn] == ctry)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                                YYDEBUGSTR, yydepth, yystate, yyctable[ctry]);
#endif
            if (yychar < 0)
            {
                yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylpp++;
#endif
                yylexp++;
            }
            if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                goto yyoverflow;
            yystate = yyctable[ctry];
            *++yystack.s_mark = (YYINT) yystate;
            *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            *++yystack.p_mark = yylloc;
#endif
            yychar  = YYEMPTY;
            if (yyerrflag > 0) --yyerrflag;
            goto yyloop;
        }
        else
        {
            yyn = yyctable[ctry];
            goto yyreduce;
        }
    } /* End of code dealing with conflicts */
#endif /* YYBTYACC */
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: state %d, shifting to state %d\n",
                            YYDEBUGSTR, yydepth, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yylloc;
#endif
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;
#if YYBTYACC

    yynewerrflag = 1;
    goto yyerrhandler;
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */

yyerrlab:
    /* explicit YYERROR from an action -- pop the rhs of the rule reduced
     * before looking for error recovery */
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif

    yynewerrflag = 0;
yyerrhandler:
    while (yyps->save)
    {
        int ctry;
        YYParseState *save = yyps->save;
#if YYDEBUG
        if (yydebug)
            fprintf(stderr, "%s[%d]: ERROR in state %d, CONFLICT BACKTRACKING to state %d, %d tokens\n",
                            YYDEBUGSTR, yydepth, yystate, yyps->save->state,
                    (int)(yylvp - yylvals - yyps->save->lexeme));
#endif
        /* Memorize most forward-looking error state in case it's really an error. */
        if (yyerrctx == NULL || yyerrctx->lexeme < yylvp - yylvals)
        {
            /* Free old saved error context state */
            if (yyerrctx) yyFreeState(yyerrctx);
            /* Create and fill out new saved error context state */
            yyerrctx                 = yyNewState((unsigned)(yystack.s_mark - yystack.s_base + 1));
            if (yyerrctx == NULL) goto yyenomem;
            yyerrctx->save           = yyps->save;
            yyerrctx->state          = yystate;
            yyerrctx->errflag        = yyerrflag;
            yyerrctx->yystack.s_mark = yyerrctx->yystack.s_base + (yystack.s_mark - yystack.s_base);
            memcpy (yyerrctx->yystack.s_base, yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yyerrctx->yystack.l_mark = yyerrctx->yystack.l_base + (yystack.l_mark - yystack.l_base);
            memcpy (yyerrctx->yystack.l_base, yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yyerrctx->yystack.p_mark = yyerrctx->yystack.p_base + (yystack.p_mark - yystack.p_base);
            memcpy (yyerrctx->yystack.p_base, yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yyerrctx->lexeme         = (int) (yylvp - yylvals);
        }
        yylvp          = yylvals   + save->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yylpp          = yylpsns   + save->lexeme;
#endif
        yylexp         = yylexemes + save->lexeme;
        yychar         = YYEMPTY;
        yystack.s_mark = yystack.s_base + (save->yystack.s_mark - save->yystack.s_base);
        memcpy (yystack.s_base, save->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
        yystack.l_mark = yystack.l_base + (save->yystack.l_mark - save->yystack.l_base);
        memcpy (yystack.l_base, save->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        yystack.p_mark = yystack.p_base + (save->yystack.p_mark - save->yystack.p_base);
        memcpy (yystack.p_base, save->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
        ctry           = ++save->ctry;
        yystate        = save->state;
        /* We tried shift, try reduce now */
        if ((yyn = yyctable[ctry]) >= 0) goto yyreduce;
        yyps->save     = save->save;
        save->save     = NULL;
        yyFreeState(save);

        /* Nothing left on the stack -- error */
        if (!yyps->save)
        {
#if YYDEBUG
            if (yydebug)
                fprintf(stderr, "%sdebug[%d,trial]: trial parse FAILED, entering ERROR mode\n",
                                YYPREFIX, yydepth);
#endif
            /* Restore state as it was in the most forward-advanced error */
            yylvp          = yylvals   + yyerrctx->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylpp          = yylpsns   + yyerrctx->lexeme;
#endif
            yylexp         = yylexemes + yyerrctx->lexeme;
            yychar         = yylexp[-1];
            yylval         = yylvp[-1];
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yylloc         = yylpp[-1];
#endif
            yystack.s_mark = yystack.s_base + (yyerrctx->yystack.s_mark - yyerrctx->yystack.s_base);
            memcpy (yystack.s_base, yyerrctx->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
            yystack.l_mark = yystack.l_base + (yyerrctx->yystack.l_mark - yyerrctx->yystack.l_base);
            memcpy (yystack.l_base, yyerrctx->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            yystack.p_mark = yystack.p_base + (yyerrctx->yystack.p_mark - yyerrctx->yystack.p_base);
            memcpy (yystack.p_base, yyerrctx->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
            yystate        = yyerrctx->state;
            yyFreeState(yyerrctx);
            yyerrctx       = NULL;
        }
        yynewerrflag = 1;
    }
    if (yynewerrflag == 0) goto yyinrecovery;
#endif /* YYBTYACC */

    YYERROR_CALL("syntax error");
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yyerror_loc_range[1] = yylloc; /* lookahead position is error start position */
#endif

#if !YYBTYACC
    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
#endif
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: state %d, error recovery shifting to state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* lookahead position is error end position */
                yyerror_loc_range[2] = yylloc;
                YYLLOC_DEFAULT(yyloc, yyerror_loc_range, 2); /* position of error span */
                *++yystack.p_mark = yyloc;
#endif
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    fprintf(stderr, "%s[%d]: error recovery discarding state %d\n",
                                    YYDEBUGSTR, yydepth, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                /* the current TOS position is the error start position */
                yyerror_loc_range[1] = *yystack.p_mark;
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
                if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark, yystack.p_mark);
#else
                    YYDESTRUCT_CALL("error: discarding state",
                                    yystos[*yystack.s_mark], yystack.l_mark);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
                --yystack.s_mark;
                --yystack.l_mark;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                --yystack.p_mark;
#endif
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            fprintf(stderr, "%s[%d]: state %d, error recovery discarding token %d (%s)\n",
                            YYDEBUGSTR, yydepth, yystate, yychar, yys);
        }
#endif
#if defined(YYDESTRUCT_CALL)
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval, &yylloc);
#else
            YYDESTRUCT_CALL("error: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
#endif /* defined(YYDESTRUCT_CALL) */
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
    yym = yylen[yyn];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: state %d, reducing by rule %d (%s)",
                        YYDEBUGSTR, yydepth, yystate, yyn, yyrule[yyn]);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            if (yym > 0)
            {
                int i;
                fputc('<', stderr);
                for (i = yym; i > 0; i--)
                {
                    if (i != yym) fputs(", ", stderr);
                    fputs(YYSTYPE_TOSTRING(yystos[yystack.s_mark[1-i]],
                                           yystack.l_mark[1-i]), stderr);
                }
                fputc('>', stderr);
            }
#endif
        fputc('\n', stderr);
    }
#endif
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)

    /* Perform position reduction */
    memset(&yyloc, 0, sizeof(yyloc));
#if YYBTYACC
    if (!yytrial)
#endif /* YYBTYACC */
    {
        YYLLOC_DEFAULT(yyloc, &yystack.p_mark[-yym], yym);
        /* just in case YYERROR is invoked within the action, save
           the start of the rhs as the error start position */
        yyerror_loc_range[1] = yystack.p_mark[1-yym];
    }
#endif

    switch (yyn)
    {
case 13:
#line 129 "parser.y"
	{ yyval.intVal = TYPE_INT; }
#line 1535 "y.tab.c"
break;
case 14:
#line 130 "parser.y"
	{ yyval.intVal = TYPE_INT; }
#line 1540 "y.tab.c"
break;
case 15:
#line 131 "parser.y"
	{ yyval.intVal = TYPE_POINTER; }
#line 1545 "y.tab.c"
break;
case 16:
#line 132 "parser.y"
	{ yyval.intVal = TYPE_POINTER; }
#line 1550 "y.tab.c"
break;
case 17:
#line 133 "parser.y"
	{ yyval.intVal = TYPE_INT; }
#line 1555 "y.tab.c"
break;
case 18:
#line 137 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_global_variable(yystack.l_mark[-3].str);
        yyval.str = yystack.l_mark[-3].str;
    }
#line 1564 "y.tab.c"
break;
case 19:
#line 142 "parser.y"
	{
        install_symbol(yystack.l_mark[-8].str);
        set_global_variable(yystack.l_mark[-8].str);
        yyval.str = yystack.l_mark[-8].str;
    }
#line 1573 "y.tab.c"
break;
case 20:
#line 150 "parser.y"
	{
        cur_function_name = copy(yystack.l_mark[-3].str);
        cur_scope++;
        set_parameter(yystack.l_mark[-3].str, 0);
        /* Section A */
        fprintf(codegen, ".global %s\n", yystack.l_mark[-3].str);
        fprintf(codegen, "%s:\n", yystack.l_mark[-3].str);
        move_reg_before_jump(yystack.l_mark[-3].str);
        changeLine();
    }
#line 1587 "y.tab.c"
break;
case 21:
#line 160 "parser.y"
	{
        /* Section B */
        /* restore ra, restore old fp, remove the frame*/
        restore_reg();
        
        pop_symbol(cur_scope);
        cur_scope--;
    }
#line 1599 "y.tab.c"
break;
case 23:
#line 168 "parser.y"
	{
        cur_function_name = copy(yystack.l_mark[-8].str);
        cur_scope++;
        install_symbol(yystack.l_mark[-5].str); set_type(yystack.l_mark[-5].str, yystack.l_mark[-6].intVal);
        install_symbol(yystack.l_mark[-2].str); set_type(yystack.l_mark[-2].str, yystack.l_mark[-3].intVal);
        set_parameter(yystack.l_mark[-8].str, 2);
        /* Section A */
        fprintf(codegen, ".global %s\n", yystack.l_mark[-8].str);
        fprintf(codegen, "%s:\n", yystack.l_mark[-8].str);
        move_reg_before_jump(yystack.l_mark[-8].str);
        push_args();
        changeLine();
    }
#line 1616 "y.tab.c"
break;
case 24:
#line 180 "parser.y"
	{
        /* Section B */
        pop_symbol(cur_scope);
        cur_scope--;
    }
#line 1625 "y.tab.c"
break;
case 25:
#line 184 "parser.y"
	{yyval.str = yystack.l_mark[-12].str;}
#line 1630 "y.tab.c"
break;
case 26:
#line 188 "parser.y"
	{
        install_symbol(yystack.l_mark[-8].str);
        set_global_variable(yystack.l_mark[-8].str);
        yyval.str = yystack.l_mark[-8].str;
    }
#line 1639 "y.tab.c"
break;
case 27:
#line 196 "parser.y"
	{
        cur_function_name = copy(yystack.l_mark[-8].str);
        cur_scope++;
        install_symbol(yystack.l_mark[-5].str); set_type(yystack.l_mark[-5].str, yystack.l_mark[-6].intVal);
        install_symbol(yystack.l_mark[-2].str); set_type(yystack.l_mark[-2].str, yystack.l_mark[-3].intVal);
        set_parameter(yystack.l_mark[-8].str, 2);
        /* Section A */
        fprintf(codegen, ".global %s\n", yystack.l_mark[-8].str);
        fprintf(codegen, "%s:\n", yystack.l_mark[-8].str);
        /* move sp, save ra, save old fp, move fp*/
        move_reg_before_jump(yystack.l_mark[-8].str);
        /* push the arguments onto the stack*/
        fprintf(codegen, "sw a0, %d(fp)\n", -12);
        fprintf(codegen, "sw a1, %d(fp)\n", -16);
        changeLine();
    }
#line 1659 "y.tab.c"
break;
case 28:
#line 212 "parser.y"
	{
        pop_symbol(cur_scope);
        cur_scope--;
    }
#line 1667 "y.tab.c"
break;
case 29:
#line 216 "parser.y"
	{ yyval.str = yystack.l_mark[-12].str; }
#line 1672 "y.tab.c"
break;
case 30:
#line 220 "parser.y"
	{
        install_symbol(yystack.l_mark[-1].str);
        set_local_variable(yystack.l_mark[-1].str);
        set_type(yystack.l_mark[-1].str, yystack.l_mark[-2].intVal);
    }
#line 1681 "y.tab.c"
break;
case 31:
#line 225 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_local_variable(yystack.l_mark[-3].str);
        set_type(yystack.l_mark[-3].str, yystack.l_mark[-4].intVal);
        pop_stack("t0", "sp", 0);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-3].str));
    }
#line 1693 "y.tab.c"
break;
case 32:
#line 233 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_local_variable(yystack.l_mark[-3].str);
        set_type(yystack.l_mark[-3].str, yystack.l_mark[-4].intVal);
        pop_stack("t0", "sp", 0);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-3].str));
    }
#line 1705 "y.tab.c"
break;
case 33:
#line 241 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_local_variable(yystack.l_mark[-3].str);
        set_type(yystack.l_mark[-3].str, yystack.l_mark[-9].intVal);
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-3].str));
    }
#line 1718 "y.tab.c"
break;
case 34:
#line 250 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_local_variable(yystack.l_mark[-3].str);
        set_type(yystack.l_mark[-3].str, yystack.l_mark[-4].intVal);
        pop_stack("t0", "sp", 0);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-3].str));
    }
#line 1730 "y.tab.c"
break;
case 35:
#line 258 "parser.y"
	{
        install_symbol(yystack.l_mark[-3].str);
        set_local_variable(yystack.l_mark[-3].str);
        set_type(yystack.l_mark[-3].str, yystack.l_mark[-10].intVal);
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-3].str));
    }
#line 1743 "y.tab.c"
break;
case 36:
#line 270 "parser.y"
	{
        install_symbol(yystack.l_mark[-4].str);
        set_local_variable(yystack.l_mark[-4].str);
        set_type(yystack.l_mark[-4].str, TYPE_POINTER);
        for (int i = 0; i < yystack.l_mark[-2].intVal; i++) {
            install_symbol("");
            set_local_variable("");
            set_type("", yystack.l_mark[-5].intVal);
        }
        /* t0 = IDENTIFIER[0]'s address*/
        fprintf(codegen, "addi t0, fp, %d\n", get_offset(yystack.l_mark[-4].str) - 4);
        /* IDENTIFIER = t0*/
        store_reg("t0", "fp", get_offset(yystack.l_mark[-4].str));
    }
#line 1761 "y.tab.c"
break;
case 37:
#line 287 "parser.y"
	{
        if (yystack.l_mark[-2].intVal == TYPE_POINTER) {
            /* t0 = expr2 * 4 (pop)*/
            pop_stack_pt("t0", "sp", 0);
            /* t1 = expr1 (pop)*/
            pop_stack("t1", "sp", 0);
            /* t0 = t1 - t0*/
            fprintf(codegen, "sub t0, t1, t0\n");
            /* push t0*/
            push_stack("t0", "sp", 0);
            
        } else {
            /* t0 = expr2 (pop)*/
            pop_stack("t0", "sp", 0);
            /* t1 = expr1 (pop)*/
            pop_stack("t1", "sp", 0);
            /* t0 = t1 + t0*/
            fprintf(codegen, "add t0, t1, t0\n");
            /* push t0*/
            push_stack("t0", "sp", 0);
            changeLine();
        }
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1789 "y.tab.c"
break;
case 38:
#line 311 "parser.y"
	{
        if (yystack.l_mark[-2].intVal == TYPE_POINTER) {
            /* t0 = expr2 * 4 (pop)*/
            pop_stack_pt("t0", "sp", 0);
            /* t1 = expr1 (pop)*/
            pop_stack("t1", "sp", 0);
            /* t0 = t1 + t0*/
            fprintf(codegen, "add t0, t1, t0\n");
            /* push t0*/
            push_stack("t0", "sp", 0);
            changeLine();
        } else {
            /* t0 = expr2 (pop)*/
            pop_stack("t0", "sp", 0);
            /* t1 = expr1 (pop)*/
            pop_stack("t1", "sp", 0);
            /* t0 = t1 - t0*/
            fprintf(codegen, "sub t0, t1, t0\n");
            /* push t0*/
            push_stack("t0", "sp", 0);
            changeLine();
        }
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1817 "y.tab.c"
break;
case 39:
#line 335 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = t1 * t0*/
        fprintf(codegen, "mul t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1833 "y.tab.c"
break;
case 40:
#line 347 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = t1 / t0*/
        fprintf(codegen, "div t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1849 "y.tab.c"
break;
case 41:
#line 359 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t2 = (t1 < t0) ? 1 : 0*/
        fprintf(codegen, "slt t2, t1, t0\n");
        /* push t2*/
        push_stack("t2", "sp", 0);
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1864 "y.tab.c"
break;
case 42:
#line 370 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t2 = (t1 > t0) ? 1 : 0*/
        fprintf(codegen, "slt t2, t0, t1\n");
        /* push t2*/
        push_stack("t2", "sp", 0);
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1879 "y.tab.c"
break;
case 43:
#line 381 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t2 = (t1 == t0) ? 1 : 0*/
        fprintf(codegen, "xor t2, t1, t0\n");
        fprintf(codegen, "sltu t2, zero, t2\n");
        fprintf(codegen, "xori t2, t2, 1\n");
        /* push t2*/
        push_stack("t2", "sp", 0);
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1896 "y.tab.c"
break;
case 44:
#line 394 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t2 = (t1 != t0) ? 1 : 0*/
        fprintf(codegen, "xor t2, t1, t0\n");
        fprintf(codegen, "sltu t2, zero, t2\n");
        /* push t2*/
        push_stack("t2", "sp", 0);
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 1912 "y.tab.c"
break;
case 45:
#line 406 "parser.y"
	{
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t0 = -t0*/
        fprintf(codegen, "sub t0, zero, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = yystack.l_mark[0].intVal;
    }
#line 1926 "y.tab.c"
break;
case 46:
#line 416 "parser.y"
	{ yyval.intVal = yystack.l_mark[0].intVal; }
#line 1931 "y.tab.c"
break;
case 47:
#line 417 "parser.y"
	{ yyval.intVal = yystack.l_mark[-1].intVal; }
#line 1936 "y.tab.c"
break;
case 48:
#line 418 "parser.y"
	{
        /* Section C */
        /* a1 = expr2 (pop)*/
        pop_stack("a1", "sp", 0);
        /* a0 = expr1 (pop)*/
        pop_stack("a0", "sp", 0);
        /* call IDENTIFIER()*/
        fprintf(codegen, "jal ra, %s\n", yystack.l_mark[-5].str);
        fprintf(codegen, "\n");
        /* Section D */
        /* push the function return value onto stack*/
        push_stack("a0", "sp", 0);
        yyval.intVal = TYPE_INT;
    }
#line 1954 "y.tab.c"
break;
case 49:
#line 432 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = t1 + t0*/
        fprintf(codegen, "ukadd8 t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 1970 "y.tab.c"
break;
case 50:
#line 444 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = (t1 == t0) ? 1 : 0*/
        fprintf(codegen, "cmpeq8 t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 1986 "y.tab.c"
break;
case 51:
#line 456 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = (t1 < t0) ? 1 : 0*/
        fprintf(codegen, "ucmplt8 t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 2002 "y.tab.c"
break;
case 52:
#line 468 "parser.y"
	{
        /* t0 = expr2 (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = expr1 (pop)*/
        pop_stack("t1", "sp", 0);
        /* t0 = t1 - t0*/
        fprintf(codegen, "uksub8 t0, t1, t0\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 2018 "y.tab.c"
break;
case 53:
#line 480 "parser.y"
	{
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = variable (pop)*/
        pop_stack("t1", "sp", 0);
        /* *variable = t0*/
        fprintf(codegen, "sw t0, 0(t1)\n");
        fprintf(codegen, "\n");
        yyval.intVal = yystack.l_mark[-2].intVal;
    }
#line 2032 "y.tab.c"
break;
case 54:
#line 490 "parser.y"
	{
        /* t0 = variable (pop)*/
        pop_stack("t0", "sp", 0);
        /* t1 = *variable*/
        fprintf(codegen, "lw t1, 0(t0)\n");
        /* push t1*/
        push_stack("t1", "sp", 0);
        changeLine();
        yyval.intVal = yystack.l_mark[0].intVal;
    }
#line 2046 "y.tab.c"
break;
case 55:
#line 500 "parser.y"
	{
        /* t0 = INTEGER*/
        fprintf(codegen, "li t0, %d\n", yystack.l_mark[0].intVal);
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = yystack.l_mark[0].intVal;
    }
#line 2058 "y.tab.c"
break;
case 56:
#line 511 "parser.y"
	{
        int idx = lookup_symbol(yystack.l_mark[0].str);
        /* t0 = IDENTIFIER's address*/
        fprintf(codegen, "addi t0, fp, %d\n", get_offset(yystack.l_mark[0].str));
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = symbol_table[idx].type;
    }
#line 2071 "y.tab.c"
break;
case 57:
#line 520 "parser.y"
	{
        /* IDENTIFIER is a pointer*/
        /* t0 = IDENTIFIER's value (IDENTIFIER[0]'s address)*/
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset(yystack.l_mark[-3].str));
        /* t1 = expr * 4 (pop)*/
        pop_stack_pt("t1", "sp", 0);
        /* t0 = IDENTIFIER[expr]'s address*/
        fprintf(codegen, "sub t0, t0, t1\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 2088 "y.tab.c"
break;
case 58:
#line 533 "parser.y"
	{
        /* IDENTIFIER is a pointer*/
        /* t0 = IDENTIFIER's value (an address)*/
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset(yystack.l_mark[0].str));
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 2101 "y.tab.c"
break;
case 59:
#line 542 "parser.y"
	{
        /* IDENTIFIER is a pointer*/
        /* t0 = IDENTIFIER's value (IDENTIFIER[0]'s address)*/
        fprintf(codegen, "lw t0, %d(fp)\n", get_offset(yystack.l_mark[-3].str));
        /* t1 = expr * 4 (pop)*/
        pop_stack_pt("t1", "sp", 0);
        /* t0 = IDENTIFIER[expr]'s address*/
        fprintf(codegen, "sub t0, t0, t1\n");
        /* push t0*/
        push_stack("t0", "sp", 0);
        changeLine();
        yyval.intVal = TYPE_INT;
    }
#line 2118 "y.tab.c"
break;
case 60:
#line 558 "parser.y"
	{ yyval.str = "expr"; }
#line 2123 "y.tab.c"
break;
case 61:
#line 559 "parser.y"
	{
        /* end_if*/
        fprintf(codegen, ".IF%d0:\n", if_counter);
    }
#line 2131 "y.tab.c"
break;
case 69:
#line 573 "parser.y"
	{
        if_counter++;
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t0 == 0: jump to .IF10 (end_if / else)*/
        /* t0 == 1: continue to do*/
        fprintf(codegen, "beq t0, zero, .IF%d0\n", if_counter);
        changeLine();
    }
#line 2144 "y.tab.c"
break;
case 71:
#line 585 "parser.y"
	{
                /* finish if part, jump to .IF11 (end_if)*/
                fprintf(codegen, "j .IF%d1\n", if_counter);
                /* else*/
                fprintf(codegen, ".IF%d0:\n", if_counter);
            }
#line 2154 "y.tab.c"
break;
case 72:
#line 591 "parser.y"
	{
                /* end_if*/
                if(!nested_if){
                    fprintf(codegen, ".IF%d1:\n", if_counter);
                    nested_if = 1;
                }else
                    fprintf(codegen, ".IF11: \n");
                    
            }
#line 2167 "y.tab.c"
break;
case 73:
#line 603 "parser.y"
	{
        fprintf(codegen, ".WHILE:\n");
    }
#line 2174 "y.tab.c"
break;
case 74:
#line 606 "parser.y"
	{
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t0 == 0: jump to .END_WHILE*/
        /* t0 == 1: continue to do*/
        fprintf(codegen, "beq t0, zero, .END_WHILE\n");
        changeLine();
    }
#line 2186 "y.tab.c"
break;
case 75:
#line 614 "parser.y"
	{
        fprintf(codegen, "j .WHILE\n");
        changeLine();
        fprintf(codegen, ".END_WHILE:\n");
    }
#line 2195 "y.tab.c"
break;
case 76:
#line 619 "parser.y"
	{
        fprintf(codegen, ".DOWHILE:\n");
    }
#line 2202 "y.tab.c"
break;
case 77:
#line 622 "parser.y"
	{
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t0 == 0: jump to .END_DOWHILE*/
        /* t0 == 1: continue to do*/
        fprintf(codegen, "beq t0, zero, .END_DOWHILE\n");
        changeLine();
        fprintf(codegen, "j .DOWHILE\n");
        changeLine();
        fprintf(codegen, ".END_DOWHILE:\n");
    }
#line 2217 "y.tab.c"
break;
case 78:
#line 636 "parser.y"
	{
        for_counter++;
        fprintf(codegen, ".FOR%d:\n", for_counter);
    }
#line 2225 "y.tab.c"
break;
case 79:
#line 640 "parser.y"
	{
        /* t0 = expr (pop)*/
        pop_stack("t0", "sp", 0);
        /* t0 == 0: jump to .END_FOR*/
        /* t0 == 1: jump to .FOR_STMT*/
        fprintf(codegen, "beq t0, zero, .END_FOR%d\n", for_counter);
        changeLine();
        fprintf(codegen, "j .FOR%d_STMT\n", for_counter);
        changeLine();
        fprintf(codegen, ".FOR%d_UPDATE:\n", for_counter);
    }
#line 2240 "y.tab.c"
break;
case 80:
#line 651 "parser.y"
	{
        fprintf(codegen, "j .FOR%d\n", for_counter);
        changeLine();
        fprintf(codegen, ".FOR%d_STMT:\n", for_counter);
    }
#line 2249 "y.tab.c"
break;
case 81:
#line 656 "parser.y"
	{
        fprintf(codegen, "j .FOR%d_UPDATE\n" , for_counter);
        changeLine();
        fprintf(codegen, ".END_FOR%d:\n" , for_counter);
    }
#line 2258 "y.tab.c"
break;
case 82:
#line 664 "parser.y"
	{
        /* Section B */
        /* a0 = function return value (pop)*/
        pop_stack("a0", "sp", 0);
        /* restore ra, restore old fp, remove the frame*/
        restore_reg();
    }
#line 2269 "y.tab.c"
break;
case 83:
#line 671 "parser.y"
	{
        fprintf(codegen, "j .END_WHILE\n");
    }
#line 2276 "y.tab.c"
break;
case 84:
#line 677 "parser.y"
	{ cur_scope++; }
#line 2281 "y.tab.c"
break;
case 85:
#line 678 "parser.y"
	{
        pop_symbol(cur_scope);
        cur_scope--;
    }
#line 2289 "y.tab.c"
break;
case 87:
#line 686 "parser.y"
	{
        /* a0 = expr (pop)*/
        pop_stack("a0", "sp", 0);
        /* a1 = 1*/
        fprintf(codegen, "li a1, 1\n");
        /* call digitalWrite()*/
        fprintf(codegen, "jal ra, digitalWrite\n");
        changeLine();
    }
#line 2302 "y.tab.c"
break;
case 88:
#line 695 "parser.y"
	{
        /* a0 = expr (pop)*/
        pop_stack("a0", "sp", 0);
        /* a1 = 0*/
        fprintf(codegen, "li a1, 0\n");
        /* call digitalWrite()*/
        fprintf(codegen, "jal ra, digitalWrite\n");
        changeLine();
    }
#line 2315 "y.tab.c"
break;
case 89:
#line 707 "parser.y"
	{
        /* a0 = expr (pop)*/
        pop_stack("a0", "sp", 0);
        /* call delay()*/
        fprintf(codegen, "jal ra, delay\n");
        changeLine();
    }
#line 2326 "y.tab.c"
break;
#line 2328 "y.tab.c"
    default:
        break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark -= yym;
#endif
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
        {
            fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
            if (!yytrial)
#endif /* YYBTYACC */
                fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[YYFINAL], yyval));
#endif
            fprintf(stderr, "shifting from state 0 to final state %d\n", YYFINAL);
        }
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        *++yystack.p_mark = yyloc;
#endif
        if (yychar < 0)
        {
#if YYBTYACC
            do {
            if (yylvp < yylve)
            {
                /* we're currently re-reading tokens */
                yylval = *yylvp++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                yylloc = *yylpp++;
#endif
                yychar = *yylexp++;
                break;
            }
            if (yyps->save)
            {
                /* in trial mode; save scanner results for future parse attempts */
                if (yylvp == yylvlim)
                {   /* Enlarge lexical value queue */
                    size_t p = (size_t) (yylvp - yylvals);
                    size_t s = (size_t) (yylvlim - yylvals);

                    s += YYLVQUEUEGROWTH;
                    if ((yylexemes = (YYINT *)realloc(yylexemes, s * sizeof(YYINT))) == NULL)
                        goto yyenomem;
                    if ((yylvals   = (YYSTYPE *)realloc(yylvals, s * sizeof(YYSTYPE))) == NULL)
                        goto yyenomem;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    if ((yylpsns   = (YYLTYPE *)realloc(yylpsns, s * sizeof(YYLTYPE))) == NULL)
                        goto yyenomem;
#endif
                    yylvp   = yylve = yylvals + p;
                    yylvlim = yylvals + s;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                    yylpp   = yylpe = yylpsns + p;
                    yylplim = yylpsns + s;
#endif
                    yylexp  = yylexemes + p;
                }
                *yylexp = (YYINT) YYLEX;
                *yylvp++ = yylval;
                yylve++;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
                *yylpp++ = yylloc;
                yylpe++;
#endif
                yychar = *yylexp++;
                break;
            }
            /* normal operation, no conflict encountered */
#endif /* YYBTYACC */
            yychar = YYLEX;
#if YYBTYACC
            } while (0);
#endif /* YYBTYACC */
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                fprintf(stderr, "%s[%d]: state %d, reading token %d (%s)\n",
                                YYDEBUGSTR, yydepth, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
    {
        fprintf(stderr, "%s[%d]: after reduction, ", YYDEBUGSTR, yydepth);
#ifdef YYSTYPE_TOSTRING
#if YYBTYACC
        if (!yytrial)
#endif /* YYBTYACC */
            fprintf(stderr, "result is <%s>, ", YYSTYPE_TOSTRING(yystos[yystate], yyval));
#endif
        fprintf(stderr, "shifting from state %d to state %d\n", *yystack.s_mark, yystate);
    }
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    *++yystack.p_mark = yyloc;
#endif
    goto yyloop;
#if YYBTYACC

    /* Reduction declares that this path is valid. Set yypath and do a full parse */
yyvalid:
    if (yypath) YYABORT;
    while (yyps->save)
    {
        YYParseState *save = yyps->save;
        yyps->save = save->save;
        save->save = yypath;
        yypath = save;
    }
#if YYDEBUG
    if (yydebug)
        fprintf(stderr, "%s[%d]: state %d, CONFLICT trial successful, backtracking to state %d, %d tokens\n",
                        YYDEBUGSTR, yydepth, yystate, yypath->state, (int)(yylvp - yylvals - yypath->lexeme));
#endif
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    yylvp          = yylvals + yypath->lexeme;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yylpp          = yylpsns + yypath->lexeme;
#endif
    yylexp         = yylexemes + yypath->lexeme;
    yychar         = YYEMPTY;
    yystack.s_mark = yystack.s_base + (yypath->yystack.s_mark - yypath->yystack.s_base);
    memcpy (yystack.s_base, yypath->yystack.s_base, (size_t) (yystack.s_mark - yystack.s_base + 1) * sizeof(YYINT));
    yystack.l_mark = yystack.l_base + (yypath->yystack.l_mark - yypath->yystack.l_base);
    memcpy (yystack.l_base, yypath->yystack.l_base, (size_t) (yystack.l_mark - yystack.l_base + 1) * sizeof(YYSTYPE));
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
    yystack.p_mark = yystack.p_base + (yypath->yystack.p_mark - yypath->yystack.p_base);
    memcpy (yystack.p_base, yypath->yystack.p_base, (size_t) (yystack.p_mark - yystack.p_base + 1) * sizeof(YYLTYPE));
#endif
    yystate        = yypath->state;
    goto yyloop;
#endif /* YYBTYACC */

yyoverflow:
    YYERROR_CALL("yacc stack overflow");
#if YYBTYACC
    goto yyabort_nomem;
yyenomem:
    YYERROR_CALL("memory exhausted");
yyabort_nomem:
#endif /* YYBTYACC */
    yyresult = 2;
    goto yyreturn;

yyabort:
    yyresult = 1;
    goto yyreturn;

yyaccept:
#if YYBTYACC
    if (yyps->save) goto yyvalid;
#endif /* YYBTYACC */
    yyresult = 0;

yyreturn:
#if defined(YYDESTRUCT_CALL)
    if (yychar != YYEOF && yychar != YYEMPTY)
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval, &yylloc);
#else
        YYDESTRUCT_CALL("cleanup: discarding token", yychar, &yylval);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */

    {
        YYSTYPE *pv;
#if defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED)
        YYLTYPE *pp;

        for (pv = yystack.l_base, pp = yystack.p_base; pv <= yystack.l_mark; ++pv, ++pp)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv, pp);
#else
        for (pv = yystack.l_base; pv <= yystack.l_mark; ++pv)
             YYDESTRUCT_CALL("cleanup: discarding state",
                             yystos[*(yystack.s_base + (pv - yystack.l_base))], pv);
#endif /* defined(YYLTYPE) || defined(YYLTYPE_IS_DECLARED) */
    }
#endif /* defined(YYDESTRUCT_CALL) */

#if YYBTYACC
    if (yyerrctx)
    {
        yyFreeState(yyerrctx);
        yyerrctx = NULL;
    }
    while (yyps)
    {
        YYParseState *save = yyps;
        yyps = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
    while (yypath)
    {
        YYParseState *save = yypath;
        yypath = save->save;
        save->save = NULL;
        yyFreeState(save);
    }
#endif /* YYBTYACC */
    yyfreestack(&yystack);
    return (yyresult);
}

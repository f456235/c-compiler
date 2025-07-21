#ifndef _yy_defines_h_
#define _yy_defines_h_

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
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union YYSTYPE {
    int intVal;
    char* str;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
extern YYSTYPE yylval;

#endif /* _yy_defines_h_ */

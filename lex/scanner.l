
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    
    int source_on = 1;
    int token_on = 1;
    char* src = "";
    char* res;
    

    void read_line(char *s){
        res = malloc(strlen(src) + strlen(s) + 1);
        strcpy(res, src);
        strcat(res, s);
        src = res;
    }

    void source(){
        if(source_on == 1)
            printf("%d:%s", yylineno-1 , src);
        src = "";
    }
%}

%option yylineno

%x COMMENT_S
%x COMMENT_M


Keywords            "for"|"do"|"while"|"break"|"continue"|"if"|"else"|"return"|"struct"|"switch"|"case"|"default"|"void"|"int"|"double"|"float"|"char"|"const"|"signed"|"unsigned"|"short"|"long"
Macros              "NULL"|"__COUNTER__"|"__LINE__"|"INT_MAX"|"INT_MIN"|"CHAR_MAX"|"CHAR_MIN"|"MAX"|"MIN"
Identifiers         [_a-zA-Z][_a-zA-Z0-9]*
Operators           "+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|"="|"&&"|"||"|"!"|"&"|"|"
Punctuations        ":"|";"|","|"."|"["|"]"|"("|")"|"{"|"}"
Integer             [+-]?[0-9]+
Floating            [+-]?[0-9]+"."[0-9]*|[+-]?[0-9]*"."[0-9]+
Char                \'(\\.|[^'\\])\'|\'"\\"[0-7]{1,3}\'|\'"\\x"[0-9a-fA-F]+\'|\'"\\u"[0-9a-fA-F]{4}\'|\'"\\U"[0-9a-fA-F]{8}\'
String              \"(\\.|[^\n"\\])*\"


%%


{Keywords}        {read_line(yytext); if(token_on) printf("#key:%s\n",yytext);}
{Macros}          {read_line(yytext); if(token_on) printf("#macro:%s\n",yytext); }
{Identifiers}     {read_line(yytext); if(token_on) printf("#id:%s\n",yytext); }
{Integer}         {read_line(yytext); if(token_on) printf("#integer:%s\n",yytext); }
{Punctuations}    {read_line(yytext); if(token_on) printf("#punc:%s\n",yytext); }
{Operators}       {read_line(yytext); if(token_on) printf("#op:%s\n",yytext); }
{Floating}        {read_line(yytext); if(token_on) printf("#float:%s\n",yytext); }
{Char}            {read_line(yytext); if(token_on) printf("#char:%s\n",yytext); }
{String}          {read_line(yytext); if(token_on) printf("#string:%s\n",yytext); }

"#pragma"[" "|"\t"]+"source"[" "|"\t"]+"on"   {read_line(yytext); source_on = 1; }
"#pragma"[" "|"\t"]+"source"[" "|"\t"]+"off"  {read_line(yytext); source_on = 0; }
"#pragma"[" "|"\t"]+"token"[" "|"\t"]+"on"    {read_line(yytext); token_on = 1; }
"#pragma"[" "|"\t"]+"token"[" "|"\t"]+"off"   {read_line(yytext); token_on = 0; }


"//".*            {read_line(yytext);}
"//".*"\\\n"      {read_line(yytext); source(); BEGIN COMMENT_S;}
<COMMENT_S>"\\\n" {read_line(yytext); source(); }
<COMMENT_S>"\n"   {read_line(yytext); source(); BEGIN 0;}

"/*"              {read_line(yytext); BEGIN COMMENT_M;}
<COMMENT_M>"*/"   {read_line(yytext); BEGIN 0;}
<COMMENT_M>"\n"   {read_line(yytext); source(); }

"\n"              {read_line(yytext); source(); }
.                 {read_line(yytext);}
<COMMENT_S>.      {read_line(yytext);}
<COMMENT_M>.      {read_line(yytext);}
%%

int yywrap() {
    return 1;
}

int main(){

    yylex();
    return 0;

}
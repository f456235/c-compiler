
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    
    char* copyline(const char *line){
        char *new_line = (char*)malloc(strlen(line)+1);
        strcpy(new_line,line);
        return new_line;
    }

    int source_on = 0;
    int token_on = 0;
%}



%x COMMENT_S
%x COMMENT_M




Identifiers         [_a-zA-Z][_a-zA-Z0-9]*
Operators           "+"|"-"|"*"|"/"|"%"|"~"|"="|"^"|"!"|"&"|"|"
Punctuations        ":"|";"|","|"."|"["|"]"|"("|")"|"{"|"}"
Integer             [0-9]+
Char                \'(\\.|[^'\\])\'|\'"\\"[0-7]{1,3}\'|\'"\\x"[0-9a-fA-F]+\'|\'"\\u"[0-9a-fA-F]{4}\'|\'"\\U"[0-9a-fA-F]{8}\'
String              \"(\\.|[^\n"\\])*\"


%%

[ \t\n]           {}

 
"#pragma"[ \t]+"source"[ \t]+"on"   {source_on = 1;}
"#pragma"[ \t]+"source"[ \t]+"off"  {source_on = 0;}
"#pragma"[ \t]+"token"[ \t]+"on"    {token_on = 1;}
"#pragma"[ \t]+"token"[ \t]+"off"   {token_on = 0;}

"__rv__ukadd8"    {yylval.str = copyline(yytext); return __RV__UKADD8; }
"__rv__cmpeq8"    {yylval.str = copyline(yytext); return __RV__CMPEQ8; }
"__rv__ucmplt8"   {yylval.str = copyline(yytext); return __RV__UCMPLT8; }
"__rv__uksub8"    {yylval.str = copyline(yytext); return __RV__UKSUB8; }
"ext_dsp_codegen" {yylval.str = copyline(yytext); return EXTDSPCODEGEN; }
"codegen"         {yylval.str = copyline(yytext); return CODEGEN;}
"digitalWrite"    {yylval.str = copyline(yytext); return DIGITALWRITE;}
"delay"           {yylval.str = copyline(yytext); return DELAY;}
"HIGH"            {yylval.intVal = 1; return HIGH;}
"LOW"             {yylval.intVal = 0; return LOW;}

"const"           {yylval.str = copyline(yytext); return CONST;}
"int"             {yylval.str = copyline(yytext); return INT;}
"uint32_t"        {yylval.str = copyline(yytext); return TYPEUINT32;}
"void"            {yylval.str = copyline(yytext); return VOID;}


"if"              {yylval.str = copyline(yytext); return IF;}
"else"            {yylval.str = copyline(yytext); return ELSE;}

"do"              {yylval.str = copyline(yytext); return DO;}
"while"           {yylval.str = copyline(yytext); return WHILE;}
"for"             {yylval.str = copyline(yytext); return FOR;}
"break"           {yylval.str = copyline(yytext); return BREAK;}

"return"          {yylval.str = copyline(yytext); return RETURN;}


{Identifiers}     {yylval.str = copyline(yytext); return IDENTIFIER;}
{Integer}         {yylval.intVal = atoi(yytext); return INTEGER;}
{Punctuations}    {yylval.str = copyline(yytext); return yytext[0];}
{Operators}       {yylval.str = copyline(yytext); return yytext[0];}



"<"               {yylval.str = copyline(yytext); return yytext[0];}

">"               {yylval.str = copyline(yytext); return yytext[0];}

"=="              {yylval.str = copyline(yytext); return EQ;}
"!="              {yylval.str = copyline(yytext); return NE;}



"//".*            {}
"//".*"\\\n"      {BEGIN COMMENT_S;}
<COMMENT_S>"\\\n" {}
<COMMENT_S>"\n"   {BEGIN 0;}

"/*"              {BEGIN COMMENT_M;}
<COMMENT_M>"*/"   {BEGIN 0;}
<COMMENT_M>"\n"   {}

.                 {}
<COMMENT_S>.      {}
<COMMENT_M>.      {}
%%


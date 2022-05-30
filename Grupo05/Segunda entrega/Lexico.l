%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

#include "y.tab.h"

FILE  *yyin;
FILE *tab;
char *yyltext;

int yyerror(void);
char errorMsg[100];


%}

%option noyywrap  
%option yylineno 

DIGITO			[0-9]
LETRA			[a-zA-Z]
COMENTARIO		-\/([^\/]|\/+[^-])*\/-

CTE_STRING		\"([^\"\\\\]|\\\\.)*\"
CTE_FLOAT		({DIGITO}+"."{DIGITO}+)|("."{DIGITO}+)|({DIGITO}+".")
CTE_INT			({DIGITO}+)|("-".{DIGITO}+)
ID			    {LETRA}({LETRA}|{DIGITO})*
OP_ASIG   		":""="
OP_SUM		    "+"
OP_MUL          "*"
OP_RES		    "-"
OP_DIV          "/"
P_ABRE		    "("
P_CIERRA	    ")"
LL_ABRE         "{"
LL_CIERRA       "}"
C_ABRE          "["
C_CIERRA        "]"
COMA            ","
PUNTO           "."
P_Y_COMA        ";"
DOS_PUNTOS      ":"
MAYOR           ">"
MENOR           "<"
MAY_O_IG        ">""="
MEN_O_IG        "<""="
DISTINTO        "!""="
IGUAL           "=""="
RESTO           "%"


%%

"DECVAR"		{return DECVAR;}
"ENDDEC"		{return ENDDEC;}
"INT"			{return INT;}
"FLOAT"			{return FLOAT;}
"STRING"		{return STRING;}

"IF"		    {return IF;}
"ELSE"			{return ELSE;}
"ENDIF"			{return ENDIF;}
"WHILE"			{return WHILE;}
"ENDWHILE"		{return ENDWHILE;}
"WRITE"			{return WRITE;}
"READ"			{return READ;}
"AVG"           {return AVG;}
"TAKE"          {return TAKE;}
"OR"|"or"		{return OR;}
"AND"|"and"		{return AND;}
"!"				{return NEGADO;}

{CTE_STRING}	{
					char nombre[31];
					char valor[30];
					sprintf(nombre, "_%s", yytext);
					if(strlen(yytext)> 32 ){
						sprintf(errorMsg, "El String \"%s\" se excede del limite de 30 caracteres.\n", yytext);
						errorLexico(errorMsg);
					}else{
						sprintf(valor, "%s", yytext);
					}
					
					if(buscarEnTabla(nombre) == -1) insertarEnTabla(nombre, "CTE_STRING", valor, (int)strlen(yytext));
					yylval.string_val = yytext;
					return CTE_STRING;

                }

{CTE_INT}		{
					if( validarEntero(yytext) == 1 ) {
						sprintf(errorMsg, "El entero \"%s\" se excede del limite (MIN: %d MAX: %d).\n", yytext, SHRT_MIN + 1, SHRT_MAX - 1);
						errorLexico(errorMsg);
					} else {
						char nombre[31];
						char valor[30];
						sprintf(nombre, "_%d", atoi(yytext));
						sprintf(valor, "%d", atoi(yytext));
					
						if(buscarEnTabla(nombre) == -1) insertarEnTabla(nombre, "CTE_INT", valor, (int)strlen(yytext));
					}
					yylval.int_val = (int)yytext;
					return CTE_INT;
                }
                
{CTE_FLOAT}		{
					if( validarFlotante(yytext) == 1) {
						sprintf(errorMsg, "El flotante \"%s\" se excede del limite (MIN: %E MAX: %E).\n", yytext, FLT_MIN, FLT_MAX);
						errorLexico(errorMsg);
					}else{
						char nombre[31];
						char valor[30];
						sprintf(nombre, "_%.2f", atof(yytext));
						sprintf(valor, "%.2f", atof(yytext));
				
					if(buscarEnTabla(nombre) == -1) insertarEnTabla(nombre, "CTE_FLOAT", valor, (int)strlen(yytext));
					}
					yylval.float_val = (int)yytext;
					return CTE_FLOAT;
                }

{ID}			{

					char nombre[31];
					char valor[30];
					sprintf(nombre, "_%d", atoi(yytext));
					sprintf(valor, "%d", atoi(yytext));
					
					if(buscarEnTabla(nombre) == -1) insertarEnTabla(nombre, "", valor, "");
					yylval.string_val = yytext;
					return ID;
                }

{OP_SUM}		{return OP_SUM;}
{OP_ASIG}		{return OP_ASIG;}
{OP_MUL}		{return OP_MUL;}
{OP_RES}		{return OP_RES;}
{OP_DIV}		{return OP_DIV;}
{P_ABRE}		{return P_ABRE;}
{P_CIERRA}		{return P_CIERRA;}
{LL_ABRE}		{return LL_ABRE;}
{LL_CIERRA}		{return LL_CIERRA;}
{C_ABRE}		{return C_ABRE;}
{C_CIERRA}		{return C_CIERRA;}
{COMA}		    {return COMA;}
{PUNTO}		    {return PUNTO;}
{P_Y_COMA}		{return P_Y_COMA;}
{DOS_PUNTOS}	{return DOS_PUNTOS;}
{MAYOR}		    {return MAYOR;}
{MENOR}		    {return MENOR;}
{MAY_O_IG}		{return MAY_O_IG;}
{MEN_O_IG}		{return MEN_O_IG;}
{DISTINTO}		{return DISTINTO;}
{IGUAL}		    {return IGUAL;}
{RESTO}		    {return RESTO;}
{COMENTARIO}    

"\n"      		
"\t"
"\n\t"
" "             		
"\r\n"
.			 { printf( "ERROR LEXICO : Caracter no reconocido: %s\n", yytext ); exit (0);}
%%

int yyerror(void)
{
	printf("\nError sintactico en la linea %d\n",yylineno-1);
	system ("Pause");
	exit (1);
}
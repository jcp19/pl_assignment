%token type
%token ident
%token num
%token str
%token while
%token if
%token ret
%token str_literal
%token begin
%token end

%{
#include <stdio.h>
#include <stdlib.h>

%}

%%
/* Ideias
 -> Precednecia de operadores
 -> Argumentos nas funcoes
 -> Mais tipos (float)
 -> Usar values no acesso aos arrays nos decl
*/
Programa : {offset = 0} Decl_block Fun_prods begin Main_block end
         ;

Decl_block :
           | Decl_block type ident ';' 											{	if(!lookup($3))
		   																			{
																						enter($3,$2,offset);
																						offset += 4; /* type -> int*/
																					}
																					else
																						error(); /* redeclaration */
																				}
		   | Decl_block type ident '[' Value']' ';'								{	if(!lookup($3))
		   																			{
																						enter($3,$2,offset);
																						offset += $5*4; /* type -> int*/
																					}
																					else
																						error();
			   																	}
           | Decl_block type ident '['Value']' '['Value']' ';'					{	if(!lookup($3))
		   																			{
																						enter($3,$2,offset);
																						offset += $5*$8*4; /* type -> int*/
																					}
																					else
																						error();
			   																	}
           | Decl_block type ident '=' Value ';'								{	if(!lookup($3))
		   																			{
																						enter($3,$2,offset);
																						assign(offset,$5); /* ?? */
																						offset += 4;
																					}
																					else
																						erro();
			   																	}
           ;

Fun_prods :
          | Fun_prods Fun_prod
          ;

Fun_prod : ident '(' ')' ':' type  '{' Decl_block LInstr '}'
         ;

LInstr : 
       | LInstr Instr
       ;

Instr : while '(' Value ')' '{' LInstr '}'
      | if '(' Value ')' '{' LInstr '}'
      | ident '=' Value BOp Value ';'
      | ident '=' UOp Value ';'
      | ident '=' Value ';'
      | Value ';'
      | ReturnExpr ';'
      ;
/* deve-se por expressoes nao atomicas entre parenteses de forma a forçar a precedencia dos operadores */
Value : '(' Value ')' 
      | str_literal 
      | num 
      | Function_call 
      | ident'['Value']'
      | ident'['Value']''['Value']'
      | ident
      ;

ReturnExpr : ret
           | ret Value
           | ret Value BOp Value 
           | ret UOp Value 
           ;

/* se adicionar args as funcoes, mudar aqui */
Function_call : ident '(' ')'
              ;


BOp : '+'
    | '-'
    ;

UOp : '+'
    | '-'
    ;

Main_block : LInstr
           ;


%%

#include "yy.lex.c"

int yyerror(char *s){
    printf("erro: %s\n",s);
}

int main() {
    yyparse();
    return 0;
}

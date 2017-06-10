%token type
%token ident
%token num
%token str
%token while
%token if
%token ret
%token str_literal

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
Programa : Decl_block Fun_prods Main_block
         ;

Decl_block : 
           | Decl_block type ident ';'
           | Decl_block type ident '[' Value']' ';'
           | Decl_block type ident '['Value']' '['Value']' ';'
           | Decl_block type ident '=' Value ';'
           ;

Fun_prods :
          | Fun_prods Fun_prod
          ;

Fun_prod : type ident '(' ')' '{' Decl_block LInstr '}'
         ;

LInstr : 
       | LInstr Instr
       ;

Instr : while '(' Value ')' '{' LInstr '}'
      | if '(' Value ')' '{' LInstr '}'
      | ident '=' Value ';'
      | ident '=' Value BOp Value ';'
      | ident '=' UOp Value ';'
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

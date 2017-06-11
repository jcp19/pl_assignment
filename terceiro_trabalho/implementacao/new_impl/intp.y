%token type
%token ident
%token num
%token str
%token while_token
%token if_token
%token ret
%token str_literal
%token begin
%token end
%token READ
%token WRITE

%{
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


int yyerror (char *s);

typedef struct {
    int valor_inicial;
    int offset;
    int numero_linhas;
    int numero_colunas;
} entrada_tabela;

typedef entrada_tabela* Entrada_tabela;

// assume-se que os arrays nao podem ser inicializados, os seus valores devem ser modificados manualmente;

Entrada_tabela new_Entrada_tabela(int valor_inicial, int offset, int numero_linhas, int numero_colunas) {
    Entrada_tabela e = malloc(sizeof(entrada_tabela));
    e->valor_inicial = valor_inicial;
    e->offset = offset;
    e->numero_linhas = numero_linhas;
    e->numero_colunas = numero_colunas;
}

GHashTable * tabela_simbolos;
int ultimo_offset = 0;


%}


%union {
    int valor;
    char * identificador;
}

%type <identificador> ident
%type <valor> num

%%

/* Ideias
neste momento so da para ints
 -> Precednecia de operadores
 -> Argumentos nas funcoes
 -> Mais tipos (float e str): omitir cenas str
 -> Usar values no acesso aos arrays nos decl
*/
Programa : Decl_block Fun_prods begin Main_block end
         ;

Decl_block : 
           | Decl_block type ident ';' { 
                       Entrada_tabela e = new_Entrada_tabela(0, ultimo_offset++, 1, 1);
                       gboolean b = g_hash_table_insert(tabela_simbolos, $3, e); 
                       if(b == FALSE){
                         yyerror("Redefinição da variável."); // por a aparecer nome
                       }
                       printf("var %s lida com sucesso\n", $3);
                      }
           | Decl_block type ident '[' Value ']' ';' {
                       printf("%s\n", $5);
                       /*Entrada_tabela e = new_Entrada_tabela(0, ultimo_offset, 1, $5);
                       ultimo_offset += $5;
                       gboolean b = g_hash_table_insert(tabela_simbolos, $3, e); 
                       if(b == FALSE){
                         yyerror("Redefinição da variável."); // por a aparecer nome
                       }*/
                       printf("var %s lida com sucesso\n", $3);

 
            }
           | Decl_block type ident '['Value']' '['Value']' ';'
           | Decl_block type ident '=' Value ';'
           ;

Fun_prods :
          | Fun_prods Fun_prod
          ;

Fun_prod : ident '(' ')' ':' type  '{' Decl_block LInstr '}'
         ;

LInstr : 
       | LInstr Instr
       ;

Instr : while_token '(' Value ')' '{' LInstr '}'
      | if_token '(' Value ')' '{' LInstr '}'
      | ident '=' Value BOp Value ';'
      | ident '=' UOp Value ';'
      | ident '=' Value ';'
      | ident '=' ident ';'
      | Value ';'
      | WRITE str_literal ';'
      | READ ident ';'
      | ReturnExpr ';'
      ;
/* deve-se por expressoes nao atomicas entre parenteses de forma a forçar a precedencia dos operadores */
Value : '(' Value ')' { return $2; }
      | num { return $1; }
      | Function_call { return $1; }
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

#include "lex.yy.c"

int yyerror (char *s) {
  fprintf(stderr, "%s \n", s);
  exit(-1);
  return 0;
}

int main() {
    tabela_simbolos =  g_hash_table_new(g_str_hash,g_str_equal);
    yyparse();
    return 0;
}

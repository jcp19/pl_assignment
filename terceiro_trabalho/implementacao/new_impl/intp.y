%token type
%token ident
%token num
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
#include <string.h>

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

int label = 0;
/*
char programa_gerado[32000];
int contador_programa_gerado = 0;

void print_programa_gerado() {
  printf("%s", strrev(strdup(programa_gerado)));
}

void adiciona_instrucoes(char * instrucoes){
    char * ins = strdup(instrucoes);
    ins = strrev(ins);
    contador_programa_gerado += (programa_gerado + contador_programa_gerado, "%s", ins);
}
*/

void registar_var(char * nome_var) {
     registar_matriz(nome_var, 1, 1);
}

void registar_array(char * nome_var, int dim) {
     registar_matriz(nome_var, 1, dim);
}

void registar_matriz(char * nome_var, int linhas, int colunas){
    Entrada_tabela e = new_Entrada_tabela(0, ultimo_offset, linhas, colunas);
    ultimo_offset += linhas * colunas;
    gboolean b = g_hash_table_insert(tabela_simbolos, nome_var, e); 
    if(b == FALSE){
        //yyerror("ERRO: Redefinição da variável '%s'\n", nome_var); 
        yyerror("ERRO: Redefinição da variável"); 
    }
}

%}


%union {
    int valor;
    char * identificador;
}

%type <identificador> ident
%type <valor> num
%type <identificador> Programa 
%type <identificador> Decl_block 

%%

/* Ideias
neste momento so da para ints
 -> Precednecia de operadores
 -> Argumentos nas funcoes
 -> Mais tipos (float e str): omitir cenas str
 -> Usar values no acesso aos arrays nos decl
*/
Programa : Decl_block Fun_prods begin Main_block end {
                //printf("declaracoes:\n%s\nstart\n%s\nmain:\n%sstop\n", $1, $2, $4);
                // completar
                printf("declaracoes:\n%s\nstart\nmain:\nstop\n", $1);
            }
         ;

Decl_block : 
           | Decl_block type ident ';' { 
                                           registar_var($3);  
                                           asprintf(&$$, "%s\t%s\n", ($1 == NULL)?"" : $1, "pushi 0");
                                       }
           | Decl_block type ident '[' num ']' ';' { 
                       registar_array($3, $5);
                       asprintf(&$$, "%s\t%s%d\n", ($1 == NULL)?"" : $1, "pushn ", $5);
                     }
           | Decl_block type ident '['num']' '['num']' ';' {
                       registar_matriz($3, $5, $8);
                       asprintf(&$$, "%s\t%s%d\n", ($1 == NULL)?"" : $1, "pushn ", $5 * $8);
                     }
           | Decl_block type ident '=' num';' {
                      registar_var($3);  
                      asprintf(&$$, "%s\t%s%d\n", ($1 == NULL)?"" : $1, "pushi ", $5);
                  }
           ;

/* implementar se e só se tiver tempo, ver como definir contexto local */
Fun_prods :
          | Fun_prods Fun_prod
          ;

/* se necessario, tirar Decl_block */
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
/* devolver nestas expressoes o resultado de por no topo da stack, tirar o num daqui */
/* por expressoes binarias e unarias aqui */
Value : '(' Value ')' 
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

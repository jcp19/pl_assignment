%token type
%token ident
%token num
%token while_token
%token if_token
%token ret
%token str_literal
%token ifel_token
%token begin
%token end
%token READ
%token WRITE

%union {
    int valor;
    char * identificador;
}

%type <identificador> ident
%type <valor> num
%type <identificador> Programa 
%type <identificador> Decl_block 
%type <identificador> Lhs
%type <identificador> Rhs
%type <identificador> Value
%type <identificador> LInstr
%type <identificador> Instr
%type <identificador> Expr

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

void registar_var(char * nome_var) {
     registar_matriz(nome_var, 1, 1);
}

int numero_colunas(char * nome){
    gpointer encontrado = g_hash_table_lookup(tabela_simbolos, nome);
    if(encontrado) {
        Entrada_tabela e = (Entrada_tabela) encontrado;
        return e->numero_colunas;
    } else {
        yyerror("ERRO: Tentativa de usar identificador não declarado.");
    }
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

int get_offset_var(char * nome){
    gpointer encontrado = g_hash_table_lookup(tabela_simbolos, nome);
    if(encontrado) {
        Entrada_tabela e = (Entrada_tabela) encontrado;
        return e->offset;
    } else {
        yyerror("ERRO: Tentativa de usar identificador não declarado.");
    }
}

%}

%%

/* Ideias
neste momento so da para ints
 -> Precednecia de operadores
 -> Argumentos nas funcoes
 -> Mais tipos (float e str): omitir cenas str
 -> Usar values no acesso aos arrays nos decl
-> Tabela de simbolos para funcoes
*/

/* todos
tirar tipo das funcoes (ou pode nem ser preciso, basta por label... 
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
  /* ver conflitos shift reduce e justificar que o comportamento padrao do yacc (shift) resolve os porblemas */
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
       | LInstr Instr {
                          asprintf(&$$, "%s%s\n", ($1 == NULL)?"" : $1, $2);
                      }
       ;

Instr : while_token '(' Value ')' '{' LInstr '}'
      | if_token '(' Value ')' '{' LInstr '}'
      | ifel_token '(' Value ')' '{' LInstr '}' '{' LInstr '}'
      | Lhs '=' Rhs ';' { asprintf($$, "%s%s", $3, $1); }
      | WRITE str_literal ';'
      | READ Lhs ';'
 /*     | ReturnExpr ';', por chamadas de funcoes tambem*/
      ;

Lhs : ident 
    | ident'['Value']' 
    | ident'['Value']''['Value']'
    ;

/* desta forma garante-se precedencia dos operadores de multiplicacao e divisao */
Rhs : Expr { $$ = $1; }
    | Rhs '+' Expr { asprintf($$, "%s%s\tadd\n", $1, $3); }
    | Rhs '-' Expr { asprintf($$, "%s%s\tsub\n", $1, $3); }
    ;

Expr: Expr '*' Value { asprintf($$, "%s%s\tmul\n", $1, $3); } 
    | Expr '/' Value { asprintf($$, "%s%s\tdiv\n", $1, $3); }
    | Expr '%' Value { asprintf($$, "%s%s\tmod\n", $1, $3); }
    | Expr '=''=' Value { asprintf($$, "%s%s\tequal\n", $1, $4); }
    | Expr '!''=' Value { asprintf($$, "%s%s\tequal\n\tnot\n", $1, $4); }
    | Expr '>''=' Value { asprintf($$, "%s%s\tsupeq\n", $1, $4); }
    | Expr '<''=' Value { asprintf($$, "%s%s\tinfeq\n", $1, $4); }
    | Expr '>' Value { asprintf($$, "%s%s\tsup\n", $1, $3); }
    | Expr '<' Value { asprintf($$, "%s%s\tinf\n", $1, $3); }
    | Value { $$ = $1; }              

/* por ops binarias e unarias!! */


/* deve-se por expressoes nao atomicas entre parenteses de forma a forçar a precedencia dos operadores */
/* devolver nestas expressoes o resultado de por no topo da stack, tirar o num daqui */
/* por expressoes binarias e unarias aqui */
Value : '(' Value ')' { $$ = $2; }
      | num { asprintf($$, "\tpushi %d\n", $1); }
      | ident { asprintf($$, "%tpushg %d\n", get_offset_var($1));}
      | ident'['Value']' {asprintf($$, "\tpushg %d\n%s\tpadd\n\tload\n", get_offset_var($1), $3);} 
      | ident'['Value']''['Value']' {
           char * cmd = "\tpushg %d\n" // get_offset_var($1)
                        "%s"  // $3
                        "\tpushi %d\n" // numero de colunas
                        "\tmul\n"
                        "%s" // $6
                        "\tpadd\n" // por esta altura tenho o offset para adicionar ao endereco
                        "\tload\n";
           asprintf($$, cmd, get_offset_var($1), $3, numero_colunas($3),$6);
         }
      | '(''!' Value')' { asprintf($$, "%s\tnot\n",$3);}
      | '(''-' Value')' { asprintf($$, "%s\n\tpushi -1\n\tmul\n",$3);}
      ;
/*
ReturnExpr : ret
          | ret Value
           | ret Value BOp Value 
           | ret UOp Value 
           ;
*/

/* se adicionar args as funcoes, mudar aqui */
Function_call : ident '(' ')'
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

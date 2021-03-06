%{
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>


typedef struct {
    int offset;
    int numero_linhas;
    int numero_colunas;
} entrada_tabela;

typedef struct {
   char* antes;
   char* depois;
} antes_depois;

typedef entrada_tabela* Entrada_tabela;

int yyerror (char *s);
Entrada_tabela new_Entrada_tabela(int, int,int);
void registar_var(char *);
int numero_colunas(char *);
void registar_array(char * nome_var, int dim);
void registar_matriz(char * nome_var, int linhas, int colunas);
int get_offset_var(char * nome);

GHashTable * tabela_simbolos;
int ultimo_offset = 0;
int label = 0;

Entrada_tabela new_Entrada_tabela(int offset, int numero_linhas, int numero_colunas) {
    Entrada_tabela e = malloc(sizeof(entrada_tabela));
    e->offset = offset;
    e->numero_linhas = numero_linhas;
    e->numero_colunas = numero_colunas;
}


void registar_var(char * nome_var) {
     registar_matriz(nome_var, 1, 1);
}

int numero_colunas(char * nome){
    gpointer encontrado = g_hash_table_lookup(tabela_simbolos, nome);
    if(encontrado) {
        Entrada_tabela e = (Entrada_tabela) encontrado;
        return e->numero_colunas;
    } else {
// por nome da var
        yyerror("ERRO: Tentativa de usar identificador não declarado.");
    }
}

void registar_array(char * nome_var, int dim) {
     registar_matriz(nome_var, 1, dim);
}

void registar_matriz(char * nome_var, int linhas, int colunas){
    Entrada_tabela e = new_Entrada_tabela(ultimo_offset, linhas, colunas);
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

%token  TYPE
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
    antes_depois a_d;
}

%type <identificador> ident
%type <valor> num
%type <identificador> Programa 
%type <identificador> Decl_block 
%type <a_d> Lhs
%type <identificador> Rhs
%type <identificador> Fun_prods
%type <identificador> Fun_prod
%type <identificador> Value
%type <identificador> LInstr
%type <identificador> Instr
%type <identificador> Expr
%type <identificador> Main_block 
%type <identificador> str_literal

%%
Programa : Decl_block Fun_prods begin Main_block end {
                printf("declaracoes:\n%s\nstart\n%s\nmain:\n%sstop\n", $1, $2, $4);
            }
         ;

Decl_block :  { $$ = ""; } 
           | Decl_block TYPE ident ';' { 
                                         registar_var($3);  
                                         asprintf(&$$, "%s\t%s\n", $1 , "pushi 0");
                                       }
           | Decl_block TYPE ident '[' num ']' ';' { 
                       registar_array($3, $5);
                       asprintf(&$$, "%s\t%s%d\n", $1, "pushn ", $5);
                     }
           | Decl_block TYPE ident '['num']' '['num']' ';' {
                       registar_matriz($3, $5, $8);
                       asprintf(&$$, "%s\t%s%d\n", $1, "pushn ", $5 * $8);
                     }
           | Decl_block TYPE ident '=' num';' {
                      registar_var($3);  
                      asprintf(&$$, "%s\t%s%d\n", $1, "pushi ", $5);
                  }
           ;

Fun_prods : { $$ = ""; }
          | Fun_prods Fun_prod { 
              $$ = ""; // Nao implementado 
          }
          ;

/* se necessario, tirar Decl_block */
Fun_prod : ident '(' ')' ':' TYPE '{' Decl_block LInstr '}' {$$="";}
         ;

LInstr : { $$ = ""; } 
       | LInstr Instr {
                          asprintf(&$$, "%s%s\n", $1, $2);
                      }
       ;

Instr : while_token '(' Rhs ')' '{' LInstr '}' { 
      char * cmd = "Label%d:\n" // nome da label
                   "%s" // condicao
                   "\tjz EndLabel%d\n" //nome da label 
                   "%s" //codigo
                   "\tjump Label%d\n" // nome da label
                   "EndLabel%d:\n"; //ultima label
      asprintf(&$$, cmd, label, $3, label, $6, label, label);
      label++;
      }
      | if_token '(' Rhs ')' '{' LInstr '}' { 
         char * cmd = "%s" // condicao
                   "\tjz Label%d\n" //nome da label 
                   "%s" //codigo
                   "Label%d:\n"; //ultima label
         asprintf(&$$, cmd, $3, label, $6, label);
         label++;
      }
      | ifel_token '(' Rhs ')' '{' LInstr '}' '{' LInstr '}' { 
          char * cmd = "%s" // condicao
                   "\tjz Label%d\n" //nome da label 
                   "%s" //codigo
                   "\tjump EndLabel%d\n"
                   "\tLabel%d:\n" //ultima label
                   "%s" // codgigo 2 
                   "EndLabel%d"; //ulitma label
         asprintf(&$$, cmd, $3, label, $6, label, label, $9, label);
         label++;
        }
      | Lhs '=' Rhs ';' { asprintf(&$$, "%s%s%s", $1.antes, $3, $1.depois); }
      | WRITE str_literal ';' { 
            asprintf(&$$, "\tpushs %s\n\twrites\n", $2); 
        }
      | WRITE Rhs ';' {
            asprintf(&$$, "%s\twritei\n", $2); 
      }
      | READ Lhs ';' { 
            asprintf(&$$, "%s\tread\n\tatoi\n%s", $2.antes, $2.depois);
      }
      ;

Lhs : ident {   
           asprintf(&$$.antes, "");
           asprintf(&$$.depois,"\tstoreg %d\n", get_offset_var($1)); 
    }
    | ident'['Value']' { 
         char * antes = "\tpushgp\n"
                        "\tpushi %d\n" 
                        "\tpadd\n"
                        "%s";
         char * depois = "\tstoren \n";
         asprintf(&$$.antes, antes, get_offset_var($1), $3);
         asprintf(&$$.depois, depois);
    }
                          
    | ident'['Value']''['Value']' {
          char * antes = "\tpushgp\n"
                         "\tpushi %d\n"  // endereco ident
                         "\tpadd\n"
                         "%s" // value1
                         "\tpushi %d\n" // numero colunas
                         "\tmul\n"
                         "%s" // value2
                         "\tadd\n";
         char * depois = "\tstoren \n";
         asprintf(&$$.antes, antes, get_offset_var($1), $3, numero_colunas($1),$6);
         asprintf(&$$.depois, depois);
    }
    ;

/* desta forma garante-se precedencia dos operadores de multiplicacao e divisao */
Rhs : Expr { $$ = $1; }
    | Rhs '+' Expr { asprintf(&$$, "%s%s\tadd\n", $1, $3); }
    | Rhs '-' Expr { asprintf(&$$, "%s%s\tsub\n", $1, $3); }
    ;

Expr: Expr '*' Value { asprintf(&$$, "%s%s\tmul\n", $1, $3); } 
    | Expr '/' Value { asprintf(&$$, "%s%s\tdiv\n", $1, $3); }
    | Expr '%' Value { asprintf(&$$, "%s%s\tmod\n", $1, $3); }
    | Expr '=''=' Value { asprintf(&$$, "%s%s\tequal\n", $1, $4); }
    | Expr '!''=' Value { asprintf(&$$, "%s%s\tequal\n\tnot\n", $1, $4); }
    | Expr '>''=' Value { asprintf(&$$, "%s%s\tsupeq\n", $1, $4); }
    | Expr '<''=' Value { asprintf(&$$, "%s%s\tinfeq\n", $1, $4); }
    | Expr '>' Value { asprintf(&$$, "%s%s\tsup\n", $1, $3); }
    | Expr '<' Value { asprintf(&$$, "%s%s\tinf\n", $1, $3); }
    | Value { $$ = $1; }              

/* deve-se por expressoes nao atomicas entre parenteses de forma a forçar a precedencia dos operadores */
Value : '(' Value ')' { $$ = $2; }
      | num { asprintf(&$$, "\tpushi %d\n", $1); }
      | ident { asprintf(&$$, "\tpushg %d\n", get_offset_var($1));}
      | ident'['Value']' {
           char * cmd = "\tpushgp\n"
                        "\tpushi %d\n" // endereco
                        "\tpadd\n"
                        "%s" // value
                        "\tloadn\n";
           asprintf(&$$, cmd, get_offset_var($1), $3);
                    //asprintf(&$$, "\tpushg %d\n%s\tpadd\n\tload\n", get_offset_var($1), $3);
        
      } 
      | ident'['Value']''['Value']' {
           char * cmd = "\tpushgp\n"
                        "\tpushi %d\n" // get_offset_var($1)
                        "\tpadd\n"
                        "%s"  // $3
                        "\tpushi %d\n" // numero de colunas
                        "\tmul\n"
                        "%s" // $6
                        "\tadd\n"
                        "\tloadn\n";
           asprintf(&$$, cmd, get_offset_var($1), $3, numero_colunas($1),$6);
         }
      | '(''!' Value')' { asprintf(&$$, "%s\tnot\n",$3);}
      | '(''-' Value')' { asprintf(&$$, "%s\n\tpushi -1\n\tmul\n",$3);}
      ;

Function_call : ident '(' ')'
              ;

Main_block : LInstr { $$ = $1; }
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

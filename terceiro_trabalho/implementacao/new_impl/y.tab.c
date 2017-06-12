/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "intp.y" /* yacc.c:339  */

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

typedef struct {
   char* antes;
   char* depois;
} antes_depois;

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
// por nome da var
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


#line 143 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TYPE = 258,
    ident = 259,
    num = 260,
    while_token = 261,
    if_token = 262,
    ret = 263,
    str_literal = 264,
    ifel_token = 265,
    begin = 266,
    end = 267,
    READ = 268,
    WRITE = 269
  };
#endif
/* Tokens.  */
#define TYPE 258
#define ident 259
#define num 260
#define while_token 261
#define if_token 262
#define ret 263
#define str_literal 264
#define ifel_token 265
#define begin 266
#define end 267
#define READ 268
#define WRITE 269

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 91 "intp.y" /* yacc.c:355  */

    int valor;
    char * identificador;
    antes_depois a_d;

#line 214 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 231 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   162

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  12
/* YYNRULES -- Number of rules.  */
#define YYNRULES  43
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  120

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   269

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,     2,     2,    28,     2,     2,
      19,    20,    26,    24,     2,    25,     2,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    21,    15,
      31,    18,    30,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    16,     2,    17,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    22,     2,    23,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   112,   112,   119,   120,   124,   128,   133,   140,   141,
     145,   148,   149,   154,   164,   172,   183,   184,   187,   190,
     196,   200,   210,   226,   227,   228,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   243,   244,   245,   246,
     247,   257,   258,   264
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TYPE", "ident", "num", "while_token",
  "if_token", "ret", "str_literal", "ifel_token", "begin", "end", "READ",
  "WRITE", "';'", "'['", "']'", "'='", "'('", "')'", "':'", "'{'", "'}'",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'!'", "'>'", "'<'", "$accept",
  "Programa", "Decl_block", "Fun_prods", "Fun_prod", "LInstr", "Instr",
  "Lhs", "Rhs", "Expr", "Value", "Main_block", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    59,    91,    93,    61,    40,
      41,    58,   123,   125,    43,    45,    42,    47,    37,    33,
      62,    60
};
# endif

#define YYPACT_NINF -89

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-89)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -89,     4,    11,   -89,     5,    29,   113,    -2,   -89,   -89,
     -89,    47,    54,    17,   101,    51,    49,    68,    81,    90,
      91,   104,   111,   109,     6,   -89,   103,   -89,    59,   -89,
     131,     8,     8,     8,     8,   120,   121,   -89,   123,    -3,
      33,    69,   -89,     8,   -89,   134,   114,   124,    92,   100,
     102,   -89,     8,   -89,     8,     8,   122,   -89,     8,     8,
     125,     8,     8,     8,   126,    75,    85,    94,   128,   -89,
     130,   118,   127,   129,   133,   132,   135,   -89,    69,    69,
       8,   -89,   -89,   -89,     8,     8,   -89,     8,   -89,   -89,
     138,    11,     8,   -89,   -89,   -89,   140,   -89,   -89,   -89,
     -89,   -89,   -89,   -89,    32,   137,    37,    58,    63,     8,
     -89,   -89,   -89,   -89,   136,   142,   -89,   -89,    78,   -89
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     8,     1,     0,     0,     0,     0,    11,     9,
       4,     0,     0,     0,    43,     0,     0,     0,     0,    20,
       0,     0,     0,     0,     0,    12,     0,     2,     0,     7,
       0,     0,     0,     0,     0,     0,    38,    37,     0,     0,
       0,    23,    35,     0,     5,     0,     0,     0,     0,     0,
       0,    19,     0,    17,     0,     0,     0,    18,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
      21,     0,     0,     0,     0,     0,     0,    36,    24,    25,
       0,    26,    27,    28,     0,     0,    33,     0,    34,    16,
       0,    11,     0,    11,    11,    11,    39,    42,    41,    29,
      30,    31,    32,     6,     0,     0,     0,     0,     0,     0,
      10,    22,    13,    14,     0,     0,    11,    40,     0,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -89,   -89,    79,   -89,   -89,   -88,   -89,   139,   -14,    74,
     -31,   -89
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,     5,     9,    14,    25,    26,    40,    41,
      42,    15
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      47,    36,    37,   104,     3,   106,   107,   108,    56,     6,
      36,    37,    36,    37,     4,    38,    39,    13,    48,    49,
      50,    74,    54,    75,    76,    39,    55,    39,   118,    67,
      81,    82,    83,     7,    86,    88,    19,    18,    20,    21,
       8,    19,    22,    20,    21,    23,    24,    22,    57,    99,
      23,    24,    16,   100,   101,   110,   102,    58,    59,    17,
     112,   105,    19,    27,    20,    21,    28,    19,    22,    20,
      21,    23,    24,    22,    44,    45,    23,    24,   115,    36,
      37,   113,    19,    29,    20,    21,   114,    60,    22,    36,
      37,    23,    24,    85,    39,    61,    62,    63,    64,    65,
      66,   119,    30,    87,    39,    19,    31,    20,    21,    89,
      32,    22,    71,    19,    23,    24,    58,    59,    58,    59,
      72,    43,    73,    33,    58,    59,    58,    59,    10,    11,
      34,    12,    78,    79,    46,    51,    69,    52,    53,    68,
      93,    70,    77,    80,    84,    90,    92,     0,    91,    94,
      96,    95,    97,   103,   111,    98,   109,     0,   116,   117,
       0,     0,    35
};

static const yytype_int8 yycheck[] =
{
      31,     4,     5,    91,     0,    93,    94,    95,    39,     4,
       4,     5,     4,     5,     3,     9,    19,    19,    32,    33,
      34,    52,    25,    54,    55,    19,    29,    19,   116,    43,
      61,    62,    63,     4,    65,    66,     4,    20,     6,     7,
      11,     4,    10,     6,     7,    13,    14,    10,    15,    80,
      13,    14,     5,    84,    85,    23,    87,    24,    25,     5,
      23,    92,     4,    12,     6,     7,    17,     4,    10,     6,
       7,    13,    14,    10,    15,    16,    13,    14,   109,     4,
       5,    23,     4,    15,     6,     7,    23,    18,    10,     4,
       5,    13,    14,    18,    19,    26,    27,    28,    29,    30,
      31,    23,    21,    18,    19,     4,    16,     6,     7,    15,
      19,    10,    20,     4,    13,    14,    24,    25,    24,    25,
      20,    18,    20,    19,    24,    25,    24,    25,    15,    16,
      19,    18,    58,    59,     3,    15,    22,    16,    15,     5,
      22,    17,    20,    18,    18,    17,    16,    -1,    69,    22,
      17,    22,    20,    15,    17,    20,    16,    -1,    22,    17,
      -1,    -1,    23
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    33,    34,     0,     3,    35,     4,     4,    11,    36,
      15,    16,    18,    19,    37,    43,     5,     5,    20,     4,
       6,     7,    10,    13,    14,    38,    39,    12,    17,    15,
      21,    16,    19,    19,    19,    39,     4,     5,     9,    19,
      40,    41,    42,    18,    15,    16,     3,    42,    40,    40,
      40,    15,    16,    15,    25,    29,    42,    15,    24,    25,
      18,    26,    27,    28,    29,    30,    31,    40,     5,    22,
      17,    20,    20,    20,    42,    42,    42,    20,    41,    41,
      18,    42,    42,    42,    18,    18,    42,    18,    42,    15,
      17,    34,    16,    22,    22,    22,    17,    20,    20,    42,
      42,    42,    42,    15,    37,    42,    37,    37,    37,    16,
      23,    17,    23,    23,    23,    42,    22,    17,    37,    23
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    32,    33,    34,    34,    34,    34,    34,    35,    35,
      36,    37,    37,    38,    38,    38,    38,    38,    38,    38,
      39,    39,    39,    40,    40,    40,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,    42,    42,    42,    42,
      42,    42,    42,    43
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     4,     7,    10,     6,     0,     2,
       9,     0,     2,     7,     7,    10,     4,     3,     3,     3,
       1,     4,     7,     1,     3,     3,     3,     3,     3,     4,
       4,     4,     4,     3,     3,     1,     3,     1,     1,     4,
       7,     4,     4,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 112 "intp.y" /* yacc.c:1646  */
    {
                //printf("declaracoes:\n%s\nstart\n%s\nmain:\n%sstop\n", $1, $2, $4);
                // completar
                printf("declaracoes:\n%s\n\tstart\nmain:\n%sstop\n", (yyvsp[-4].identificador), (yyvsp[-1].identificador));
            }
#line 1387 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 119 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = ""; }
#line 1393 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 120 "intp.y" /* yacc.c:1646  */
    { 
                                         registar_var((yyvsp[-1].identificador));  
                                         asprintf(&(yyval.identificador), "%s\t%s\n", ((yyvsp[-3].identificador) == NULL)?"" : (yyvsp[-3].identificador), "pushi 0");
                                       }
#line 1402 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 124 "intp.y" /* yacc.c:1646  */
    { 
                       registar_array((yyvsp[-4].identificador), (yyvsp[-2].valor));
                       asprintf(&(yyval.identificador), "%s\t%s%d\n", (yyvsp[-6].identificador), "pushn ", (yyvsp[-2].valor));
                     }
#line 1411 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 128 "intp.y" /* yacc.c:1646  */
    {
                       registar_matriz((yyvsp[-7].identificador), (yyvsp[-5].valor), (yyvsp[-2].valor));
                       asprintf(&(yyval.identificador), "%s\t%s%d\n", ((yyvsp[-9].identificador) == NULL)?"" : (yyvsp[-9].identificador), "pushn ", (yyvsp[-5].valor) * (yyvsp[-2].valor));
                     }
#line 1420 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 133 "intp.y" /* yacc.c:1646  */
    {
                      registar_var((yyvsp[-3].identificador));  
                      asprintf(&(yyval.identificador), "%s\t%s%d\n", ((yyvsp[-5].identificador) == NULL)?"" : (yyvsp[-5].identificador), "pushi ", (yyvsp[-1].valor));
                  }
#line 1429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 148 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = ""; }
#line 1435 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 149 "intp.y" /* yacc.c:1646  */
    {
                          asprintf(&(yyval.identificador), "%s%s\n", (yyvsp[-1].identificador), (yyvsp[0].identificador));
                      }
#line 1443 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 154 "intp.y" /* yacc.c:1646  */
    { 
      char * cmd = "Label%d:\n" // nome da label
                   "%s" // condicao
                   "\tjz EndLabel%d\n" //nome da label (nao esquecer incrementar no fim
                   "%s" //codigo
                   "\tjump Label%d\n" // nome da label
                   "EndLabel%d:\n"; //ultima label
      asprintf(&(yyval.identificador), cmd, label, (yyvsp[-4].identificador), label, (yyvsp[-1].identificador), label, label);
      label++;
      }
#line 1458 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 164 "intp.y" /* yacc.c:1646  */
    { 
         char * cmd = "%s" // condicao
                   "\tjz Label%d\n" //nome da label (nao esquecer incrementar no fim
                   "%s" //codigo
                   "Label%d:\n"; //ultima label
         asprintf(&(yyval.identificador), cmd, (yyvsp[-4].identificador), label, (yyvsp[-1].identificador), label);
         label++;
      }
#line 1471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 172 "intp.y" /* yacc.c:1646  */
    { 
          char * cmd = "%s" // condicao
                   "\tjz Label%d\n" //nome da label (nao esquecer incrementar no fim
                   "%s" //codigo
                   "\tjump EndLabel%d\n"
                   "\tLabel%d:\n" //ultima label
                   "%s" // codgigo 2 
                   "EndLabel%d"; //ulitma label
         asprintf(&(yyval.identificador), cmd, (yyvsp[-7].identificador), label, (yyvsp[-4].identificador), label, label, (yyvsp[-1].identificador), label);
         label++;
        }
#line 1487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 183 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s%s", (yyvsp[-3].a_d).antes, (yyvsp[-1].identificador), (yyvsp[-3].a_d).depois); }
#line 1493 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 184 "intp.y" /* yacc.c:1646  */
    { 
            asprintf(&(yyval.identificador), "\tpushs %s\n\twrites\n", (yyvsp[-1].identificador)); 
        }
#line 1501 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 187 "intp.y" /* yacc.c:1646  */
    {
            asprintf(&(yyval.identificador), "%s\twritei\n", (yyvsp[-1].identificador)); 
      }
#line 1509 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 190 "intp.y" /* yacc.c:1646  */
    { 
            /* mudar se divir acesso a [][] em dus partes */  
            asprintf(&(yyval.identificador), "%s\tread\n\tatoi\n%s", (yyvsp[-1].a_d).antes, (yyvsp[-1].a_d).depois);
      }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 196 "intp.y" /* yacc.c:1646  */
    {   
           asprintf(&(yyval.a_d).antes, "");
           asprintf(&(yyval.a_d).depois,"\tstoreg %d\n", get_offset_var((yyvsp[0].identificador))); 
    }
#line 1527 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 200 "intp.y" /* yacc.c:1646  */
    { 
         char * antes = "\tpushgp\n"
                        "\tpushi %d\n"  // endereco ident
                        "\tpadd\n"
                        "%s"; // value
         char * depois = "\tstoren \n";
         asprintf(&(yyval.a_d).antes, antes, get_offset_var((yyvsp[-3].identificador)), (yyvsp[-1].identificador));
         asprintf(&(yyval.a_d).depois, depois);
    }
#line 1541 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 210 "intp.y" /* yacc.c:1646  */
    {
          char * antes = "\tpushgp\n"
                         "\tpushi %d\n"  // endereco ident
                         "\tpadd\n"
                         "%s" // value1
                         "\tpushi %d\n" // numero colunas
                         "\tmul\n"
                         "%s" // value2
                         "\tadd\n";
         char * depois = "\tstoren \n";
         asprintf(&(yyval.a_d).antes, antes, get_offset_var((yyvsp[-6].identificador)), (yyvsp[-4].identificador), numero_colunas((yyvsp[-6].identificador)),(yyvsp[-1].identificador));
         asprintf(&(yyval.a_d).depois, depois);
    }
#line 1559 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 226 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = (yyvsp[0].identificador); }
#line 1565 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 227 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tadd\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1571 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 228 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tsub\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1577 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 231 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tmul\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1583 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 232 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tdiv\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1589 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 233 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tmod\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1595 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 234 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tequal\n", (yyvsp[-3].identificador), (yyvsp[0].identificador)); }
#line 1601 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 235 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tequal\n\tnot\n", (yyvsp[-3].identificador), (yyvsp[0].identificador)); }
#line 1607 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 236 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tsupeq\n", (yyvsp[-3].identificador), (yyvsp[0].identificador)); }
#line 1613 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 237 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tinfeq\n", (yyvsp[-3].identificador), (yyvsp[0].identificador)); }
#line 1619 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 238 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tsup\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1625 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 239 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s%s\tinf\n", (yyvsp[-2].identificador), (yyvsp[0].identificador)); }
#line 1631 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 240 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = (yyvsp[0].identificador); }
#line 1637 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 243 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = (yyvsp[-1].identificador); }
#line 1643 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 244 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "\tpushi %d\n", (yyvsp[0].valor)); }
#line 1649 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 245 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "\tpushg %d\n", get_offset_var((yyvsp[0].identificador)));}
#line 1655 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 246 "intp.y" /* yacc.c:1646  */
    {asprintf(&(yyval.identificador), "\tpushg %d\n%s\tpadd\n\tload\n", get_offset_var((yyvsp[-3].identificador)), (yyvsp[-1].identificador));}
#line 1661 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 247 "intp.y" /* yacc.c:1646  */
    {
           char * cmd = "\tpushg %d\n" // get_offset_var($1)
                        "%s"  // $3
                        "\tpushi %d\n" // numero de colunas
                        "\tmul\n"
                        "%s" // $6
                        "\tpadd\n" // por esta altura tenho o offset para adicionar ao endereco
                        "\tload\n";
           asprintf(&(yyval.identificador), cmd, get_offset_var((yyvsp[-6].identificador)), (yyvsp[-4].identificador), numero_colunas((yyvsp[-4].identificador)),(yyvsp[-1].identificador));
         }
#line 1676 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 257 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s\tnot\n",(yyvsp[-1].identificador));}
#line 1682 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 258 "intp.y" /* yacc.c:1646  */
    { asprintf(&(yyval.identificador), "%s\n\tpushi -1\n\tmul\n",(yyvsp[-1].identificador));}
#line 1688 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 264 "intp.y" /* yacc.c:1646  */
    { (yyval.identificador) = (yyvsp[0].identificador); }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1698 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 267 "intp.y" /* yacc.c:1906  */


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

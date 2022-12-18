/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "src/parser.y"

    #include <iostream>
    #include <assert.h>
    #include "parser.h"
    extern Ast ast;
    int yylex();
    int yyerror( char const * );

    Type* currentType;

#line 79 "src/parser.cpp"




# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ID = 3,                         /* ID  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_FLOATING = 5,                   /* FLOATING  */
  YYSYMBOL_CONST = 6,                      /* CONST  */
  YYSYMBOL_TYPE_INT = 7,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_FLOAT = 8,                 /* TYPE_FLOAT  */
  YYSYMBOL_TYPE_VOID = 9,                  /* TYPE_VOID  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_BREAK = 13,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 14,                  /* CONTINUE  */
  YYSYMBOL_RETURN = 15,                    /* RETURN  */
  YYSYMBOL_LPAREN = 16,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 17,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 18,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 19,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 20,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 21,                    /* RBRACE  */
  YYSYMBOL_COMMA = 22,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 23,                 /* SEMICOLON  */
  YYSYMBOL_ADD = 24,                       /* ADD  */
  YYSYMBOL_SUB = 25,                       /* SUB  */
  YYSYMBOL_MUL = 26,                       /* MUL  */
  YYSYMBOL_DIV = 27,                       /* DIV  */
  YYSYMBOL_MOD = 28,                       /* MOD  */
  YYSYMBOL_AND = 29,                       /* AND  */
  YYSYMBOL_OR = 30,                        /* OR  */
  YYSYMBOL_NOT = 31,                       /* NOT  */
  YYSYMBOL_LESS = 32,                      /* LESS  */
  YYSYMBOL_LESSEQ = 33,                    /* LESSEQ  */
  YYSYMBOL_GREAT = 34,                     /* GREAT  */
  YYSYMBOL_GREATEQ = 35,                   /* GREATEQ  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_NEQ = 37,                       /* NEQ  */
  YYSYMBOL_ASSIGN = 38,                    /* ASSIGN  */
  YYSYMBOL_THEN = 39,                      /* THEN  */
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_Stmts = 42,                     /* Stmts  */
  YYSYMBOL_Stmt = 43,                      /* Stmt  */
  YYSYMBOL_LVal = 44,                      /* LVal  */
  YYSYMBOL_AssignStmt = 45,                /* AssignStmt  */
  YYSYMBOL_ExpStmt = 46,                   /* ExpStmt  */
  YYSYMBOL_BlockStmt = 47,                 /* BlockStmt  */
  YYSYMBOL_48_1 = 48,                      /* $@1  */
  YYSYMBOL_IfStmt = 49,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 50,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 51,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 52,              /* ContinueStmt  */
  YYSYMBOL_ReturnStmt = 53,                /* ReturnStmt  */
  YYSYMBOL_Exp = 54,                       /* Exp  */
  YYSYMBOL_ConstExp = 55,                  /* ConstExp  */
  YYSYMBOL_AddExp = 56,                    /* AddExp  */
  YYSYMBOL_MulExp = 57,                    /* MulExp  */
  YYSYMBOL_UnaryExp = 58,                  /* UnaryExp  */
  YYSYMBOL_PrimaryExp = 59,                /* PrimaryExp  */
  YYSYMBOL_FuncRParams = 60,               /* FuncRParams  */
  YYSYMBOL_Cond = 61,                      /* Cond  */
  YYSYMBOL_LOrExp = 62,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 63,                   /* LAndExp  */
  YYSYMBOL_EqExp = 64,                     /* EqExp  */
  YYSYMBOL_RelExp = 65,                    /* RelExp  */
  YYSYMBOL_Type = 66,                      /* Type  */
  YYSYMBOL_ArrConstIndices = 67,           /* ArrConstIndices  */
  YYSYMBOL_ArrValIndices = 68,             /* ArrValIndices  */
  YYSYMBOL_DeclStmt = 69,                  /* DeclStmt  */
  YYSYMBOL_ConstDefList = 70,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 71,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 72,              /* ConstInitVal  */
  YYSYMBOL_ConstInitValList = 73,          /* ConstInitValList  */
  YYSYMBOL_VarDefList = 74,                /* VarDefList  */
  YYSYMBOL_VarDef = 75,                    /* VarDef  */
  YYSYMBOL_VarInitVal = 76,                /* VarInitVal  */
  YYSYMBOL_VarInitValList = 77,            /* VarInitValList  */
  YYSYMBOL_FuncDef = 78,                   /* FuncDef  */
  YYSYMBOL_79_2 = 79,                      /* $@2  */
  YYSYMBOL_80_3 = 80,                      /* $@3  */
  YYSYMBOL_FuncParams = 81,                /* FuncParams  */
  YYSYMBOL_FuncParam = 82                  /* FuncParam  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   227

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  102
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    49,    49,    56,    61,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    85,    98,   116,   123,
     128,   137,   137,   146,   153,   156,   163,   170,   177,   185,
     188,   195,   202,   209,   212,   222,   236,   239,   249,   259,
     273,   276,   288,   291,   295,   303,   306,   309,   313,   321,
     326,   331,   338,   343,   346,   354,   357,   365,   368,   372,
     380,   383,   387,   391,   395,   403,   407,   411,   418,   423,
     432,   437,   446,   449,   456,   461,   470,   492,   513,   520,
     523,   530,   535,   544,   549,   558,   577,   597,   612,   631,
     637,   640,   647,   652,   661,   668,   661,   693,   698,   703,
     710,   716,   733
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ID", "INTEGER",
  "FLOATING", "CONST", "TYPE_INT", "TYPE_FLOAT", "TYPE_VOID", "IF", "ELSE",
  "WHILE", "BREAK", "CONTINUE", "RETURN", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "COMMA", "SEMICOLON", "ADD", "SUB",
  "MUL", "DIV", "MOD", "AND", "OR", "NOT", "LESS", "LESSEQ", "GREAT",
  "GREATEQ", "EQ", "NEQ", "ASSIGN", "THEN", "$accept", "Program", "Stmts",
  "Stmt", "LVal", "AssignStmt", "ExpStmt", "BlockStmt", "$@1", "IfStmt",
  "WhileStmt", "BreakStmt", "ContinueStmt", "ReturnStmt", "Exp",
  "ConstExp", "AddExp", "MulExp", "UnaryExp", "PrimaryExp", "FuncRParams",
  "Cond", "LOrExp", "LAndExp", "EqExp", "RelExp", "Type",
  "ArrConstIndices", "ArrValIndices", "DeclStmt", "ConstDefList",
  "ConstDef", "ConstInitVal", "ConstInitValList", "VarDefList", "VarDef",
  "VarInitVal", "VarInitValList", "FuncDef", "$@2", "$@3", "FuncParams",
  "FuncParam", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-95)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     166,    88,  -140,  -140,   156,  -140,  -140,  -140,    -1,    10,
       8,    15,   107,   190,    22,  -140,   190,   190,   190,    52,
     166,  -140,    18,  -140,    37,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,   -12,   175,  -140,  -140,    63,  -140,  -140,   190,
     190,    53,    90,   190,   190,  -140,  -140,  -140,  -140,    62,
      84,  -140,   166,  -140,  -140,  -140,  -140,  -140,   190,   190,
    -140,   190,   190,   190,   190,   190,    54,    66,  -140,  -140,
      -3,    95,   190,   -11,    74,  -140,   -12,    99,   103,   106,
      82,    92,   122,  -140,  -140,   137,   125,  -140,   175,   175,
    -140,  -140,  -140,   190,   190,     4,    91,   174,  -140,  -140,
     190,  -140,   140,   190,    19,    90,  -140,   166,   190,   190,
     190,   190,   190,   190,   190,   190,   166,  -140,  -140,   173,
     -12,  -140,   190,    30,   156,    29,  -140,  -140,  -140,  -140,
     180,  -140,   187,   106,    82,    92,    92,   -12,   -12,   -12,
     -12,  -140,  -140,   188,    20,  -140,  -140,   196,   186,  -140,
      78,  -140,  -140,   166,  -140,  -140,  -140,   100,   191,   156,
     193,  -140,  -140,   145,  -140,  -140,    30,   194,  -140,   192,
    -140,   180,  -140,   198,  -140,  -140,   199
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    16,    47,    48,     0,    65,    66,    67,     0,     0,
       0,     0,     0,     0,    21,    15,     0,     0,     0,     0,
       2,     4,    45,     5,     0,     7,     8,     9,    10,    11,
      12,    20,    31,    33,    36,    40,     0,    13,    14,    51,
       0,    17,     0,     0,     0,    27,    28,    30,    45,     0,
       0,    23,     0,    42,    43,    44,     1,     3,     0,     0,
       6,     0,     0,     0,     0,     0,    85,     0,    84,    50,
       0,     0,     0,     0,     0,    75,    60,     0,    52,    53,
      55,    57,     0,    29,    46,     0,     0,    19,    34,    35,
      37,    38,    39,     0,     0,    87,     0,     0,    73,    41,
       0,    71,     0,     0,     0,     0,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    22,    18,     0,
      32,    86,     0,     0,    99,    85,    83,    49,    70,    76,
       0,    74,    24,    54,    56,    58,    59,    61,    62,    63,
      64,    26,    69,     0,     0,    89,    88,     0,    95,    98,
       0,    78,    77,     0,    68,    91,    93,     0,   100,     0,
       0,    80,    82,     0,    25,    90,     0,     0,    97,     0,
      79,     0,    92,   102,    96,    81,   101
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,   167,   -16,     1,  -140,  -140,    49,  -140,  -140,
    -140,  -140,  -140,  -140,   -10,   -83,   -35,    67,     0,  -140,
    -140,   176,  -140,   114,   115,    77,    -4,   -68,  -140,  -140,
    -140,   118,  -139,  -140,  -140,   128,  -138,  -140,  -140,  -140,
    -140,  -140,    68
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    19,    20,    21,    48,    23,    24,    25,    52,    26,
      27,    28,    29,    30,    31,   151,    32,    33,    34,    35,
      70,    77,    78,    79,    80,    81,    36,    95,    41,    37,
      74,    75,   152,   163,    67,    68,   146,   157,    38,    96,
     160,   148,   149
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      42,    22,    49,    50,    57,   104,   156,    93,    76,    76,
     119,   162,    61,    62,    99,    43,    53,    54,    55,   100,
     129,    22,   122,     1,     2,     3,    44,   103,   172,    69,
      71,    45,   175,     1,     2,     3,    13,   122,    46,   143,
     144,   155,   123,    51,    16,    17,    13,    93,    86,    87,
     144,    18,    56,    22,    16,    17,    58,   130,   120,    59,
      60,    18,   102,    90,    91,    92,    66,    94,   120,    57,
     -94,    72,    93,    76,    76,    76,    76,   137,   138,   139,
     140,     1,     2,     3,   121,    83,    22,   120,    97,    98,
     127,   132,    94,    73,    13,   120,   105,   106,   150,   161,
     141,    84,    16,    17,    39,   176,    40,   124,    22,    18,
       1,     2,     3,   145,   101,   120,   107,    22,   110,   111,
     147,   165,   166,    13,   112,   113,   114,   115,    88,    89,
      47,    16,    17,   108,   145,   109,   120,   164,    18,   116,
       1,     2,     3,     4,     5,     6,     7,     8,   118,     9,
      10,    11,    12,    13,    22,   147,   145,    14,   117,   128,
      15,    16,    17,     5,     6,     7,   170,   171,    18,     1,
       2,     3,     4,     5,     6,     7,     8,   125,     9,    10,
      11,    12,    13,     1,     2,     3,    14,   135,   136,    15,
      16,    17,   142,     1,     2,     3,    13,    18,   153,   158,
     150,    63,    64,    65,    16,    17,    13,   154,   159,   167,
     169,    18,    14,   173,    16,    17,    93,   122,   174,    85,
      82,    18,   133,   131,   134,   126,     0,   168
};

static const yytype_int16 yycheck[] =
{
       4,     0,    12,    13,    20,    73,   144,    18,    43,    44,
      93,   150,    24,    25,    17,    16,    16,    17,    18,    22,
     103,    20,    18,     3,     4,     5,    16,    38,   166,    39,
      40,    23,   171,     3,     4,     5,    16,    18,    23,   122,
      20,    21,    38,    21,    24,    25,    16,    18,    58,    59,
      20,    31,     0,    52,    24,    25,    38,    38,    93,    22,
      23,    31,    72,    63,    64,    65,     3,    38,   103,    85,
      16,    18,    18,   108,   109,   110,   111,   112,   113,   114,
     115,     3,     4,     5,    94,    23,    85,   122,    22,    23,
     100,   107,    38,     3,    16,   130,    22,    23,    20,    21,
     116,    17,    24,    25,    16,   173,    18,    16,   107,    31,
       3,     4,     5,   123,    19,   150,    17,   116,    36,    37,
     124,    21,    22,    16,    32,    33,    34,    35,    61,    62,
      23,    24,    25,    30,   144,    29,   171,   153,    31,    17,
       3,     4,     5,     6,     7,     8,     9,    10,    23,    12,
      13,    14,    15,    16,   153,   159,   166,    20,    21,    19,
      23,    24,    25,     7,     8,     9,    21,    22,    31,     3,
       4,     5,     6,     7,     8,     9,    10,     3,    12,    13,
      14,    15,    16,     3,     4,     5,    20,   110,   111,    23,
      24,    25,    19,     3,     4,     5,    16,    31,    11,     3,
      20,    26,    27,    28,    24,    25,    16,    19,    22,    18,
      17,    31,    20,    19,    24,    25,    18,    18,   169,    52,
      44,    31,   108,   105,   109,    97,    -1,   159
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    12,
      13,    14,    15,    16,    20,    23,    24,    25,    31,    41,
      42,    43,    44,    45,    46,    47,    49,    50,    51,    52,
      53,    54,    56,    57,    58,    59,    66,    69,    78,    16,
      18,    68,    66,    16,    16,    23,    23,    23,    44,    54,
      54,    21,    48,    58,    58,    58,     0,    43,    38,    22,
      23,    24,    25,    26,    27,    28,     3,    74,    75,    54,
      60,    54,    18,     3,    70,    71,    56,    61,    62,    63,
      64,    65,    61,    23,    17,    42,    54,    54,    57,    57,
      58,    58,    58,    18,    38,    67,    79,    22,    23,    17,
      22,    19,    54,    38,    67,    22,    23,    17,    30,    29,
      36,    37,    32,    33,    34,    35,    17,    21,    23,    55,
      56,    54,    18,    38,    16,     3,    75,    54,    19,    55,
      38,    71,    43,    63,    64,    65,    65,    56,    56,    56,
      56,    43,    19,    55,    20,    54,    76,    66,    81,    82,
      20,    55,    72,    11,    19,    21,    76,    77,     3,    22,
      80,    21,    72,    73,    43,    21,    22,    18,    82,    17,
      21,    22,    76,    19,    47,    72,    67
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    44,    45,    46,
      46,    48,    47,    47,    49,    49,    50,    51,    52,    53,
      53,    54,    55,    56,    56,    56,    57,    57,    57,    57,
      58,    58,    58,    58,    58,    59,    59,    59,    59,    60,
      60,    60,    61,    62,    62,    63,    63,    64,    64,    64,
      65,    65,    65,    65,    65,    66,    66,    66,    67,    67,
      68,    68,    69,    69,    70,    70,    71,    71,    72,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    75,    76,
      76,    76,    77,    77,    79,    80,    78,    81,    81,    81,
      82,    82,    82
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     3,
       1,     0,     4,     2,     5,     7,     5,     2,     2,     3,
       2,     1,     1,     1,     3,     3,     1,     3,     3,     3,
       1,     4,     2,     2,     2,     1,     3,     1,     1,     3,
       1,     0,     1,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     1,     1,     4,     3,
       4,     3,     4,     3,     3,     1,     3,     4,     1,     3,
       2,     3,     1,     3,     1,     1,     3,     2,     4,     1,
       3,     2,     3,     1,     0,     0,     8,     3,     1,     0,
       2,     5,     4
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2: /* Program: Stmts  */
#line 49 "src/parser.y"
             {
            ast.setRoot((yyvsp[0].stmttype));
        }
#line 1288 "src/parser.cpp"
    break;

  case 3: /* Stmts: Stmts Stmt  */
#line 56 "src/parser.y"
                  {
            SeqNode* node = dynamic_cast<SeqNode*>((yyvsp[-1].stmttype));
            node->addNext(dynamic_cast<StmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = dynamic_cast<StmtNode*>(node);
        }
#line 1298 "src/parser.cpp"
    break;

  case 4: /* Stmts: Stmt  */
#line 61 "src/parser.y"
            {
            SeqNode* node = new SeqNode();
            node->addNext(dynamic_cast<StmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = dynamic_cast<StmtNode*>(node);
        }
#line 1308 "src/parser.cpp"
    break;

  case 5: /* Stmt: AssignStmt  */
#line 70 "src/parser.y"
                   {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1314 "src/parser.cpp"
    break;

  case 6: /* Stmt: ExpStmt SEMICOLON  */
#line 71 "src/parser.y"
                         {(yyval.stmttype)=(yyvsp[-1].stmttype);}
#line 1320 "src/parser.cpp"
    break;

  case 7: /* Stmt: BlockStmt  */
#line 72 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1326 "src/parser.cpp"
    break;

  case 8: /* Stmt: IfStmt  */
#line 73 "src/parser.y"
               {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1332 "src/parser.cpp"
    break;

  case 9: /* Stmt: WhileStmt  */
#line 74 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1338 "src/parser.cpp"
    break;

  case 10: /* Stmt: BreakStmt  */
#line 75 "src/parser.y"
                  {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1344 "src/parser.cpp"
    break;

  case 11: /* Stmt: ContinueStmt  */
#line 76 "src/parser.y"
                     {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1350 "src/parser.cpp"
    break;

  case 12: /* Stmt: ReturnStmt  */
#line 77 "src/parser.y"
                   {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1356 "src/parser.cpp"
    break;

  case 13: /* Stmt: DeclStmt  */
#line 78 "src/parser.y"
                 {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1362 "src/parser.cpp"
    break;

  case 14: /* Stmt: FuncDef  */
#line 79 "src/parser.y"
                {(yyval.stmttype)=(yyvsp[0].stmttype);}
#line 1368 "src/parser.cpp"
    break;

  case 15: /* Stmt: SEMICOLON  */
#line 80 "src/parser.y"
                  {(yyval.stmttype) = new EmptyStmt();}
#line 1374 "src/parser.cpp"
    break;

  case 16: /* LVal: ID  */
#line 85 "src/parser.y"
           {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[0].strtype));
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[0].strtype));
                delete [](char*)(yyvsp[0].strtype);
                assert(se != nullptr);
            }
            (yyval.exprtype) = new Id(se);
            delete [](yyvsp[0].strtype);
        }
#line 1391 "src/parser.cpp"
    break;

  case 17: /* LVal: ID ArrValIndices  */
#line 98 "src/parser.y"
                         {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-1].strtype));
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-1].strtype));
                delete [](char*)(yyvsp[-1].strtype);
                assert(se != nullptr);
            }
            Id* newId = new Id(se);
            newId->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[0].stmttype)));
            (yyval.exprtype) =  newId;
            delete [](yyvsp[-1].strtype);
        }
#line 1410 "src/parser.cpp"
    break;

  case 18: /* AssignStmt: LVal ASSIGN Exp SEMICOLON  */
#line 116 "src/parser.y"
                                  {
            (yyval.stmttype) = new AssignStmt((yyvsp[-3].exprtype), (yyvsp[-1].exprtype));
        }
#line 1418 "src/parser.cpp"
    break;

  case 19: /* ExpStmt: ExpStmt COMMA Exp  */
#line 123 "src/parser.y"
                          {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>((yyvsp[-2].stmttype));
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1428 "src/parser.cpp"
    break;

  case 20: /* ExpStmt: Exp  */
#line 128 "src/parser.y"
            {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1438 "src/parser.cpp"
    break;

  case 21: /* $@1: %empty  */
#line 137 "src/parser.y"
               {
            identifiers = new SymbolTable(identifiers);
        }
#line 1446 "src/parser.cpp"
    break;

  case 22: /* BlockStmt: LBRACE $@1 Stmts RBRACE  */
#line 140 "src/parser.y"
                     {
            (yyval.stmttype) = new CompoundStmt((yyvsp[-1].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
        }
#line 1457 "src/parser.cpp"
    break;

  case 23: /* BlockStmt: LBRACE RBRACE  */
#line 146 "src/parser.y"
                      {
            (yyval.stmttype) = new CompoundStmt(nullptr);
        }
#line 1465 "src/parser.cpp"
    break;

  case 24: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 153 "src/parser.y"
                                              {
            (yyval.stmttype) = new IfStmt((yyvsp[-2].exprtype), (yyvsp[0].stmttype));
        }
#line 1473 "src/parser.cpp"
    break;

  case 25: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 156 "src/parser.y"
                                             {
            (yyval.stmttype) = new IfElseStmt((yyvsp[-4].exprtype), (yyvsp[-2].stmttype), (yyvsp[0].stmttype));
        }
#line 1481 "src/parser.cpp"
    break;

  case 26: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 163 "src/parser.y"
                                      {
            (yyval.stmttype) = new WhileStmt((yyvsp[-2].exprtype),(yyvsp[0].stmttype));
        }
#line 1489 "src/parser.cpp"
    break;

  case 27: /* BreakStmt: BREAK SEMICOLON  */
#line 170 "src/parser.y"
                        {
            (yyval.stmttype) = new BreakStmt();
        }
#line 1497 "src/parser.cpp"
    break;

  case 28: /* ContinueStmt: CONTINUE SEMICOLON  */
#line 177 "src/parser.y"
                          {
            (yyval.stmttype) = new ContinueStmt();
        }
#line 1505 "src/parser.cpp"
    break;

  case 29: /* ReturnStmt: RETURN Exp SEMICOLON  */
#line 185 "src/parser.y"
                             {
            (yyval.stmttype) = new ReturnStmt((yyvsp[-1].exprtype));
        }
#line 1513 "src/parser.cpp"
    break;

  case 30: /* ReturnStmt: RETURN SEMICOLON  */
#line 188 "src/parser.y"
                         {
            (yyval.stmttype) = new ReturnStmt(nullptr);
        }
#line 1521 "src/parser.cpp"
    break;

  case 31: /* Exp: AddExp  */
#line 195 "src/parser.y"
               {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1529 "src/parser.cpp"
    break;

  case 32: /* ConstExp: AddExp  */
#line 202 "src/parser.y"
               {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1537 "src/parser.cpp"
    break;

  case 33: /* AddExp: MulExp  */
#line 209 "src/parser.y"
               {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1545 "src/parser.cpp"
    break;

  case 34: /* AddExp: AddExp ADD MulExp  */
#line 212 "src/parser.y"
                          {
            SymbolEntry *se;
            if((yyvsp[-2].exprtype)->getType()->isAnyInt() && (yyvsp[0].exprtype)->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::ADD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1560 "src/parser.cpp"
    break;

  case 35: /* AddExp: AddExp SUB MulExp  */
#line 222 "src/parser.y"
                          {
            SymbolEntry *se;
            if((yyvsp[-2].exprtype)->getType()->isAnyInt() && (yyvsp[0].exprtype)->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::SUB, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1575 "src/parser.cpp"
    break;

  case 36: /* MulExp: UnaryExp  */
#line 236 "src/parser.y"
                 {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1583 "src/parser.cpp"
    break;

  case 37: /* MulExp: MulExp MUL UnaryExp  */
#line 239 "src/parser.y"
                            {
            SymbolEntry *se;
            if((yyvsp[-2].exprtype)->getType()->isAnyInt() && (yyvsp[0].exprtype)->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MUL, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1598 "src/parser.cpp"
    break;

  case 38: /* MulExp: MulExp DIV UnaryExp  */
#line 249 "src/parser.y"
                            {
            SymbolEntry *se;
            if((yyvsp[-2].exprtype)->getType()->isAnyInt() && (yyvsp[0].exprtype)->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::DIV, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1613 "src/parser.cpp"
    break;

  case 39: /* MulExp: MulExp MOD UnaryExp  */
#line 259 "src/parser.y"
                            {
            SymbolEntry *se;
            if((yyvsp[-2].exprtype)->getType()->isAnyInt() && (yyvsp[0].exprtype)->getType()->isAnyInt()){
                se = new TemporarySymbolEntry(TypeSystem::intType, SymbolTable::getLabel());
            }
            else{
                se = new TemporarySymbolEntry(TypeSystem::floatType, SymbolTable::getLabel());
            }
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::MOD, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1628 "src/parser.cpp"
    break;

  case 40: /* UnaryExp: PrimaryExp  */
#line 273 "src/parser.y"
                   {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1636 "src/parser.cpp"
    break;

  case 41: /* UnaryExp: ID LPAREN FuncRParams RPAREN  */
#line 276 "src/parser.y"
                                     {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-3].strtype));
            if(se == nullptr)
            {
                fprintf(stderr, "identifier \"%s\" is undefined\n", (char*)(yyvsp[-3].strtype));
                delete [](char*)(yyvsp[-3].strtype);
                assert(se != nullptr);
            }
            SymbolEntry *tmp = new TemporarySymbolEntry(se->getType(), SymbolTable::getLabel());
            (yyval.exprtype) = new FuncCallNode(tmp, new Id(se), dynamic_cast<FuncCallParamsNode*>((yyvsp[-1].stmttype)));
        }
#line 1653 "src/parser.cpp"
    break;

  case 42: /* UnaryExp: ADD UnaryExp  */
#line 288 "src/parser.y"
                     {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1661 "src/parser.cpp"
    break;

  case 43: /* UnaryExp: SUB UnaryExp  */
#line 291 "src/parser.y"
                     {
            SymbolEntry *tmp = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
            (yyval.exprtype) = new OneOpExpr(tmp, OneOpExpr::SUB, (yyvsp[0].exprtype));
        }
#line 1670 "src/parser.cpp"
    break;

  case 44: /* UnaryExp: NOT UnaryExp  */
#line 295 "src/parser.y"
                     {
            SymbolEntry *tmp = new TemporarySymbolEntry((yyvsp[0].exprtype)->getType(), SymbolTable::getLabel());
            (yyval.exprtype) = new OneOpExpr(tmp, OneOpExpr::NOT, (yyvsp[0].exprtype));
        }
#line 1679 "src/parser.cpp"
    break;

  case 45: /* PrimaryExp: LVal  */
#line 303 "src/parser.y"
             {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1687 "src/parser.cpp"
    break;

  case 46: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 306 "src/parser.y"
                          {
            (yyval.exprtype) = (yyvsp[-1].exprtype);
        }
#line 1695 "src/parser.cpp"
    break;

  case 47: /* PrimaryExp: INTEGER  */
#line 309 "src/parser.y"
                {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constIntType, (yyvsp[0].itype));
            (yyval.exprtype) = new Constant(se);
        }
#line 1704 "src/parser.cpp"
    break;

  case 48: /* PrimaryExp: FLOATING  */
#line 313 "src/parser.y"
                 {
            SymbolEntry *se = new ConstantSymbolEntry(TypeSystem::constFloatType, (yyvsp[0].ftype));
            (yyval.exprtype) = new Constant(se);
        }
#line 1713 "src/parser.cpp"
    break;

  case 49: /* FuncRParams: FuncRParams COMMA Exp  */
#line 321 "src/parser.y"
                              {
            FuncCallParamsNode* node = dynamic_cast<FuncCallParamsNode*>((yyvsp[-2].stmttype));
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1723 "src/parser.cpp"
    break;

  case 50: /* FuncRParams: Exp  */
#line 326 "src/parser.y"
            {
            FuncCallParamsNode* node = new FuncCallParamsNode();
            node->addNext((yyvsp[0].exprtype));
            (yyval.stmttype) = node;
        }
#line 1733 "src/parser.cpp"
    break;

  case 51: /* FuncRParams: %empty  */
#line 331 "src/parser.y"
               {
            (yyval.stmttype) = nullptr;
        }
#line 1741 "src/parser.cpp"
    break;

  case 52: /* Cond: LOrExp  */
#line 338 "src/parser.y"
               {(yyval.exprtype) = (yyvsp[0].exprtype);}
#line 1747 "src/parser.cpp"
    break;

  case 53: /* LOrExp: LAndExp  */
#line 343 "src/parser.y"
                {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1755 "src/parser.cpp"
    break;

  case 54: /* LOrExp: LOrExp OR LAndExp  */
#line 346 "src/parser.y"
                          {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::OR, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1764 "src/parser.cpp"
    break;

  case 55: /* LAndExp: EqExp  */
#line 354 "src/parser.y"
              {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1772 "src/parser.cpp"
    break;

  case 56: /* LAndExp: LAndExp AND EqExp  */
#line 357 "src/parser.y"
                          {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::AND, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1781 "src/parser.cpp"
    break;

  case 57: /* EqExp: RelExp  */
#line 365 "src/parser.y"
               {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1789 "src/parser.cpp"
    break;

  case 58: /* EqExp: EqExp EQ RelExp  */
#line 368 "src/parser.y"
                        {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::EQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1798 "src/parser.cpp"
    break;

  case 59: /* EqExp: EqExp NEQ RelExp  */
#line 372 "src/parser.y"
                         {
            SymbolEntry* se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::NEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1807 "src/parser.cpp"
    break;

  case 60: /* RelExp: AddExp  */
#line 380 "src/parser.y"
               {
            (yyval.exprtype) = (yyvsp[0].exprtype);
        }
#line 1815 "src/parser.cpp"
    break;

  case 61: /* RelExp: RelExp LESS AddExp  */
#line 383 "src/parser.y"
                           {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESS, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1824 "src/parser.cpp"
    break;

  case 62: /* RelExp: RelExp LESSEQ AddExp  */
#line 387 "src/parser.y"
                             {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::LESSEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1833 "src/parser.cpp"
    break;

  case 63: /* RelExp: RelExp GREAT AddExp  */
#line 391 "src/parser.y"
                            {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREAT, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1842 "src/parser.cpp"
    break;

  case 64: /* RelExp: RelExp GREATEQ AddExp  */
#line 395 "src/parser.y"
                              {
            SymbolEntry *se = new TemporarySymbolEntry(TypeSystem::boolType, SymbolTable::getLabel());
            (yyval.exprtype) = new BinaryExpr(se, BinaryExpr::GREATEQ, (yyvsp[-2].exprtype), (yyvsp[0].exprtype));
        }
#line 1851 "src/parser.cpp"
    break;

  case 65: /* Type: TYPE_INT  */
#line 403 "src/parser.y"
                 {
            (yyval.type) = TypeSystem::intType;
            currentType = TypeSystem::intType;
        }
#line 1860 "src/parser.cpp"
    break;

  case 66: /* Type: TYPE_FLOAT  */
#line 407 "src/parser.y"
                   {
            (yyval.type) = TypeSystem::floatType;
            currentType = TypeSystem::floatType;
        }
#line 1869 "src/parser.cpp"
    break;

  case 67: /* Type: TYPE_VOID  */
#line 411 "src/parser.y"
                  {
            (yyval.type) = TypeSystem::voidType;
        }
#line 1877 "src/parser.cpp"
    break;

  case 68: /* ArrConstIndices: ArrConstIndices LBRACKET ConstExp RBRACKET  */
#line 418 "src/parser.y"
                                                   {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>((yyvsp[-3].stmttype));
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;          
        }
#line 1887 "src/parser.cpp"
    break;

  case 69: /* ArrConstIndices: LBRACKET ConstExp RBRACKET  */
#line 423 "src/parser.y"
                                   {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;
        }
#line 1897 "src/parser.cpp"
    break;

  case 70: /* ArrValIndices: ArrValIndices LBRACKET Exp RBRACKET  */
#line 432 "src/parser.y"
                                            {
            ExprStmtNode* node = dynamic_cast<ExprStmtNode*>((yyvsp[-3].stmttype));
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;          
        }
#line 1907 "src/parser.cpp"
    break;

  case 71: /* ArrValIndices: LBRACKET Exp RBRACKET  */
#line 437 "src/parser.y"
                              {
            ExprStmtNode* node = new ExprStmtNode();
            node->addNext((yyvsp[-1].exprtype));
            (yyval.stmttype) = node;
        }
#line 1917 "src/parser.cpp"
    break;

  case 72: /* DeclStmt: CONST Type ConstDefList SEMICOLON  */
#line 446 "src/parser.y"
                                          {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 1925 "src/parser.cpp"
    break;

  case 73: /* DeclStmt: Type VarDefList SEMICOLON  */
#line 449 "src/parser.y"
                                  {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 1933 "src/parser.cpp"
    break;

  case 74: /* ConstDefList: ConstDefList COMMA ConstDef  */
#line 456 "src/parser.y"
                                    {
            DeclStmt* node = dynamic_cast<DeclStmt*>((yyvsp[-2].stmttype));
            node->addNext(dynamic_cast<DefNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 1943 "src/parser.cpp"
    break;

  case 75: /* ConstDefList: ConstDef  */
#line 461 "src/parser.y"
                 {
            DeclStmt* node = new DeclStmt(true);
            node->addNext(dynamic_cast<DefNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 1953 "src/parser.cpp"
    break;

  case 76: /* ConstDef: ID ASSIGN ConstExp  */
#line 470 "src/parser.y"
                           {
            //首先判断是否重定义
            if(identifiers->isRedefine((yyvsp[-2].strtype))) {
                fprintf(stderr, "identifier %s redefined\n", (yyvsp[-2].strtype));
                exit(EXIT_FAILURE);
            }
            // 此处文法有改动
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::constIntType;
            }
            else{
                type = TypeSystem::constFloatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            // 类型向上转换
            (yyval.stmttype) = new DefNode(new Id(se), dynamic_cast<Node*>((yyvsp[0].exprtype)), true, false);
        }
#line 1979 "src/parser.cpp"
    break;

  case 77: /* ConstDef: ID ArrConstIndices ASSIGN ConstInitVal  */
#line 492 "src/parser.y"
                                              { 
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = new ConstIntArrayType();
            }
            else{
                type = new ConstFloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[-2].stmttype)));
            // 类型向上转换
            (yyval.stmttype) = new DefNode(id, dynamic_cast<Node*>((yyvsp[0].stmttype)), true, true);
        }
#line 2001 "src/parser.cpp"
    break;

  case 78: /* ConstInitVal: ConstExp  */
#line 513 "src/parser.y"
                 {
            // 不能直接赋值，否则根本无法判断是list还是expr
            InitValNode* newNode = new InitValNode(true);
            newNode->setLeafNode(dynamic_cast<ExprNode*>((yyvsp[0].exprtype)));
            (yyval.stmttype) = newNode;
        }
#line 2012 "src/parser.cpp"
    break;

  case 79: /* ConstInitVal: LBRACE ConstInitValList RBRACE  */
#line 520 "src/parser.y"
                                      {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 2020 "src/parser.cpp"
    break;

  case 80: /* ConstInitVal: LBRACE RBRACE  */
#line 523 "src/parser.y"
                     {
            (yyval.stmttype) = new InitValNode(true);
    }
#line 2028 "src/parser.cpp"
    break;

  case 81: /* ConstInitValList: ConstInitValList COMMA ConstInitVal  */
#line 530 "src/parser.y"
                                           {
            InitValNode* node = dynamic_cast<InitValNode*>((yyvsp[-2].stmttype));
            node->addNext(dynamic_cast<InitValNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 2038 "src/parser.cpp"
    break;

  case 82: /* ConstInitValList: ConstInitVal  */
#line 535 "src/parser.y"
                    {
            InitValNode* newNode = new InitValNode(true);
            newNode->addNext(dynamic_cast<InitValNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = newNode;
        }
#line 2048 "src/parser.cpp"
    break;

  case 83: /* VarDefList: VarDefList COMMA VarDef  */
#line 544 "src/parser.y"
                                {
            DeclStmt* node = dynamic_cast<DeclStmt*>((yyvsp[-2].stmttype));
            node->addNext(dynamic_cast<DefNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 2058 "src/parser.cpp"
    break;

  case 84: /* VarDefList: VarDef  */
#line 549 "src/parser.y"
               {
            DeclStmt* node = new DeclStmt(true);
            node->addNext(dynamic_cast<DefNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 2068 "src/parser.cpp"
    break;

  case 85: /* VarDef: ID  */
#line 558 "src/parser.y"
           {
            //首先判断是否重定义
            if(identifiers->isRedefine((yyvsp[0].strtype))) {
                fprintf(stderr, "identifier %s redefined\n", (yyvsp[0].strtype));
                exit(EXIT_FAILURE);
            }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 2092 "src/parser.cpp"
    break;

  case 86: /* VarDef: ID ASSIGN Exp  */
#line 577 "src/parser.y"
                      {
            //首先判断是否重定义
            if(identifiers->isRedefine((yyvsp[-2].strtype))) {
                fprintf(stderr, "identifier %s redefined\n", (yyvsp[-2].strtype));
                exit(EXIT_FAILURE);
        }
            // 首先将ID插入符号表中
            Type* type;
            if(currentType->isInt()){
                type = TypeSystem::intType;
            }
            else{
                type = TypeSystem::floatType;
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), dynamic_cast<Node*>((yyvsp[0].exprtype)), false, false);//类型向上转换
        }
#line 2116 "src/parser.cpp"
    break;

  case 87: /* VarDef: ID ArrConstIndices  */
#line 597 "src/parser.y"
                           {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-1].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-1].strtype), se);
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);//类型向上转换
        }
#line 2136 "src/parser.cpp"
    break;

  case 88: /* VarDef: ID ArrConstIndices ASSIGN VarInitVal  */
#line 612 "src/parser.y"
                                            {
            Type* type;
            if(currentType->isInt()){
                type = new IntArrayType();
            }
            else{
                type = new FloatArrayType();
            }
            SymbolEntry *se;
            se = new IdentifierSymbolEntry(type, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[-2].stmttype)));
            (yyval.stmttype) = new DefNode(id, dynamic_cast<Node*>((yyvsp[0].stmttype)), false, true);//类型向上转换
        }
#line 2156 "src/parser.cpp"
    break;

  case 89: /* VarInitVal: Exp  */
#line 631 "src/parser.y"
            {
            InitValNode* node = new InitValNode(false);
            node->setLeafNode(dynamic_cast<ExprNode*>((yyvsp[0].exprtype)));
            (yyval.stmttype) = node;
        }
#line 2166 "src/parser.cpp"
    break;

  case 90: /* VarInitVal: LBRACE VarInitValList RBRACE  */
#line 637 "src/parser.y"
                                    {
            (yyval.stmttype) = (yyvsp[-1].stmttype);
        }
#line 2174 "src/parser.cpp"
    break;

  case 91: /* VarInitVal: LBRACE RBRACE  */
#line 640 "src/parser.y"
                     {
            (yyval.stmttype) = new InitValNode(false);
    }
#line 2182 "src/parser.cpp"
    break;

  case 92: /* VarInitValList: VarInitValList COMMA VarInitVal  */
#line 647 "src/parser.y"
                                       {
            InitValNode* node = dynamic_cast<InitValNode*>((yyvsp[-2].stmttype));
            node->addNext(dynamic_cast<InitValNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = node;
        }
#line 2192 "src/parser.cpp"
    break;

  case 93: /* VarInitValList: VarInitVal  */
#line 652 "src/parser.y"
                  {
            InitValNode* newNode = new InitValNode(false);
            newNode->addNext(dynamic_cast<InitValNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = newNode;
        }
#line 2202 "src/parser.cpp"
    break;

  case 94: /* $@2: %empty  */
#line 661 "src/parser.y"
                {
            Type *funcType;
            funcType = new FunctionType((yyvsp[-1].type),{});
            SymbolEntry *se = new IdentifierSymbolEntry(funcType, (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            identifiers = new SymbolTable(identifiers);
        }
#line 2214 "src/parser.cpp"
    break;

  case 95: /* $@3: %empty  */
#line 668 "src/parser.y"
                         {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-3].strtype));
            assert(se != nullptr);
            if((yyvsp[0].stmttype)!=nullptr){
                //将函数参数类型写入符号表
                (dynamic_cast<FunctionType*>(se->getType()))->setparamsType(
                    (dynamic_cast<FuncDefParamsNode*>((yyvsp[0].stmttype)))->getParamsType()
                );
            }   
        }
#line 2230 "src/parser.cpp"
    break;

  case 96: /* FuncDef: Type ID $@2 LPAREN FuncParams $@3 RPAREN BlockStmt  */
#line 679 "src/parser.y"
                         {
            SymbolEntry *se;
            se = identifiers->lookup((yyvsp[-6].strtype));
            assert(se != nullptr);
            (yyval.stmttype) = new FunctionDef(se, dynamic_cast<FuncDefParamsNode*>((yyvsp[-3].stmttype)), (yyvsp[0].stmttype));
            SymbolTable *top = identifiers;
            identifiers = identifiers->getPrev();
            delete top;
            delete [](yyvsp[-6].strtype);
        }
#line 2245 "src/parser.cpp"
    break;

  case 97: /* FuncParams: FuncParams COMMA FuncParam  */
#line 693 "src/parser.y"
                                   {
            FuncDefParamsNode* node = dynamic_cast<FuncDefParamsNode*>((yyvsp[-2].stmttype));
            node->addNext((dynamic_cast<DefNode*>((yyvsp[0].stmttype)))->getId());
            (yyval.stmttype) = node;
        }
#line 2255 "src/parser.cpp"
    break;

  case 98: /* FuncParams: FuncParam  */
#line 698 "src/parser.y"
                  {
            FuncDefParamsNode* node = new FuncDefParamsNode();
            node->addNext((dynamic_cast<DefNode*>((yyvsp[0].stmttype)))->getId());
            (yyval.stmttype) = node;
        }
#line 2265 "src/parser.cpp"
    break;

  case 99: /* FuncParams: %empty  */
#line 703 "src/parser.y"
               {
            (yyval.stmttype) = nullptr;
        }
#line 2273 "src/parser.cpp"
    break;

  case 100: /* FuncParam: Type ID  */
#line 710 "src/parser.y"
                {
            SymbolEntry *se = new IdentifierSymbolEntry((yyvsp[-1].type), (yyvsp[0].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[0].strtype), se);
            (yyval.stmttype) = new DefNode(new Id(se), nullptr, false, false);
        }
#line 2283 "src/parser.cpp"
    break;

  case 101: /* FuncParam: Type ID LBRACKET RBRACKET ArrConstIndices  */
#line 716 "src/parser.y"
                                                 {
            Type* arrayType; 
            if((yyvsp[-4].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
                (dynamic_cast<IntArrayType*>(arrayType))->pushBackDimension(-1);
            }
            else if((yyvsp[-4].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                (dynamic_cast<FloatArrayType*>(arrayType))->pushBackDimension(-1);
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-3].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-3].strtype), se);
            Id* id = new Id(se);
            id->addIndices(dynamic_cast<ExprStmtNode*>((yyvsp[0].stmttype)));
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2305 "src/parser.cpp"
    break;

  case 102: /* FuncParam: Type ID LBRACKET RBRACKET  */
#line 733 "src/parser.y"
                                 {
            Type* arrayType; 
            if((yyvsp[-3].type)==TypeSystem::intType){
                arrayType = new IntArrayType();
                (dynamic_cast<IntArrayType*>(arrayType))->pushBackDimension(-1);
            }
            else if((yyvsp[-3].type)==TypeSystem::floatType){
                arrayType = new FloatArrayType();
                (dynamic_cast<FloatArrayType*>(arrayType))->pushBackDimension(-1);
            }
            //最高维未指定，记为默认值-1
            SymbolEntry *se = new IdentifierSymbolEntry(arrayType, (yyvsp[-2].strtype), identifiers->getLevel());
            identifiers->install((yyvsp[-2].strtype), se);
            Id* id = new Id(se);
            (yyval.stmttype) = new DefNode(id, nullptr, false, true);
        }
#line 2326 "src/parser.cpp"
    break;


#line 2330 "src/parser.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 751 "src/parser.y"


int yyerror(char const* message)
{
    std::cerr<<message<<std::endl;
    return -1;
}

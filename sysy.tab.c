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




/* First part of user prologue.  */
#line 7 "src/sysy.y"


#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"

// 声明 lexer 函数和错误处理函数
int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

using namespace std;


#line 86 "sysy.tab.c"

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

#include "sysy.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_RETURN = 4,                     /* RETURN  */
  YYSYMBOL_LESSEQUAL = 5,                  /* LESSEQUAL  */
  YYSYMBOL_GREATEREQUAL = 6,               /* GREATEREQUAL  */
  YYSYMBOL_EQUAL = 7,                      /* EQUAL  */
  YYSYMBOL_NOTEQUAL = 8,                   /* NOTEQUAL  */
  YYSYMBOL_ANDOP = 9,                      /* ANDOP  */
  YYSYMBOL_OROP = 10,                      /* OROP  */
  YYSYMBOL_CONST = 11,                     /* CONST  */
  YYSYMBOL_IDENT = 12,                     /* IDENT  */
  YYSYMBOL_INT_CONST = 13,                 /* INT_CONST  */
  YYSYMBOL_14_ = 14,                       /* ';'  */
  YYSYMBOL_15_ = 15,                       /* ','  */
  YYSYMBOL_16_ = 16,                       /* '='  */
  YYSYMBOL_17_ = 17,                       /* '('  */
  YYSYMBOL_18_ = 18,                       /* ')'  */
  YYSYMBOL_19_ = 19,                       /* '{'  */
  YYSYMBOL_20_ = 20,                       /* '}'  */
  YYSYMBOL_21_ = 21,                       /* '+'  */
  YYSYMBOL_22_ = 22,                       /* '-'  */
  YYSYMBOL_23_ = 23,                       /* '!'  */
  YYSYMBOL_24_ = 24,                       /* '*'  */
  YYSYMBOL_25_ = 25,                       /* '/'  */
  YYSYMBOL_26_ = 26,                       /* '%'  */
  YYSYMBOL_27_ = 27,                       /* '<'  */
  YYSYMBOL_28_ = 28,                       /* '>'  */
  YYSYMBOL_YYACCEPT = 29,                  /* $accept  */
  YYSYMBOL_CompUnit = 30,                  /* CompUnit  */
  YYSYMBOL_Decl = 31,                      /* Decl  */
  YYSYMBOL_ConstDecl = 32,                 /* ConstDecl  */
  YYSYMBOL_BType = 33,                     /* BType  */
  YYSYMBOL_ConstDefList = 34,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 35,                  /* ConstDef  */
  YYSYMBOL_ConstInitVal = 36,              /* ConstInitVal  */
  YYSYMBOL_FuncDef = 37,                   /* FuncDef  */
  YYSYMBOL_FuncType = 38,                  /* FuncType  */
  YYSYMBOL_Block = 39,                     /* Block  */
  YYSYMBOL_BlockItemList = 40,             /* BlockItemList  */
  YYSYMBOL_BlockItem = 41,                 /* BlockItem  */
  YYSYMBOL_Stmt = 42,                      /* Stmt  */
  YYSYMBOL_Exp = 43,                       /* Exp  */
  YYSYMBOL_LVal = 44,                      /* LVal  */
  YYSYMBOL_PrimaryExp = 45,                /* PrimaryExp  */
  YYSYMBOL_Number = 46,                    /* Number  */
  YYSYMBOL_UnaryExp = 47,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 48,                   /* UnaryOp  */
  YYSYMBOL_MulExp = 49,                    /* MulExp  */
  YYSYMBOL_BinPriOp = 50,                  /* BinPriOp  */
  YYSYMBOL_AddExp = 51,                    /* AddExp  */
  YYSYMBOL_BinOp = 52,                     /* BinOp  */
  YYSYMBOL_RelExp = 53,                    /* RelExp  */
  YYSYMBOL_RelOp = 54,                     /* RelOp  */
  YYSYMBOL_EqExp = 55,                     /* EqExp  */
  YYSYMBOL_EqOp = 56,                      /* EqOp  */
  YYSYMBOL_LAndExp = 57,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 58,                    /* LOrExp  */
  YYSYMBOL_ConstExp = 59                   /* ConstExp  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   49

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  29
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  52
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  77

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   268


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
       2,     2,     2,    23,     2,     2,     2,    26,     2,     2,
      17,    18,    24,    21,    15,    22,     2,    25,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    14,
      27,    16,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    19,     2,    20,     2,     2,     2,     2,
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
       5,     6,     7,     8,     9,    10,    11,    12,    13
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    55,    55,    74,    83,    93,   102,   107,   119,   129,
     140,   151,   162,   171,   176,   188,   194,   203,   214,   223,
     232,   238,   244,   253,   262,   268,   278,   284,   290,   299,
     305,   316,   322,   328,   337,   343,   354,   360,   369,   375,
     386,   392,   398,   404,   413,   419,   430,   436,   445,   451,
     461,   467,   477
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
  "\"end of file\"", "error", "\"invalid token\"", "INT", "RETURN",
  "LESSEQUAL", "GREATEREQUAL", "EQUAL", "NOTEQUAL", "ANDOP", "OROP",
  "CONST", "IDENT", "INT_CONST", "';'", "','", "'='", "'('", "')'", "'{'",
  "'}'", "'+'", "'-'", "'!'", "'*'", "'/'", "'%'", "'<'", "'>'", "$accept",
  "CompUnit", "Decl", "ConstDecl", "BType", "ConstDefList", "ConstDef",
  "ConstInitVal", "FuncDef", "FuncType", "Block", "BlockItemList",
  "BlockItem", "Stmt", "Exp", "LVal", "PrimaryExp", "Number", "UnaryExp",
  "UnaryOp", "MulExp", "BinPriOp", "AddExp", "BinOp", "RelExp", "RelOp",
  "EqExp", "EqOp", "LAndExp", "LOrExp", "ConstExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-39)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      13,   -39,    25,   -39,    14,   -39,    10,    12,     9,     6,
     -39,    -8,    26,   -39,   -39,    15,     6,   -39,   -39,   -39,
      -8,   -39,   -39,   -39,    17,   -39,   -39,   -39,   -39,    -8,
     -18,   -10,    -4,    11,    23,    24,   -39,    21,   -39,   -39,
      18,   -39,   -39,   -39,   -39,   -39,    -8,   -39,   -39,    -8,
     -39,   -39,   -39,   -39,    -8,   -39,   -39,    -8,    -8,    -8,
      22,   -39,   -39,   -39,   -18,   -10,    -4,    11,    23,    -8,
       7,   -39,   -39,   -39,   -39,    21,   -39
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,     0,     2,     0,     1,     0,     0,     0,    13,
      10,     0,     0,    15,     3,     0,    13,    16,    19,    23,
       0,    26,    27,    28,     0,    21,    24,    22,    29,     0,
      34,    38,    44,    48,    50,    18,     5,     0,    12,    14,
       0,    17,    25,    31,    32,    33,     0,    36,    37,     0,
      42,    43,    40,    41,     0,    46,    47,     0,     0,     0,
       0,     6,    20,    30,    35,    39,    45,    49,    51,     0,
       0,     8,    52,     9,     4,     0,     7
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -39,   -39,   -39,   -39,   -39,   -39,   -38,   -39,   -39,   -39,
     -39,    27,   -39,   -39,   -20,   -39,   -39,   -39,   -26,   -39,
      -9,   -39,   -15,   -39,   -16,   -39,   -14,   -39,   -17,   -39,
     -39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,    13,    14,    37,    70,    61,    71,     3,     4,
      10,    15,    16,    17,    24,    25,    26,    27,    28,    29,
      30,    46,    31,    49,    32,    54,    33,    57,    34,    35,
      73
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      40,    50,    51,    42,    18,    19,    43,    44,    45,    20,
      11,    47,    48,    21,    22,    23,     1,    12,    55,    56,
      63,    74,    75,    52,    53,     5,     6,     7,     9,    36,
       8,    41,    58,    60,    59,    38,    62,    76,    69,    65,
      64,    66,    68,    39,    67,     0,     0,     0,     0,    72
};

static const yytype_int8 yycheck[] =
{
      20,     5,     6,    29,    12,    13,    24,    25,    26,    17,
       4,    21,    22,    21,    22,    23,     3,    11,     7,     8,
      46,    14,    15,    27,    28,     0,    12,    17,    19,     3,
      18,    14,     9,    12,    10,    20,    18,    75,    16,    54,
      49,    57,    59,    16,    58,    -1,    -1,    -1,    -1,    69
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    30,    37,    38,     0,    12,    17,    18,    19,
      39,     4,    11,    31,    32,    40,    41,    42,    12,    13,
      17,    21,    22,    23,    43,    44,    45,    46,    47,    48,
      49,    51,    53,    55,    57,    58,     3,    33,    20,    40,
      43,    14,    47,    24,    25,    26,    50,    21,    22,    52,
       5,     6,    27,    28,    54,     7,     8,    56,     9,    10,
      12,    35,    18,    47,    49,    51,    53,    55,    57,    16,
      34,    36,    43,    59,    14,    15,    35
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    29,    30,    31,    32,    33,    34,    34,    35,    36,
      37,    38,    39,    40,    40,    41,    41,    42,    43,    44,
      45,    45,    45,    46,    47,    47,    48,    48,    48,    49,
      49,    50,    50,    50,    51,    51,    52,    52,    53,    53,
      54,    54,    54,    54,    55,    55,    56,    56,    57,    57,
      58,    58,    59
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     5,     1,     0,     3,     3,     1,
       5,     1,     3,     0,     2,     1,     1,     3,     1,     1,
       3,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
       1,     3,     1
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
        yyerror (ast, YY_("syntax error: cannot back up")); \
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
                  Kind, Value, ast); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (ast);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep, ast);
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
                 int yyrule, std::unique_ptr<BaseAST> &ast)
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
                       &yyvsp[(yyi + 1) - (yynrhs)], ast);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, ast); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, std::unique_ptr<BaseAST> &ast)
{
  YY_USE (yyvaluep);
  YY_USE (ast);
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
yyparse (std::unique_ptr<BaseAST> &ast)
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
  case 2: /* CompUnit: FuncDef  */
#line 55 "src/sysy.y"
            {
    std::cout << "CompUnit" << std::endl;
    auto comp_unit = make_unique<CompUnitAST>();
    comp_unit->func_def = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    ast = move(comp_unit);
  }
#line 1183 "sysy.tab.c"
    break;

  case 3: /* Decl: ConstDecl  */
#line 74 "src/sysy.y"
              {
    std::cout << "Decl" << std::endl;
    auto ast = new DeclAST();
    ast->const_decl = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1194 "sysy.tab.c"
    break;

  case 4: /* ConstDecl: CONST BType ConstDef ConstDefList ';'  */
#line 83 "src/sysy.y"
                                          {
    std::cout << "ConstDecl" << std::endl;
    auto ast = new ConstDeclAST();
    ast->b_type = unique_ptr<BaseAST>((yyvsp[-3].ast_val));
    ast->const_def_list = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1206 "sysy.tab.c"
    break;

  case 5: /* BType: INT  */
#line 93 "src/sysy.y"
        {
    std::cout << "BType" << std::endl;
    auto ast = new BTypeAST();
    ast->type = "int";
    (yyval.ast_val) = ast;
  }
#line 1217 "sysy.tab.c"
    break;

  case 6: /* ConstDefList: %empty  */
#line 102 "src/sysy.y"
    {
    std::cout << "ConstDefList1" << std::endl;
    auto ast = new ConstDefListAST();
    (yyval.ast_val) = ast;
  }
#line 1227 "sysy.tab.c"
    break;

  case 7: /* ConstDefList: ConstDefList ',' ConstDef  */
#line 107 "src/sysy.y"
                              {
    std::cout << "ConstDefList2" << std::endl;
    auto ast = new ConstDefListAST();
    // Since unique_ptr's can't be copied, we move them
    // Makes all ConstDefLists except the final one invalid
    ast->const_defs = move(unique_ptr<BaseAST>((yyvsp[-2].ast_val))->const_defs); 
    (ast->const_defs).push_back(unique_ptr<BaseAST>((yyvsp[0].ast_val)));
    (yyval.ast_val) = ast;
  }
#line 1241 "sysy.tab.c"
    break;

  case 8: /* ConstDef: IDENT '=' ConstInitVal  */
#line 119 "src/sysy.y"
                           {
    std::cout << "ConstDef" << std::endl;
    auto ast = new ConstDefAST();
    ast->ident = *unique_ptr<string>((yyvsp[-2].str_val));
    ast->const_init_val = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1253 "sysy.tab.c"
    break;

  case 9: /* ConstInitVal: ConstExp  */
#line 129 "src/sysy.y"
             {
    std::cout << "ConstInitVal" << std::endl;
    auto ast = new ConstInitValAST();
    ast->const_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1264 "sysy.tab.c"
    break;

  case 10: /* FuncDef: FuncType IDENT '(' ')' Block  */
#line 140 "src/sysy.y"
                                 {
    std::cout << "FuncDef" << std::endl;
    auto ast = new FuncDefAST();
    ast->func_type = unique_ptr<BaseAST>((yyvsp[-4].ast_val));
    ast->ident = *unique_ptr<string>((yyvsp[-3].str_val));
    ast->block = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1277 "sysy.tab.c"
    break;

  case 11: /* FuncType: INT  */
#line 151 "src/sysy.y"
        {
    std::cout << "FuncType" << std::endl;
    auto ast = new FuncTypeAST();
    ast->func_type = "int";
    (yyval.ast_val) = ast;
  }
#line 1288 "sysy.tab.c"
    break;

  case 12: /* Block: '{' BlockItemList '}'  */
#line 162 "src/sysy.y"
                          {
    std::cout << "Block" << std::endl;
    auto ast = new BlockAST();
    ast->block_item_list = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1299 "sysy.tab.c"
    break;

  case 13: /* BlockItemList: %empty  */
#line 171 "src/sysy.y"
    {
    std::cout << "BlockItemList1" << std::endl;
    auto ast = new BlockItemListAST();
    (yyval.ast_val) = ast;
  }
#line 1309 "sysy.tab.c"
    break;

  case 14: /* BlockItemList: BlockItem BlockItemList  */
#line 176 "src/sysy.y"
                            {
    std::cout << "BlockItemList2" << std::endl;
    auto ast = new BlockItemListAST();
    // Since unique_ptr's can't be copied, we move them
    // Makes all BlockItemLists except the final one invalid
    ast->block_items = move(unique_ptr<BaseAST>((yyvsp[0].ast_val))->block_items);
    (ast->block_items).push_back(unique_ptr<BaseAST>((yyvsp[-1].ast_val)));
    (yyval.ast_val) = ast;
  }
#line 1323 "sysy.tab.c"
    break;

  case 15: /* BlockItem: Decl  */
#line 188 "src/sysy.y"
         {
    std::cout << "BlockItem1" << std::endl;
    auto ast = new BlockItemAST1();
    ast->decl = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1334 "sysy.tab.c"
    break;

  case 16: /* BlockItem: Stmt  */
#line 194 "src/sysy.y"
         {
    std::cout << "BlockItem2" << std::endl;
    auto ast = new BlockItemAST2();
    ast->stmt = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1345 "sysy.tab.c"
    break;

  case 17: /* Stmt: RETURN Exp ';'  */
#line 203 "src/sysy.y"
                   {
    std::cout << "Stmt" << std::endl;
    auto ast = new StmtAST();
    ast->exp = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1356 "sysy.tab.c"
    break;

  case 18: /* Exp: LOrExp  */
#line 214 "src/sysy.y"
           {
    std::cout << "Exp" << std::endl;
    auto ast = new ExpAST();
    ast->l_or_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1367 "sysy.tab.c"
    break;

  case 19: /* LVal: IDENT  */
#line 223 "src/sysy.y"
          {
    std::cout << "LVal" << std::endl;
    auto ast = new LValAST();
    ast->ident = *unique_ptr<string>((yyvsp[0].str_val));
    (yyval.ast_val) = ast;
  }
#line 1378 "sysy.tab.c"
    break;

  case 20: /* PrimaryExp: '(' Exp ')'  */
#line 232 "src/sysy.y"
                {
    std::cout << "PrimaryExp1" << std::endl;
    auto ast = new PrimaryExpAST1();
    ast->exp = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1389 "sysy.tab.c"
    break;

  case 21: /* PrimaryExp: LVal  */
#line 238 "src/sysy.y"
         {
    std::cout << "PrimaryExp3" << std::endl;
    auto ast = new PrimaryExpAST3();
    ast->l_val = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1400 "sysy.tab.c"
    break;

  case 22: /* PrimaryExp: Number  */
#line 244 "src/sysy.y"
           {
    std::cout << "PrimaryExp2" << std::endl;
    auto ast = new PrimaryExpAST2();
    ast->number = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1411 "sysy.tab.c"
    break;

  case 23: /* Number: INT_CONST  */
#line 253 "src/sysy.y"
              {
    std::cout << "Number" << std::endl;
    auto ast = new NumberAST();
    ast->int_const = (yyvsp[0].int_val);
    (yyval.ast_val) = ast;
  }
#line 1422 "sysy.tab.c"
    break;

  case 24: /* UnaryExp: PrimaryExp  */
#line 262 "src/sysy.y"
               {
    std::cout << "UnaryExp1" << std::endl;
    auto ast = new UnaryExpAST1();
    ast->primary_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1433 "sysy.tab.c"
    break;

  case 25: /* UnaryExp: UnaryOp UnaryExp  */
#line 268 "src/sysy.y"
                     {
    std::cout << "UnaryExp2" << std::endl;
    auto ast = new UnaryExpAST2();
    ast->unary_op = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    ast->unary_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1445 "sysy.tab.c"
    break;

  case 26: /* UnaryOp: '+'  */
#line 278 "src/sysy.y"
        {
    std::cout << "UnaryOp1" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = positive_op;
    (yyval.ast_val) = ast;
  }
#line 1456 "sysy.tab.c"
    break;

  case 27: /* UnaryOp: '-'  */
#line 284 "src/sysy.y"
        {
    std::cout << "UnaryOp2" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = negative_op;
    (yyval.ast_val) = ast;
  }
#line 1467 "sysy.tab.c"
    break;

  case 28: /* UnaryOp: '!'  */
#line 290 "src/sysy.y"
        {
    std::cout << "UnaryOp3" << std::endl;
    auto ast = new UnaryOpAST();
    ast->op = not_op;
    (yyval.ast_val) = ast;
  }
#line 1478 "sysy.tab.c"
    break;

  case 29: /* MulExp: UnaryExp  */
#line 299 "src/sysy.y"
             {
    std::cout << "MulExp1" << std::endl;
    auto ast = new MulExpAST1();
    ast->unary_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1489 "sysy.tab.c"
    break;

  case 30: /* MulExp: MulExp BinPriOp UnaryExp  */
#line 305 "src/sysy.y"
                             {
    std::cout << "MulExp2" << std::endl;
    auto ast = new MulExpAST2();
    ast->mul_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->bin_pri_op = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    ast->unary_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1502 "sysy.tab.c"
    break;

  case 31: /* BinPriOp: '*'  */
#line 316 "src/sysy.y"
        {
    std::cout << "BinPriOp1" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = mul_op;
    (yyval.ast_val) = ast;
  }
#line 1513 "sysy.tab.c"
    break;

  case 32: /* BinPriOp: '/'  */
#line 322 "src/sysy.y"
        {
    std::cout << "BinPriOp2" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = div_op;
    (yyval.ast_val) = ast;
  }
#line 1524 "sysy.tab.c"
    break;

  case 33: /* BinPriOp: '%'  */
#line 328 "src/sysy.y"
        {
    std::cout << "BinPriOp3" << std::endl;
    auto ast = new BinPriOpAST();
    ast->op = mod_op;
    (yyval.ast_val) = ast;
  }
#line 1535 "sysy.tab.c"
    break;

  case 34: /* AddExp: MulExp  */
#line 337 "src/sysy.y"
           {
    std::cout << "AddExp1" << std::endl;
    auto ast = new AddExpAST1();
    ast->mul_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1546 "sysy.tab.c"
    break;

  case 35: /* AddExp: AddExp BinOp MulExp  */
#line 343 "src/sysy.y"
                        {
    std::cout << "AddExp2" << std::endl;
    auto ast = new AddExpAST2();
    ast->add_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->bin_op = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    ast->mul_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1559 "sysy.tab.c"
    break;

  case 36: /* BinOp: '+'  */
#line 354 "src/sysy.y"
        {
    std::cout << "BinOp1" << std::endl;
    auto ast = new BinOpAST();
    ast->op = add_op;
    (yyval.ast_val) = ast;
  }
#line 1570 "sysy.tab.c"
    break;

  case 37: /* BinOp: '-'  */
#line 360 "src/sysy.y"
        {
    std::cout << "BinOp2" << std::endl;
    auto ast = new BinOpAST();
    ast->op = sub_op;
    (yyval.ast_val) = ast;
  }
#line 1581 "sysy.tab.c"
    break;

  case 38: /* RelExp: AddExp  */
#line 369 "src/sysy.y"
           {
    std::cout << "RelExp1" << std::endl;
    auto ast = new RelExpAST1();
    ast->add_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1592 "sysy.tab.c"
    break;

  case 39: /* RelExp: RelExp RelOp AddExp  */
#line 375 "src/sysy.y"
                        {
    std::cout << "RelExp2" << std::endl;
    auto ast = new RelExpAST2();
    ast->rel_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->rel_op = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    ast->add_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1605 "sysy.tab.c"
    break;

  case 40: /* RelOp: '<'  */
#line 386 "src/sysy.y"
        {
    std::cout << "RelOp1" << std::endl;
    auto ast = new RelOpAST();
    ast->op = less_op;
    (yyval.ast_val) = ast;
  }
#line 1616 "sysy.tab.c"
    break;

  case 41: /* RelOp: '>'  */
#line 392 "src/sysy.y"
        {
    std::cout << "RelOp2" << std::endl;
    auto ast = new RelOpAST();
    ast->op = greater_op;
    (yyval.ast_val) = ast;
  }
#line 1627 "sysy.tab.c"
    break;

  case 42: /* RelOp: LESSEQUAL  */
#line 398 "src/sysy.y"
              {
    std::cout << "RelOp3" << std::endl;
    auto ast = new RelOpAST();
    ast->op = less_equal_op;
    (yyval.ast_val) = ast;
  }
#line 1638 "sysy.tab.c"
    break;

  case 43: /* RelOp: GREATEREQUAL  */
#line 404 "src/sysy.y"
                 {
    std::cout << "RelOp4" << std::endl;
    auto ast = new RelOpAST();
    ast->op = greater_equal_op;
    (yyval.ast_val) = ast;
  }
#line 1649 "sysy.tab.c"
    break;

  case 44: /* EqExp: RelExp  */
#line 413 "src/sysy.y"
           {
    std::cout << "EqExp1" << std::endl;
    auto ast = new EqExpAST1();
    ast->rel_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1660 "sysy.tab.c"
    break;

  case 45: /* EqExp: EqExp EqOp RelExp  */
#line 419 "src/sysy.y"
                      {
    std::cout << "EqExp2" << std::endl;
    auto ast = new EqExpAST2();
    ast->eq_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->eq_op = unique_ptr<BaseAST>((yyvsp[-1].ast_val));
    ast->rel_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1673 "sysy.tab.c"
    break;

  case 46: /* EqOp: EQUAL  */
#line 430 "src/sysy.y"
          {
    std::cout << "EqOp1" << std::endl;
    auto ast = new EqOpAST();
    ast->op = equal_op;
    (yyval.ast_val) = ast;
  }
#line 1684 "sysy.tab.c"
    break;

  case 47: /* EqOp: NOTEQUAL  */
#line 436 "src/sysy.y"
             {
    std::cout << "EqOp2" << std::endl;
    auto ast = new EqOpAST();
    ast->op = not_equal_op;
    (yyval.ast_val) = ast;
  }
#line 1695 "sysy.tab.c"
    break;

  case 48: /* LAndExp: EqExp  */
#line 445 "src/sysy.y"
          {
    std::cout << "LAndExp1" << std::endl;
    auto ast = new LAndExpAST1();
    ast->eq_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1706 "sysy.tab.c"
    break;

  case 49: /* LAndExp: LAndExp ANDOP EqExp  */
#line 451 "src/sysy.y"
                        {
    std::cout << "LAndExp2" << std::endl;
    auto ast = new LAndExpAST2();
    ast->l_and_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->eq_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1718 "sysy.tab.c"
    break;

  case 50: /* LOrExp: LAndExp  */
#line 461 "src/sysy.y"
            {
    std::cout << "LOrExp1" << std::endl;
    auto ast = new LOrExpAST1();
    ast->l_and_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1729 "sysy.tab.c"
    break;

  case 51: /* LOrExp: LOrExp OROP LAndExp  */
#line 467 "src/sysy.y"
                        {
    std::cout << "LOrExp2" << std::endl;
    auto ast = new LOrExpAST2();
    ast->l_or_exp = unique_ptr<BaseAST>((yyvsp[-2].ast_val));
    ast->l_and_exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1741 "sysy.tab.c"
    break;

  case 52: /* ConstExp: Exp  */
#line 477 "src/sysy.y"
        {
    std::cout << "ConstExp" << std::endl;
    auto ast = new ConstExpAST();
    ast->exp = unique_ptr<BaseAST>((yyvsp[0].ast_val));
    (yyval.ast_val) = ast;
  }
#line 1752 "sysy.tab.c"
    break;


#line 1756 "sysy.tab.c"

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
      yyerror (ast, YY_("syntax error"));
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
                      yytoken, &yylval, ast);
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, ast);
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
  yyerror (ast, YY_("memory exhausted"));
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
                  yytoken, &yylval, ast);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, ast);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 485 "src/sysy.y"


// 定义错误处理函数, 其中第二个参数是错误信息
// parser 如果发生错误 (例如输入的程序出现了语法错误), 就会调用这个函数
void yyerror(unique_ptr<BaseAST> &ast, const char *s) {
  cerr << "error: " << s << endl;
}

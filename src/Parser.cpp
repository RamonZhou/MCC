/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "ast.hpp" 
#include <string>
#include <iostream>


void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);

AST::Program *Root;

#line 86 "Parser.cpp"

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
    COMMA = 258,
    ELLIPSES = 259,
    DOT = 260,
    SQUOTE = 261,
    DQUOTE = 262,
    SEMI = 263,
    QUES = 264,
    COLON = 265,
    LPAREN = 266,
    RPAREN = 267,
    LBRACKET = 268,
    RBRACKET = 269,
    LBRACE = 270,
    RBRACE = 271,
    SHLEQ = 272,
    SHL = 273,
    SHREQ = 274,
    SHR = 275,
    EQ = 276,
    GE = 277,
    GT = 278,
    LE = 279,
    LT = 280,
    NEQ = 281,
    NOT = 282,
    ASSIGN = 283,
    AND = 284,
    BANDEQ = 285,
    BAND = 286,
    OR = 287,
    BOREQ = 288,
    BOR = 289,
    ARW = 290,
    BXOREQ = 291,
    BXOR = 292,
    BNOT = 293,
    DADD = 294,
    ADDEQ = 295,
    ADD = 296,
    DSUB = 297,
    SUBEQ = 298,
    SUB = 299,
    MULEQ = 300,
    MUL = 301,
    DIVEQ = 302,
    DIV = 303,
    MODEQ = 304,
    MOD = 305,
    STRUCT = 306,
    UNION = 307,
    TYPEDEF = 308,
    CONST = 309,
    ENUM = 310,
    PTR = 311,
    ARRAY = 312,
    IF = 313,
    ELSE = 314,
    FOR = 315,
    WHILE = 316,
    BREAK = 317,
    CONTINUE = 318,
    RETURN = 319,
    SIZEOF = 320,
    TRUE = 321,
    FALSE = 322,
    BOOL = 323,
    SHORT = 324,
    INT = 325,
    LONG = 326,
    CHAR = 327,
    FLOAT = 328,
    DOUBLE = 329,
    VOID = 330,
    INTEGER = 331,
    IDENTIFIER = 332,
    REAL = 333,
    CHARACTER = 334,
    STRING = 335,
    FUNC_CALL_ARG_LIST = 336
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 19 "parser.y"

    int iVal;
    std::string *sVal;
    double dVal;
    char cVal;
	std::string *strVal;

    AST::Program *program;

    AST::Def *def;
    AST::Defs *defs; 
    AST::FuncDef *funcDef;
    AST::VarDef *varDef;
        AST::VarList *varList;
        AST::VarInit *varInit;
    AST::IntType *intType;
    AST::CharType *charType;
    AST::FloatType *floatType;
    AST::DoubleType *doubleType;
    AST::StringType *stringType;
    AST::BoolType *boolType;
    AST::VoidType *voidType;
    AST::StructType *structType;
    AST::PointerType *pointerType;
    AST::ArrayType *arrayType;
    AST::DefinedType *definedType;

    AST::StructMembers *structMembers;
    AST::StructMember *structMember;
    AST::MemberList *memberList;


    AST::MemberList *memberList;
    AST::Parms *parms;
    AST::Parm *parm;

    AST::TypeDef *typeDef;
    AST::VarType *varType;

    AST::Stms *stms;
    AST::Stm *stm;
    AST::IfStm *ifStm;
    AST::ForStm *forStm;
    AST::WhileStm *whileStm;
    AST::BreakStm* breakStm;
	AST::ContinueStm* continueStm;
    AST::ReturnStm *returnStm;

    AST::Block *block;
    AST::Parm *parm;
    AST::Parms *parms;
    AST::VarInit *varInit;
    AST::VarList *varList;

    AST::Exp *exp;
    AST::Exps *exps;
    AST::ArraySubscript *arraySubscript;
    AST::Constant* constant;
	

#line 278 "Parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);





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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1308

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  82
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  131
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  229

#define YYUNDEFTOK  2
#define YYMAXUTOK   336


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   153,   153,   156,   157,   160,   161,   162,   165,   166,
     169,   170,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   184,   188,   189,   193,   194,   198,   199,
     200,   204,   205,   209,   210,   211,   215,   216,   219,   220,
     223,   226,   229,   230,   231,   234,   235,   238,   239,   242,
     243,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   259,   260,   263,   264,   267,   270,   273,   276,
     277,   280,   283,   284,   285,   286,   287,   288,   289,   291,
     292,   293,   294,   295,   296,   297,   298,   299,   300,   301,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,   321,   322,
     323,   324,   325,   326,   327,   328,   329,   330,   331,   332,
     335,   338,   339,   340,   341,   342,   343,   346,   347,   348,
     351,   352
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "COMMA", "ELLIPSES", "DOT", "SQUOTE",
  "DQUOTE", "SEMI", "QUES", "COLON", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "SHLEQ", "SHL", "SHREQ", "SHR", "EQ",
  "GE", "GT", "LE", "LT", "NEQ", "NOT", "ASSIGN", "AND", "BANDEQ", "BAND",
  "OR", "BOREQ", "BOR", "ARW", "BXOREQ", "BXOR", "BNOT", "DADD", "ADDEQ",
  "ADD", "DSUB", "SUBEQ", "SUB", "MULEQ", "MUL", "DIVEQ", "DIV", "MODEQ",
  "MOD", "STRUCT", "UNION", "TYPEDEF", "CONST", "ENUM", "PTR", "ARRAY",
  "IF", "ELSE", "FOR", "WHILE", "BREAK", "CONTINUE", "RETURN", "SIZEOF",
  "TRUE", "FALSE", "BOOL", "SHORT", "INT", "LONG", "CHAR", "FLOAT",
  "DOUBLE", "VOID", "INTEGER", "IDENTIFIER", "REAL", "CHARACTER", "STRING",
  "FUNC_CALL_ARG_LIST", "$accept", "Program", "Defs", "Def", "FuncDef",
  "VarType", "Type", "StructMembers", "StructMember", "MemberList",
  "_MemberList", "ParmList", "_ParmList", "Parm", "Block", "VarDef",
  "VarList", "_VarList", "VarInit", "Stms", "Stm", "IfStm", "ForStm",
  "WhileStm", "BreakStm", "ContinueStm", "ReturnStm", "TypeDef", "Exp",
  "ArraySubscript", "Constant", "Exps", "_Exps", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336
};
# endif

#define YYPACT_NINF (-167)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-132)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -167,     5,    42,  -167,     1,  1228,  1118,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,   -57,   -39,  -167,
    -167,  -167,   -56,   -39,    -9,    15,    21,    22,  -167,    16,
      72,    18,  1228,   309,  -167,   -48,    -8,  -167,  -167,   -47,
    -167,  -167,   -46,    26,    37,    39,  1228,   309,   309,   309,
     309,   309,   309,   309,   309,    32,  -167,  -167,  -167,    81,
    -167,  -167,  -167,   980,  -167,  -167,    71,   100,  -167,    95,
     106,   103,   110,  -167,     7,  1228,   108,    -7,    -7,    -7,
      -7,    -7,    -7,    -7,    -7,   233,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,  -167,   309,
     309,  -167,   309,   309,   309,   309,   309,   309,   309,   309,
    -167,  -167,    41,  -167,  -167,  -167,   118,   309,    79,    25,
     112,   686,   381,   113,   125,   728,   770,   980,   186,   980,
     186,  1226,  1239,  1239,  1239,  1239,  1226,   980,  1090,   980,
    1192,  1056,   980,  1124,   980,  1158,   980,    58,   980,    58,
     980,    -7,   980,    -7,   980,    -7,   126,   142,    -7,  -167,
    -167,  -167,  -167,   309,   309,  -167,  -167,  -167,   119,   120,
     121,   129,   130,   215,    28,   -48,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,   472,   429,  1022,   309,
     291,   309,  -167,  -167,  -167,   515,  -167,   812,   309,   558,
     854,  -167,   124,   601,   309,   124,    82,   309,   644,  -167,
     124,   896,   309,  -167,   124,   938,  -167,   124,  -167
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,     0,     0,     0,    17,    12,    13,
      14,    15,    18,    23,    16,     3,     5,    44,    10,     6,
       7,    25,     0,    11,    47,     0,     0,    43,    20,     0,
       0,     0,    35,     0,    41,     0,     0,    27,    19,    30,
      24,    71,    39,     0,     0,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   121,   122,   124,    73,
     125,   123,   126,    48,    72,    74,    47,    42,    22,     0,
      29,     0,     0,    38,     0,     0,     0,    88,    87,    89,
      82,    79,    84,    80,    86,     0,   129,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    83,     0,
       0,    85,     0,     0,     0,     0,     0,     0,     0,     0,
      21,    26,     0,     8,    50,     9,    33,     0,    73,   126,
       0,     0,   128,     0,     0,     0,     0,   115,    95,   116,
      96,   101,    98,    97,   100,    99,   102,   109,   106,   117,
     103,   107,   119,   105,   118,   104,   113,    93,   114,    94,
     111,    91,   110,    90,   112,    92,    28,     0,    81,    75,
      77,    76,    78,     0,     0,   120,    61,    40,     0,     0,
       0,     0,     0,     0,    73,    44,    58,    59,    49,    52,
      53,    54,    55,    56,    57,    60,     0,   127,   108,     0,
       0,     0,    67,    68,    70,     0,    51,     0,     0,     0,
       0,    69,     0,     0,     0,     0,    63,     0,     0,    66,
       0,     0,     0,    62,     0,     0,    65,     0,    64
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -167,  -167,  -167,  -167,  -167,    -2,   145,  -167,  -167,  -167,
    -167,  -167,  -167,    73,  -126,  -166,  -167,  -167,   127,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,   -13,   -40,  -167,
    -167,  -167,  -167
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    15,    16,    42,    18,    30,    40,    71,
      72,    43,    44,    45,   125,    19,    25,    26,    27,   167,
     188,   189,   190,   191,   192,   193,   194,    20,    63,    64,
      65,   133,   134
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      17,   187,    32,    22,    68,     3,    88,    77,    78,    79,
      80,    81,    82,    83,    84,   123,    21,    28,    29,    33,
      24,    31,   124,    34,    35,   -46,    41,    36,    39,    66,
      70,    73,   108,   -16,   208,   111,   -23,   -16,    74,    86,
      75,   186,   -37,    85,    76,   131,   132,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,    69,   156,
     157,    88,   158,   159,   160,   161,   162,   163,   164,   165,
      37,   -16,   -16,   130,   -23,   -23,   216,   168,    38,   219,
      86,   169,    86,     4,   223,     5,     6,   108,   226,    33,
     111,   228,   -16,   -45,   115,   -23,   117,   120,   119,   -32,
       7,   121,     8,   122,     9,    10,    11,    12,   166,    13,
     127,   -36,    14,     4,   170,   172,     6,   196,   173,   -31,
     199,   200,   201,   197,   198,   -23,   -23,   202,   203,   124,
       7,   220,     8,   205,     9,    10,    11,    12,   126,    13,
     176,    23,    14,    46,   195,     0,     0,   124,   177,   207,
     209,   210,    67,     0,     0,   185,     0,     0,   213,    47,
       0,     0,     0,    48,   218,     0,     0,   221,     0,     0,
      49,    50,   225,    51,    52,     0,    53,     0,    54,     0,
       0,     0,     0,     4,     0,     5,     6,     0,   185,    88,
     178,     0,   179,   180,   181,   182,   183,    55,    56,    57,
       7,     0,     8,     0,     9,    10,    11,    12,    58,   184,
      60,    61,   129,   204,     0,   108,    46,   110,   111,     0,
     113,     0,   115,     0,   117,     0,   119,     0,     0,     0,
       0,     0,    47,     0,    46,     0,    48,     0,     0,     0,
       0,     0,     0,    49,    50,     0,    51,    52,     0,    53,
      47,    54,     0,     0,    48,     0,     0,     0,     0,     0,
       0,    49,    50,     0,    51,    52,     0,    53,     0,    54,
      55,    56,    57,     0,     4,     0,     0,     6,     0,     0,
       0,    58,    59,    60,    61,    62,     0,     0,    55,    56,
      57,     7,    46,     8,     0,     9,    10,    11,    12,    58,
     128,    60,    61,   129,     0,     0,     0,     0,    47,     0,
      46,     0,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,    51,    52,     0,    53,    47,    54,     0,     0,
      48,     0,     4,     0,     0,     6,     0,    49,    50,     0,
      51,    52,     0,    53,     0,    54,    55,    56,    57,     7,
       0,     8,     0,     9,    10,    11,    12,    58,   184,    60,
      61,   129,     0,     0,    55,    56,    57,     0,     0,     0,
       0,     0,     0,     0,  -131,    58,    59,    60,    61,    62,
      87,     0,     0,     0,    88,     0,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    99,
     100,   101,   102,   103,   104,   105,     0,   106,   107,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,  -130,     0,     0,     0,     0,     0,    87,     0,
       0,     0,    88,     0,     0,     0,    89,    90,    91,    92,
      93,    94,    95,    96,    97,    98,     0,    99,   100,   101,
     102,   103,   104,   105,     0,   106,   107,     0,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     206,    87,     0,     0,     0,    88,     0,     0,     0,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,     0,
      99,   100,   101,   102,   103,   104,   105,     0,   106,   107,
       0,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   211,    87,     0,     0,     0,    88,     0,
       0,     0,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,     0,    99,   100,   101,   102,   103,   104,   105,
       0,   106,   107,     0,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   214,    87,     0,     0,
       0,    88,     0,     0,     0,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    99,   100,   101,   102,
     103,   104,   105,     0,   106,   107,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   217,
      87,     0,     0,     0,    88,     0,     0,     0,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    98,     0,    99,
     100,   101,   102,   103,   104,   105,     0,   106,   107,     0,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   222,    87,     0,     0,     0,    88,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,    99,   100,   101,   102,   103,   104,   105,     0,
     106,   107,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,    87,     0,     0,   171,    88,
       0,     0,     0,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,    99,   100,   101,   102,   103,   104,
     105,     0,   106,   107,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    87,   174,     0,
       0,    88,     0,     0,     0,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    99,   100,   101,   102,
     103,   104,   105,     0,   106,   107,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    87,
       0,     0,     0,    88,   175,     0,     0,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    99,   100,
     101,   102,   103,   104,   105,     0,   106,   107,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,    87,     0,     0,   212,    88,     0,     0,     0,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,     0,
      99,   100,   101,   102,   103,   104,   105,     0,   106,   107,
       0,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,    87,     0,     0,   215,    88,     0,     0,
       0,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,     0,    99,   100,   101,   102,   103,   104,   105,     0,
     106,   107,     0,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,    87,     0,     0,   224,    88,
       0,     0,     0,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,     0,    99,   100,   101,   102,   103,   104,
     105,     0,   106,   107,     0,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,    87,     0,     0,
     227,    88,     0,     0,     0,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,     0,    99,   100,   101,   102,
     103,   104,   105,     0,   106,   107,     0,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    87,
       0,     0,     0,    88,     0,     0,     0,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,     0,    99,   100,
     101,   102,   103,   104,   105,     0,   106,   107,     0,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,    87,     0,     0,     0,    88,     0,     0,     0,     0,
      90,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,   100,     0,   102,   103,     0,   105,     0,     0,   107,
       0,   108,     0,   110,   111,     0,   113,     0,   115,    88,
     117,     0,   119,     0,    90,     0,    92,    93,    94,    95,
      96,    97,    98,     0,     0,   100,     0,   102,     0,     0,
     105,     0,     0,   107,     0,   108,     0,   110,   111,     0,
     113,     0,   115,    88,   117,     0,   119,     0,    90,     0,
      92,    93,    94,    95,    96,    97,    98,     0,     0,     0,
       0,   102,     0,     0,   105,     0,     0,   107,     0,   108,
       0,   110,   111,     0,   113,     0,   115,    88,   117,     0,
     119,     0,    90,     0,    92,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,   102,     0,     0,     0,     0,
       0,   107,     0,   108,     0,   110,   111,     0,   113,     4,
     115,    88,   117,     0,   119,     0,    90,     0,    92,    93,
      94,    95,    96,    97,    98,     0,     7,     0,     8,   102,
       9,    10,    11,    12,     0,    13,     0,   108,    14,   110,
     111,     0,   113,     0,   115,    88,   117,     0,   119,     0,
      90,     0,    92,    93,    94,    95,    96,    97,    98,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,     0,   110,   111,     0,   113,     0,   115,    88,
     117,     0,   119,     0,    90,     0,    92,     0,    94,    95,
      96,    97,    88,     0,     0,     0,     0,    90,     0,    92,
       0,     0,     0,     0,     0,   108,     0,   110,   111,     0,
     113,     0,   115,     0,   117,     0,   119,     0,   108,     4,
     110,   111,     6,   113,     0,   115,     0,   117,     0,   119,
       0,     0,     0,     0,     0,     0,     7,     0,     8,     0,
       9,    10,    11,    12,     0,    13,     0,     0,    14
};

static const yytype_int16 yycheck[] =
{
       2,   167,    11,     5,    12,     0,    13,    47,    48,    49,
      50,    51,    52,    53,    54,     8,    15,    56,    57,    28,
      77,    77,    15,     8,     3,     3,     8,    11,    30,    77,
      77,    77,    39,     8,   200,    42,     8,    12,    12,    11,
       3,   167,     3,    11,    46,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,    76,   109,
     110,    13,   112,   113,   114,   115,   116,   117,   118,   119,
       8,    56,    57,    85,    56,    57,   212,   127,    16,   215,
      11,    12,    11,    51,   220,    53,    54,    39,   224,    28,
      42,   227,    77,     3,    46,    77,    48,    12,    50,     3,
      68,     8,    70,     3,    72,    73,    74,    75,    77,    77,
      12,     3,    80,    51,    12,    12,    54,   167,     3,     3,
      11,    11,    11,   173,   174,    56,    57,     8,     8,    15,
      68,    59,    70,   183,    72,    73,    74,    75,    75,    77,
       8,     6,    80,    11,   167,    -1,    -1,    15,    16,   199,
     200,   201,    35,    -1,    -1,   167,    -1,    -1,   208,    27,
      -1,    -1,    -1,    31,   214,    -1,    -1,   217,    -1,    -1,
      38,    39,   222,    41,    42,    -1,    44,    -1,    46,    -1,
      -1,    -1,    -1,    51,    -1,    53,    54,    -1,   200,    13,
      58,    -1,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    -1,    70,    -1,    72,    73,    74,    75,    76,    77,
      78,    79,    80,     8,    -1,    39,    11,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    11,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    -1,    41,    42,    -1,    44,
      27,    46,    -1,    -1,    31,    -1,    -1,    -1,    -1,    -1,
      -1,    38,    39,    -1,    41,    42,    -1,    44,    -1,    46,
      65,    66,    67,    -1,    51,    -1,    -1,    54,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    -1,    -1,    65,    66,
      67,    68,    11,    70,    -1,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    -1,    -1,    -1,    -1,    27,    -1,
      11,    -1,    31,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    -1,    41,    42,    -1,    44,    27,    46,    -1,    -1,
      31,    -1,    51,    -1,    -1,    54,    -1,    38,    39,    -1,
      41,    42,    -1,    44,    -1,    46,    65,    66,    67,    68,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    76,    77,    78,    79,    80,
       9,    -1,    -1,    -1,    13,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,     3,    -1,    -1,    -1,    -1,    -1,     9,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    -1,    28,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       8,     9,    -1,    -1,    -1,    13,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     8,     9,    -1,    -1,    -1,    13,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,     8,     9,    -1,    -1,
      -1,    13,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     8,
       9,    -1,    -1,    -1,    13,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    -1,    28,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,     8,     9,    -1,    -1,    -1,    13,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     9,    -1,    -1,    12,    13,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     9,    10,    -1,
      -1,    13,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     9,
      -1,    -1,    -1,    13,    14,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     9,    -1,    -1,    12,    13,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    -1,
      28,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,     9,    -1,    -1,    12,    13,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,     9,    -1,    -1,    12,    13,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,     9,    -1,    -1,
      12,    13,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    -1,    28,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,     9,
      -1,    -1,    -1,    13,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    -1,    28,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,     9,    -1,    -1,    -1,    13,    -1,    -1,    -1,    -1,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    29,    -1,    31,    32,    -1,    34,    -1,    -1,    37,
      -1,    39,    -1,    41,    42,    -1,    44,    -1,    46,    13,
      48,    -1,    50,    -1,    18,    -1,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    -1,    31,    -1,    -1,
      34,    -1,    -1,    37,    -1,    39,    -1,    41,    42,    -1,
      44,    -1,    46,    13,    48,    -1,    50,    -1,    18,    -1,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    -1,    -1,    37,    -1,    39,
      -1,    41,    42,    -1,    44,    -1,    46,    13,    48,    -1,
      50,    -1,    18,    -1,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    39,    -1,    41,    42,    -1,    44,    51,
      46,    13,    48,    -1,    50,    -1,    18,    -1,    20,    21,
      22,    23,    24,    25,    26,    -1,    68,    -1,    70,    31,
      72,    73,    74,    75,    -1,    77,    -1,    39,    80,    41,
      42,    -1,    44,    -1,    46,    13,    48,    -1,    50,    -1,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    -1,    41,    42,    -1,    44,    -1,    46,    13,
      48,    -1,    50,    -1,    18,    -1,    20,    -1,    22,    23,
      24,    25,    13,    -1,    -1,    -1,    -1,    18,    -1,    20,
      -1,    -1,    -1,    -1,    -1,    39,    -1,    41,    42,    -1,
      44,    -1,    46,    -1,    48,    -1,    50,    -1,    39,    51,
      41,    42,    54,    44,    -1,    46,    -1,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    70,    -1,
      72,    73,    74,    75,    -1,    77,    -1,    -1,    80
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    83,    84,     0,    51,    53,    54,    68,    70,    72,
      73,    74,    75,    77,    80,    85,    86,    87,    88,    97,
     109,    15,    87,    88,    77,    98,    99,   100,    56,    57,
      89,    77,    11,    28,     8,     3,    11,     8,    16,    87,
      90,     8,    87,    93,    94,    95,    11,    27,    31,    38,
      39,    41,    42,    44,    46,    65,    66,    67,    76,    77,
      78,    79,    80,   110,   111,   112,    77,   100,    12,    76,
      77,    91,    92,    77,    12,     3,    87,   110,   110,   110,
     110,   110,   110,   110,   110,    11,    11,     9,    13,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    28,
      29,    30,    31,    32,    33,    34,    36,    37,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      12,     8,     3,     8,    15,    96,    95,    12,    77,    80,
      87,   110,   110,   113,   114,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,    77,   101,   110,    12,
      12,    12,    12,     3,    10,    14,     8,    16,    58,    60,
      61,    62,    63,    64,    77,    87,    96,    97,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   110,   110,    11,
      11,    11,     8,     8,     8,   110,     8,   110,    97,   110,
     110,     8,    12,   110,     8,    12,    96,     8,   110,    96,
      59,   110,     8,    96,    12,   110,    96,    12,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    82,    83,    84,    84,    85,    85,    85,    86,    86,
      87,    87,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    89,    89,    90,    90,    91,    91,
      91,    92,    92,    93,    93,    93,    94,    94,    95,    95,
      96,    97,    98,    98,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   103,   103,   104,   104,   105,   106,   107,   108,
     108,   109,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   112,   112,   112,   112,   112,   112,   113,   113,   113,
     114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     6,     6,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     4,
       2,     5,     4,     1,     2,     0,     3,     1,     3,     1,
       0,     3,     1,     3,     1,     0,     3,     1,     2,     1,
       3,     3,     3,     1,     0,     3,     1,     1,     3,     2,
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     7,     5,     9,     8,     5,     2,     2,     3,
       2,     4,     1,     1,     1,     4,     4,     4,     4,     2,
       2,     4,     2,     2,     2,     2,     2,     2,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     5,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
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
  case 2:
#line 153 "parser.y"
                                    { (yyval.program) = new AST::Program((yyvsp[0].defs)); Root = (yyval.program); }
#line 1841 "Parser.cpp"
    break;

  case 3:
#line 156 "parser.y"
                                                                                                                        {  (yyval.defs) = (yyvsp[-1].defs); (yyval.defs)->push_back((yyvsp[0].def));   }
#line 1847 "Parser.cpp"
    break;

  case 4:
#line 157 "parser.y"
                                                                                                                                        {  (yyval.defs) = new AST::Defs();   }
#line 1853 "Parser.cpp"
    break;

  case 5:
#line 160 "parser.y"
                                                                                                                {  (yyval.def) = (yyvsp[0].funcDef);   }
#line 1859 "Parser.cpp"
    break;

  case 6:
#line 161 "parser.y"
                                                                                                                                {  (yyval.def) = (yyvsp[0].varDef);   }
#line 1865 "Parser.cpp"
    break;

  case 7:
#line 162 "parser.y"
                                                                                                                                {  (yyval.def) = (yyvsp[0].typeDef);   }
#line 1871 "Parser.cpp"
    break;

  case 8:
#line 165 "parser.y"
                                                                                {  (yyval.funcDef) = new AST::FuncDef((yyvsp[-5].varType),*(yyvsp[-4].sVal),(yyvsp[-2].parms));   }
#line 1877 "Parser.cpp"
    break;

  case 9:
#line 166 "parser.y"
                                                                                        {  (yyval.funcDef) = new AST::FuncDef((yyvsp[-5].varType),*(yyvsp[-4].sVal),(yyvsp[-2].parms),(yyvsp[0].block));   }
#line 1883 "Parser.cpp"
    break;

  case 10:
#line 169 "parser.y"
                                                                                                                {  (yyval.varType) = (yyvsp[0].varType);   }
#line 1889 "Parser.cpp"
    break;

  case 11:
#line 170 "parser.y"
                                                                                                                {  (yyval.varType) = (yyvsp[0].varType); (yyval.varType)->SetConst();   }
#line 1895 "Parser.cpp"
    break;

  case 12:
#line 173 "parser.y"
                                                                                                        {  (yyval.varType) = new AST::IntType();   }
#line 1901 "Parser.cpp"
    break;

  case 13:
#line 174 "parser.y"
                                                            {  (yyval.varType) = new AST::CharType();   }
#line 1907 "Parser.cpp"
    break;

  case 14:
#line 175 "parser.y"
                                                             {  (yyval.varType) = new AST::FloatType();   }
#line 1913 "Parser.cpp"
    break;

  case 15:
#line 176 "parser.y"
                                                              {  (yyval.varType) = new AST::DoubleType();   }
#line 1919 "Parser.cpp"
    break;

  case 16:
#line 177 "parser.y"
                                                              {  (yyval.varType) = new AST::StringType();   }
#line 1925 "Parser.cpp"
    break;

  case 17:
#line 178 "parser.y"
                                                            {  (yyval.varType) = new AST::BoolType();   }
#line 1931 "Parser.cpp"
    break;

  case 18:
#line 179 "parser.y"
                                                            {  (yyval.varType) = new AST::VoidType();   }
#line 1937 "Parser.cpp"
    break;

  case 19:
#line 180 "parser.y"
                                                                                                        {  (yyval.varType) = new AST::StructType((yyvsp[-1].structMembers));   }
#line 1943 "Parser.cpp"
    break;

  case 20:
#line 181 "parser.y"
                                                                                                                        {  (yyval.varType) = new AST::PointerType((yyvsp[-1].varType));   }
#line 1949 "Parser.cpp"
    break;

  case 21:
#line 182 "parser.y"
                                                                                                {  (yyval.varType) = new AST::ArrayType((yyvsp[-4].varType),(yyvsp[-1].iVal));   }
#line 1955 "Parser.cpp"
    break;

  case 22:
#line 183 "parser.y"
                                                                                                        {  (yyval.varType) = new AST::ArrayType((yyvsp[-3].varType));   }
#line 1961 "Parser.cpp"
    break;

  case 23:
#line 184 "parser.y"
                                                                                                                        {  (yyval.varType) = new AST::DefinedType(*(yyvsp[0].sVal));   }
#line 1967 "Parser.cpp"
    break;

  case 24:
#line 188 "parser.y"
                                                            {  (yyval.structMembers) = (yyvsp[-1].structMembers); if ((yyvsp[0].structMember) != NULL) (yyval.structMembers)->push_back((yyvsp[0].structMember));   }
#line 1973 "Parser.cpp"
    break;

  case 25:
#line 189 "parser.y"
                                                            {  (yyval.structMembers) = new AST::StructMembers();   }
#line 1979 "Parser.cpp"
    break;

  case 26:
#line 193 "parser.y"
                                                            {  (yyval.structMember) = new AST::StructMember((yyvsp[-2].varType),(yyvsp[-1].memberList));   }
#line 1985 "Parser.cpp"
    break;

  case 27:
#line 194 "parser.y"
                                                            {  (yyval.structMember) = NULL;  }
#line 1991 "Parser.cpp"
    break;

  case 28:
#line 198 "parser.y"
                                                                                                        {  (yyval.memberList) = (yyvsp[-2].memberList); (yyval.memberList)->push_back(*(yyvsp[0].sVal));   }
#line 1997 "Parser.cpp"
    break;

  case 29:
#line 199 "parser.y"
                                                                                                                        {  (yyval.memberList) = new AST::MemberList(); (yyval.memberList)->push_back(*(yyvsp[0].sVal));   }
#line 2003 "Parser.cpp"
    break;

  case 30:
#line 200 "parser.y"
                                                                                                                                        {  (yyval.memberList) = new AST::MemberList();   }
#line 2009 "Parser.cpp"
    break;

  case 31:
#line 204 "parser.y"
                                                                                                        {  (yyval.memberList) = (yyvsp[-2].memberList); (yyval.memberList)->push_back(*(yyvsp[0].sVal));   }
#line 2015 "Parser.cpp"
    break;

  case 32:
#line 205 "parser.y"
                                                                                                                        {  (yyval.memberList) = new AST::MemberList(); (yyval.memberList)->push_back(*(yyvsp[0].sVal));   }
#line 2021 "Parser.cpp"
    break;

  case 33:
#line 209 "parser.y"
                                                                {  (yyval.parms) = (yyvsp[-2].parms); (yyval.parms)->push_back((yyvsp[0].parm));  }
#line 2027 "Parser.cpp"
    break;

  case 34:
#line 210 "parser.y"
                                                                {  (yyval.parms) = new AST::Parms(); (yyval.parms)->push_back((yyvsp[0].parm)); }
#line 2033 "Parser.cpp"
    break;

  case 35:
#line 211 "parser.y"
                                                                {  (yyval.parms) = new AST::Parms(); }
#line 2039 "Parser.cpp"
    break;

  case 36:
#line 215 "parser.y"
                                                                {  (yyval.parms) = (yyvsp[-2].parms); (yyval.parms)->push_back((yyvsp[0].parm));  }
#line 2045 "Parser.cpp"
    break;

  case 37:
#line 216 "parser.y"
                                                                {  (yyval.parms) = new AST::Parms(); (yyval.parms)->push_back((yyvsp[0].parm)); }
#line 2051 "Parser.cpp"
    break;

  case 38:
#line 219 "parser.y"
                                                                {  (yyval.parm) = new AST::Parm((yyvsp[-1].varType),*(yyvsp[0].sVal));   }
#line 2057 "Parser.cpp"
    break;

  case 39:
#line 220 "parser.y"
                                                                {  (yyval.parm) = new AST::Parm((yyvsp[0].varType));   }
#line 2063 "Parser.cpp"
    break;

  case 40:
#line 223 "parser.y"
                                                                                                                {  (yyval.block) = new AST::Block((yyvsp[-1].stms));   }
#line 2069 "Parser.cpp"
    break;

  case 41:
#line 226 "parser.y"
                                                                {  (yyval.varDef) = new AST::VarDef((yyvsp[-2].varType),(yyvsp[-1].varList));   }
#line 2075 "Parser.cpp"
    break;

  case 42:
#line 229 "parser.y"
                                                                {  (yyval.varList) = (yyvsp[-2].varList); (yyval.varList)->push_back((yyvsp[0].varInit));   }
#line 2081 "Parser.cpp"
    break;

  case 43:
#line 230 "parser.y"
                                                                {  (yyval.varList) = new AST::VarList(); (yyval.varList)->push_back((yyvsp[0].varInit));   }
#line 2087 "Parser.cpp"
    break;

  case 44:
#line 231 "parser.y"
                                                                {  (yyval.varList) = new AST::VarList();   }
#line 2093 "Parser.cpp"
    break;

  case 45:
#line 234 "parser.y"
                                                                {  (yyval.varList) = (yyvsp[-2].varList); (yyval.varList)->push_back((yyvsp[0].varInit));  }
#line 2099 "Parser.cpp"
    break;

  case 46:
#line 235 "parser.y"
                                                                {  (yyval.varList) = new AST::VarList(); (yyval.varList)->push_back((yyvsp[0].varInit));  }
#line 2105 "Parser.cpp"
    break;

  case 47:
#line 238 "parser.y"
                                                                {  (yyval.varInit) = new AST::VarInit(*(yyvsp[0].sVal));  }
#line 2111 "Parser.cpp"
    break;

  case 48:
#line 239 "parser.y"
                                                                {  (yyval.varInit) = new AST::VarInit(*(yyvsp[-2].sVal),(yyvsp[0].exp));  }
#line 2117 "Parser.cpp"
    break;

  case 49:
#line 242 "parser.y"
                                                                                                        {  (yyval.stms) = (yyvsp[-1].stms); if ((yyvsp[0].stm) != NULL) (yyval.stms)->push_back((yyvsp[0].stm));   }
#line 2123 "Parser.cpp"
    break;

  case 50:
#line 243 "parser.y"
                                                                                                                                        {  (yyval.stms) = new AST::Stms();   }
#line 2129 "Parser.cpp"
    break;

  case 51:
#line 246 "parser.y"
                                                                                                                        {  (yyval.stm) = (yyvsp[-1].exp);   }
#line 2135 "Parser.cpp"
    break;

  case 52:
#line 247 "parser.y"
                                                                                                                        {  (yyval.stm) = (yyvsp[0].ifStm);   }
#line 2141 "Parser.cpp"
    break;

  case 53:
#line 248 "parser.y"
                                                                                                                                {  (yyval.stm) = (yyvsp[0].forStm);   }
#line 2147 "Parser.cpp"
    break;

  case 54:
#line 249 "parser.y"
                                                                                                                        {  (yyval.stm) = (yyvsp[0].whileStm);   }
#line 2153 "Parser.cpp"
    break;

  case 55:
#line 250 "parser.y"
                                                                                                                                {  (yyval.stm) = (yyvsp[0].breakStm);   }
#line 2159 "Parser.cpp"
    break;

  case 56:
#line 251 "parser.y"
                                                                                                                        {  (yyval.stm) = (yyvsp[0].continueStm);   }
#line 2165 "Parser.cpp"
    break;

  case 57:
#line 252 "parser.y"
                                                                                                                        {  (yyval.stm) = (yyvsp[0].returnStm);   }
#line 2171 "Parser.cpp"
    break;

  case 58:
#line 253 "parser.y"
                                                                                                                                {  (yyval.stm) = (yyvsp[0].block);   }
#line 2177 "Parser.cpp"
    break;

  case 59:
#line 254 "parser.y"
                                                                                                                                {  (yyval.stm) = (yyvsp[0].varDef);   }
#line 2183 "Parser.cpp"
    break;

  case 60:
#line 255 "parser.y"
                                                                                                                                {  (yyval.stm) = (yyvsp[0].typeDef);   }
#line 2189 "Parser.cpp"
    break;

  case 61:
#line 256 "parser.y"
                                                                                                                                {  (yyval.stm) = NULL;   }
#line 2195 "Parser.cpp"
    break;

  case 62:
#line 259 "parser.y"
                                                                                        {  (yyval.ifStm) = new AST::IfStm((yyvsp[-4].exp),(yyvsp[-2].block),(yyvsp[0].block));   }
#line 2201 "Parser.cpp"
    break;

  case 63:
#line 260 "parser.y"
                                                                                                {  (yyval.ifStm) = new AST::IfStm((yyvsp[-2].exp),(yyvsp[0].block));   }
#line 2207 "Parser.cpp"
    break;

  case 64:
#line 263 "parser.y"
                                                                                {  (yyval.forStm) = new AST::ForStm((yyvsp[-6].exp),(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].block));   }
#line 2213 "Parser.cpp"
    break;

  case 65:
#line 264 "parser.y"
                                                                                {  (yyval.forStm) = new AST::ForStm((yyvsp[-5].varDef),(yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].block));   }
#line 2219 "Parser.cpp"
    break;

  case 66:
#line 267 "parser.y"
                                                                    {  (yyval.whileStm) = new AST::WhileStm((yyvsp[-2].exp),(yyvsp[0].block));  }
#line 2225 "Parser.cpp"
    break;

  case 67:
#line 270 "parser.y"
                                                                    {  (yyval.breakStm) = new AST::BreakStm();  }
#line 2231 "Parser.cpp"
    break;

  case 68:
#line 273 "parser.y"
                                                                    {  (yyval.continueStm) = new AST::ContinueStm();  }
#line 2237 "Parser.cpp"
    break;

  case 69:
#line 276 "parser.y"
                                                                    {  (yyval.returnStm) = new AST::ReturnStm((yyvsp[-1].exp));  }
#line 2243 "Parser.cpp"
    break;

  case 70:
#line 277 "parser.y"
                                                                    {  (yyval.returnStm) = new AST::ReturnStm();  }
#line 2249 "Parser.cpp"
    break;

  case 71:
#line 280 "parser.y"
                                                                    {  (yyval.typeDef) = new AST::TypeDef((yyvsp[-2].varType),*(yyvsp[-1].sVal));  }
#line 2255 "Parser.cpp"
    break;

  case 72:
#line 283 "parser.y"
                                                                    {  (yyval.exp) = (yyvsp[0].arraySubscript);  }
#line 2261 "Parser.cpp"
    break;

  case 73:
#line 284 "parser.y"
                                                                    {  (yyval.exp) = new AST::Variable(*(yyvsp[0].sVal));  }
#line 2267 "Parser.cpp"
    break;

  case 74:
#line 285 "parser.y"
                                                                    {  (yyval.exp) = (yyvsp[0].constant);  }
#line 2273 "Parser.cpp"
    break;

  case 75:
#line 286 "parser.y"
                                                                                        {  (yyval.exp) = new AST::SizeOf(*(yyvsp[-1].sVal));   }
#line 2279 "Parser.cpp"
    break;

  case 76:
#line 287 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::SizeOf((yyvsp[-1].exp));   }
#line 2285 "Parser.cpp"
    break;

  case 77:
#line 288 "parser.y"
                                                                                                        {  (yyval.exp) = new AST::SizeOf((yyvsp[-1].varType));   }
#line 2291 "Parser.cpp"
    break;

  case 78:
#line 289 "parser.y"
                                                                                        {  (yyval.exp) = new AST::FuncCall(*(yyvsp[-3].sVal),(yyvsp[-1].exps));   }
#line 2297 "Parser.cpp"
    break;

  case 79:
#line 291 "parser.y"
                                                                                                        {  (yyval.exp) = new AST::UnaryPlus((yyvsp[0].exp));   }
#line 2303 "Parser.cpp"
    break;

  case 80:
#line 292 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::UnaryMinus((yyvsp[0].exp));   }
#line 2309 "Parser.cpp"
    break;

  case 81:
#line 293 "parser.y"
                                                                                                {  (yyval.exp) = new AST::TypeCast((yyvsp[-2].varType),(yyvsp[0].exp));   }
#line 2315 "Parser.cpp"
    break;

  case 82:
#line 294 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::PrefixInc((yyvsp[0].exp));   }
#line 2321 "Parser.cpp"
    break;

  case 83:
#line 295 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::PostfixInc((yyvsp[-1].exp));   }
#line 2327 "Parser.cpp"
    break;

  case 84:
#line 296 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::PrefixDec((yyvsp[0].exp));   }
#line 2333 "Parser.cpp"
    break;

  case 85:
#line 297 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::PostfixDec((yyvsp[-1].exp));   }
#line 2339 "Parser.cpp"
    break;

  case 86:
#line 298 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::Indirection((yyvsp[0].exp));   }
#line 2345 "Parser.cpp"
    break;

  case 87:
#line 299 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::AddressOf((yyvsp[0].exp));   }
#line 2351 "Parser.cpp"
    break;

  case 88:
#line 300 "parser.y"
                                                                                                                                {  (yyval.exp) = new AST::LogicNot((yyvsp[0].exp));   }
#line 2357 "Parser.cpp"
    break;

  case 89:
#line 301 "parser.y"
                                                                                                                                {  (yyval.exp) = new AST::BitwiseNot((yyvsp[0].exp));   }
#line 2363 "Parser.cpp"
    break;

  case 90:
#line 303 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::Division((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2369 "Parser.cpp"
    break;

  case 91:
#line 304 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::Multiplication((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2375 "Parser.cpp"
    break;

  case 92:
#line 305 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::Modulo((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2381 "Parser.cpp"
    break;

  case 93:
#line 306 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::Addition((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2387 "Parser.cpp"
    break;

  case 94:
#line 307 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::Subtraction((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2393 "Parser.cpp"
    break;

  case 95:
#line 308 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::LeftShift((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2399 "Parser.cpp"
    break;

  case 96:
#line 309 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::RightShift((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2405 "Parser.cpp"
    break;

  case 97:
#line 310 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicGT((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2411 "Parser.cpp"
    break;

  case 98:
#line 311 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicGE((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2417 "Parser.cpp"
    break;

  case 99:
#line 312 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicLT((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2423 "Parser.cpp"
    break;

  case 100:
#line 313 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicLE((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2429 "Parser.cpp"
    break;

  case 101:
#line 314 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicEQ((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2435 "Parser.cpp"
    break;

  case 102:
#line 315 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicNEQ((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2441 "Parser.cpp"
    break;

  case 103:
#line 316 "parser.y"
                                                                                                        {  (yyval.exp) = new AST::BitwiseAND((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2447 "Parser.cpp"
    break;

  case 104:
#line 317 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::BitwiseXOR((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2453 "Parser.cpp"
    break;

  case 105:
#line 318 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::BitwiseOR((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2459 "Parser.cpp"
    break;

  case 106:
#line 319 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicAND((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2465 "Parser.cpp"
    break;

  case 107:
#line 320 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::LogicOR((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2471 "Parser.cpp"
    break;

  case 108:
#line 321 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::TernaryCondition((yyvsp[-4].exp),(yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2477 "Parser.cpp"
    break;

  case 109:
#line 322 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::DirectAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2483 "Parser.cpp"
    break;

  case 110:
#line 323 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::DivAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2489 "Parser.cpp"
    break;

  case 111:
#line 324 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::MulAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2495 "Parser.cpp"
    break;

  case 112:
#line 325 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::ModAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2501 "Parser.cpp"
    break;

  case 113:
#line 326 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::AddAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2507 "Parser.cpp"
    break;

  case 114:
#line 327 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::SubAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2513 "Parser.cpp"
    break;

  case 115:
#line 328 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::SHLAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2519 "Parser.cpp"
    break;

  case 116:
#line 329 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::SHRAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2525 "Parser.cpp"
    break;

  case 117:
#line 330 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::BitwiseANDAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2531 "Parser.cpp"
    break;

  case 118:
#line 331 "parser.y"
                                                                                                                        {  (yyval.exp) = new AST::BitwiseXORAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2537 "Parser.cpp"
    break;

  case 119:
#line 332 "parser.y"
                                                                                                                {  (yyval.exp) = new AST::BitwiseORAssign((yyvsp[-2].exp),(yyvsp[0].exp));   }
#line 2543 "Parser.cpp"
    break;

  case 120:
#line 335 "parser.y"
                                                                       {  (yyval.arraySubscript) = new AST::ArraySubscript((yyvsp[-3].exp),(yyvsp[-1].exp));  }
#line 2549 "Parser.cpp"
    break;

  case 121:
#line 338 "parser.y"
                                                                                                                        {  (yyval.constant) =  new AST::Constant(true);   }
#line 2555 "Parser.cpp"
    break;

  case 122:
#line 339 "parser.y"
                                                                                                                                {  (yyval.constant) =  new AST::Constant(false);   }
#line 2561 "Parser.cpp"
    break;

  case 123:
#line 340 "parser.y"
                                                                                                                                {  (yyval.constant) =  new AST::Constant((yyvsp[0].cVal));   }
#line 2567 "Parser.cpp"
    break;

  case 124:
#line 341 "parser.y"
                                                                                                                                {  (yyval.constant) =  new AST::Constant((yyvsp[0].iVal));   }
#line 2573 "Parser.cpp"
    break;

  case 125:
#line 342 "parser.y"
                                                                                                                                {  (yyval.constant) =  new AST::Constant((yyvsp[0].dVal));   }
#line 2579 "Parser.cpp"
    break;

  case 126:
#line 343 "parser.y"
                                                                                                                                {  (yyval.constant) =  new AST::Constant(*(yyvsp[0].strVal));   }
#line 2585 "Parser.cpp"
    break;

  case 127:
#line 346 "parser.y"
                                                                    {  (yyval.exps) = (yyvsp[-2].exps); (yyval.exps)->push_back((yyvsp[0].exp));  }
#line 2591 "Parser.cpp"
    break;

  case 128:
#line 347 "parser.y"
                                                                    {  (yyval.exps) = new AST::Exps(); (yyval.exps)->push_back((yyvsp[0].exp));  }
#line 2597 "Parser.cpp"
    break;

  case 129:
#line 348 "parser.y"
                                                                    {  (yyval.exps) = new AST::Exps();  }
#line 2603 "Parser.cpp"
    break;

  case 130:
#line 351 "parser.y"
                                                                    {  (yyval.exps) = (yyvsp[-2].exps); (yyval.exps)->push_back((yyvsp[0].exp));  }
#line 2609 "Parser.cpp"
    break;

  case 131:
#line 352 "parser.y"
                                                                    {  (yyval.exps) = new AST::Exps(); (yyval.exps)->push_back((yyvsp[0].exp));  }
#line 2615 "Parser.cpp"
    break;


#line 2619 "Parser.cpp"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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

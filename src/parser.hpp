/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_HPP_INCLUDED
# define YY_YY_PARSER_HPP_INCLUDED
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
    STRING = 331,
    INTEGER = 332,
    IDENTIFIER = 333,
    REAL = 334,
    CHARACTER = 335,
    STRINGCONST = 336,
    FUNC_CALL_ARG_LIST = 337
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

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

    AST::Exp *exp;
    AST::Exps *exps;
    AST::ArraySubscript *arraySubscript;
    AST::Constant* constant;
	

#line 194 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

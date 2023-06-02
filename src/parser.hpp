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
    LPAREN = 264,
    RPAREN = 265,
    LBRACKET = 266,
    RBRACKET = 267,
    LBRACE = 268,
    RBRACE = 269,
    SHL = 270,
    SHR = 271,
    EQ = 272,
    GE = 273,
    GT = 274,
    LE = 275,
    LT = 276,
    NEQ = 277,
    NOT = 278,
    ASSIGN = 279,
    AND = 280,
    BAND = 281,
    OR = 282,
    BOR = 283,
    ARW = 284,
    BXOR = 285,
    BNOT = 286,
    ADD = 287,
    SUB = 288,
    MUL = 289,
    DIV = 290,
    MOD = 291,
    STRUCT = 292,
    TYPEDEF = 293,
    CONST = 294,
    PTR = 295,
    ARRAY = 296,
    IF = 297,
    ELSE = 298,
    FOR = 299,
    WHILE = 300,
    BREAK = 301,
    CONTINUE = 302,
    RETURN = 303,
    TRUE = 304,
    FALSE = 305,
    BOOL = 306,
    SHORT = 307,
    INT = 308,
    LONG = 309,
    CHAR = 310,
    FLOAT = 311,
    DOUBLE = 312,
    VOID = 313,
    STRING = 314,
    INTEGER = 315,
    IDENTIFIER = 316,
    REAL = 317,
    CHARACTER = 318,
    STRINGCONST = 319,
    FUNC_CALL_ARG_LIST = 320,
    BXO = 321
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
	

#line 178 "parser.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_HPP_INCLUDED  */

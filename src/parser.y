%{
#include "AST.hpp" 
#include <string>
#include <iostream>


void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);

AST::Program *Root;
%}

%output "Parser.cpp"

%union {
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
    AST::TypeDef *typeDef;
    AST::VarType *varType;

    AST::Stm *stm;
    AST::IfStm *ifStm;
    AST::ForStm *forStm;
    AST::WhileStm *whileStm;
    AST::BreakStm* breakStm;
	AST::ContinueStm* continueStm;
    AST::ReturnStm *returnStm;
    AST::Stms *stms;
    AST::Block *block;
    AST::Parm *parm;
    AST::ParmList *parmList;
    AST::VarInit *varInit;
    AST::VarList *varList;

    AST::Expr *expr;
    AST::Constant* constant;
	AST::ExprList* exprList;
}

%token  COMMA ELLIPSES DOT SQUOTE DQUOTE SEMI QUES COLON
		LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
		SHLEQ SHL SHREQ SHR
		EQ GE GT LE LT NEQ NOT ASSIGN
		AND BANDEQ BAND OR BOREQ BOR
		ARW BXOREQ BXOR BNOT
		DADD ADDEQ ADD DSUB SUBEQ SUB
		MULEQ MUL DIVEQ DIV MODEQ MOD
		STRUCT UNION TYPEDEF CONST ENUM PTR ARRAY
		IF ELSE FOR WHILE 
		BREAK CONTINUE RETURN SIZEOF TRUE FALSE
		BOOL SHORT INT LONG CHAR FLOAT DOUBLE VOID


%token<iVal> INTEGER
%token<sVal> IDENTIFIER 
%token<dVal> REAL
%token<cVal> CHARACTER
%token<strVal> STRING
%type<program>							Program	
%type<def>								Def	
%type<defs>							    Defs
%type<funcDef>							FuncDef	
%type<varDef>							VarDef	
%type<typeDef>							TypeDef	
%type<varType>							VarType _VarType
%type<builtInType>						BuiltInType
%type<fieldDecls>						FieldDecls
%type<fieldDecl>						FieldDecl
%type<memList>							MemList _MemList	
%type<stmt>								Stmt
%type<ifStmt>							IfStmt
%type<forStmt>							ForStmt
%type<whileStmt>						WhileStmt
%type<doStmt>							DoStmt
%type<switchStmt>						SwitchStmt
%type<caseList>							CaseList
%type<caseStmt>							CaseStmt
%type<breakStmt>						BreakStmt
%type<continueStmt>						ContinueStmt
%type<returnStmt>						ReturnStmt
%type<stmts>							Stmts
%type<block>							Block
%type<arg>								Arg
%type<argList>							ArgList _ArgList
%type<varInit>							VarInit	
%type<varList>							VarList _VarList
%type<expr>								Expr	
%type<constant>							Constant
%type<exprList>							ExprList _ExprList
%type<enm>								Enm
%type<enmList>							EnmList	_EnmList

%start Program
%%

Program:    Defs                    { $$ = new AST::Program($1); Root = $$; }
            ;

Defs:		Defs Def												{  $$ = $1; $$->push_back($2);   }
			|														{  $$ = new AST::Defs();   }
			;

Def:		FuncDef												{  $$ = $1;   }
			| VarDef												{  $$ = $1;   }
			| TypeDef												{  $$ = $1;   }
			;

FuncDef:	VarType IDENTIFIER LPAREN ParmList RPAREN SEMI 			{  $$ = new AST::FuncDef($1,*$2,$4);   }
			| VarType IDENTIFIER LPAREN ParmList RPAREN Block		{  $$ = new AST::FuncDef($1,*$2,$4,$6);   }
			;

VarType:	Type												{  $$ = $1;   }
			| CONST Type										{  $$ = $2; $$->SetConst();   }
			;

Type:	    INT												{  $$ = new AST::IntType();   }
            | CHAR                                          {  $$ = new AST::CharType();   }
            | FLOAT                                          {  $$ = new AST::FloatType();   }
            | DOUBLE                                          {  $$ = new AST::DoubleType();   }
            | STRING                                          {  $$ = new AST::StringType();   }
            | BOOL                                          {  $$ = new AST::BoolType();   }
            | VOID                                          {  $$ = new AST::VoidType();   }
			| STRUCT LBRACE StructMembers RBRACE						{  $$ = new AST::StructType($3);   }
			| Type PTR											{  $$ = new AST::PointerType($1);   }
			| Type ARRAY LPAREN INTEGER RPAREN					{  $$ = new AST::ArrayType($1,$4);   }
			| Type ARRAY LPAREN RPAREN							{  $$ = new AST::ArrayType($1);   }
			| IDENTIFIER											{  $$ = new AST::DefinedType(*$1);   }
			;

StructMembers:
            StructMembers StructMember                      {  $$ = $1; if ($2 != NULL) $$->push_back($2);   }
            |                                               {  $$ = new AST::StructMembers();   }
            ;

StructMember:
            VarType MemberList SEMI                         {  $$ = new AST::StructMember($1,$2);   }
            | SEMI                                          {  $$ = NULL;  }
            ;

MemberList:
            _MemberList COMMA IDENTIFIER								{  $$ = $1; $$->push_back(*$3);   }
			| IDENTIFIER											{  $$ = new AST::MemberList(); $$->push_back(*$1);   }	
			|														{  $$ = new AST::MemberList();   }
			;

_MemberList:	
            _MemberList COMMA IDENTIFIER								{  $$ = $1; $$->push_back(*$3);   }
			| IDENTIFIER											{  $$ = new AST::MemberList(); $$->push_back(*$1);   }
			;
        
ParmList:
            _ParaList COMMA Parm                                {  $$ = $1; $$->push_back(*$3);  }
            | Parm                                              {  $$ = new AST::Parms(); $$->push_back(*$1); }
            ;
        
Parm:       VarType IDENTIFIER                                  {  $$ = new AST::Parm($1,*$2);   }
            | VarType                                           {  $$ = new AST::5($1);   }
            ;

Block:		LBRACE Stms RBRACE										{  $$ = new AST::Block($2);   }
			;

VarDef:     VarType VarList SEMI                                {  $$ = new AST::VarDecl($1,$2);   }
            ;

VarList:    _VarList COMMA VarInit                              {  $$ = $1; $$->push_back($3);   }
            | VarInit                                           {  $$ = new AST::VarList(); $$->push_back($1);   }
            |                                                   {  $$ = new AST::VarList();   }
            ;

_VarList:   _VarList COMMA VarInit                              {  $$ = $1; $$->push_back($3);  }
            | VarInit                                           {  $$ = new AST::VarList(); $$->push_back($1);  }
            ;

VarInit:    IDENTIFIER                                          {  $$ = new AST::VarInit(*$1);  }
            | IDENTIFIER ASSIGN Exp                             {  $$ = new AST::VarInit(*$1,$3);  }
            ;

Stms:		Stms Stm     										{  $$ = $1; if ($2 != NULL) $$->push_back($2);   }	
			|														{  $$ = new AST::Stms();   }
			;

Stm:		Exp SEMI												{  $$ = $1;   }
			| IfStm												{  $$ = $1;   }
			| ForStm												{  $$ = $1;   }
			| WhileStm											{  $$ = $1;   }
			| BreakStm												{  $$ = $1;   }
			| ContinueStm											{  $$ = $1;   }
			| ReturnStm											{  $$ = $1;   }
			| Block													{  $$ = $1;   }
			| VarDef												{  $$ = $1;   }
			| TypeDef												{  $$ = $1;   }
			| SEMI													{  $$ = NULL;   }
			;

IfStm:		IF LPAREN Exp RPAREN Block ELSE Block					{  $$ = new AST::IfStmt($3,$5,$7);   }
			| IF LPAREN Exp RPAREN Block         					{  $$ = new AST::IfStmt($3,$5);   }
            ;

ForStm:	    FOR LPAREN Exp SEMI Exp SEMI Exp RPAREN Block			{  $$ = new AST::ForStmt($3,$5,$7,$9);   }
            | FOR LPAREN VarDef Exp SEMI Exp RPAREN Block			{  $$ = new AST::ForStmt($3,$4,$6,$8);   }
			;

WhileStm:   WHILE LPAREN Exp RPAREN Block                           {  $$ = new AST::WhileStm($3,$5);  }
            ;

BreakStm:   BREAK SEMI                                              {  $$ = new AST::BreakStm();  }
            ;

ContinueStm: CONTINUE SEMI                                          {  $$ = new AST::ContinueStm();  }
            ;

ReturnStm:  RETURN Exp SEMI                                         {  $$ = new AST::ReturnStm($2);  }
            | RETURN SEMI                                           {  $$ = new AST::ReturnStm();  }
            ;

TypeDef:    TYPEDEF VarType IDENTIFIER SEMI                         {  $$ = new AST::TypeDef($2,*$3);  }
            ;



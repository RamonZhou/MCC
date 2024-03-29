%{
#include "ast.hpp" 
#include <string>
#include <iostream>

void yyerror(const char *s) {
    std::printf("Error: %s\n", s);
    std::exit(1); 
}

int yylex(void);

AST::Program *Root;
%}

%define parse.error verbose

%output "parser.cpp"

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
	
}

%token  COMMA ELLIPSES DOT SQUOTE DQUOTE SEMI
		LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
		SHL SHR
		EQ GE GT LE LT NEQ NOT ASSIGN
		AND BAND OR BOR
		ARW BXOR BNOT
		ADD SUB
		MUL DIV MOD
		STRUCT TYPEDEF CONST PTR ARRAY
		IF ELSE FOR WHILE 
		BREAK CONTINUE RETURN TRUE FALSE
		BOOL SHORT INT LONG CHAR FLOAT DOUBLE VOID STRING


%token<iVal> INTEGER
%token<sVal> IDENTIFIER 
%token<dVal> REAL
%token<cVal> CHARACTER
%token<strVal> STRINGCONST
%type<program>							Program	

%type<def>								Def	
%type<defs>							    Defs
%type<funcDef>							FuncDef	
%type<varType>                          VarType Type
%type<structMembers>                    StructMembers
%type<structMember>                     StructMember
%type<memberList>                       MemberList _MemberList
%type<parms>                            ParmList _ParmList
%type<parm>                             Parm
%type<block>							Block
%type<varDef>							VarDef	
%type<varList>                          VarList
%type<varInit>                          VarInit

%type<stms>							    Stms
%type<stm>								Stm
%type<ifStm>							IfStm
%type<forStm>							ForStm
%type<whileStm>						    WhileStm
%type<breakStm>						    BreakStm
%type<continueStm>						ContinueStm
%type<returnStm>						ReturnStm
%type<typeDef>							TypeDef	

%type<exp>								Exp
%type<exps>                             Exps _Exps
%type<arraySubscript>                   ArraySubscript	
%type<constant>							Constant NegConstant

%nonassoc IF
%nonassoc ELSE

%left	COMMA 
%left	FUNC_CALL_ARG_LIST
%right	ASSIGN
%left	OR
%left	AND
%left	BOR
%left	BXO
%left	BAND
%left	EQ NEQ
%left	GE GT LE LT
%left	SHL SHR
%left	ADD SUB
%left	MUL DIV MOD
%right	NOT BNOT
%left	DOT ARW

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
            _ParmList COMMA Parm                                {  $$ = $1; $$->push_back($3);  }
            | Parm                                              {  $$ = new AST::Parms(); $$->push_back($1); }
            |                                                   {  $$ = new AST::Parms(); }
            ;

_ParmList:
            _ParmList COMMA Parm                                {  $$ = $1; $$->push_back($3);  }
            | Parm                                              {  $$ = new AST::Parms(); $$->push_back($1); }
            ;
        
Parm:       VarType IDENTIFIER                                  {  $$ = new AST::Parm($1,*$2);   }
            | VarType                                           {  $$ = new AST::Parm($1);   }
            ;

Block:		LBRACE Stms RBRACE										{  $$ = new AST::Block($2);   }
			;

VarDef:     VarType VarList SEMI                                {  $$ = new AST::VarDef($1,$2);   }
            ;

VarList:    VarList COMMA VarInit                              {  $$ = $1; $$->push_back($3);   }
            | VarInit                                           {  $$ = new AST::VarList(); $$->push_back($1);   }
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

IfStm:		IF LPAREN Exp RPAREN Block ELSE Block					{  $$ = new AST::IfStm($3,$5,$7);   }
			| IF LPAREN Exp RPAREN Block         					{  $$ = new AST::IfStm($3,$5);   }
            ;

ForStm:	    FOR LPAREN Exp SEMI Exp SEMI Exp RPAREN Block			{  $$ = new AST::ForStm($3,$5,$7,$9);   }
            | FOR LPAREN VarDef Exp SEMI Exp RPAREN Block			{  $$ = new AST::ForStm($3,$4,$6,$8);   }
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

Exp:        ArraySubscript  %prec ARW                               {  $$ = $1;  }
            | IDENTIFIER                                            {  $$ = new AST::Variable(*$1);  }
            | SUB NegConstant %prec Exp                                { $$ = $1; }
            | Constant                                              {  $$ = $1;  }
            | IDENTIFIER LPAREN Exps RPAREN						    {  $$ = new AST::FuncCall(*$1,$3);   }

            | Exp DOT IDENTIFIER                                    {  $$ = new AST::StructReference($1,*$3);  }
            | Exp ARW IDENTIFIER                                    {  $$ = new AST::StructDereference($1,*$3);  }

            | ADD Exp	%prec NOT									{  $$ = new AST::UnaryPlus($2);   }
			| SUB Exp	%prec NOT									{  $$ = new AST::UnaryMinus($2);   }
			| LPAREN VarType RPAREN Exp %prec NOT					{  $$ = new AST::TypeCast($2,$4);   }
			| MUL Exp	%prec NOT									{  $$ = new AST::Indirection($2);   }
			| BAND Exp	%prec NOT									{  $$ = new AST::AddressOf($2);   }
			| NOT Exp												{  $$ = new AST::LogicNot($2);   }
			| BNOT Exp												{  $$ = new AST::BitwiseNot($2);   }

            | Exp DIV Exp											{  $$ = new AST::Division($1,$3);   }
			| Exp MUL Exp											{  $$ = new AST::Multiplication($1,$3);   } 
			| Exp MOD Exp 										    {  $$ = new AST::Modulo($1,$3);   }
			| Exp ADD Exp											{  $$ = new AST::Addition($1,$3);   } 
			| Exp SUB Exp											{  $$ = new AST::Subtraction($1,$3);   } 
            | Exp SHL Exp											{  $$ = new AST::LeftShift($1,$3);   } 
			| Exp SHR Exp											{  $$ = new AST::RightShift($1,$3);   } 
			| Exp GT Exp											{  $$ = new AST::LogicGT($1,$3);   } 
			| Exp GE Exp											{  $$ = new AST::LogicGE($1,$3);   } 
			| Exp LT Exp											{  $$ = new AST::LogicLT($1,$3);   } 
			| Exp LE Exp											{  $$ = new AST::LogicLE($1,$3);   } 
			| Exp EQ Exp											{  $$ = new AST::LogicEQ($1,$3);   } 
			| Exp NEQ Exp											{  $$ = new AST::LogicNEQ($1,$3);   } 
            | Exp BAND Exp										    {  $$ = new AST::BitwiseAND($1,$3);   }
			| Exp BXOR Exp										    {  $$ = new AST::BitwiseXOR($1,$3);   }
			| Exp BOR Exp											{  $$ = new AST::BitwiseOR($1,$3);   } 
			| Exp AND Exp											{  $$ = new AST::LogicAND($1,$3);   } 
			| Exp OR Exp											{  $$ = new AST::LogicOR($1,$3);   } 
			| Exp ASSIGN Exp 										{  $$ = new AST::DirectAssign($1,$3);   } 
            | LPAREN Exp RPAREN									    {  $$ = $2;   }

ArraySubscript:
            Exp LBRACKET Exp RBRACKET %prec ARW	                       {  $$ = new AST::ArraySubscript($1,$3);  }
            ;
            
Constant:	TRUE													{  $$ =  new AST::Constant(true);   }
			| FALSE													{  $$ =  new AST::Constant(false);   }
			| CHARACTER												{  $$ =  new AST::Constant($1);   }
			| INTEGER 												{  $$ =  new AST::Constant($1);   }
			| REAL													{  $$ =  new AST::Constant($1);   }
			| STRINGCONST												{  $$ =  new AST::Constant(*$1);   }
			;

NegConstant:
            | INTEGER 												{  $$ =  new AST::Constant(-$1);   }
			| REAL													{  $$ =  new AST::Constant(-$1);   }
            ;

Exps:       _Exps COMMA Exp                                         {  $$ = $1; $$->push_back($3);  }
            | Exp  %prec FUNC_CALL_ARG_LIST                         {  $$ = new AST::Exps(); $$->push_back($1);  }
            |                                                       {  $$ = new AST::Exps();  }
            ;

_Exps:      _Exps COMMA Exp                                         {  $$ = $1; $$->push_back($3);  }  
            | Exp   %prec FUNC_CALL_ARG_LIST                        {  $$ = new AST::Exps(); $$->push_back($1);  }
            ;
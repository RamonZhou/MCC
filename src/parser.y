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
%type<varType>                          VarType Type
%type<varType>                          VarType
%type<structMembers>                    StructMembers
%type<structMember>                     StructMember
%type<memberList>                       MemberList _MemberList
%type<parms>                            ParmList
%type<parm>                             Parm
%type<block>							Block
%type<varDef>							VarDef	
%type<varList>                          VarList _VarList
%type<varInit>                          VarInit

%type<Stms>							    Stms
%type<Stm>								Stm
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
%type<constant>							Constant


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
            | VarType                                           {  $$ = new AST::Parm($1);   }
            ;

Block:		LBRACE Stms RBRACE										{  $$ = new AST::Block($2);   }
			;

VarDef:     VarType VarList SEMI                                {  $$ = new AST::VarDef($1,$2);   }
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

Exp:        ArraySubscript                                          {  $$ = $1;  }
            | IDENTIFIER                                            {  $$ = new AST::Variable($1);  }
            | Constant                                              {  $$ = $1;  }
            | SIZEOF LPAREN IDENTIFIER RPAREN						{  $$ = new AST::SizeOf(*$3);   }
			| SIZEOF LPAREN Exp RPAREN								{  $$ = new AST::SizeOf($3);   }
			| SIZEOF LPAREN VarType RPAREN							{  $$ = new AST::SizeOf($3);   }
            | IDENTIFIER LPAREN Exps RPAREN						{  $$ = new AST::FuncCall(*$1,$3);   }
            | NOT Exp												{  $$ = new AST::LogicNot($2);   }
            | Exp DIV Exp											{  $$ = new AST::Division($1,$3);   }
			| Exp MUL Exp											{  $$ = new AST::Multiplication($1,$3);   } 
			| Exp MOD Exp 										{  $$ = new AST::Modulo($1,$3);   }
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
            | Exp BAND Exp										{  $$ = new AST::BitwiseAND($1,$3);   }
			| Exp BXOR Exp										{  $$ = new AST::BitwiseXOR($1,$3);   }
			| Exp BOR Exp											{  $$ = new AST::BitwiseOR($1,$3);   } 
			| Exp AND Exp											{  $$ = new AST::LogicAND($1,$3);   } 
			| Exp OR Exp											{  $$ = new AST::LogicOR($1,$3);   } 
			| Exp QUES Exp COLON Exp								{  $$ = new AST::TernaryCondition($1,$3,$5);   }
			| Exp ASSIGN Exp 										{  $$ = new AST::DirectAssign($1,$3);   } 
			| Exp DIVEQ Exp 										{  $$ = new AST::DivAssign($1,$3);   } 
			| Exp MULEQ Exp										{  $$ = new AST::MulAssign($1,$3);   }  
			| Exp MODEQ Exp										{  $$ = new AST::ModAssign($1,$3);   } 
			| Exp ADDEQ Exp										{  $$ = new AST::AddAssign($1,$3);   } 
			| Exp SUBEQ Exp										{  $$ = new AST::SubAssign($1,$3);   } 
			| Exp SHLEQ Exp										{  $$ = new AST::SHLAssign($1,$3);   } 
			| Exp SHREQ Exp										{  $$ = new AST::SHRAssign($1,$3);   } 
			| Exp BANDEQ Exp										{  $$ = new AST::BitwiseANDAssign($1,$3);   } 
			| Exp BXOREQ Exp										{  $$ = new AST::BitwiseXORAssign($1,$3);   } 
			| Exp BOREQ Exp										{  $$ = new AST::BitwiseORAssign($1,$3);   }

ArraySubscript:
            Exp LBRACKET Exp RBRACKET                        {  $$ = new AST::ArraySubscript(*$1,$3);  }
            ;
            
Constant:	TRUE													{  $$ =  new AST::Constant(true);   }
			| FALSE													{  $$ =  new AST::Constant(false);   }
			| CHARACTER												{  $$ =  new AST::Constant($1);   }
			| INTEGER 												{  $$ =  new AST::Constant($1);   }
			| REAL													{  $$ =  new AST::Constant($1);   }
			| STRING												{  $$ =  new AST::Constant(*$1);   }
			;

Exps:       _Exps COMMA Exp                                         {  $$ = $1; $$->push_back($3);  }
            | Exp                                                   {  $$ = new AST::Exps(); $$->push_back($1);  }
            |                                                       {  $$ = new AST:Exps();  }
            ;

_Exps:      _Exps COMMA Exp                                         {  $$ = $1; $$->push_back($3);  }  
            | Exp                                                   {  $$ = new AST::Exps(); $$->push_back($1);  }
            ;
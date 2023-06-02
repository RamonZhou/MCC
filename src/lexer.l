%{
#include "ast.hpp"
#include "parser.hpp"
#include <stdio.h>
#include <string>
#include <iostream>
extern "C" int yywrap() {return 1;}

char Convert(char ch){
	switch(ch){
	case 'a': return '\a';
	case 'b': return '\b';
	case 'f': return '\f';
	case 'n': return '\n';
	case 'r': return '\r';
	case 't': return '\t';
	case 'v': return '\v';
	case '\\': return '\\';
	case '\'': return '\'';
	case '\"': return '\"';
	default:
		if ('0'<=ch && ch<='9')
			return (char)(ch-'0');
		else
			return ch;
	}
}
%}

%option yylineno
%option never-interactive
%option outfile="lexer.cpp"

%%
","														{return COMMA;}
"..."													{return ELLIPSES;}
"."														{return DOT;}
";"														{return SEMI;}
"("														{return LPAREN;}
")"														{return RPAREN;}
"["														{return LBRACKET;}
"]"														{return RBRACKET;}
"{"														{return LBRACE;}
"}"														{return RBRACE;}
"<<"													{return SHL;}
">>"													{return SHR;}
"=="													{return EQ;}
">="													{return GE;}
">"														{return GT;}
"<="													{return LE;}
"<"														{return LT;}
"!"														{return NOT;}
"="														{return ASSIGN;}
"&&"													{return AND;}
"&"														{return BAND;}
"||"													{return OR;}
"|"														{return BOR;}
"->"													{return ARW;}
"^"														{return BXOR;}
"~"														{return BNOT;}
"+"														{return ADD;}
"-"														{return SUB;}
"*"														{return MUL;}
"/"														{return DIV;}
"%"														{return MOD;}
"struct"												{return STRUCT;}
"typedef"												{return TYPEDEF;}
"const"													{return CONST;}
"ptr"													{return PTR;}
"array"													{return ARRAY;}
"if"													{return IF;}
"else"													{return ELSE;}
"for"													{return FOR;}
"while"													{return WHILE;}
"continue"												{return CONTINUE;}
"return"												{return RETURN;}
"true"													{return TRUE; }
"false"													{return FALSE; }
"break"													{return BREAK; }
"bool"													{return BOOL; }
"short"													{return SHORT; }
"int"													{return INT; }
"long"													{return LONG; }
"char"													{return CHAR; }
"float"													{return FLOAT; }
"double"												{return DOUBLE; }
"string"												{return STRING;}
"void"													{return VOID; }
[ \t\n]													{ ; }
"/*"[^*]*[*]+([^*/][^*]*[*]+)*"/"						{ ; }
"//".*													{ ; }
"\'"\\."\'"												{ 
															yylval.cVal = Convert(yytext[2]);
															return CHARACTER; 
														}
"\'"[^\\']"\'"											{ 
															yylval.cVal = yytext[1];
															return CHARACTER; 
														}
"\'"													{return SQUOTE; }
"\""(\\.|[^"\\])*"\""									{
															yylval.strVal = new std::string("");
															for (int i = 1; i <= yyleng-2; i++)
																if (yytext[i] == '\\'){
																	i++;
																	yylval.strVal->push_back(Convert(yytext[i]));
																}else{
																	yylval.strVal->push_back(yytext[i]);
																}
															return STRINGCONST;
														}
"\""													{return DQUOTE;}
[a-zA-Z_][a-zA-Z0-9_]*									{ 
															yylval.sVal = new std::string(yytext, yyleng);
															return IDENTIFIER; 
														} 
[0-9]+\.[0-9]+											{ 
															double dtmp;
															sscanf(yytext, "%lf", &dtmp);
															yylval.dVal = dtmp;
															return REAL; 
														}
[0-9]+													{
															int itmp;
															sscanf(yytext, "%d", &itmp);
															yylval.iVal = itmp; 
															return INTEGER; 
														}
%%
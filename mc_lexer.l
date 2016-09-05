%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "mc_scanner.h"
#undef  YY_DECL
#define YY_DECL int MC::MC_Scanner::yylex( MC::MC_Parser::semantic_type * const lval, MC::MC_Parser::location_type *loc )


/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}


%option debug
%option nodefault
%option yyclass="MC::MC_Scanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}
[\t\n ]       /*ignore white space*/
"+"			{ return MC::MC_Parser::token::ADD;}
"-"			{ return MC::MC_Parser::token::MIN;}
"*"			{ return MC::MC_Parser::token::MUL;}
"/"			{ return MC::MC_Parser::token::DIV;}
"("			{ return MC::MC_Parser::token::LP;}
")"			{ return MC::MC_Parser::token::RP;}
"log"		{ return MC::MC_Parser::token::LOG;}

[0-9][.]?[0-9]* {
				yylval->num_val = atof( yytext );
				return MC::MC_Parser::token::NUMBER;
			}

%%

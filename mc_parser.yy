%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {MC}
%define parser_class_name {MC_Parser}

%code requires{
   namespace MC {
      class MC_Driver;
      class MC_Scanner;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { MC_Scanner  &scanner  }
%parse-param { MC_Driver  &driver  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "mc_driver.h"

#undef yylex
#define yylex scanner.yylex
}

%union{
	double num_val;
}

%define parse.assert

%token<num_val> NUMBER
%token ADD
%token MIN
%token MUL
%token DIV
%token LP
%token RP
%token LOG
%token IF
%token ELSE
%token WHILE
%token END

%locations

%left ADD MIN
%left MUL DIV

%%

exp : primary_exp 
    | LP exp RP	 

    | exp MUL exp {driver.addAction(token::MUL);}
    | exp DIV exp {driver.addAction(token::DIV);}
    | exp ADD exp {driver.addAction(token::ADD);}
    | exp MIN exp {driver.addAction(token::MIN);}
	| LOG LP exp RP {driver.addAction(token::LOG);}
	
	| ELSE
	| END
	;

primary_exp : NUMBER      {driver.addAction(token::NUMBER, $1);}
			| MIN NUMBER  {driver.addAction(token::NUMBER, -1 * $2);}
            ;
%%


void 
MC::MC_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}

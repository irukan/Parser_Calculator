#ifndef __MCDRIVER_HPP__
#define __MCDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>
#include <stack>
#include <vector>
#include "mc_scanner.h"
#include "mc_parser.tab.hh"
#include "mc_action.h"

namespace MC{


class MC_Driver{
public:
   MC_Driver(){
	   parser  = nullptr;
	   scanner = nullptr;   
   }

   virtual ~MC_Driver();
   
   /** 
    * parse - parse from a file
    * @param filename - valid string with input file
    */
   void parse( const char * const filename );
   /** 
    * parse - parse from a c++ input stream
    * @param is - std::istream&, valid input stream
    */
   void parse( std::istream &iss );

   void action();
   double getResult();
   void addAction(MC::MC_Parser::token::yytokentype act, double num);
   void addAction(MC::MC_Parser::token::yytokentype act);

private:
   std::stack<double> m_RsltStack;
   std::vector<MC_Action> actionTree;

   void parse_helper( std::istream &stream );

   MC::MC_Parser  *parser  ;
   MC::MC_Scanner *scanner ;
};

} /* end namespace MC */
#endif /* END __MCDRIVER_HPP__ */

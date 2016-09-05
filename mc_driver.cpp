#include <cctype>
#include <fstream>
#include <cassert>
#include <iostream>

#include "mc_driver.h"

MC::MC_Driver::~MC_Driver()
{
   delete(scanner);
   scanner = nullptr;
   delete(parser);
   parser = nullptr;
}

void 
MC::MC_Driver::parse( const char * const filename )
{
   assert( filename != nullptr );
   std::ifstream in_file( filename );
   if( ! in_file.good() )
   {
       exit( EXIT_FAILURE );
   }
   parse_helper( in_file );
   return;
}

void
MC::MC_Driver::parse( std::istream &stream )
{
	actionTree.clear();
	actionTree.shrink_to_fit();

	while(!m_RsltStack.empty())
		m_RsltStack.pop();

	if( ! stream.good()  && stream.eof() )
   {
       return;
   }
   //else
   parse_helper( stream ); 
   return;
}


void 
MC::MC_Driver::parse_helper( std::istream &stream )
{
   
   delete(scanner);
   try
   {
      scanner = new MC::MC_Scanner( &stream );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate scanner: (" <<
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   
   delete(parser); 
   try
   {
      parser = new MC::MC_Parser( (*scanner) /* scanner */, 
                                  (*this) /* driver */ );
   }
   catch( std::bad_alloc &ba )
   {
      std::cerr << "Failed to allocate parser: (" << 
         ba.what() << "), exiting!!\n";
      exit( EXIT_FAILURE );
   }
   const int accept( 0 );
   if( parser->parse() != accept )
   {
      std::cerr << "Parse failed!!\n";
   }
   return;
}
//############################################################

void 
MC::MC_Driver::action()
{
	for (size_t idx = 0; idx < actionTree.size(); idx++)
		actionTree[idx].action();
}

double
MC::MC_Driver::getResult()
{
	return m_RsltStack.top();
}

void 
MC::MC_Driver::addAction(MC::MC_Parser::token::yytokentype act, double num)
{
	actionTree.push_back(MC_Action(m_RsltStack, num));
}

void 
MC::MC_Driver::addAction(MC::MC_Parser::token::yytokentype act)
{
	actionTree.push_back(MC_Action(m_RsltStack, act));
}

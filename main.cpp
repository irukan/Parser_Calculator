#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include "mc_driver.h"

int 
main( const int argc, const char **argv )
{
	std::stringstream ss;
	ss << "(1 + 2) * log(3)";

	MC::MC_Driver driver;
	driver.parse(ss);
	driver.action();
	
	std::cout << "##################################" <<std::endl;
	std::cout << "Result = " << driver.getResult() << std::endl;

	return( EXIT_SUCCESS );
}

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>

TEST_CASE( "Test for helloworld", "[classic]" )
{
		std::cout << "Hello test!" << std::endl;	
}

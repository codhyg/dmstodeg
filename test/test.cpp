#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <cmath>
#include "../src/mathmodel.h"

TEST_CASE( "DMS to deg conversion test", "[classic]" )
{
		std::cout << "Hello test!" << std::endl;	
		CHECK( std::round( dmsToDegConversion(2, 2, 2) * 100000) / 100000 == 2.03389);
		CHECK( std::round( dmsToDegConversion(15, 25, 13) * 100000) / 100000 == 15.42028);
}

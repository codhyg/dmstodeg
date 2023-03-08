
add_executable(test-runner test.cpp catch.hpp ../src/mathmodel.h 
												../src/mathmodel.cpp) 
add_test(NAME Test-dms COMMAND test-runner)

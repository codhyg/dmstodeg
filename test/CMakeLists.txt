add_executable(test-runner test.cpp catch.hpp ../../src/addfunc.h
												../../src/addfunc.cpp) 
add_test(NAME Test_helloworld COMMAND test-runner)

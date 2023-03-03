add_executable(test-runner test.cpp catch.hpp ../src/mainwindow.h 
												../src/mainwindow.cpp) 
add_test(NAME Test-dms COMMAND test-runner)

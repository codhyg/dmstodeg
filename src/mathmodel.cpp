#include "mathmodel.h"

double dmsToDegConversion(int deg, int min, int sec)
{
    const int sixty{ 60 }; //60 seconds in one minute, 60 minutes in one degree

    return (double)deg + ((double)sec/sixty + (double)min)/sixty;
}

%module my_cpp

%{
#define SWIG_FILE_WITH_INIT
#include "my_cpp.h"
%}

int leap_year(int year);
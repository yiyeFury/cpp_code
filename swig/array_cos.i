%module array_cos

%{
#define SWIG_FILE_WITH_INIT
#include "my_cpp.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
    import_array();
%}


/*  typemaps for the two arrays, the second will be modified in-place */
%apply (double* IN_ARRAY1, int DIM1) {(double * in_array, int size_in)}
%apply (double* INPLACE_ARRAY1, int DIM1) {(double * out_array, int size_out)}

void array_cos(double *in_array, double *out_array, int size);
int leap_year(int year);
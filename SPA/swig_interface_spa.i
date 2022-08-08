%module SPA

%{
#define SWIG_FILE_WITH_INIT
#include "SPA.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
    import_array();
%}


/*  typemaps for the two arrays, the second will be modified in-place */
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float * solar_zenith, int rows, int cols)}
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float * mask, int mask_rows, int mask_cols)}

%apply (float* IN_ARRAY1, int DIM1) {(float * lats, int lats_size)}
%apply (float* IN_ARRAY1, int DIM1) {(float * lons, int lons_size)}


/*  Wrapper for cos_doubles that massages the types */
%inline %{

    // void PrintTestFunc(int *test_data, int test_size,
    //                    int num_thread) {
    //     PrintTest(test_data, test_size,
    //                     num_thread);
    // }
    /*  takes as input two numpy arrays */
    void CalcSolarAngleFunc(float *solar_zenith, int rows, int cols,
                    float *lats, int lats_size,
                    float *lons, int lons_size,
                    int year, int month, int day,
                    int hour=0, int minute=0, int second=0,
                    int num_thread=4) {
        /*  calls the original funcion, providing only the size of the first */
        CalcSolarAngle(solar_zenith, rows, cols,
                    lats, lats_size,
                    lons, lons_size,
                    year, month, day,
                    hour, minute, second,
                    num_thread);
    }

void CalcSolarAngleMaskFunc(float *solar_zenith, int rows, int cols,
                            float *mask, int mask_rows, int mask_cols,
                        float *lats, int lats_size,
                        float *lons, int lons_size,
                        int year, int month, int day,
                        int hour=0, int minute=0, int second=0,
                        int num_thread=4) {
    /*  calls the original funcion, providing only the size of the first */
    CalcSolarAngleMask(solar_zenith, rows, cols,
                   mask, mask_rows, mask_cols,
                   lats, lats_size,
                   lons, lons_size,
                   year, month, day,
                   hour, minute, second,
                   num_thread);
}
    
    
%}



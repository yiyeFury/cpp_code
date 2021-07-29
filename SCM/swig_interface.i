%module SCM

%{
#define SWIG_FILE_WITH_INIT
#include "successive_correction.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
    import_array();
%}


/*  typemaps for the two arrays, the second will be modified in-place */
%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float * bkg_data, int bkg_rows, int bkg_cols)}
%apply (float* IN_ARRAY2, int DIM1, int DIM2) {(float * obs_data, int obs_rows, int obs_cols)}

%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float * dst_data, int dst_rows, int dst_cols)}

%apply (float* IN_ARRAY1, int DIM1) {(float * lats, int lats_size)}
%apply (float* IN_ARRAY1, int DIM1) {(float * lons, int lons_size)}


/*  Wrapper for cos_doubles that massages the types */
%inline %{
    /*  takes as input two numpy arrays */
    void SuccessiveCorrectionFunc(float *bkg_data, int bkg_rows, int bkg_cols,
                          float *obs_data, int obs_rows, int obs_cols,
                          float *dst_data, int dst_rows, int dst_cols,
                          float *lats, int lats_size,
                          float *lons, int lons_size,
                          float search_radius,
                          float influence_radius,
                          float fill_value) {
        /*  calls the original funcion, providing only the size of the first */
        SuccessiveCorrection(bkg_data, bkg_rows, bkg_cols,
                          obs_data, obs_rows, obs_cols,
                          dst_data, dst_rows, dst_cols,
                          lats, lats_size,
                          lons, lons_size,
                          search_radius,
                          influence_radius,
                          fill_value);
    }
%}

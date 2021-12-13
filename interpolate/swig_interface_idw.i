%module IDW

%{
#define SWIG_FILE_WITH_INIT
#include "IDW.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
    import_array();
%}


/*  typemaps for the two arrays, the second will be modified in-place */
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float * dst_data, int dst_rows, int dst_cols)}
%apply (float* IN_ARRAY1, int DIM1) {(float * dst_lats, int dst_lats_size)}
%apply (float* IN_ARRAY1, int DIM1) {(float * dst_lons, int dst_cols_size)}

%apply (float* IN_ARRAY1, int DIM1) {(float * obs_data, int obs_size)}
%apply (float* IN_ARRAY1, int DIM1) {(float * obs_lats, int obs_lats_size)}
%apply (float* IN_ARRAY1, int DIM1) {(float * obs_lons, int obs_lons_size)}


/*  Wrapper for cos_doubles that massages the types */
%inline %{

    /*  takes as input two numpy arrays */
    void InverseDistanceWeightFunc(float *obs_data, int obs_size,
                           float *obs_lats, int obs_lats_size,
                           float *obs_lons, int obs_lons_size,
                           float *dst_data, int dst_rows, int dst_cols,
                           float *dst_lats, int dst_lats_size,
                           float *dst_lons, int dst_cols_size,
                           float search_radius,
                           float power_value,
                           int num_thread) {
        /*  calls the original funcion, providing only the size of the first */
        InverseDistanceWeight(obs_data, obs_size,
                              obs_lats, obs_lons,
                              dst_data, dst_rows, dst_cols,
                              dst_lats, dst_lons,
                              search_radius,
                              power_value,
                              num_thread);
    }
    
%}


float GreatCircleDistanceIDW(float lon1, float lat1, float lon2, float lat2, float radius);

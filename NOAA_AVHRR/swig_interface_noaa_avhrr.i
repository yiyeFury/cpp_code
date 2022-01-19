%module NOAA_AVHRR_CPP

%{
#define SWIG_FILE_WITH_INIT
#include "noaa_avhrr.h"
%}

/*  include the numpy typemaps */
%include "numpy.i"
/*  need this for correct module initialization */
%init %{
    import_array();
%}


/*  typemaps for the two arrays, the second will be modified in-place */
%apply (int* IN_ARRAY1, int DIM1) {(int * earth_data, int num_word)}
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) {(float * channel_data, int num_obs, int num_channel)}


/*  Wrapper for cos_doubles that massages the types */
%inline %{

    /*  takes as input two numpy arrays */
    void EarthDataSplitFunc(int * earth_data, int num_word,
                    float * channel_data, int num_obs, int num_channel) {
        /*  calls the original funcion, providing only the size of the first */
        EarthDataSplit(earth_data, num_word,
                    channel_data, num_obs, num_channel);
    }
    
    
%}



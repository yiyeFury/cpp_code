swig -c++ -python swig_interface.i

python setup_numpy.py build_ext --inplace

swig -c++ -python swig_interface.i && python setup_numpy.py build_ext --inplace
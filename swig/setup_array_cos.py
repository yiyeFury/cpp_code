# -*- coding: utf-8 -*-
# DateTime:  2020/1/21 15:16
# Description: setup.py file for SWIG

##
# package **********************************************************************
import warnings
import os
import sys
import numpy as np
from distutils.core import setup, Extension

# class ************************************************************************
# function *********************************************************************
example_module = Extension('_array_cos',
                           sources=['array_cos_wrap.cxx', 'my_cpp.cpp'],
                           include_dirs=[np.get_include()],
                           )
setup(name='array_cos',
      version='0.1',
      author="SWIG Docs",
      description="""Simple swig example from docs""",
      ext_modules=[example_module],
      py_modules=["array_cos"],
      )




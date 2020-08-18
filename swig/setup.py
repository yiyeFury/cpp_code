# -*- coding: utf-8 -*-
# DateTime:  2020/1/21 15:16
# Description: setup.py file for SWIG

##
# package **********************************************************************
import warnings
import os
import sys

from distutils.core import setup, Extension

# class ************************************************************************
# function *********************************************************************
example_module = Extension('_my_cpp',
                           sources=['my_cpp_wrap.cxx', 'my_cpp.cpp'],
                           )
setup(name='my_cpp',
      version='0.1',
      author="SWIG Docs",
      description="""Simple swig example from docs""",
      ext_modules=[example_module],
      py_modules=["my_cpp"],
      )




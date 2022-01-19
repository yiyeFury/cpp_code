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
from Cython.Build import cythonize

# class ************************************************************************
# function *********************************************************************
module_name = 'NOAA_AVHRR_CPP'  # 模块名字，python中import的名字
swig_interface_file_name = 'swig_interface_noaa_avhrr.i'  # swig接口文件名字
cpp_name = 'noaa_avhrr.cpp'  # cpp 脚本的名字

extension_name = '_' + module_name
cxx_name = swig_interface_file_name.rstrip('.i') + '_wrap.cxx'

eigen_dir = r"D:\Program\eigen\eigen-3.3.9\Eigen"

extension_source = [cxx_name, cpp_name]

# 单线程 ------------------------------------------------------------------------
# example_module = Extension(extension_name,
#                            sources=extension_source,
#                            include_dirs=[np.get_include(), eigen_dir],
#                            )
# setup(name=module_name,
#       version='0.1',
#       author="xzl",
#       description="""swig bind cpp and python for fusion""",
#       ext_modules=[example_module],
#       py_modules=[module_name],
#       )

# 并行 --------------------------------------------------------------------------
example_module = Extension(extension_name,
                           sources=extension_source,
                           include_dirs=[np.get_include(), eigen_dir],
                           # For Microsoft Visual C++ compiler, use '/openmp' instead of '-fopenmp'.
                           # extra_compile_args=['-fopenmp'],
                           # extra_link_args=['-fopenmp'],
                           extra_compile_args=['/openmp'],
                           extra_link_args=['/openmp'],
                           )
setup(name=module_name,
      version='0.1',
      author="xzl",
      description="""swig bind cpp and python for noaa avhrr""",
      # ext_modules=[example_module],
      ext_modules=cythonize(example_module),
      py_modules=[module_name],
      )




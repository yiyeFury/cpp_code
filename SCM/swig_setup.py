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
module_name = 'SCM'  # 模块名字，python中import的名字
swig_interface_file_name = 'swig_interface.i'  # swig接口文件名字
cpp_name = 'successive_correction.cpp'  # cpp 脚本的名字

extension_name = '_' + module_name
cxx_name = swig_interface_file_name.rstrip('.i') + '_wrap.cxx'

extension_source = [cxx_name, cpp_name]
example_module = Extension(extension_name,
                           sources=extension_source,
                           include_dirs=[np.get_include()],
                           )
setup(name=module_name,
      version='0.1',
      author="xzl",
      description="""swig bind cpp and python for scm""",
      ext_modules=[example_module],
      py_modules=[module_name],
      )




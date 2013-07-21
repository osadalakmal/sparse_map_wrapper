#!/usr/bin/env python

"""
setup.py file for google sparse hash map wrapper
"""

from distutils.core import setup, Extension
sparse_map_module = Extension('_sparse_map',
                           sources=['sparse_map_wrap.cxx', 'sparse_map.c'],
                           )

setup (name = 'sparse_map',
       version = '0.1',
       author      = "Osada Paranaliyanage",
       description = """Simple wrapper around sparse hash map from google""",
       ext_modules = [sparse_map_module],
       py_modules = ["sparse_map"],
       )

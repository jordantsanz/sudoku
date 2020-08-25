from ctypes import c_double, c_int, CDLL
import sys

lib_path = './mainmodule.so'
mainmodule = CDLL(lib_path)

puzzle = mainmodule.create(40)

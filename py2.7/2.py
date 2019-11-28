# -*- coding: UTF-8 -*-
from  __future__ import print_function
letters = ("A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z")
n = input("n = ")
k = 0
for i in range(0, n):
    for j in range(0, n - i):
        print (letters[k], end='')
        k += 1
    print ("\n", end='')
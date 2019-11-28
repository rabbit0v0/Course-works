# -*- coding: UTF-8 -*-
import math

x = input("input a number:")
a = x / 1000
b = (x % 1000) / 100
c = (x % 100) / 10
d = x % 10

a = (a + 9) % 10
b = (b + 9) % 10
c = (c + 9) % 10
d = (d + 9) % 10

y = c * 1000 + d * 100 + a * 10 + b

print "%04d" %(y)
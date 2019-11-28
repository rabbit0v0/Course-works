# -*- coding: UTF-8 -*-
import math

x = input("x = ")

if x > 0:
    y = (math.sin(x)**2 + math.cos(x) + 1)**3 - 3*(math.sin(x)**2 + math.cos(x))
if x < 0:
    y = 4 * math.sin(x)**2 + 4 * math.cos(x) - 1
if x == 0:
    y = math.pi
print y
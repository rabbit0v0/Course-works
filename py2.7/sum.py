# -*- coding: UTF-8 -*-
import math

n = input("数据个数:")
sum = 0
tot = 0
for num in range(0, n):
    s = input()
    if s >= 60:
        sum += s
        tot += 1
print "总分:%d\n共%d个"%(sum, tot)

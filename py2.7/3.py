# -*- coding: UTF-8 -*-
a = input("a = ")
n = input("n = ")
base = 10
pre = a
while pre/10 != 0:
    pre /= 10
    base *= 10
sum = 0
now = a
for num in range(0, n):
    sum += now
    now = now * base + a
print sum

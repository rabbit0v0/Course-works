# -*- coding: UTF-8 -*-
dots = {}


def init(k):
    print(k)
    x = input("x = ")
    y = input("y = ")
    dots[k] = (x, y)


def slope(p1, p2):
    p = (p2[1]-p1[1])/(p2[0]-p1[0])
    return p


def intercept(p1, p2):
    p = (p2[1] - p1[1]) / (p2[0] - p1[0])
    b = p1[1] - p*p1[0]
    return b


init("p1")
init("p2")
s = slope(dots["p1"], dots["p2"])
i = intercept(dots["p1"], dots["p2"])
print "slope %0.2f"%(s)
print "intercept %0.2f"%(i)

# -*- coding: UTF-8 -*-

for num in range(0, 4):
    n = input("[1]苹果\n[2]梨\n[3]橘子\n[4]葡萄\n[0]退出\n请输入序号：\n")
    if n == 0:
        break
    if n == 1:
        print "3.00元／千克"
    elif n == 2:
        print "2.50元／千克"
    elif n == 3:
        print "4.10元／千克"
    elif n == 4:
        print "10.20元／千克"
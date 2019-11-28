# -*- coding: UTF-8 -*-
def count(aList, x):
    sum = 0
    for num in range(0, len(aList)):
        if aList[num] == x:
            sum += 1

    return sum


def main():
    l = []
    c = raw_input("请输入以逗号分隔的列表元素：")
    for k in c.split(','):
        l.append(str(k))
    a = raw_input("请输入需要计数的元素：")
    ans = count(l, a)
    print ans

main()
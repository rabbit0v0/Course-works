# -*- coding: UTF-8 -*-
import Tkinter


def cal(aa, ii, nn):
    y = aa * ((1 + ii) ** nn)
    return y


a = input("本金 = ")
i = input("年利率 = ")
n = input("年数 = ")
ans = cal(a, i, n)
print '%.2f' % ans

root = Tkinter.Tk()
h = cal(a, i, 20)+30
canvas = Tkinter.Canvas(root, width = 600, height = h, bg = 'white')
canvas.pack()
for k in range(0, 10):
    s = cal(a, i, (2 * (k + 1)))
    canvas.create_rectangle(25+k*60, h-s-10, k*60+40, h-10, fill = 'black')
    canvas.create_text(30+k*60, h-s-20, text = '%.2f' % s)
canvas.create_text(80, 10, text = "您的增值情况是%.2f" % ans)

Tkinter.mainloop()
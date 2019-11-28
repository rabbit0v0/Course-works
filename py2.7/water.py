# -*- coding: UTF-8 -*-
import time
from Tkinter import*
tk = Tk()
canvas = Canvas(tk,width=400,height=200)
canvas.pack()
canvas.create_polygon(10,10,10,60,50,35)  ##创建三角形
for x in range(0,60):
    canvas.move(1,5,0)  ##把任意画好的对象移动到把x和y坐标增加给定值的位置
    tk.update()         ##强制tkinter更新屏幕（重画）     
    time.sleep(0.05)    ##让程序休息二十分之一秒（0.05秒），然后再继续
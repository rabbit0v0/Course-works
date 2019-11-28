import Tkinter
import time
root = Tkinter.Tk()
canvas = Tkinter.Canvas(root, width = 600, height = 400, bg = 'white')
canvas.pack()
ball = canvas.create_oval(280, 180, 320, 220, fill = 'pink', outline = '')
v = 0
h = 200
t = 0.05
r = 20
while 1:
    while h <= 400-r:
        canvas.move(ball, 0, v*t)
        root.update()
        h = h + v*t
        v = v + 9.8 * t
        time.sleep(0.01)
    v = -v
    if v == 0:
        break
    while v <= 0:
        canvas.move(ball, 0, v * t)
        root.update()
        h = h + v * t
        v = v + 9.8 * t
        time.sleep(0.01)

Tkinter.mainloop()
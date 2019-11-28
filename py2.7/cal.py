import math
import Tkinter


class stack:
    data = []

    def __init__(self):
        self.top = 0

    def push(self, c):
        stack.data.append(c)
        self.top += 1

    def pop(self):
        self.top -= 1
        stack.data.pop()
        return stack.data[self.top]

    def query(self):
        return stack.data[self.top - 1]

    def clear(self):
        while (len(stack.data)):
            stack.data.pop()
        self.top = 0


class cal:
    def __init__(self):
        root = Tkinter.Tk()
        root.geometry('400x300')
        bot_1 = Tkinter.Button(root, text='1', width=5, bg='grey')
        bot_2 = Tkinter.Button(root, text='2', width=5, bg='grey')
        bot_3 = Tkinter.Button(root, text='3', width=5, bg='grey')
        bot_4 = Tkinter.Button(root, text='4', width=5, bg='grey')
        bot_5 = Tkinter.Button(root, text='5', width=5, bg='grey')
        bot_6 = Tkinter.Button(root, text='6', width=5, bg='grey')
        bot_7 = Tkinter.Button(root, text='7', width=5, bg='grey')
        bot_8 = Tkinter.Button(root, text='8', width=5, bg='grey')
        bot_9 = Tkinter.Button(root, text='9', width=5, bg='grey')
        bot_0 = Tkinter.Button(root, text='0', width=5, bg='grey')
        bot_add = Tkinter.Button(root, text='+', width=5, bg='orange')
        bot_sub = Tkinter.Button(root, text='-', width=5, bg='orange')
        bot_plu = Tkinter.Button(root, text='*', width=5, bg='orange')
        bot_div = Tkinter.Button(root, text='/', width=5, bg='orange')
        bot_1.pack()
        bot_2.pack()
        bot_3.pack()
        bot_4.pack()
        bot_5.pack()
        bot_6.pack()
        bot_7.pack()
        bot_8.pack()
        bot_9.pack()
        bot_0.pack()
        bot_add.pack()
        bot_sub.pack()
        bot_plu.pack()
        bot_div.pack()
        root.mainloop()


def main():
    tex = stack()
    newcal = cal()


main()

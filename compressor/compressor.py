# -*- coding: UTF-8 -*-
import os
try:
    import Tkinter as tk
    import tkFileDialog as fd
except:
    import tkinter as tk
    import tkinter.filedialog as fd
from functools import partial
has = {}
dic = []

class nodes:
    def __init__(self,n = '', v = '', w = 1, lc = None, rc = None):
        self.name = n
        self.v = v
        self.w = w
        self.lc = lc
        self.rc = rc

    def __lt__(self, other):
        return self.w < other.w

    def __gt__(self, other):
        return self.w > other.w

    def __ge__(self, other):
        return self.w >= other.w

    def __le__(self, other):
        return self.w <= other.w


def huffman():
    h = sorted(dic, key = lambda d : d.w)
    while len(h) > 1:
        a = h.pop(0)
        b = h.pop(0)
        f = nodes()
        f.lc = a
        f.rc = b
        f.w = a.w + b.w
        h.append(f)
        h = sorted(h, key=lambda d: d.w)
    return h


def through(the_node, code = ''):
    the_node.v = code
    if the_node.name in has:
        has[the_node.name] = code
        # print the_node.name
        # print the_node.v
    if the_node.lc != None:
        through(the_node.lc, code+'0')
    if the_node.rc != None:
        through(the_node.rc, code+'1')


def cal(content):
    num = 0
    for i in content:
        if i in has:
            dic[has[i]].w += 1
        else:
            has[i] = num
            num += 1
            dic.append(nodes())
            dic[has[i]].name = i
    # for i in has:
    #     print i
    #     print dic[has[i]].w


def rewrite_com(old, path):
    txt = open(path+'/compressed.out', 'wb')
    str0 = ''
    for i in old:
        str0 += has[i]
        while len(str0) >= 8:
            tmp = str0[:8]
            str0 = str0[8:]
            numb = int(tmp, 2)
            txt.write(chr(numb))
    if len(str0) > 0:
        tmp = str0
        while len(tmp) < 8:
            tmp += '0'
        numb = int(tmp, 2)
        txt.write(chr(numb))



def rewrite_dic(path):
    txt = open(path+'/dict.txt', 'w')
    for i in has:
        txt.write(i)
        txt.write(' ')
        txt.write(has[i])
        txt.write('\n')




class denodes():
    def __init__(self, c = '', str = '', lc = None, rc = None):
        self.c = c
        self.str = str
        self.lc = lc
        self.rc = rc


def sep(txt):
    l = []
    num = 0
    flag = True
    for i in txt:
        if flag:
            node = denodes()
            node.c = i
            l.append(node)
            flag = False
        elif i == ' ':
            continue
        elif i == '\n':
            flag = True
            num += 1
        else:
            l[num].str += i
    return l


def maketree(root, str, c):
    if len(str) == 0:
        root.c = c
    else:
        if str[0] == '0':
            str = str[1:]
            if root.lc == None:
                root.lc = denodes()
            maketree(root.lc, str, c)
        elif str[0] == '1':
            str = str[1:]
            if root.rc == None:
                root.rc = denodes()
            maketree(root.rc, str, c)


def dictree(l):
    root = denodes()
    for i in range(0, len(l)):
        maketree(root, l[i].str, l[i].c)
    return root


def searchtree(out, root, c):
    # global dec
    if c == '0':
        newnode = root.lc
        if newnode.c == '':
            return newnode
        else:
            # dec += newnode.c
            # print newnode.c
            out.write(newnode.c)
            return None
    else:
        newnode = root.rc
        if newnode.c == '':
            return newnode
        else:
            # dec += newnode.c
            # print newnode.c
            out.write(newnode.c)
            return None


def findword(text, out, root, txt):
    tmp = root
    num = 0
    a = []
    quater = len(txt)/4.0
    for j in range (1, 5):
        a.append(quater * j)
    i = 0
    while len(txt) > num:
        # if num % 500000:
        #     print num
        if num == a[i]:
            i += 1
            text.insert(tk.END, "解压进度：%d%%\n" % (i * 25))
            text.update()
            text.see(tk.END)
        if txt[num] != '0' and txt[num] != '1':
            text.insert(tk.END, "[Error]文件错误！\n")
            break
        tmp = searchtree(out, tmp, txt[num])
        num += 1
        if tmp == None:
            tmp = root
    if num == len(txt):
        text.insert(tk.END, "解压已完成！\n")


def decode(txt):
    res = ''
    for i in txt:
        s = bin(ord(i))
        s = s[2:]
        while len(s) < 8:
            s = '0' + s
        res += s

    return res


path = ''
def getfile(text):
    global path
    path = fd.askopenfilename()
    print 'Set input file: ' + path
    text.set(path)

dict = ''
def getdict(text):
    global dict
    dict = fd.askopenfilename()
    print 'Set dict: ' + dict
    text.set(dict)

outpath = ''
def getoutpath(text):
    global outpath
    outpath = fd.askdirectory()
    print 'Set outpath: ' + outpath
    text.set(outpath)


def compress(text):
    global path
    global outpath
    # text.insert(tk.END, "文件路径")
    if path == '':
        text.insert(tk.END, "请选择文件！\n")
        return
    elif outpath == '':
        text.insert(tk.END, "请选择压缩路径！\n")
        return
    elif not os.path.exists(path):
        text.insert(tk.END, "[Error]文件不存在！\n")
        return
    elif not os.path.exists(outpath):
        text.insert(tk.END, "[Error]压缩目标路径不存在！\n")
        return
    txt = open(path)
    content = txt.read()
    # getting = raw_input("请输入压缩文件的存储位置：")
    cal(content)
    text.insert(tk.END, "正在构建字典树...\n")
    text.update()
    text.see(tk.END)
    huffed = huffman()
    through(huffed[0])
    text.insert(tk.END, "正在生成二进制文件...\n")
    text.update()
    text.see(tk.END)
    rewrite_dic(outpath)
    rewrite_com(content, outpath)
    percent = 100 * (os.path.getsize(outpath + '/compressed.out') / float(os.path.getsize(path)))
    text.insert(tk.END, "压缩完成！ 压缩率：%d%%\n" % percent)
    text.update()
    text.see(tk.END)

def depress(text):
    global outpath
    global dict
    global path
    global dicreaded
    # dictionary = raw_input("请输入字典路径：")
    # text = raw_input("请输入压缩文件路径：")
    # goingto = raw_input("请输入解压后的文件的存储位置：")
    # text.insert(tk.END, "请稍候...")
    if path == '':
        text.insert(tk.END, "请选择压缩文件！\n")
        return
    elif outpath == '':
        text.insert(tk.END, "请输入解压后的文件的存储位置！\n")
        return
    elif dict == '':
        text.insert(tk.END, "请选择字典路径！\n")
        return
    elif not os.path.exists(path):
        text.insert(tk.END, "[Error]压缩文件不存在！\n")
        return
    elif not os.path.exists(outpath):
        text.insert(tk.END, "[Error]解压目标路径不存在！\n")
        return
    elif not os.path.exists(dict):
        text.insert(tk.END, "[Error]字典文件不存在！\n")
        return
    d = open(dict).read()
    txt = open(path).read()
    text.insert(tk.END, "正在构建字典树...\n")
    text.update()
    text.see(tk.END)
    l = sep(d)
    root = dictree(l)
    text.insert(tk.END, "正在解析二进制文件...\n")
    text.update()
    text.see(tk.END)
    ans = decode(txt)
    text.insert(tk.END, "正在解压文件...\n")
    text.update()
    text.see(tk.END)
    res = open(outpath+'/depressed.txt', 'w')
    findword(text, res, root, ans)
    # res.write(dec)

    text.update()
    text.see(tk.END)

window = tk.Tk()
window.title('文本压缩')
window.geometry('600x400')

l1c = tk.StringVar()
l2c = tk.StringVar()
l3c = tk.StringVar()

# lb = tk.Label(root, text='')
# lb.pack()
# entry = tk.Entry(root, textvariable = path)
# entry.pack()
l1 = tk.Label(window, textvariable=l1c, wraplength = 400)
l1.grid(row = 0, column = 1, columnspan = 9)
# l1.pack()
button = tk.Button(window, text="选择文件", command=partial(getfile, l1c), width = 10)
button.grid(row = 0, column = 0)
# button.pack()

l2 = tk.Label(window, textvariable=l2c, wraplength = 400)
l2.grid(row = 1, column = 1, columnspan = 9)
# l2.pack()
button2 = tk.Button(window, text="选择字典", command=partial(getdict, l2c), width = 10)
button2.grid(row = 1, column = 0)
# button2.pack()

l3 = tk.Label(window, textvariable=l3c, wraplength = 400)
l3.grid(row = 2, column = 1, columnspan = 9)
# l3.pack()
button3 = tk.Button(window, text="选择输出路径", command=partial(getoutpath, l3c), width = 10)
button3.grid(row = 2, column = 0)
# button3.pack()

l4 = tk.Label(window, bg = 'white', width = 10, height = 1)
l4.grid(row = 3, column = 0,  columnspan = 10)

text = tk.Text(window, width=40, height=50)
button4 = tk.Button(window,text="压缩", command=partial(compress, text))
button4.grid(row = 4, column = 0)
# button4.pack()
button5 = tk.Button(window,text="解压", command=partial(depress, text))
button5.grid(row = 5, column = 0)
# button5.pack()
text.grid(row = 6, column = 0, columnspan = 5, rowspan = 2, sticky = 'w')
# the_dic = tk.Text(window, width=45, height=50)
# the_dic.grid(row = 6, column = 5, columnspan = 5, rowspan = 2, sticky = 'w')
# text.pack()

window.mainloop()

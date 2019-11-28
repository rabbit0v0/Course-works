# -*- coding: UTF-8 -*-
import os
has = {}
dic = []
# dec = ''


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


def compress():
    path = raw_input("请输入文件路径：")
    txt = open(path)
    content = txt.read()
    getting = raw_input("请输入压缩文件的存储位置：")
    cal(content)
    print "正在构建字典树..."
    huffed = huffman()
    through(huffed[0])
    print "正在生成二进制文件..."
    rewrite_dic(getting)
    rewrite_com(content, getting) 
    percent = 100 * (os.path.getsize(getting + '/compressed.out') / float(os.path.getsize(path)))
    print "压缩完成 压缩率：%d%%" % percent




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


def findword(out, root, txt):
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
            print "解压进度：%d%%" % (i * 25)
        tmp = searchtree(out, tmp, txt[num])
        num += 1
        if tmp == None:
            tmp = root


def decode(txt):
    res = ''
    for i in txt:
        s = bin(ord(i))
        s = s[2:]
        while len(s) < 8:
            s = '0' + s
        res += s

    return res


def depress():
    global dec
    dictionary = raw_input("请输入字典路径：")
    text = raw_input("请输入压缩文件路径：")
    goingto = raw_input("请输入解压后的文件的存储位置：")
    print "请稍候..."
    dict = open(dictionary).read()
    txt = open(text).read()
    l = sep(dict)
    print "正在构建字典树..."
    root = dictree(l)
    print "正在解析二进制文件..."
    ans = decode(txt)
    print "正在解压文件..."
    res = open(goingto+'/depressed.txt', 'w')
    findword(res, root, ans)
    # res.write(dec)
    print "解压已完成"


def main():

    choice = input("[1]压缩\n[2]解压\n")
    if choice == 1:
        compress()
    elif choice == 2:
        depress()
    else:
        return


main()
# -*- coding: UTF-8 -*-
import Tkinter
data = open("data.txt", "r")
educated = {'Bachelors', 'Masters', 'Doctorate'}
tot = 0
edu_sum = 0
whi_sum = 0
male_sum = 0
sum_of_edu = 0
sum_of_unedu = 0
sum_of_whi = 0
sum_of_nonwhi = 0
sum_of_female = 0
sum_of_male = 0


def edu(k, p):
    global edu_sum, sum_of_edu, sum_of_unedu
    if k == "Bachelors" or k == "Masters" or k == "Doctorate":
        edu_sum += 1
        if p == ">50K.":
            sum_of_edu += 1
        return
    if p == ">50K.":
        sum_of_unedu += 1


def race(k ,p):
    global whi_sum, sum_of_whi, sum_of_nonwhi
    if k == 'White':
        whi_sum += 1
        if p == '>50K.':
            sum_of_whi += 1
        return
    if p == '>50K.':
        sum_of_nonwhi += 1


def sex(k, p):
    global male_sum, sum_of_male, sum_of_female
    if k == 'Male':
        male_sum += 1
        if p == '>50K.':
            sum_of_male += 1
        return
    if p == '>50K.':
        sum_of_female += 1


while True:
    text = data.readline()
    if text == "":
        break
    tot += 1
    sa = text.split(",")[14].split()[0]
    edu(text.split(",")[3].split()[0], sa)
    race(text.split(",")[8].split()[0], sa)
    sex(text.split(",")[9].split()[0], sa)
edurate = sum_of_edu/float(edu_sum)
whirate = sum_of_whi/float(whi_sum)
malerate = sum_of_male/float(male_sum)
root = Tkinter.Tk()
canvas = Tkinter.Canvas(root, width = 320, height = 820, bg = 'white')
canvas.create_line((50, 250-5), (50, 50-5), fill = 'black', arrow='last')
canvas.create_line((50, 250-5), (250, 250-5), fill = 'black', arrow='last')
canvas.create_rectangle((80, 250-5-(edurate*200)), (100, 250-5), fill = 'black')
canvas.create_rectangle((100, 250-5-(1-edurate)*200), (120, 250-5))
canvas.create_rectangle((170, 250-5-(1-sum_of_unedu/float(tot-edu_sum))*200),(190, 250-5))
canvas.create_rectangle((150, 250-5-sum_of_unedu/float(tot-edu_sum)*200), (170, 250-5), fill = 'black')

canvas.create_line((50, 500-5), (50, 300-5), fill = 'black', arrow='last')
canvas.create_line((50, 500-5), (250, 500-5), fill = 'black', arrow='last')
canvas.create_rectangle((80, 500-5-sum_of_whi/float(whi_sum)*200), (100, 500-5), fill = 'black')
canvas.create_rectangle((100, 500-5-(1-(sum_of_whi/float(whi_sum)))*200), (120, 500-5))
canvas.create_rectangle((170, 500-5-(1-sum_of_nonwhi/float(tot-whi_sum))*200),(190, 500-5))
canvas.create_rectangle((150, 500-5-sum_of_nonwhi/float(tot-whi_sum)*200), (170, 500-5), fill = 'black')

canvas.create_line((50, 745), (50, 545), fill = 'black', arrow='last')
canvas.create_line((50, 745), (250, 745), fill = 'black', arrow='last')
canvas.create_rectangle((80, 745-sum_of_male/float(male_sum)*200), (100, 745), fill = 'black')
canvas.create_rectangle((100, 745-(1-(sum_of_male/float(male_sum)))*200), (120, 745))
canvas.create_rectangle((170, 745-(1-sum_of_female/float(tot-male_sum))*200),(190, 745))
canvas.create_rectangle((150, 745-sum_of_female/float(tot-male_sum)*200), (170, 745), fill = 'black')

canvas.create_text(250, 30, anchor = 'sw', text = "收入>50K")
canvas.create_rectangle((230, 20), (240, 25), fill = 'black')
canvas.create_text(250, 50, anchor = 'sw', text = "收入<=50K")
canvas.create_rectangle((230, 40), (240, 45))

canvas.create_text(70, 280, anchor = 'sw', text = "有学位的人\n%.2f" % edurate)
canvas.create_text(150, 280, anchor = 'sw', text = "其他人\n%.2f" % (1-edurate))

canvas.create_text(85, 530, anchor = 'sw', text = "白人\n%.2f" % whirate)
canvas.create_text(150, 530, anchor = 'sw', text = "其他人\n%.2f" % (1-whirate))

canvas.create_text(85, 780, anchor = 'sw', text = "男人\n%.2f" % malerate)
canvas.create_text(155, 780, anchor = 'sw', text = "女人\n%.2f" % (1-malerate))
canvas.pack()
Tkinter.mainloop()



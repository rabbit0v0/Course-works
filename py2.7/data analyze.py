set0 = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

data1 = raw_input("a:")
data1.split('\t')
data2 = raw_input("b:")
data2.split('\t')
for i in range(len(data1)):
    if data1[i] == "1":
        if data2[i] == "1":
            set0[0] += 1
        if data2[i] == "2":
            set0[1] += 1
        if data2[i] == "3":
            set0[2] += 1
        if data2[i] == "4":
            set0[3] += 1
        if data2[i] == "5":
            set0[4] += 1
    if data1[i] == "2":
        if data2[i] == "1":
            set0[5] += 1
        if data2[i] == "2":
            set0[6] += 1
        if data2[i] == "3":
            set0[7] += 1
        if data2[i] == "4":
            set0[8] += 1
        if data2[i] == "5":
            set0[9] += 1
    if data1[i] == "3":
        if data2[i] == "1":
            set0[10] += 1
        if data2[i] == "2":
            set0[11] += 1
        if data2[i] == "3":
            set0[12] += 1
        if data2[i] == "4":
            set0[13] += 1
        if data2[i] == "5":
            set0[14] += 1
print set0
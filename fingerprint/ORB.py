# coding:UTF-8
import cv2
import numpy as np
import h5py
import matplotlib.pyplot as plt
from svmutil import *
from svm import *


def read(Str):
    addr = ''
    for i in Str:
        if i == '[':
            continue
        if i == ']':
            continue
        addr = addr+i
    return addr


def conv(Str):
    for i in Str:
        if i == '[':
            continue
        if i == ']':
            continue
        if i == '0':
            return 0
        if i == '1':
            return 1


def reshape1(mat):
    if mat.shape[0] != 100:
        tmp = np.zeros(32)
        tmp = [tmp]
        for i in range(100-mat.shape[0]):
            mat = np.append(mat, tmp, axis=0)
    return mat


ORB = []
lableMatrix = []
root = '/Users/jinxiufen/Downloads/fingerprint/data/'
model = svm_load_model(root+"train_model2.m")
for test_num in range(1, 26):
    name = "%03d" % test_num
    file = h5py.File(root+'gen_hdf5/hdf5_file/test/test_hdf5_part' + name + '_perblock100.h5', 'r')
    for i in range(file['img'].shape[0]):
        data1 = file['img'][i]
        data2 = file['img_p'][i]
        label = file['label'][i]
        addr1 = root + 'test/KD4A' + read(str(data1)) + 'JPG'
        addr2 = root + 'test/KD4A' + read(str(data2)) + 'JPG'
        lableMatrix.append(float(conv(str(label))))
        img1 = cv2.imread(addr1, 0)
        img2 = cv2.imread(addr2, 0)
        orb = cv2.ORB_create(nfeatures=100)
        kp1 = orb.detect(img1, None)
        kp2 = orb.detect(img2, None)
        kp1, des1 = orb.compute(img1, kp1)
        kp2, des2 = orb.compute(img2, kp2)
        des1 = reshape1(des1)
        des2 = reshape1(des2)
        des1 = np.reshape(des1, (1, 3200))
        des2 = np.reshape(des2, (1, 3200))
        ORB.append(np.hstack((des1, des2))[0])

lableMatrix = np.array(lableMatrix).T
p_label, p_acc, p_val = svm_predict(lableMatrix, ORB, model)
print p_label


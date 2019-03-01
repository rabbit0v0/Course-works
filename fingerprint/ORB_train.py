import numpy as np
import cv2
from matplotlib import pyplot as plt
import h5py
from svmutil import *


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


lableMatrix = []
ORB = []
root = '/Users/jinxiufen/Downloads/fingerprint/data/'
for test_num in range(1, 109):
    print test_num
    name = "%03d" % test_num
    file = h5py.File(root+'gen_hdf5/hdf5_file/train/train_hdf5_part' + name + '_perblock100.h5', 'r')
    for i in range(file['img'].shape[0]):
        data1 = file['img'][i]
        data2 = file['img_p'][i]
        label = file['label'][i]
        addr1 = root + 'test/KD4A' + read(str(data1)) + 'JPG'
        addr2 = root + 'test/KD4A' + read(str(data2)) + 'JPG'
        lableMatrix.append(float(conv(str(label))))
        # print(float(conv(str(label))))
        img1 = cv2.imread(addr1, 0)
        img2 = cv2.imread(addr2, 0)
        orb = cv2.ORB_create(nfeatures=100)
        kp1 = orb.detect(img1, None)
        kp2 = orb.detect(img2, None)
        kp1, des1 = orb.compute(img1, kp1)
        kp2, des2 = orb.compute(img2, kp2)
        des1 = reshape1(des1)
        des2 = reshape1(des2)
        des1 = np.reshape(des1, (3200))
        des2 = np.reshape(des2, (3200))
        # print(np.hstack((des1, des2))[0])
        ORB.append(np.hstack((des1, des2)))

lableMatrix = np.array(lableMatrix).T
ORB = np.array(ORB)

model = svm_train(lableMatrix, ORB)
svm_save_model(root+"train_model2.m", model)
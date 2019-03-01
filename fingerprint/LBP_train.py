# coding:UTF-8

import scipy.io as scio
from scipy.stats import itemfreq
from skimage.feature import local_binary_pattern
import skimage
import numpy as np
import h5py
import matplotlib.pyplot as plt
from sklearn import svm


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


# set for LBP
radius = 3
n_points = 8 * radius

# get matrix
root = '/Users/jinxiufen/Downloads/fingerprint/data/'
LBP = []
lableMatrix = []
for test_num in range(1, 109):
    print test_num
    name = "%03d" % test_num
    file = h5py.File(root+'gen_hdf5/hdf5_file/train/train_hdf5_part' + name + '_perblock100.h5', 'r')
    np.set_printoptions(threshold='nan')
    for i in range(file['img'].shape[0]):
        data1 = file['img'][i]
        data2 = file['img_p'][i]
        label = file['label'][i]
        addr1 = root + 'test1/KD4A' + read(str(data1)) + 'JPG'
        addr2 = root + 'test1/KD4A' + read(str(data2)) + 'JPG'
        lableMatrix.append(float(conv(str(label))))
        image1 = plt.imread(addr1)
        image1 = skimage.color.rgb2gray(image1)
        image2 = plt.imread(addr2)
        image2 = skimage.color.rgb2gray(image2)
        lbp1 = local_binary_pattern(image1, n_points, radius, method='uniform')
        x1 = itemfreq(lbp1.ravel())
        hist1 = x1[:, 1] / sum(x1[:, 1])
        lbp2 = local_binary_pattern(image2, n_points, radius, method='uniform')
        x2 = itemfreq(lbp2.ravel())
        hist2 = x2[:, 1] / sum(x2[:, 1])
        LBP.append(np.hstack((hist1, hist2)))
    # print file['img'].shape[0]


lableMatrix = np.array(lableMatrix).T
print lableMatrix
# print LBP
# model = svm_train(lableMatrix, LBP)
# svm_save_model(root+"train_model.m", model)

clf = svm.SVC(C=1.0, cache_size=200, class_weight=None, coef0=0.0,
    decision_function_shape='ovr', degree=3, gamma='auto', kernel='rbf',
    max_iter=-1, probability=False, random_state=None, shrinking=True,
    tol=0.00001, verbose=True)
clf.fit(X=LBP, y=lableMatrix)
import pickle
with open('LBP_model.pkl', 'wb') as save:
    pickle.dump(clf, save)
# coding:UTF-8

import scipy.io as scio
from scipy.stats import itemfreq
from skimage.feature import local_binary_pattern
import skimage
import numpy as np
import h5py
import matplotlib.pyplot as plt
from sklearn.svm import LinearSVC
from skimage import feature
import cv2

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

class LocalBinaryPatterns:
    def __init__(self, numPoints, radius):
        # store the number of points and radius
        self.numPoints = numPoints
        self.radius = radius

    def describe(self, image, eps=1e-7):
        # compute the Local Binary Pattern representation
        # of the image, and then use the LBP representation
        # to build the histogram of patterns
        lbp = feature.local_binary_pattern(image, self.numPoints,
                                           self.radius, method="uniform")
        # default? uniform?
        (hist, _) = np.histogram(lbp.ravel(),
                                 bins=np.arange(0, self.numPoints + 3),
                                 range=(0, self.numPoints + 2))

        # normalize the histogram
        hist = hist.astype("float")
        hist /= (hist.sum() + eps)

        # return the histogram of Local Binary Patterns
        return hist

# set for LBP
radius = 3
n_points = 8 * radius

desc = LocalBinaryPatterns(n_points, radius)

# get matrix
root = '/Users/jinxiufen/Downloads/fingerprint/data/'
LBP = []
lableMatrix = []
for test_num in range(1, 109):
    print test_num
    name = "%03d" % test_num
    file = h5py.File(root+'gen_hdf5/hdf5_file/train/train_hdf5_part' + name + '_perblock100.h5', 'r')
    for i in range(file['img'].shape[0]):
        data1 = file['img'][i]
        data2 = file['img_p'][i]
        label = file['label'][i]
        addr1 = root + 'test1/KD4A' + read(str(data1)) + 'JPG'
        addr2 = root + 'test1/KD4A' + read(str(data2)) + 'JPG'
        lableMatrix.append(float(conv(str(label))))
        image1 = cv2.imread(addr1, 0)
        image2 = cv2.imread(addr2, 0)
        hist1 = desc.describe(image1)
        hist2 = desc.describe(image2)
        LBP.append(np.hstack((hist1, hist2)))

    # ----------- Your Initial Code -----------
        # image1 = plt.imread(addr1)
        # image1 = skimage.color.rgb2gray(image1)
        # image2 = plt.imread(addr2)
        # image2 = skimage.color.rgb2gray(image2)
        # lbp1 = local_binary_pattern(image1, n_points, radius, method='uniform')
        # x1 = itemfreq(lbp1.ravel())
        # hist1 = x1[:, 1] / sum(x1[:, 1])
        # lbp2 = local_binary_pattern(image2, n_points, radius, method='uniform')
        # x2 = itemfreq(lbp2.ravel())
        # hist2 = x2[:, 1] / sum(x2[:, 1])
        # LBP.append(np.hstack((hist1, hist2)))
        # print np.hstack((hist1, hist2))
    # print file['img'].shape[0]
    # ----------- Your Initial Code -----------

# Train LinearSVC
model = LinearSVC(C=100.0, random_state=42, verbose=True, max_iter=50000)
model.fit(LBP, lableMatrix)

# Save model to mua.pkl
import pickle
with open('mua.pkl', 'wb') as save:
    pickle.dump(model, save)

# Try validation (Not on test set)
pred = model.predict(LBP)
print('Pred: ', pred)
print('Truth: ', lableMatrix)
tot = len(LBP)
nice = np.sum(1 - np.abs(pred-np.array(lableMatrix)))
print('Accuracy:', nice / tot)

# rand = []
# for i in range(2000):
#     r = np.random.random(LBP[0].shape)
#     rand.append(r / np.sum(r))
# pred = model.predict(rand)
# print(pred)
# print(np.sum(pred))

# ----------- Your Initial Code -----------
# lableMatrix = np.array(lableMatrix).T
# print LBP
# model = svm_train(lableMatrix, LBP)
# svm_save_model(root+"train_model.m", model)
# clf = svm.SVC()
# clf.fit(LBP, lableMatrix)
# ----------- Your Initial Code -----------
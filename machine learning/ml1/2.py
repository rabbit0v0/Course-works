#!/usr/bin/python
# coding=utf-8
from numpy import *
import matplotlib.pyplot as plt


# generate data
def dataSet():
    datMat = zeros([90, 2])
    x_mean = [1, 3, 8]
    y_mean = [1, 5, 2]
    x = []
    y = []
    for meanX in x_mean:
        xx = random.normal(meanX, 1, [30, 1])
        x.extend(xx)
    for meanY in y_mean:
        yy = random.normal(meanY, 1, [30, 1])
        y.extend(yy)
    for i in range(90):
        datMat[i, 0] = x[i]
        datMat[i, 1] = y[i]

    datMat = array(datMat)
    return datMat


def distance(a, b):
    return sqrt(sum(power(a - b, 2))) 


def randCent(dataSet, k):
    n = shape(dataSet)[1]
    centroids = mat(zeros((k, n)))
    for j in range(n):
        minJ = min(dataSet[:, j])
        maxJ = max(dataSet[:, j])
        rangeJ = float(maxJ - minJ)
        centroids[:, j] = minJ + rangeJ * random.rand(k, 1)
    return centroids


def KCL(dataSet, k, lr=1, penalty=0.05):
    m = shape(dataSet)[0]
    dists = mat(zeros((m, 2)))
    centroids = randCent(dataSet, k)
    flag = False
    while not flag:
        for i in range(m):
            minDist = inf
            minIndex = -1
            for j in range(k):
                distJI = distance(centroids[j, :], dataSet[i, :])
                if distJI < minDist:
                    minDist = distJI
                    minIndex = j
            if dists[i, 0] != minIndex:
                flag = False
            else:
                flag = True
            dists[i, :] = minIndex, minDist ** 2

        for cent in range(k):
            # penalize the reval
            secDist = inf
            secIndex = -1
            for i in range(k):
                if i != cent:
                    dist = distance(centroids[cent, :], centroids[i, :])
                    if dist < secDist:
                        secDist = dist
                        secIndex = i

            ptsInClust = dataSet[nonzero(dists[:, 0] == cent)[0]]  # points in cluster

            centroids[cent, :] = centroids[cent, :] + lr * (mean(ptsInClust, axis=0) - centroids[cent, :])
            centroids[secIndex, :] = centroids[secIndex, :] - lr * penalty * (
                        mean(ptsInClust, axis=0) - centroids[secIndex, :])

    return centroids, dists


datMat = dataSet()

myCentroids, dists = KCL(datMat, 3)

mu_x = [0, 0, 0]
mu_y = [0, 0, 0]
color = ['purple', 'gray', 'pink']
for i in range(3):
    mu_x[i] = myCentroids[i, 0]
    mu_y[i] = myCentroids[i, 1]
for i in range(3):
    plt.scatter(datMat[i * 30:i * 30 + 30, 0], datMat[i * 30:i * 30 + 30:, 1], c=color[i], alpha=0.6)

plt.scatter(mu_x, mu_y, c='r', s=50)
plt.show()
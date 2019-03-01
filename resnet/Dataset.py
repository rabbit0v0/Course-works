import numpy as np
import json
import tensorflow as tf
import random
import copy

class Dataset(object):
    def __init__(self, txt_path, dic_path, batch_size):
        self.train_index = 0
        self.test_index = 0
        self.train_sum = 0
        self.test_sum = 0

        self.txt_path = txt_path
        self.dic_path = dic_path
        self.batch_size = batch_size
        self.fasta = []
        self.ss = []
        self.dic = {}
        self.dictionary()
        self.preprocess()


    def preprocess(self):
        with open(self.txt_path + 'ss.txt', 'r') as f:
            label_lines = json.loads(f.readline())

        with open(self.txt_path + 'fasta_1mer.txt', 'r') as f:
            lines = f.readlines()
            assert len(lines) == len(label_lines)
            for k in range(len(lines)):
                # if k == 200:
                #     break
                split = lines[k].split()
                labels = label_lines[k]
                length = len(split)
                for i in range(1, length - 1):
                    tmp = []
                    tmp.append(self.dic[split[i - 1]])
                    tmp.append(self.dic[split[i]])
                    tmp.append(self.dic[split[i + 1]])
                    self.fasta.append(np.array(tmp).astype('float32'))
                    self.ss.append(np.array([labels[i]]).astype('int32'))
            # for i in range(np.shape(self.ss)[0]):
            #     for r in range(3660 - np.shape(self.ss[i])[0]):
            #         self.ss[i].append('0')
        self.train_sum = len(self.fasta)
        self.test_sum = len(self.fasta)

    def shuffle(self):
        combine = list(zip(copy.deepcopy(self.fasta), copy.deepcopy(self.ss)))
        random.shuffle(combine)
        self.fasta[:], self.ss[:] = zip(*combine)

    def dictionary(self):
        with open(self.dic_path, 'r') as f:
            for line in f.readlines():
                i = line.split()
                # self.dic[i[0]] = i[1:]
                self.dic[i[0]] = np.array(i[1:]).astype('float32')
        self.dic['0'] = np.zeros(128,)

    def next_train_batch(self):
        if self.train_index + self.batch_size > self.train_sum - 1:
            self.train_index = 0
        fs = self.fasta[self.train_index:self.train_index + self.batch_size]
        s = self.ss[self.train_index:self.train_index + self.batch_size]
        self.train_index += self.batch_size
        return np.array(fs).reshape(self.batch_size, 3, 128, 1), np.array(s).reshape((self.batch_size)) - 1

    def next_test_batch(self):
        if self.test_index + self.batch_size > self.test_sum - 1:
            self.test_index = 0
        fs = self.fasta[self.test_index:self.test_index + self.batch_size]
        s = self.ss[self.test_index:self.test_index + self.batch_size]
        self.test_index += self.batch_size
        return np.array(fs).reshape(self.batch_size, 3, 128, 1), np.array(s).reshape((self.batch_size)) - 1

    def refresh(self):
        self.shuffle()
        self.train_index = 0
        self.test_index = 0




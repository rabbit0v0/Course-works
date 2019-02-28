//
//  queue.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/19.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int maxsize = 1000, front = 0, back = 0, size = 0;
int* l = new int [maxsize];

void add(int x){
    if (size == maxsize - 1){
        int* _l = new int [2 * maxsize];
        for (int i = 0; i < maxsize - front; ++i){
            _l[i] = l[i + front];
        }
        for (int i = 0; i < back; ++i){
            _l[i + maxsize - front] = l[i];
        }
        front = 0;
        back = maxsize;
        _l[maxsize] = x;
        size++;
        maxsize *= 2;
        delete []l;
        l = _l;
        return;
    }
    l[++back] = x;
    size++;
}

void pop(){
    if (front != maxsize - 1){
        front = front + 1;
        size--;
    }
    else{
        front = 0;
        size--;
    }
}

int query(){
    if (front == maxsize - 1)
        return l[0];
    return l[front + 1];
}
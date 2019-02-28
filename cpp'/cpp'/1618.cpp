//
//  1618.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/25.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, k, a[100005];
int head = -1, tail = -1, l[100001];

void pushmax(int i){
    if (tail == head){
        l[++tail] = i;
        return;
    }
    if (a[l[tail]] < a[i]){
        tail--;
        pushmax(i);
        return;
    }
    l[++tail] = i;
}

void pushmin(int i){
    if (tail == head){
        l[++tail] = i;
        return;
    }
    if (a[l[tail]] > a[i]){
        tail--;
        pushmin(i);
        return;
    }
    l[++tail] = i;
}

void pop(int i){
    if (l[head + 1] == i){
        head++;
    }
}

int main(){
    scanf("%d", &n);
    scanf("%d", &k);
    for (int i = 0; i < n; ++i){
        scanf("%d", &a[i]);
        if (i < k)
            pushmin(i);
    }
    printf("%d", a[l[0]]);
    int m = 1;
    while (m < n - k + 1) {
        pop(m - 1);
        pushmin(m + k - 1);
        printf(" %d", a[l[head + 1]]);
        m++;
    }
    printf("\n");
    head = -1;
    tail = -1;
    for (int i = 0; i < k; ++i){
        pushmax(i);
    }
    printf("%d", a[l[0]]);
    m = 1;
    while (m < n - k + 1) {
        pop(m - 1);
        pushmax(m + k - 1);
        printf(" %d", a[l[head + 1]]);
        m++;
    }
}
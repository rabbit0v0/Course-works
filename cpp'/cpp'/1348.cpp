//
//  1348.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int m[1000000], w[1000000], l[10001];
double men, women;
int headm, headw, tailm, tailw, waitm, waitw;

void pushm(int x){
    m[tailm++] = x;
}

void pushw(int x){
    w[tailw++] = x;
}

void popm(){
    if (headm == tailm)
        return;
    headm++;
}

void popw(){
    if (headw == tailw)
        return;
    headw++;
}

bool emptym(){
    return headm == tailm;
}

bool emptyw(){
    return headw == tailw;
}

int min(int a, int b){
    if (a <= b)
        return a;
    return b;
}

void wait(int j){
    int peo = min(tailm - headm, tailw - headw);
    for (int i = 0; i < peo; ++i){
        waitm += (l[j] - m[headm]);
        waitw += (l[j] - w[headw]);
        popm();
        popw();
    }
}

int divide(int* a,int low,int high){
    int k = a[low];
    do{
        while (low < high && a[high] >= k)
            --high;
        if (low < high){
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <= k)
            ++low;
        if (low < high){
            a[high] = a[low];
            --high;
        }
    }while(low != high);
        a[low] = k;
        return low;
}

void sort(int* a, int low, int high){
    int mid;
    if (low >= high)
        return;
    mid = divide(a, low, high);
    sort(a, low, mid - 1);
    sort(a, mid + 1, high);
}

int main(){
    int n, man;
    int k = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        int k;
        scanf("%d", &k);
        l[i] = l[i - 1] + k;
    }
    
    scanf("%d", &man);
    
    for (int i = 0; i < man; ++i){
        int sex, t;
        scanf("%d", &sex);
        scanf("%d", &t);
        if (sex == 1){
            men++;
            pushm(t);
        }
        else if (sex == 2){
            women++;
            pushw(t);
        }
    }
    
    sort(m, 0, men - 1);
    sort(w, 0, women - 1);
    
    for (int i = 0; i < n; ++i){
        while (m[k] <= l[i] && w[k] <= l[i]){
            tailm = ++k;
            tailw = k;
        }
        wait(k);
    }
    
    double avem = waitm / men;
    double avew = waitw / women;
    
    printf("%.2f ", avem);
    printf("%.2f", avew);
    return 0;
}
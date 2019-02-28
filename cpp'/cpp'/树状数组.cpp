//
//  树状数组.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/11.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int N, M;
int a[100001], c[100001];

int lowbit(int p){
    return (p&(-p));
}

void add(int p, int x){
    while (p < N){
        c[p] += x;
        p += lowbit(p);
    }
}

int query(int p){
    int tmp = 0;
    while(p){
        tmp += c[p];
        p -= lowbit(p);
    }
    return tmp;
}

int main(){
    scanf("%d", &N);
    for (int i = 0; i < N; ++i){
        scanf("%d", &a[i]);
        add(i, a[i]);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; ++i){
        char c;
        int l, x;
        scanf("%c", &c);
        while (c != 'Q' || c != 'C')
            scanf("%c", &c);
        scanf("%d%d", &l, &x);
        if (c == 'C'){
            add(l, x - a[i]);
            a[i] = x;
        }
        if (c == 'Q'){
            int sum = query(x) - query(l - 1);
            printf("%d\n", sum);
        }
    }
}
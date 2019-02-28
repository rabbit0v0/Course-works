//
//  1620.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/6.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, q;
int l[60005][32];
int l0[60005];

int lowbit(int p){
    return (p&(-p));
}

void add(int r, int p, int x){
    while (p <= n){
        l[p][r] += x;
        p += lowbit(p);
    }
}

int query(int r, int p){
    int tmp = 0;
    while(p){
        tmp += l[p][r];
        p -= lowbit(p);
    }
    return tmp;
}

void exchange(int x, int y){
    int tem = l0[x];
    for (int i = 1; i < 32; ++i){
        int ch = y % 2 - tem % 2;
        add(i, x, ch);
        y /= 2;
        tem /= 2;
    }
}

void ask(int l, int r){
    long long sum = 0;
    long long base = 1;
    for (int k = 1; k < 32; ++k){
        int a = query(k, r) - query(k, l - 1);
        int b = r - l - a + 1;
        sum += a * b * base;
        sum %= 1000000007;
        base *= 2;
    }
    printf("%lld\n", sum);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        int tem, j = 1;
        scanf("%d", &tem);
        l0[i] = tem;
        while (tem != 0){
            add(j, i, tem % 2);
            tem = tem / 2;
            j++;
        }
    }
        scanf("%d", &q);
    for (int i = 1; i <= q; ++i){
        int op;
        scanf("%d", &op);
        if (op == 1){
            int x, y;
            scanf("%d%d", &x, &y);
            exchange(x, y);
            l0[x] = y;
        }
        if (op == 0){
            int l, r;
            scanf("%d%d", &l, &r);
            ask(l, r);
        }
    }
    
}

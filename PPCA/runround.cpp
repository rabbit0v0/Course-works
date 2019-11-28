//
//  runround.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/16.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:runround
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
using namespace std;
int M, len, a[10];
int check(int k){
    bool now[10] = {0};
    int m = 0;
    while (k > 0){
        if (!(k % 10)) return 0;
        a[++m] = k % 10;
        k /= 10;
    }
    len = m;
    for (int i = 1; i <= len; ++i){
        if (now[a[i]] == 1)
            return 0;
        else now[a[i]] = 1;
    }
    for (int i = 1; i <= len / 2; ++i){
        swap(a[i], a[len - i + 1]);
    }
    a[0] = a[len];
    return 1;
}

int main(){
    freopen("runround.in","r",stdin);
    freopen("runround.out","w",stdout);
    cin >> M;
    for (int i = M + 1; i <= 65535000; ++i){
        if (!check(i)) continue;
        int k = 1, j = 1;
        bool flag[10] = {0};
        while (k <= len){
            if (flag[(j + a[j]) % len]) break;
            else flag[(j + a[j]) % len] = 1;
            k++;
            j = (j + a[j]) % len;
        }
        k = 0;
        for (int m = 0; m < 10; ++m){
            if (flag[m] == 1)
                k++;
        }
        if (k >= len){
            cout << i << '\n';
            return 0;
        }
    }
}

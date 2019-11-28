//
//  frac1.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/15.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: frac1
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int N, sum;
struct re{
    int son, mot;
    re(){
        son = 0, mot = 0;
    }
};
re res[100000];

bool cmp(re a, re b){
    float aa = (float)a.son / (float)a.mot;
    float bb = (float)b.son / (float)b.mot;
    return aa < bb;
}

int cal(int x, int y){
    int z = y;
    while (x % y != 0){
        z = x % y;
        x = y;
        y = z;
    }
    return z;
}

int main(){
    freopen("frac1.in","r",stdin);
    freopen("frac1.out","w",stdout);
    int a = 1, b = 2;
    cin >> N;
    cout << "0/1\n";
    while (b <= N){
        for (a = 1; a < b; ++a){
            if (cal(b, a) == 1){
                res[sum].son = a;
                res[sum++].mot = b;
            }
        }
        b++;
    }
    sort(res, res + sum, cmp);
    for (int i = 0; i < sum; ++i){
        cout << res[i].son << '/' << res[i].mot << '\n';
    }
    cout << "1/1" << '\n';
}

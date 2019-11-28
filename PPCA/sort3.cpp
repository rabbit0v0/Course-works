//
//  sort3.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/15.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: sort3
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int N, res;
int data0[1005], data[1005];
int one, two, three;

int main(){
    freopen("sort3.in","r",stdin);
    freopen("sort3.out","w",stdout);
    int two0 = 10000, three0 = 10000;
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> data[i];
        data0[i] = data[i];
    }
    sort(data0, data0 + N);
    for (int i = 0; i < N; ++i){
        if (two0 == 10000 && data0[i] == 2)
            two0 = i;
        else if (three0 == 10000 && data0[i] == 3){
            three0 = i;
            break;
        }
    }
    for (int i = 0; i < min(three0, N); ++i){
        if (data[i] == 3) three++;
        else if (data[i] == 2 && i < two0) two++;
        else if (data[i] == 1 && i >= two0) one++;
    }
    res = three + max(two, one);
    cout << res << '\n';
}

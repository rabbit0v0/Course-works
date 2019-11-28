//
//  crypt1.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/12.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: crypt1
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int N, cant_be_muler, sum;
int dig[10];
bool exi[10];

int main(){
    freopen("crypt1.in", "r", stdin);
    freopen("crypt1.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; ++i){
        cin >> dig[i];
        exi[dig[i]] = 1;
    }
    sort(dig, dig + N);
    cant_be_muler = N;
    for (int i = 0; i < N; ++i){
        if (dig[i] * dig[0] > 10){
            cant_be_muler = i;
            break;
        }
    }
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            for (int k = 0; k < N; ++k){
                for (int l = 0; l < N; ++l){
                    for (int m = 0; m < N; ++m){
                        int a = dig[i] * 100 + dig[j] * 10 + dig[k];
                        int b = dig[l] * a;
                        int c = dig[m] * a;
                        int d = b + 10 * c;
                        bool flag = 1;
                        if (b >= 1000 || c >= 1000 || d >= 10000) continue;
                        while (b != 0){
                            if (!exi[b % 10]){
                                flag = 0;
                                break;
                            }
                            b /= 10;
                        }
                        while (c != 0){
                            if (!exi[c % 10]){
                                flag = 0;
                                break;
                            }
                            c /= 10;
                        }
                        while (d != 0){
                            if (!exi[d % 10]){
                                flag = 0;
                                break;
                            }
                            d /= 10;
                        }
                        if (!flag) continue;
                        sum++;
                    }
                }
            }
        }
    }
    cout << sum << '\n';
}

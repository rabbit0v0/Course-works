//
//  sprime.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/14.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: sprime
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <map>
using namespace std;
int N, k;
int tem[100000], tot, pri[100000],sum;
map<int, int> themap;

bool check(int x){
    bool flag = 1;
    for (int i = 2; i <= sqrt(x); ++i){
        if (x % i == 0)
            flag = 0;
    }
    return flag;
}

int main(){
    freopen("sprime.in", "r", stdin);
    freopen("sprime.out", "w", stdout);
    cin >> N;
    if (N == 1){
        cout << 2 << '\n' << 3 <<'\n' << 5 << '\n' << 7 <<'\n';
        return 0;
    }
    int high = 1;
    for (int i = 1; i < N; ++i){
        high *= 10;
    }
    int one[4] = {2, 3, 5, 7}, last[4] = {1, 3, 7, 9};
    for (int i = 0; i < 4; ++i){
        k = high;
        int tmp = one[i] * high;
        for (int j = 0; j < 4; ++j){
            int k1 = k / 10;
            int tmp0 = tmp + last[j] * k1;
            int t0 = tmp0;
            while (t0 % 10 == 0){
                t0 /= 10;
            }
            if (!check(t0))
                continue;
            for (int l = 0; l < 4; ++l){
                int k2 = k1 / 10;
                int tmp1 = tmp0 + last[l] * k2;
                int t1 = tmp1;
                while (t1 % 10 == 0){
                    t1 /= 10;
                }
                if (!check(t1))
                    continue;
                for (int m = 0; m < 4; ++m){
                    int k3 = k2 / 10;
                    int tmp2 = tmp1 + last[m] * k3;
                    int t2 = tmp2;
                    while (t2 % 10 == 0){
                        t2 /= 10;
                    }
                    if (!check(t2))
                        continue;
                    for (int n = 0; n < 4; ++n){
                        int k4 = k3 / 10;
                        int tmp3 = tmp2 + last[n] * k4;
                        int t3 = tmp3;
                        while (t3 % 10 == 0){
                            t3 /= 10;
                        }
                        if (!check(t3))
                            continue;
                        for (int o = 0; o < 4; ++o){
                            int k5 = k4 / 10;
                            int tmp4 = tmp3 + last[o] * k5;
                            int t4 = tmp4;
                            while (t4 % 10 == 0){
                                t4 /= 10;
                            }
                            if (!check(t4))
                                continue;
                            for (int p = 0; p < 4; ++p){
                                int k6 = k5 / 10;
                                int tmp5 = tmp4 + last[p] * k6;
                                int t5 = tmp5;
                                while (t5 % 10 == 0){
                                    t5 /= 10;
                                }
                                if (!check(t5))
                                    continue;
                                for (int q = 0; q < 4; ++q){
                                    int k7 = k6 / 10;
                                    int tmp6 = tmp5 + last[q] * k7;
                                    int t6 = tmp6;
                                    while (t6 % 10 == 0){
                                        t6 /= 10;
                                    }
                                    if (!check(t6))
                                        continue;
                                    if (themap.count(tmp6))
                                        continue;
                                    else{
                                        tem[tot++] = tmp6;
                                        themap[tmp6] = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (int i = 0; i < tot; ++i){
        cout << tem[i] << '\n';
    }
}

//
//  shopping.cpp
//  PPCA
//
//  Created by 施晓钰 on 20/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:shopping
 LANG: C++
 */
#include <stdio.h>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;
struct sale{
    int v, k[1002];
};
sale a[102];
struct need{
    int k, c, p;
};
need t[7];
int s, b;
int backpack[6][6][6][6][6];

int main(){
    freopen("shopping.in","r",stdin);
    freopen("shopping.out","w",stdout);
    cin >> s;
    for (int i = 1; i <= s; ++i){
        int num;
        cin >> num;
        for (int j = 1; j <= num; ++j){
            int no;
            cin >> no;
            cin >> a[i].k[no];
        }
        cin >> a[i].v;
    }
    cin >> b;
    for (int i = 1; i <= b; ++i){
        cin >> t[i].c >> t[i].k >> a[++s].v;
        a[s].k[t[i].c] = 1;
    }
    memset(backpack, 50, sizeof(backpack));
    backpack[0][0][0][0][0] = 0;
    for (int i = 1; i <= s; ++i){
        int m1 = a[i].k[t[1].c];
        int m2 = a[i].k[t[2].c];
        int m3 = a[i].k[t[3].c];
        int m4 = a[i].k[t[4].c];
        int m5 = a[i].k[t[5].c];
        for (int b1 = m1; b1 <= t[1].k; ++b1){
            for (int b2 = m2; b2 <= t[2].k; ++b2){
                for (int b3 = m3; b3 <= t[3].k; ++b3){
                    for (int b4 = m4; b4 <= t[4].k; ++b4){
                        for (int b5 = m5; b5 <= t[5].k; ++b5){
                            backpack[b1][b2][b3][b4][b5] = min(backpack[b1][b2][b3][b4][b5], backpack[b1-m1][b2-m2][b3-m3][b4-m4][b5-m5]+a[i].v);
                        }
                    }
                }
            }
        }
    }
    cout << backpack[t[1].k][t[2].k][t[3].k][t[4].k][t[5].k] << '\n';
}

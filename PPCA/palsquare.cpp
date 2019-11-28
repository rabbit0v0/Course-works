//
//  palsquare.cpp
//  PPCA
//
//  Created by 施晓钰 on 2017/7/11.
//  Copyright © 2017年 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG: palsquare
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <fstream>
using namespace std;
int B, sum;
int numbers[305][100];
int getit[305];

int main(){
    freopen("palsquare.in", "r", stdin);
    freopen("palsquare.out", "w", stdout);
    cin >> B;
    for (int i = 1; i < 300; ++i){
        int k = i * i;
        int m = 0;
        while(k != 0){
            numbers[i][++m] = k % B;
            k /= B;
        }
        numbers[i][0] = m;
    }
    for (int i = 0; i < 300; ++i){
        bool flag = 1;
        for (int j = 1; j <= numbers[i][0] / 2; ++j){
            if (numbers[i][j] != numbers[i][numbers[i][0] - j + 1])
                flag = 0;
        }
        if (flag) getit[sum++] = i;
    }
    for (int i = 1; i < sum; ++i){
        int s[100];
        int k = getit[i];
        int m = 0;
        while(k != 0){
            s[++m] = k % B;
            k /= B;
        }
        for (int l = m; l >= 1; --l){
            if (s[l] >= 10)
                cout << (char)(s[l] + 55);
            else
                cout << s[l];
        }
        cout << ' ';
        for (int l = numbers[getit[i]][0]; l >= 1; --l){
            if (numbers[getit[i]][l] >= 10)
                cout << (char)(numbers[getit[i]][l] + 55);
            else
                cout << numbers[getit[i]][l];
        }
        cout << '\n';
    }
}

//
//  add.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/7/13.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
string a, b;
int a1[100001], b1[100001], c[100001];
int a_len, b_len, c_len, i, x;

int main(){
    cin >> a >> b;
    a_len = a.length();
    b_len = b.length();
    
    for (int i = 0; i <= a_len - 1; i++){
        a1[a_len - i] = a[i] - 48;
    }
    
    for (int i = 0; i <= b_len - 1; i++){
        b1[b_len - i] = b[i] - 48;
    }
    c_len = 1;
    x = 0;
    while (c_len <= a_len || c_len <= b_len ){
        c[c_len] = a1[c_len] + b1[c_len] + x;
        x = c[c_len] / 10;
        c[c_len] = c[c_len] % 10;
        c_len++;
    }
    c[c_len] = x;
    if (c[c_len] == 0 ){
        c_len--;
    }
    
    for (i = c_len; i >= 1; i--)
        cout << c[i];
    cout << endl;
    
    return 0;
}

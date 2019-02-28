//
//  1001 oj.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/1/23.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
    int H, h, n, x[1005], num = 0;
    cin >> H >> h >> n;
    for (int i = 1; i <= n; ++i){
        cin >> x[i];
    }
    for (int i = 1; i <= n; ++i){
        if (x[i] <= H + h){
            num++;
        }
    }
    cout << num;
}

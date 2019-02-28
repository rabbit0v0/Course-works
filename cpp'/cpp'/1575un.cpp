//
//  1575.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/2.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int l, n, m, D[50005], d[50005], res;

void half(int max, int min){
    int k = 0;
    int mid = (max + min) / 2;
    if (mid == min){
        /*for (int i = 1; i <= n; ++i){
            if (d[i] < max)
                k++;
        }
        if (k == m)
            res = max;
        else*/
            res = mid;
        return;
    }
    for (int i = 1; i <= n; ++i){
        if (d[i] < mid){
            k++;
            i++;
        }
        if (k > m){
            max = mid;
            break;
        }
    }
    if (k <= m)
        min = mid;
    half (max, min);
}

int main(){
    cin >> l >> n >> m;
    for (int i = 1; i <= n; ++i){
        cin >> D[i];
    }
    D[n + 1] = l;
    
    for (int i = 1; i <= n + 1; ++i){
        d[i] = D[i] - D[i - 1];
        //cout << d[i] << '\n';
    }
    half (l, 0);
    cout << res;
}

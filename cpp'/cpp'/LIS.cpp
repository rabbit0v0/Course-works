//
//  LIS.cpp
//  cpp'
//
//  Created by 施晓钰 on 2016/12/16.
//  Copyright © 2016年 施晓钰. All rights reserved.
//

#include <iostream>
using namespace std;

int n, x[1000005], y[1000005];

int main(){
    int top = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i){
        cin >> x[i];
        if (x[i] > y[top]){
            y[++top] = x[i];
        }
        else{
            int l = 0, r = top, mid;
            while (l <= r) {
                mid = (l + r) / 2;
                if (x[i] > y[mid]){
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            y[l] = x[i];
        }
    }
    cout << top;
}

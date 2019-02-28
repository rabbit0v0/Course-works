//
//  绮礼的阴谋 绮礼的阴谋 琦礼的阴谋.cpp
//  cpp'
//
//  Created by 施晓钰 on 2016/12/14.
//  Copyright © 2016年 施晓钰. All rights reserved.
//

#include <iostream>
#include <algorithm>
using namespace std;

struct s{
    int a, b;
    s(int x = 0, int y = 0){
        a = x;
        b = y;
    }
};
bool cmp(s aa, s bb){
    return aa.a < bb.a;
}
s sight[10001];

int s;

int main(){
    int n, L, R;
    cin >> n;
    int t = 0;
    while (t < n){
        cin >> sight[t].a >> sight[t].b;
        t++;
    }
    sort(sight, sight + n, cmp);
    L = sight[0].a;
    R = sight[0].b;
    for (int i = 1; i < n; ++i){
        if (sight[i].b > R && sight[i].a < R){
            R = sight[i].b;
        }
        if (sight[i].a > R){
            s += R - L;
            L = sight[i].a;
            R = sight[i].b;
        }
        if (i == n - 1){
            s += R - L;
        }
    }
    cout << s;
}

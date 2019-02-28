//
//  1570.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/2/6.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int n, t;
long long ni[100005], ti[100005];
int bigger(long long num, int max, int min){
    int mid = (max + min) / 2;
    if (mid == min)
        return mid;
    if (ni[mid] <= num)
        return bigger (num, max, mid);
    else
        return bigger (num, mid, min);
}

int main(){
    cin >> n >> t;
    for (int i = 1; i <= n; ++i){
        scanf("%lld", &ni[i]);
    }
    ni[0] = -1;
    ni[n + 1] = 2000000001;
   
    for (int i = 0; i < t; ++i){
        scanf("%lld", &ti[i]);
        int q = bigger (ti[i], n + 1, 0);
        printf("%d\n", n - q);
    }
    
    return 0;
}

//
//  1640.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/29.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int n;
int l[100005];

int divide(int* a,int low,int high){
    int k = a[low];
    do{
        while (low < high && a[high] >= k)
            --high;
        if (low < high){
            a[low] = a[high];
            ++low;
        }
        while (low < high && a[low] <= k)
            ++low;
        if (low < high){
            a[high] = a[low];
            --high;
        }
    }while(low != high);
    a[low] = k;
    return low;
}

void sort(int* a, int low, int high){
    int mid;
    if (low >= high)
        return;
    mid = divide(a, low, high);
    sort(a, low, mid - 1);
    sort(a, mid + 1, high);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d", &l[i]);
    }
    sort(l, 1, n);
    int time = 0, people = 0;
    for (int i = 1; i <= n; ++i){
        if (l[i] >= time){
            people++;
            time += l[i];
        }
    }
    printf("%d", n - people);
}

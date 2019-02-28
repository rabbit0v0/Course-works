//
//  1634.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/23.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int sum;
int a[100001];

int divide(int* a, int low, int high){
    int k = a[low];
    do{
        while(low < high && a[high] >= k){
            high--;
            sum++;
        }
        if (low < high){
            a[low] = a[high];
            low++;
            sum++;
        }
        while(low < high && a[low] <= k){
            low++;
            sum++;
        }
        if (low < high){
            a[high] = a[low];
            high--;
            sum++;
        }
    }while(low != high);
    a[low] = k;
    return low;
}

void quicksort(int* a, int low, int high){
    int mid;
    if (low >= high)
        return;
    mid = divide(a, low, high);
    quicksort(a, low, mid - 1);
    quicksort(a, mid + 1, high);
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    if (k == 3){
        for(int i = 0; i < n; ++i)
            scanf("%d", &a[i]);
        quicksort(a, 0, n - 1);
        printf("%d", sum);
    }
}

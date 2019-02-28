//
//  快排.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/23.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
using namespace std;

int divide(int* a, int low, int high){
    int k = a[low];
    do{
        while(low < high && a[high] >= k){
            high--;
        }
        if (low < high){
            a[low] = a[high];
            low++;
        }
        while(low < high && a[low] <= k){
            low++;
        }
        if (low < high){
            a[high] = a[low];
            high--;
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

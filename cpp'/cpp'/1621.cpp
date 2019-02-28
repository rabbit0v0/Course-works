//
//  1621.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/5.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, maxsize, size;
int mat[1005][1005], tol[1005][1005];

int divide(int k, int low, int high){
    int m = tol[low][k];
    do {
        while (low < high && tol[high][k] >= m)
            high--;
        if (low < high){
            tol[low][k] = tol[high][k];
            low++;
        }
        while (low < high && tol[low][k] <= m)
            low++;
        if (low < high){
            tol[high][k] = tol[low][k];
            high--;
        }
    }while(low != high);
    tol[low][k] = m;
    return low;
}

void sort(int k, int low, int high){
    int mid;
    if (low >= high)
        return;
    mid = divide(k, low, high);
    sort(k, low, mid - 1);
    sort(k, mid + 1, high);
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        getchar();
        for (int j = 1; j <= n; ++j){
            char c;
            scanf("%c", &c);
            if (c == '1')
                mat[i][j] = 1;
            else
                mat[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j){
            if (mat[i][j])
                tol[i][j] = tol[i][j - 1] + 1;
            else
                tol[i][j] = 0;
        }
    }
    for (int i = 1; i <= n; ++i){
        sort (i, 1, n);
        size = tol[n][i];
        if (size > maxsize){
            maxsize = size;
        }
        for (int j = n; j >= 1; --j){
            if (tol[j][i] == 0)
                break;
            size = tol[j][i] * (n - j + 1);
            if (size > maxsize){
                maxsize = size;
            }
        }
    }
    printf("%d", maxsize);
}

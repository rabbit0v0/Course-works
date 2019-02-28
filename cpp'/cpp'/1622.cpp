//
//  1622.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/2.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, tai0, tai1, top0, top1;
int l0[200000], l1[200000];
bool rev;

bool empty(int k){
    if (k){
        return tai1 == top1;
    }
    else
        return tai0 == top0;
}

void push(int x){
    if (!rev)
        l0[tai0++] = x;
    else
        l1[tai1++] = x;
}

bool cal(int k, int n, bool tem){
    bool res = 0;
    if (rev){
        if (!empty(0)){
            if (k == 0 && n == tai0 - 1){
                return tem;
            }
        }
        else{
            if (k == 1 && n == top1){
                return tem;
            }
        }
        if (k == 1 && n == top1){
            tem = (!tem || !l0[top0]);
            res = cal(0, top0, tem);
        }
        else if (k == 1 && n > top1){
            tem = (!tem || !l1[--n]);
            res = cal(1, n, tem);
        }
        else if (k == 0 && n < tai0 - 1){
            tem = (!tem || !l0[++n]);
            res = cal(0, n, tem);
        }
    }
    else{
        if (!empty(1)){
            if (k == 1 && n == tai1 - 1){
                return tem;
            }
        }
        else{
            if (k == 0 && n == top0){
                return tem;
            }
        }
         if (k == 0 && n == top0){
            tem = (!tem || !l1[top1]);
            res = cal(1, top1, tem);
        }
        else if (k == 0 && n > top0){
            tem = (!tem || !l0[--n]);
            res = cal(0, n, tem);
        }
        else if (k == 1 && n < tai1 - 1){
            tem = (!tem || !l1[++n]);
            res = cal(1, n, tem);
        }
    }
    
    return res;
}

void query(){
    if (empty(0) && empty(1)){
        puts("Invalid.\n");
    }
    else if (rev){
        bool tem = 0;
        int res = 0;
        if (!empty(1)){
            tem = l1[tai1 - 1];
            res = cal(1, tai1 - 1, tem);
        }
        else{
            tem = l0[top0];
            res = cal(0, top0, tem);
        }
        printf("%d\n", res);
    }
    else if (!rev){
        bool tem = 0;
        int res = 0;
        if (!empty(0)){
            tem = l0[tai0 - 1];
            res = cal(0, tai0 - 1, tem);
        }
        else{
            tem = l1[top1];
            res = cal(1, top1, tem);
        }

        printf("%d\n", res);
    }
}

void pop(){
    if (!rev){
        if (!empty(0))
            tai0--;
        else if (!empty(1))
            top1++;
    }
    else{
        if (!empty(1))
            tai1--;
        else if (!empty(0))
            top0++;
    }
}

int main(){
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; ++i){
        char c, b = 0;
        c = getchar();
        while(c != '\n' && c != ' '){
            b = c;
            c = getchar();
        }
        if (b == 'H'){
            int k;
            scanf("%d", &k);
            getchar();
            push(k);
        }
        else if (b == 'Y'){
            query();
        }
        else if (b == 'E'){
            rev = 1 - rev;
        }
        else if (b == 'P'){
            pop();
        }
    }
}

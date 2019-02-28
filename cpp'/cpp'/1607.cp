//
//  1607.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/8.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, q, head, tail, tail0;
int l0[2000001];
struct node{
    int id;
    int team;
    node(int a = 0, int b = 0){
        id = a;
        team = b;
    }
};
node l[2000001];

void push(int id, int t){
    for (int i = 1; i <= tail; ++i){
        
    }
}

int pop(){
    if (head == tail)
        return -1;
    head++;
    return l[head - 1].id;
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i){
        scanf("%d", &l0[i]);
    }
    scanf("%d", &q);
    for (int i = 1; i <= q; ++i){
        int fun;
        scanf("%d", &fun);
        if (fun == 0){
            if (tail0 != n){
                ++tail0;
                push(tail0, l0[tail0]);
            }
        }
        if (fun == 1){
            cout << pop();
        }
    }
    return 0;
}
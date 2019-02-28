//
//  1635+.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/31.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, m, big;

struct node{
    int no;
    int cost;
    bool know;
    node* next;
    node(){
        no = 0;
        cost = 5000000;
        next = NULL;
        know = 0;
    }
};
node themap[1000001];

void push(int u, int v){
    node* tem = new node;
    tem->no = v;
    tem->next = themap[u].next;
    themap[u].next = tem;
    node* tmp = new node;
    tmp->no = u;
    tmp->next = themap[v].next;
    themap[v].next = tmp;
}

void cal(int x){
    
}

int main(){
    scanf("%d%d", &n, &m);
    big = n++;
    for (int i = 0; i < m; ++i){
        int u, v, c;
        scanf("%d%d%d", &u, &v, &c);
        push(u, v);
        c--;
        while(c){
            push(big, v);
            push(big, u);
            big++;
            c--;
        }
    }
    themap[1].cost = 0;
    themap[1].know = 1;
    cal(1);
    printf("%d", themap[n].cost);
    return 0;
}

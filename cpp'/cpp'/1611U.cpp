//
//  1611.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/4.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, x;
bool color[100002];

struct node{
    int no;
    node* next;
    node (int a = 0, node* p = NULL){
        no = a, next = p;
    }
};
node l[200002];

void addto(node* son, node father){
    node* tem = father.next;
    father.next = son;
    son->next = tem;
}

void dfs(int k){
    
}

int main(){
    scanf("%d", &n);
    for (int i = 1; i < n; ++i){
        int u, v;
        scanf("%d%d", &u, &v);
        node* tem1 = new node;
        tem1->no = u;
        addto(tem1, l[v]);
        node* tem2 = new node;
        tem2->no = v;
        addto(tem2, l[v]);
    }
    scanf("%d", &x);
    
}

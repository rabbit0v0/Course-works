//
//  1619.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/5.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int m, n;
struct node{
    int no;
    int v;
    node* next;
    node(int a = 0, int b = 0, node* p = NULL){
        no = a;
        v = b;
        next = p;
    }
};
node candy[200002];

void addto(node* son, node father){
    node* tem = father.next;
    father.next = son;
    son->next = tem;
}

void dfs(int k, int pre){
    candy[k].no = candy[k].v + pre;
    if (candy[k].next == NULL)
        return;
    node* tem = candy[k].next;
    while (tem != NULL){
        dfs(tem->no, candy[k].no);
        tem = tem->next;
    }
}

int main(){
    scanf("%d%d", &m, &n);
    int x, y;
    for (int i = 1; i < n; ++i){
        scanf("%d%d", &x, &y);
        node* tem = new node;
        tem->no = x;
        addto(tem, candy[y]);
        node* temp = new node;
        temp->no = y;
        addto(temp, candy[x]);
    }
    int v;
    for (int i = 1; i <= n; ++i){
        scanf("%d", &v);
        candy[i].v = v;
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i){
        int op;
        scanf("%d", &op);
        if (op == 0){
            int a, b;
            scanf("%d%d", &a, &b);
            candy[a].v = b;
            
            
            
        }
        else{
            int k;
            
        }
    }
}

//
//  1554.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/29.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, root;
struct node{
    int no;
    int len;//or sum of sons
    node* next;
    node(){
        no = 0; len = 0; next = NULL;
    }
};
node tree[800005];
bool visit[800005];
void push(int u, int v, int w){
    node* tem = new node;
    tem->no = v;
    tem->len = w;
    tem->next = tree[u].next;
    tree[u].next = tem;
    node* tmp = new node;
    tmp->no = u;
    tmp->len = w;
    tmp->next = tree[v].next;
    tree[v].next = tmp;
}

class queue{
    node l[800005];
    int head, tail;
public:
    queue(){
        head = 0; tail = 0;
    }
    void push(node p){
        l[++tail] = p;
    }
    node pop(){
        return l[++head];
    }
    bool empty(){
        return head == tail;
    }
};
queue k;

void thr(node* p){
    if (p == NULL)
        return;
    node* tem = p->next;
    while (tem != NULL){
        
    }
}

int main(){
    scanf("%d%d", &n, &root);
    for (int i = 1; i < n; ++i){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        push(x, y, z);
    }
    k.push(tree[root]);
    
}

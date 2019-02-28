//
//  1375.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/5/29.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, m, root, num = 2;
struct node{
    int no;
    int newno;
    int low;
    int high;
    node* next;
    node(){
        no = 0;
        newno = 0;
        low = 0;
        high = 0;
        next = NULL;
    }
};
node tree[40005];

void push(int a, int b){
    tree[a].no = a;
    tree[b].no = b;
    node* tem = new node;
    tem->no = a;
    tem->next = tree[b].next;
    tree[b].next = tem;
    node* tmp = new node;
    tmp->no = b;
    tmp->next = tree[a].next;
    tree[a].next = tmp;
}

void down(node* p){
    p->low = p->newno;
    node* tem = p->next;
    while(tem != NULL){
        if(tree[tem->no].newno == 0){
            tree[tem->no].newno = num++;
            down(&tree[tem->no]);
        }
        tem = tem->next;
    }
    p->high = num;
    //cout << p->no << ' ' << p->newno << ' ' << p->low << ' ' << p->high << '\n';
}

void givenewno(){
    down(&tree[root]);
}

int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        if (b == -1){
            root = a;
            tree[root].no = root;
            tree[root].newno = 1;
        }
        else
            push(a, b);
    }
    givenewno();
    scanf("%d", &m);
    for (int i = 0; i < m; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        if (tree[b].newno < tree[a].high && tree[b].newno > tree[a].low)
            printf("%d\n", 1);
        else if (tree[a].newno < tree[b].high && tree[a].newno > tree[b].low)
            printf("%d\n", 2);
        else
            printf("%d\n", 0);
    }
}

//
//  1051.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/24.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int n, m, comp;

struct node{
    int data;
    node* pre;
    node* next;
    node(int a = 0, node* p = NULL, node* q = NULL){
        data = a;
        pre = p;
        next = q;
    }
};

node* head = new node;
node* tail = head;

void add(int c){
    node* tem = new node;
    tem->data = c;
    tem->pre = tail;
    tail->next = tem;
    tail = tem;
}

node* find(int c){
    node* now = head;
    while(now != tail){
        now = now->next;
        comp++;
        if (c == now->data)
            return now;
    }
    return NULL;
}

void push(node* p){
    if (p == NULL)
        return;
    if (p == head->next)
        return;
    if (p == tail){
        tail = p->pre;
        p->pre->next = p->next;
        head->next->pre = p;
        p->next = head->next;
        head->next = p;
        p->pre = head;
        return;
    }
    p->pre->next = p->next;
    p->next->pre = p->pre;
    head->next->pre = p;
    p->next = head->next;
    head->next = p;
    p->pre = head;
}

int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i){
        int c;
        scanf("%d", &c);
        add(c);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; ++i){
        int c;
        scanf("%d", &c);
        push(find(c));
    }
    printf("%d", comp);
    return 0;
}
//
//  单循环链表.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/21.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int no = 1;
struct node{
    int num;
    int data;
    node* next;
    node(int n = no, int x = 0, node* p = NULL){
        num = n;
        data = x;
        next = p;
    }
};

node* a = new node;
node* e = a;

void add(int x, node* p = e){
    if (e->next == NULL){
        a->num = no++;
        a->data = x;
        a->next = a;
        return;
    }
    node* n = new node;
    n->data = x;
    n->next = p->next;
    p->next = n;
    n->num = no++;
    if (p == e)
        e = n;
}

node* pre(node* p){
    node* q = e;
    while(q->next != p){
        q = q->next;
    }
    return q;
}

node* findpre(int k){
    node* q = e;
    while(q->next->data != k){
        q = q->next;
    }
    return q;
}

node* find(int k){
    node* q = e;
    while(q->data != k){
        q = q->next;
    }
    return q;
}

void del(node* p){
    node* q = pre(p);
    q->next = p->next;
    delete p;
}

void deldata(int k){
    node* p = findpre(k);
    node* q = p->next;
    p->next = p->next->next;
    delete q;
}
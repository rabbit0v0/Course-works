//
//  循环链表.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/21.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

struct node{
    int data;
    node* next;
    node* pre;
    
    node(int x = 0, node* p = NULL, node* q = NULL){
        data = x;
        pre = p;
        next = q;
    }
};

node* a = new node;

void add(int x, node* p = a->pre, node* q = a){
    if (a->pre == NULL){
        a->data = x;
        a->pre = a;
        a->next = a;
        return;
    }
    node* n = new node;
    n->data = x;
    n->pre = p;
    n->next = q;
    p->next = n;
    q->pre = n;
}

void del(node* p){
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete p;
}

node* find(int k){
    node* e = a;
    while (e->data != k){
        e = e->next;
    }
    return e;
}

void all(){
    node* e = a;
    do{
        cout << e->data;
        e = e->next;
    }while(e != a);
}


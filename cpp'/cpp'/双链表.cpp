//
//  双链表.cpp
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
    node* pre;
    node* next;
    node(int x = 0, node* p = NULL, node* q = NULL){
        data = x;
        pre = p;
        next = q;
    }
};

node* head;
node* tail;

void add(int x, node* p = tail->pre, node* q = tail){
    node* a = new node;
    a->data = x;
    if (tail->pre == NULL){
        head->next = a;
        tail->pre = a;
        a->pre = head;
        a->next = tail;
        return;
    }
    a->pre = p;
    a->next = q;
    p->next = a;
    q->pre = a;
}

void del(node* p){
    p->pre->next = p->next;
    p->next->pre = p->pre;
    delete p;
}

node* find(int k){
    node* e = head;
    while (e != tail){
        e = e->next;
        if(e->data == k)
            return e;
    }
    return NULL;
}

void all(){
    node* e = head;
    while (e != tail){
        e = e->next;
        cout << e->data;
    }
}

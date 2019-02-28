//
//  括号匹配.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/21.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

int maxsize = 1000, top = -1;
char* l = new char [maxsize];

void push(char c){
    if (top == maxsize - 1){
        char* _l = new char [2 * maxsize];
        for (int i = 0; i < maxsize; ++i){
            _l[i] = l[i];
        }
        _l[maxsize] = c;
        maxsize *= 2;
        ++top;
        delete []l;
        l = _l;
        return;
    }
    l[++top] = c;
    return;
}

void pop(){
    top--;
}

char query(){
    return l[top];
}

bool empty(){
    if (top == -1)
        return true;
    return false;
}

int main(){
    char c;
    while ( (c = getchar()) != '\n'){
        if (c == '(' || c == '[' || c == '{')
            push(c);
        if (c == ')'){
            if (!empty() && query() == '(')
                pop();
            else
                push(c);
        }
        if (c == ']'){
            if (!empty() && query() == '[')
                pop();
            else
                push(c);
        }
        if (c == '}'){
            if (!empty() && query() == '{')
                pop();
            else
                push(c); //可能会TLE.
        }
    }
    if (empty()){
        cout << "yes";
        return 0;
    }
    cout << "no";
    return 0;
}

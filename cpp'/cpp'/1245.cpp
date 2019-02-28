//
//  1245.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/4/4.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;

class stack{
    int head = 0, tail = 0;
    public:
    char s[1005];
    
    void push(char c){
        s[++tail] = c;
    }
    
    void pop(){
        if (head == tail)
            return;
        tail--;
    }
    
    bool empty(){
        return head == tail;
    }
    
    char query(){
        return s[tail];
    }
    int len(){
        return tail - head;
    }
};

stack ori, out, fun, cal, oth;

int main(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF){
        if (c != ' ')
            ori.push(c);
        if (c >= '0' && c <= '9')
            continue;
        else
            ori.push(' ');
    }
    
    while (!ori.empty()){
        c = ori.query();
        if (c >= '0' && c <= '9'){
            while (c >= '0' && c <= '9'){
                out.push(c);
                ori.pop();
                if (ori.empty())
                    break;
                c = ori.query();
            }
            out.push(' ');
        }
        else if (c == ')' || c == '*' || c == '/')
            fun.push(c);
        else if (c == '+' || c == '-'){
            if (fun.query() == ')' || fun.query() == '+' || fun.query() == '-'){
                fun.push(c);
            }
            else {
                while(fun.query() == '*' || fun.query() == '/'){
                    out.push(fun.query());
                    out.push(' ');
                    fun.pop();
                    if (fun.empty())
                        break;
                }
                fun.push(c);
            }
        }
        else if (c == '('){
            while (fun.query() != ')'){
                out.push(fun.query());
                out.push(' ');
                fun.pop();
            }
            fun.pop();
        }
        ori.pop();
        if ((c = ori.query()) == ' '){
            ori.pop();
        }
    }
    
    while (!fun.empty()){
        out.push(fun.query());
        out.push(' ');
        fun.pop();
    }
    if (out.query() != ' '){
        cal.push(out.query());
        printf("%c", out.query());
    }
    out.pop();
    while (!out.empty()){
            cal.push(out.query());
        printf("%c", out.query());
        out.pop();
    }
    printf("\n");
    
    int l[1000], no = 0;
    while (!cal.empty()){
        char k = cal.query();
        if (k >= '0' && k <= '9'){
            int sum = 0;
            int base = 1;
            while (k != ' '){
                sum += (k - 48) * base;
                cal.pop();
                if (cal.empty())
                    break;
                k = cal.query();
                base *= 10;
            }
            l[++no] = sum;
        }
        else if (k == '+'){
            int re = l[no] + l[no - 1];
            l[--no] = re;
            cal.pop();
        }
        else if (k == '-'){
            int re = l[no] - l[no - 1];
            l[--no] = re;
            cal.pop();
        }
        else if (k == '*'){
            int re = l[no] * l[no - 1];
            l[--no] = re;
            cal.pop();
        }
        else if (k == '/'){
            int re = l[no] / l[no - 1];
            l[--no] = re;
            cal.pop();
        }
        else if (k == ' '){
            cal.pop();
        }
        else
            cal.pop();
    }
    printf("%d", l[1]);
}
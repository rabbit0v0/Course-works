//
//  1207.cpp
//  cpp'
//
//  Created by 施晓钰 on 2017/3/28.
//  Copyright © 2017年 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int truck[20001], coach[20001];
int head1 = -1, head2 = -1, tail1 = -1, tail2 = -1;
double waitc, waitt;

void read(int &x)
{
    char c = getchar(), b = 1;
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            b = -1;
    for (x = 0; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x*= b;
    
}

void wait1(int t){
    waitc += t - coach[++head1];
}

void wait2(int t){
    waitt += t - truck[++head2];
}

int main(){
    int n, c, ship = 0;
    read(n);
    for (int i = 0; i < n; ++i){
        read(c);
        if (c == 0){
            read(coach[++tail1]);
        }
        if (c == 1){
            read(truck[++tail2]);
        }
    }
    
    while (head1 < tail1 || head2 < tail2){
        int car = 0;
        for (int i = 0; i < 8; ++i){
            if (head1 < tail1 && coach[head1 + 1] <= ship * 10){
                wait1(ship * 10);
                car++;
            }
            else
                break;
        }
        while(car++ < 10){
            if (head2 < tail2 && truck[head2 + 1] <= ship * 10){
                wait2(ship * 10);
            }
            else
                break;
        }
        if (car < 10){
            while (car++ < 10){
                if (head1 < tail1 && coach[head1 + 1] <= ship * 10){
                    wait1(ship * 10);
                }
            }
        }
        ship++;
    }
    waitc /= (tail1 + 1);
    waitt /= (tail2 + 1);
    printf("%.3f ", waitc);
    printf("%.3f", waitt);
}

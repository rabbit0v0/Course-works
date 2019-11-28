//
//  farm.cpp
//  PPCA
//
//  Created by 施晓钰 on 03/08/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <iostream>
using namespace std;
int M, N;
struct path{
    int s, e, l, f, next;
} road[40001];

int main(){
    cin >> N >> M;
    for (int i = 1; i <= M; ++i)
        cin >> road[i].s >> road[i].e >> road[i].l;
    
}

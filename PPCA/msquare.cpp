//
//  msquare.cpp
//  PPCA
//
//  Created by 施晓钰 on 18/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:msquare
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <queue>
#include <map>
using namespace std;
int status[9];
struct opra{
    string situ = "012348765";
    string step = "";
};
queue<opra> opr;
map<string, bool> done;

opra A(opra tem){
    int tmp[5];
    for (int i = 5; i <= 8; ++i)
        tmp[i - 4] = tem.situ[i];
    for (int i = 1; i < 5; ++i){
        tem.situ[i + 4] = tem.situ[i];
        tem.situ[i] = tmp[i];
    }
    tem.step += 'A';
    return tem;
}

opra B(opra tem){
    int tmp[2];
    tmp[0] = tem.situ[4];
    tmp[1] = tem.situ[8];
    for (int i = 4; i > 1; --i){
        tem.situ[i] = tem.situ[i - 1];
        tem.situ[i + 4] = tem.situ[i + 3];
    }
    tem.situ[1] = tmp[0];
    tem.situ[5] = tmp[1];
    tem.step += 'B';
    return tem;
}

opra C(opra tem){
    int tmp = tem.situ[2];
    tem.situ[2] = tem.situ[6];
    tem.situ[6] = tem.situ[7];
    tem.situ[7] = tem.situ[3];
    tem.situ[3] = tmp;
    tem.step += 'C';
    return tem;
}

void bfs(){
    opra beg;
    opr.push(beg);
    while (!opr.empty()){
        opra tmp = opr.front();
        opr.pop();
        if (done.count(tmp.situ))
            continue;
        done[tmp.situ] = 1;
        bool flag = 1;
        for (int i = 1; i <= 8; ++i){
            if (tmp.situ[i] - 48 != status[i]){
                flag = 0;
                break;
            }
        }
        if (flag){
            cout << tmp.step.length() << '\n' << tmp.step << '\n';
            break;
        }
        opr.push(A(tmp));
        opr.push(B(tmp));
        opr.push(C(tmp));
    }
}

int main(){
    freopen("msquare.in","r",stdin);
    freopen("msquare.out","w",stdout);
    for (int i = 1; i < 5; ++i)
        cin >> status[i];
    for (int i = 8; i > 4; --i)
        cin >> status[i];
    bfs();
}

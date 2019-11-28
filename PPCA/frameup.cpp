//
//  frameup.cpp
//  PPCA
//
//  Created by 施晓钰 on 24/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:frameup
 LANG: C++
 */
#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stack>
#include <algorithm>
using namespace std;
int H, W;
char frame[31][31];
int upper[27], lower[27], leftside[27], rightside[27], sum;
bool got[27], pushed[27];
stack<char> order;
char* res[10000];
int amo;

void dfs(int tot){
    if (tot == sum){
        char tmp[27];
        res[amo] = new char[31];
        while (!order.empty()){
            res[amo][sum - tot] = order.top();
            tmp[tot--] = order.top();
            order.pop();
        }
        amo++;
        for (int i = 1; i <= sum; ++i)
            order.push(tmp[i]);
        return;
    }
    for (int x = 1; x < 27; ++x){
        if (!got[x] || pushed[x])
            continue;
        bool flag = 1;
        for (int i = leftside[x]; i <= rightside[x]; ++i){
            if (!((frame[upper[x]][i] - 'A' + 1 == x || frame[upper[x]][i] == '.') && (frame[lower[x]][i] - 'A' + 1 == x || frame[lower[x]][i] == '.'))){
                flag = 0;
                break;
            }
        }
        for (int i = upper[x]; i <= lower[x]; ++i){
            if (!((frame[i][leftside[x]] - 'A' + 1 == x || frame[i][leftside[x]] == '.') && (frame[i][rightside[x]] - 'A' + 1 == x || frame[i][rightside[x]] == '.'))){
                flag = 0;
                break;
            }
        }
        if (flag){
            order.push(x + 'A' - 1);
            pushed[x] = 1;
            char note1[2][40], note2[2][40];
            for (int i = leftside[x]; i <= rightside[x]; ++i) {
                note1[0][i] = frame[upper[x]][i];
                note1[1][i] = frame[lower[x]][i];
                frame[upper[x]][i] = '.', frame[lower[x]][i] = '.';
            }
            for (int i = upper[x] + 1; i <= lower[x] - 1; ++i){
                note2[0][i] = frame[i][leftside[x]];
                note2[1][i] = frame[i][rightside[x]];
                frame[i][leftside[x]] = '.', frame[i][rightside[x]] = '.';
            }
            dfs(tot + 1);
            if (order.top() == x + 'A' - 1){
                pushed[order.top() - 'A' + 1] = 0;
                order.pop();
            }
            for (int i = leftside[x]; i <= rightside[x]; ++i) {
                frame[upper[x]][i] = note1[0][i];
                frame[lower[x]][i] = note1[1][i];
            }
            for (int i = upper[x] + 1; i <= lower[x] - 1; ++i){
                frame[i][leftside[x]] = note2[0][i];
                frame[i][rightside[x]] = note2[1][i];
            }
        }
    }
}

int main(){
    freopen("frameup.in", "r", stdin);
    freopen("frameup.out", "w", stdout);
    memset(upper, 31, sizeof(upper));
    memset(leftside, 31, sizeof(leftside));
    cin >> H >> W;
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j)
            cin >> frame[i][j];
    for (int i = 1; i <= H; ++i){
        for (int j = 1; j <= W; ++j){
            if (frame[i][j] != '.'){
                int x = frame[i][j] - 'A' + 1;
                got[x] = 1;
                if (i < upper[x])
                    upper[x] = i;
                if (i > lower[x])
                    lower[x] = i;
                if (j < leftside[x])
                    leftside[x] = j;
                if (j > rightside[x])
                    rightside[x] = j;
            }
        }
    }
    for (int x = 1; x < 27; ++x)
        if (got[x])
            sum++;
    dfs(0);
    string ans[10000];
    for (int i = 0; i < amo; ++i)
        ans[i] += string(res[i]);
    sort(ans, ans + amo);
    for (int i = 0; i < amo; ++i){
        for (int j = 0; j < sum; ++j){
            cout << ans[i][j];
        }
        cout << '\n';
    }
}

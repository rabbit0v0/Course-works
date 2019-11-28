//
//  floyd.cpp
//  PPCA
//
//  Created by 施晓钰 on 31/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <cstring>
#include <iostream>
using namespace std;
int hour[1001][1001];
int main(){
    int n;
    cin >> n;
    while (n){
        memset(hour, 10000000, sizeof(hour));
        for (int i = 1; i <= n; ++i){
            int m;
            cin >> m;
            for (int i = 1; i <= m; ++i){
                int p, t;
                cin >> p >> t;
                hour[i][p] = t;
            }
        }
        bool is = 0;
        for (int i = 1; i <= n; ++i){
            bool flag = 0;
            for (int j = 1; j <= n; ++j){
                if (hour[j][i])
                    flag = 1;
            }
            if (!flag && is){
                cout << "disjoint\n";
                return 0;
            }
            if (!flag)
                is = 1;
        }
        for (int k = 1; k <= n; ++k){
            for (int i = 1; i <= n; ++i){
                for (int j = 1; j <= n; ++j){
                    if (k == j || i == j || i == k) continue;
                    if (hour[i][j] > hour[i][k] + hour[k][j])
                        hour[i][j] = hour[i][k] + hour[k][j];
                }
            }
        }
        int mindis = 99999999, beg = 0;
        for (int i = 1; i <= n; ++i){
            int maxdis = 0;
            for(int j = 1; j <= n; ++j){
                if (i == j) continue;
                if (maxdis < hour[i][j])
                    maxdis = hour[i][j];
            }
            if (maxdis < mindis){
                mindis = maxdis;
                beg = i;
            }
        }
        cout << beg << ' ' << mindis << '\n';
    }
}

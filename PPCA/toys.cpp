//
//  toys.cpp
//  PPCA
//
//  Created by 施晓钰 on 27/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cstring>
using namespace std;
int n, m, x1, y1, x2, y2, ans[5005];
struct node{
    int x, y;
};
node point[5005];
struct board{
    node x1, x2;
};
board boards[5005];
int xmult(node p, node p1, node p2){
    int res = (p1.x - p.x)*(p2.y - p.y) - (p2.x - p.x)*(p1.y - p.y);
    return res;
}
int main(){
    int k;
    cin >> k;
    while (k != 0){
        memset(ans,0,sizeof(ans));
        n = k;
        cin >> m >> x1 >> y1 >> x2 >> y2;
        for (int i = 0; i < n; ++i){
            cin >> boards[i].x1.x >> boards[i].x2.x;
            boards[i].x1.y = y1, boards[i].x2.y = y2;
        }
        boards[n].x1.x = x2, boards[n].x1.y = y1;
        boards[n].x2.x = x2, boards[n].x2.y = y2;
        for (int i = 0; i < m; ++i)
            cin >> point[i].x >> point[i].y;
        for (int i = 0; i < m; ++i){
            int minim = 0, maxim = n;
            int res = 0;
            while (minim <= maxim){
                int mid = (minim + maxim) / 2;
                if (xmult(point[i], boards[mid].x1, boards[mid].x2) < 0){
                    res = mid;
                    maxim = mid - 1;
                }
                else
                    minim = mid + 1;
            }
            ans[res]++;
        }
        for (int i = 0; i <= n; ++i){
            cout << i << ':' << ans[i] << '\n';
        }
        cin >> k;
        if (k != 0)
            cout << '\n';
        else break;
    }
}

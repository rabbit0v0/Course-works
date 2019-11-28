//
//  intersection.cpp
//  PPCA
//
//  Created by 施晓钰 on 28/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
#define eps 1e-8
#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
struct node{
    int x, y;
};
node start, ending;
int n, l, r, t, d;

int dblcmp(double m) {
    if (fabs(m) < eps) return 0;
    return m > 0 ? 1 : -1;
}

double Multi(node p1, node p2, node p0) {
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

bool check(node a, node b, node c, node d){
    bool flag = 0;
    if (dblcmp(max(a.x, b.x)-min(c.x, d.x)) >= 0 && dblcmp(max(c.x, d.x)-min(a.x, b.x)) >= 0 && dblcmp(max(a.y, b.y)-min(c.y, d.y)) >= 0 && dblcmp(max(c.y, d.y)-min(a.y, b.y)) >= 0 && dblcmp(Multi(a, d, c)*Multi(b, d, c)) <= 0 && dblcmp(Multi(c, b, a)*Multi(d, b, a)) <= 0)
        flag = 1;
    return flag;
}
int main(){
    cin >> n;
    while (n--){
        bool flag = 1;
        int a, b, c, e;
        cin >> start.x >> start.y >> ending.x >> ending.y >> a >> b >> c >> e;
        l = min(a, c);
        r = max(a, c);
        t = max(b, e);
        d = min(b, e);
        node lt, ld, rt, rd;
        lt.x = l, lt.y = t;
        ld.x = l, ld.y = d;
        rt.x = r, rt.y = t;
        rd.x = r, rd.y = d;
        if (min(start.y, ending.y) >= t || max(start.y, ending.y) <= e || min(start.x,ending.x) >= r || max(start.x, ending.x) <= l)
            flag = 0;
        if (!check(start, ending, lt, rt) && !check(start, ending, rt, rd) && !check(start, ending, rd, ld) && !check(start, ending, ld, lt))
            flag = 0;
        if (flag) cout << "T\n";
        else cout << "F\n";
    }
}

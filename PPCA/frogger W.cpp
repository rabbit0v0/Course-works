////
////  frogger.cpp
////  PPCA
////
////  Created by 施晓钰 on 01/08/2017.
////  Copyright © 2017 幺幺. All rights reserved.
////
//#define inf 0.001
//#include <stdio.h>
//#include <iostream>
//#include <iomanip>
//#include <queue>
//#include <cmath>
//using namespace std;
//struct node{
//    int x, y;
//    bool operator == (const node &b){
//        return (x == b.x && y == b.y);
//    }
//};
//node point[205];
//bool visit[205];
//int x;
//
//double dist(node a, node b){
//    double res = sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
//    return res;
//}
//
//bool bfs(double dis){
//    for (int i = 0; i <= 200; ++i)
//        visit[i] = 0;
//    queue<int> test;
//    test.push(0);
//    visit[0] = 1;
//    while (!test.empty()){
//        node now = point[test.front()];
//        if (now == point[1])
//            return 1;
//        test.pop();
//        for (int i = 0; i < x; ++i){
//            if (!visit[i] && dist(point[i], now) <= dis){
//                test.push(i);
//                visit[i] = 1;
//            }
//        }
//    }
//    return 0;
//}
//
//double bi(double h, double l){
//    if (h - l < inf)
//        return h;
//    double mid = (h + l) / 2;
//    double res = 0;
//    if (!bfs(mid))
//        res = bi(h, mid + 0.001);
//    else
//        res = bi(mid, l);
//    return res;
//}
//
//int main(){
//    int num = 0;
//    while (cin >> x){
//        num++;
//        if (x == 0) break;
//        for (int i = 0; i < x; ++i)
//            scanf("%d%d", &point[i].x, &point[i].y);
//            //cin >> point[i].x >> point[i].y;
//        double start = dist(point[0], point[1]);
//        double res = bi(start, 0);
//        //cout.setf(ios::fixed);
//        //cout << "Scenario #" << num << '\n' << "Frog Distance = " << showpoint << setprecision(3) << res << '\n';
//        printf("Scenario #%d\nFrog Distance = %.3f\n", num, res);
//    }
//}

//
//  ant.cpp
//  PPCA
//  极角排序
//  Created by 施晓钰 on 28/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <string.h>
#include <math.h>
using namespace std;

const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x) < eps)return 0;
    if(x < 0)return -1;
    else return 1;
}
struct Point
{
    double x,y;
    int index;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    //叉积
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    //点积
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};
double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}
int pos;
Point p[100];
bool cmp(Point a,Point b)
{
    double tmp = (a-p[pos])^(b-p[pos]);
    if(sgn(tmp) == 0)
        return dist(p[pos],a) < dist(p[pos],b);
    else if(sgn(tmp) < 0)return false;
    else return true;
}
int main()
{
    int T;
    scanf("%d",&T);
    int n;
    while(T--)
    {
        scanf("%d",&n);
        for(int i = 0;i < n;i++)
        {
            scanf("%d%lf%lf",&p[i].index,&p[i].x,&p[i].y);
            if( p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x) )
                swap(p[0],p[i]);
        }
        pos = 0;
        for(int i = 1;i < n;i++)
        {
            sort(p+i,p+n,cmp);
            pos ++;
        }
        printf("%d",n);
        for(int i = 0;i < n;i++)
            printf(" %d",p[i].index);
        printf("\n");
    }
    return 0;
}

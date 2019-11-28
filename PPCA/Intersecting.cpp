//
//  Intersecting.cpp
//  PPCA
//
//  Created by 施晓钰 on 30/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//

#include<cstdio>
#include<cstring>
#include<cmath>
#include <algorithm>
using namespace std;
#define inf 1e-8
struct line
{
    double a,b,c,d;
}a,b;
double x,y;
void intersection()
{
    double a1=a.b-a.d,b1=a.c-a.a,c1=a.a*a.d-a.c*a.b;
    double a2=b.b-b.d,b2=b.c-b.a,c2=b.a*b.d-b.c*b.b;
    x=(c1*b2-c2*b1)/(a2*b1-a1*b2);
    y=(a2*c1-a1*c2)/(a1*b2-a2*b1);
}
int main()
{
    int t;
    puts("INTERSECTING LINES OUTPUT");
    scanf("%d",&t);
    for(;t--;)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a.a,&a.b,&a.c,&a.d,&b.a,&b.b,&b.c,&b.d);
        if(abs((a.a-a.c)*(b.b-b.d)-(a.b-a.d)*(b.a-b.c))<inf)
        {
            if(abs((a.c-a.a)*(b.b-a.b)-(a.d-a.b)*(b.a-a.a))<inf)
                puts("LINE");
            else
                puts("NONE");
        }
        else
        {
            intersection();
            printf("POINT %.2f %.2f\n",x,y);
        }
    }
    puts("END OF OUTPUT");
    return 0;
}

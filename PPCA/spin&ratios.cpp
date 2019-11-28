//
//  spin.cpp
//  PPCA
//
//  Created by 施晓钰 on 18/07/2017.
//  Copyright © 2017 幺幺. All rights reserved.
//
/*
 ID: yy_20161
 PROG:ratios
 LANG: C++
 */
//#include <iostream>
//#include <fstream>
//using namespace std;
//struct wheel
//{
//    int spd,start[6],len[6],size;
//};
//int main()
//{
//    short sp[361];
//    wheel w[5];
//    int time,i,j,k;
//    ifstream fin;
//    ofstream fout;
//    
//    fin.open("spin.in");
//    for(i=0;i<5;i++) {
//        fin>>w[i].spd>>j;
//        w[i].size=j;
//        while(--j>=0)
//            fin>>w[i].start[j]>>w[i].len[j];
//    }
//    fin.close();
//    
//    fout.open("spin.out");
//    for(time=0;time<360;time++) {
//        for(i=0;i<360;i++)
//            sp[i]=-1;
//        for(i=0;i<5;i++) {
//            for(j=0;j<w[i].size;j++) {
//                for(k=w[i].start[j];k<=w[i].start[j]+w[i].len[j];k++) {
//                    if(sp[k%360]==i-1)
//                        sp[k%360]=i;
//                }
//                w[i].start[j]=(w[i].start[j]+w[i].spd)%360;
//            }
//        }
//        for(i=0;i<360;i++)
//            if(sp[i]==4) {
//                fout<<time<<endl;
//                return 0;
//            }
//    }
//    fout<<"none"<<endl;
//    fout.close();
//}
#include <cstdio>

int d[4][3];

int main()
{
    freopen("ratios.in", "r", stdin);
    freopen("ratios.out", "w", stdout);
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 3; ++j)
            scanf("%d", &d[i][j]);
    }
    int p;
    for (p = 0; p < 3; ++p)
        if (d[3][p]) break;
    for (int lam = 1; lam <= 100; ++lam)
    {
        for (int i = 0; i<=100 && d[1][0]*i<=d[0][0]*lam && d[1][1]*i<=d[0][1]*lam && d[1][2]*i<=d[0][2]*lam; ++i)
            for (int j = 0; j<=100 && d[1][0]*i+d[2][0]*j<=d[0][0]*lam && d[1][1]*i+d[2][1]*j<=d[0][1]*lam && d[1][2]*i+d[2][2]*j<=d[0][2]*lam; ++j)
            {
                int k = (d[0][p]*lam - d[1][p]*i - d[2][p]*j) / d[3][p], kk;
                for (kk = 0; kk < 3; ++kk)
                {
                    if (d[1][kk]*i + d[2][kk]*j + d[3][kk]*k != d[0][kk]*lam)
                        break;
                }
                if (kk == 3)
                {
                    printf("%d %d %d %d\n", i, j, k, lam);
                    return 0;
                }
            }
    }
    printf("NONE\n");
    return 0;
}

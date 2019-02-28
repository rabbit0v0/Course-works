//
//  wtf.cpp
//  cpp'
//
//  Created by 施晓钰 on 02/08/2017.
//  Copyright © 2017 施晓钰. All rights reserved.
//

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <cmath>
#include <map>
using namespace std;
ifstream fin ("/Users/jinxiufen/Documents/cpp'/cpp'/public.txt");
ifstream ffin ("/Users/jinxiufen/Documents/cpp'/cpp'/private.txt");
struct tim{
    double one, two, three;
    int timesone, timestwo, timesthree, time1, time2, time3;
};
tim use[100000];
bool done[100000];

int main(){
    while(fin){
        int a, b, d;
        double t;
        fin >> a >> b >> d >> t;
        if (d == 1){
            use[a].one = (use[a].one * use[a].timesone + t) / (use[a].timesone + 1);
            use[a].timesone++;
            use[b].one = (use[b].one * use[b].timesone + t) / (use[b].timesone + 1);
            use[b].timesone++;
        }
        else if (d == 2){
            use[a].two = (use[a].two * use[a].timestwo + t) / (use[a].timestwo + 1);
            use[a].timestwo++;
            use[b].two = (use[b].two * use[b].timestwo + t) / (use[b].timestwo + 1);
            use[b].timestwo++;
        }
        else if (d == 3){
            use[a].three = (use[a].three * use[a].timesthree + t) / (use[a].timesthree + 1);
            use[a].timesthree++;
            use[b].three = (use[b].three * use[b].timesthree + t) / (use[b].timesthree + 1);
            use[b].timesthree++;
        }
    }
    while (ffin){
        int a, b, d;
        double t;
        ffin >> a >> b >> d >> t;
        if (d == 1){
            if (use[a].one && (use[a].one - t > 0.4 * use[a].one || t - use[a].one > 0.4 * use[a].one) && !done[a]){
                cout << a << '\n';
                done[a] = 1;
            }
            else{
                use[a].time1++;
                use[a].one = (use[a].one * (use[a].timesone + use[a].time1 - 1) + t) / (use[a].timesone + use[a].time1);
            }
            if (use[b].one && (use[b].one - t > 0.4 * use[b].one || t - use[b].one > 0.4 * use[b].one) && !done[b]){
                cout << b << '\n';
                done[b] = 1;
            }
            else{
                use[b].time1++;
                use[b].one = (use[b].one * (use[b].timesone + use[b].time1 - 1) + t) / (use[b].timesone + use[b].time1);
            }
        }
        else if (d == 2){
            if (use[a].two && (use[a].two - t > 0.4 * use[a].two || t - use[a].two > 0.4 * use[a].two) && !done[a]){
                cout << a << '\n';
                done[a] = 1;
            }
            else{
                use[a].time2++;
                use[a].two = (use[a].two * (use[a].timestwo + use[a].time2 - 1) + t) / (use[a].timestwo + use[a].time2);
            }
            if (use[b].two && (use[b].two - t > 0.4 * use[b].two || t - use[b].two > 0.4 * use[b].two) && !done[b]){
                cout << b << '\n';
                done[b] = 1;
            }
            else{
                use[b].time2++;
                use[b].two = (use[b].two * (use[b].timestwo + use[b].time2 - 1) + t) / (use[b].timestwo + use[b].time2);
            }
        }
        else if (d == 3){
            if (use[a].three && (use[a].three - t > 0.4 * use[a].three || t - use[a].three > 0.4 * use[a].three) && !done[a]){
                done[a] = 1;
                cout << a << '\n';
            }
            else{
                use[a].time3++;
                use[a].three = (use[a].three * (use[a].timesthree + use[a].time3 - 1) + t) / (use[a].timesthree + use[a].time3);
            }
            if (use[b].three && (use[b].three - t > 0.4 * use[b].three || t - use[b].three > 0.4 * use[b].three) && !done[b]){
                done[b] = 1;
                cout << b << '\n';
            }
            else{
                use[b].time3++;
                use[b].three = (use[b].three * (use[b].timesthree + use[b].time3 - 1) + t) / (use[b].timesthree + use[b].time3);
            }
        }
    }
}

//
//  main.cpp
//  mips
//
//  Created by 施晓钰 on 2017/6/26.
//  Copyright © 2017年 幺幺. All rights reserved.
//

#include <iostream>
#include "Header.hpp"
using namespace std;

int main(int argc, char* argv[]) {
    //fin.open(argv[1]);
    sto();
    regs.reg[37].data = getin;
    //fin.close();
    while (1){
        stream.cal();
        stream.RB();
        stream.MA();
        stream.EX();
        stream.ID();
        stream.IF();
        stream.unlock();
    }

    return 0;
}

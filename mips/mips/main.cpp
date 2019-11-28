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
    fin.open(argv[1]);
    sto();
    regs.reg[37].data = getin;
    fin.close();
    while (1){
        stream[0].IF();
        stream[0].ID();
        stream[0].EX();
        stream[0].MA();
        stream[0].RB();
    }
    
    return 0;
}

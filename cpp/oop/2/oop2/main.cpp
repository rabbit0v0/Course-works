#include <iostream>
#include <string>
#include <fstream>
#include "lispexprocessorclass.hpp"
using namespace std;
int main(int argc, char *argv[])
{
    string input_path, output_path;
    if (argc < 3)
    {
        cout << "for usage as an non-interactive tool: lispex <your lisp source code> <outputname>" << endl;
        cout << "Please input your source code path:";
        getline(cin, input_path);
        cout << "Please input the output name of the generated TeX code:";
        getline(cin, output_path);
    }
    else {
        input_path = string(argv[1]);
        output_path = string(argv[2]);
    }
    ifstream fin(input_path);
    ofstream fout(output_path);
    LisPeXProcessor.compile(fin, fout);
    fin.close();
    fout.close();
    return 0;
}
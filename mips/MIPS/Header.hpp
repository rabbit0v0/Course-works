#ifndef Header_h
#define Header_h
#include <iostream>
#include <cstdio>
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
using namespace std;
//ifstream fin;
ifstream fin("../testdata/array_test1-mahaojun.s");
ifstream fcin("../testdata/array_test1-mahaojun.in");
//ifstream cin("../test.txt");
class Fc{
public:
    int func;
    long rdest, rsrc1, rsrc2;
    int src, EX_MA_kind, EX_MA_reg;//registers' numbers & the imm number
    long gotolabel, res1, res2;
    bool EX_MA_go;
    int iniline;
    vector<int> vec;
    string labelname;
    Fc(){
        EX_MA_go = 0;
        func = -1, rdest = -1, rsrc1 = -1, rsrc2 = -1, src = 0, labelname = "", gotolabel = -1, res1 = 0, res2 = 0, EX_MA_kind = 0;
        iniline = -1;
    }
};
Fc textope[100000]; int textamo = 0;
map<string, long> datamap;
map<string, long> textmap;

class STORAGE{
public:
    int up = 0;
    unsigned char storage[4194305] = {0};
    STORAGE(){
        up = 0;
    }
    void align(int n){
        while ((up % (int)pow(2, n)) != 0) up++;
    }
    void ascii(vector<int> vec){
        int len = vec.size();
        for (int i = 0; i < len; i++) {
            storage[up++] = (char)vec[i];
        }
    }
    void bytein(vector<int> vec){
        int len = vec.size();
        for (int i = 0; i < len; i++) storage[up++] = vec[i];
    }
    void halfin(vector<int> vec){
        int len = vec.size();
        for (int i = 0; i < len; i++){
            storage[up++] = (char)((vec[i] & 0xFF00) >> 8);
            storage[up++] = (char)(vec[i] & 0xFF);
        }
    }
    void wordin(vector<int> vec){
        int len = vec.size();
        for (int i = 0; i < len; i++){
            storage[up++] = (char)((vec[i] >> 24) & 0xFF);
            storage[up++] = (char)((vec[i] >> 16) & 0xFF);
            storage[up++] = (char)((vec[i] >> 8) & 0xFF);
            storage[up++] = (char)(vec[i] & 0xFF);
        }
    }
    void space(int n) {up += n;}
};
STORAGE st;

class REGISTER{
    struct registers{
        long data;
        registers(){
            data = 0;//data?
        }
    };
public:
    registers reg[40];
    REGISTER(){
        reg[29].data = 4194303;
    }

};
REGISTER regs;

Fc funcs(string l, string oop){
    Fc opr;
    if (oop == "\t.align"){
        int i = oop.length() + 1;
        int sum = 0;
        while (i < l.length()){
            sum = sum * 10 + l[i++] - 48;
        }
        st.align(sum);
    }
    else if (oop == "\t.ascii"){
        int i = oop.length() + 2;
        while (i < l.length() - 1) {
            if (l[i] == '\\') {
                if (l[++i] == '\\')
                    opr.vec.push_back('\\');
                else if (l[i] == 'n')
                    opr.vec.push_back('\n');
                else if (l[i] == '0')
                    opr.vec.push_back('\0');
                else if (l[i] == 't')
                    opr.vec.push_back('\t');
                else if (l[i] == 'r')
                    opr.vec.push_back('\r');
                i++;
                continue;
            }
            opr.vec.push_back(l[i++]);
        }
        st.ascii(opr.vec);
    }
    else if (oop == "\t.asciiz"){
        int i = oop.length() + 2;
        while (i < l.length() - 1) {
            if (l[i] == '\\') {
                if (l[++i] == '\\')
                    opr.vec.push_back('\\');
                else if (l[i] == 'n')
                    opr.vec.push_back('\n');
                else if (l[i] == '0')
                    opr.vec.push_back('\0');
                else if (l[i] == 't')
                    opr.vec.push_back('\t');
                else if (l[i] == 'r')
                    opr.vec.push_back('\r');
                else if (l[i] == '\'')
                    opr.vec.push_back('\'');
                else if (l[i] == '\"')
                    opr.vec.push_back('\"');
                i++;
                continue;
            }
            //d cout << l[i];
            opr.vec.push_back(l[i++]);
        }
        opr.vec.push_back('\0');
        //for (int j = 0; j < opr.vec.size() ; ++j){
//            cout << opr.vec[j];
        //}
        st.ascii(opr.vec);
    }
    else if (oop == "\t.byte"){
        int i = oop.length() + 1;
        while (i < l.length()){
            if (l[i] == '\\') {
                if (l[++i] == '\\')
                    opr.vec.push_back('\\');
                else if (l[i] == 'n')
                    opr.vec.push_back('\n');
                else if (l[i] == '0')
                    opr.vec.push_back('\0');
                else if (l[i] == 't')
                    opr.vec.push_back('\t');
                else if (l[i] == 'r')
                    opr.vec.push_back('\r');
                else if (l[i] == '\'')
                    opr.vec.push_back('\'');
                else if (l[i] == '\"')
                    opr.vec.push_back('\"');
                i += 3;
                continue;
            }
            int sum = 0, sym = 1;
            while (l[i] != ' ' && l[i] != ',' && l[i] != '\0'){
                if (l[i] == '-'){
                    sym = -1;
                    i++;
                    continue;
                }
                sum = sum * 10 + l[i++] - 48;
            }
            sum *= sym;
            opr.vec.push_back(sum);
            i += 3;
        }
        st.bytein(opr.vec);
    }
    else if (oop == "\t.half"){
        int i = oop.length() + 1;
        while (i < l.length()){
            int sum = 0, sym = 1;
            while (l[i] != ' ' && l[i] != ',' && l[i] != '\0'){
                if (l[i] == '-'){
                    sym = -1;
                    i++;
                    continue;
                }
                sum = sum * 10 + l[i++] - 48;
            }
            sum *= sym;
            opr.vec.push_back(sum);
            i += 3;
        }
        st.halfin(opr.vec);
    }
    else if (oop == "\t.word"){
        int i = oop.length() + 1;
        while (i < l.length()){
            int sum = 0, sym = 1;
            while (l[i] != ' ' && l[i] != ',' && l[i] != '\0'){
                if (l[i] == '-'){
                    sym = -1;
                    i++;
                    continue;
                }
                sum = sum * 10 + l[i++] - 48;
            }
            sum *= sym;
            opr.vec.push_back(sum);
            i += 3;
        }
//        for (int j = 0; j < opr.vec.size(); ++j){
//            cout << opr.vec[j] << ' ';
//        }
        st.wordin(opr.vec);
    }
    else if (oop == "\t.space"){
        int i = oop.length() + 1;
        int sum = 0;
        while (i < l.length()){
            sum = sum * 10 + l[i++] - 48;
        }
        st.space(sum);
    }
    return opr;
}

long trans (char* p, int k){//if $number???
    long tem = 0;
    if (p[1] >= 48 && p[1] <= 57){
        int i = 1;
        while(i < k) tem = tem * 10 + p[i++] - 48;
    }
    if (p[1] == 'a' && p[2] == 't') tem = 1;
    else if (p[1] == 'v') tem = p[2] - 46;
    else if (p[1] == 'a') tem = p[2] - 44;
    else if (p[1] == 't') if (p[2] < '8' && p[2] >= '0') tem = p[2] - 40; else tem = p[2] - 24;
    else if (p[1] == 's') if (p[2] < '8' && p[2] >= '0') tem = p[2] - 32; else if (p[2] == 8) tem = 30; else tem = 29;
    else if (p[1] == 'k') tem = p[2] - 22;
    else if (p[1] == 'g') tem = 28;
    else if (p[1] == 'f') tem = 30;
    else if (p[1] == 'r') tem = 31;
    return tem;
}

int getin = 0;
Fc fromooptoFc(string l, int flag){
    char op[100] = {0};
    int i = 0;
    Fc opr;
    while(l[i] != ' ' && l[i] != '\0'){
        op[i] = l[i];
        i++;
    }
    i++;
    string oop = op;
    if (oop[1] == '.'){opr = funcs(l, oop);}
    else if (l[l.length() - 1] == ':'){
        opr.func = 0;
        int emm = 0;
        while (op[emm] == '\t' || op[emm] == ' ') emm++;
        int emmm = 0;
        char te[100] = {0};
        while (emm + emmm < oop.length() - 1) {te[emmm] = op[emm + emmm];emmm++;}
        string tem = te;
        if (flag == 0) {
//            datamap[tem] = stoamo;
            datamap[tem] = st.up;
//            cout << tem << ' ' << datamap[tem] << ' ' << st.up << '\n';
        }
        else {
            textmap[tem] = textamo;
            //cout<<textmap[tem]<<endl;
        }
        //cout << tem << '\n';
        if (tem == "main") {
            getin = textamo;
        }
    }
    else if (oop == "\tadd" || oop == "\taddu" || oop == "\taddiu" || oop == "\tsub" || oop == "\tsubu" || oop == "\txor" || oop == "\txoru" || oop == "\trem" || oop == "\tremu" || oop == "\tseq" || oop == "\tsge" || oop == "\tsgt" || oop == "\tsle" || oop == "\tslt" || oop == "\tsne"){
        if (oop == "\tadd") opr.func = 1;
        else if (oop == "\taddu") opr.func = 2;
        else if (oop == "\taddiu") opr.func = 3;
        else if (oop == "\tsub") opr.func = 4;
        else if (oop == "\tsubu") opr.func = 5;
        else if (oop == "\txor") opr.func = 14;
        else if (oop == "\txoru") opr.func = 15;
        else if (oop == "\trem") opr.func = 18;
        else if (oop == "\tremu") opr.func = 19;
        else if (oop == "\tseq") opr.func = 21;
        else if (oop == "\tsge") opr.func = 22;
        else if (oop == "\tsgt") opr.func = 23;
        else if (oop == "\tsle") opr.func = 24;
        else if (oop == "\tslt") opr.func = 25;
        else if (oop == "\tsne") opr.func = 26;
        for (int j = 0; j < 3; ++j){
            char c[5] = {0};
            int k = 0;
            while (l[i] == ' ') i++;
            while (l[i] != ',' && l[i] != '\0'){
                c[k] = l[i];
                i++, k++;
            }
            i++;
            if (c[0] == '$'){
                if (j == 0) opr.rdest = trans(c, k);
                else if (j == 1) opr.rsrc1 = trans(c, k);
                else if (j == 2) opr.rsrc2 = trans(c, k);
            }
            else {
                int k0 = 0, sym = 1;
                if (c[0] == '-') {sym = -1; k0++;}
                int sum = 0;
                while (k0 < k) sum = sum * 10 + (c[k0++] - 48);
                opr.src = sum * sym;
            }
        }
    }

    else if (oop == "\tmul" || oop == "\tmulu" || oop == "\tdiv" || oop == "\tdivu"){
        int cal = 0, now = i;
        while (now < l.length()){
            if (l[now] == ',')
                cal++;
            now++;
        }
        if (cal == 1){
            if (oop == "\tmul") opr.func = 8;
            else if (oop == "\tmulu") opr.func = 9;
            else if (oop == "\tdiv") opr.func = 12;
            else if (oop == "\tdivu") opr.func = 13;
            for (int j = 0; j < 2; ++j){
                char c[5];
                int k = 0;
                while (l[i] == ' ') i++;
                while (l[i] != ',' && l[i] != '\0'){
                    c[k] = l[i];
                    i++, k++;
                }
                i++;
                if (c[0] == '$'){
                    if (j == 0) opr.rdest = trans(c, k);
                    else if (j == 1) opr.rsrc2 = trans(c, k);
                }
                else {
                    int k0 = 0, sym = 1;
                    if (c[0] == '-'){sym = -1; k0++;}
                    int sum = 0;
                    while (k0 < k) sum = sum * 10 + (c[k0++] - 48);
                    opr.src = sum * sym;
                }
            }
        }
        else{
            if (oop == "\tmul") opr.func = 6;
            else if (oop == "\tmulu") opr.func = 7;
            else if (oop == "\tdiv") opr.func = 10;
            else if (oop == "\tdivu") opr.func = 11;
            for (int j = 0; j < 3; ++j){
                char c[5];
                int k = 0;
                while (l[i] == ' ') i++;
                while (l[i] != ',' && l[i] != '\0'){
                    c[k] = l[i];
                    i++, k++;
                }
                i++;
                if (c[0] == '$'){
                    if (j == 0) opr.rdest = trans(c, k);
                    else if (j == 1) opr.rsrc1 = trans(c, k);
                    else if (j == 2) opr.rsrc2 = trans(c, k);
                }
                else {
                    int k0 = 0, sym = 1;
                    if (c[0] == '-'){sym = -1; k0++;}
                    int sum = 0;
                    while (k0 < k) sum = sum * 10 + c[k0++] - 48;
                    opr.src = sum * sym;
                }
            }
        }
    }
    else if (oop == "\tneg" || oop == "\tnegu" || oop == "\tmove"){
        if (oop == "\tneg") opr.func = 16;
        else if (oop == "\tmove") opr.func = 51;
        else opr.func = 17;
        for (int j = 0; j < 2; ++j){
            char c[5];
            int k = 0;
            while (l[i] == ' ') i++;
            while (l[i] != ',' && l[i] != '\0'){
                c[k] = l[i];
                i++, k++;
            }
            if (j == 0) opr.rdest = trans(c, k);
            else opr.rsrc1 = trans(c, k);
            i++;
        }
    }
    else if (oop == "\tli"){
        opr.func = 20;
        char c[5];
        int k = 0;
        while (l[i] == ' ') i++;
        while (l[i] != ',' && l[i] != '\0'){
            c[k] = l[i];
            i++, k++;
        }
        //cout << "li : " << c << ' ';
        opr.rdest = trans(c, k);
        //cout << opr.rdest << '\n';
        k = 0; i++;
        while (l[i] == ' ') i++;
        while (l[i] != ',' && l[i] != '\0'){
            c[k] = l[i];
            i++, k++;
        }
        int k0 = 0, sym = 1;
        int sum = 0;
        if (c[0] == '-'){sym = -1; k0++;}
        while (k0 < k) sum = sum * 10 + c[k0++] - 48;
        opr.src = sum * sym;
    }
    else if (oop == "\tb" || oop == "\tj" || oop == "\tjal" || oop == "jal"){
        if (oop == "\tb") opr.func = 27;
        else if (oop == "\tj") opr.func = 40;
        else if (oop == "\tjal" || oop == "jal") opr.func = 42;
        while (l[i] == ' ') i++;
        while (l[i] != '\0') {
            opr.labelname = opr.labelname + l[i]; i++;
//            cout<<opr.labelname<<endl;
        }

    }
    else if (oop == "\tbeq" || oop == "\tbne" || oop == "\tbge" || oop == "\tble" || oop == "\tbgt" || oop == "\tblt"){
        if (oop == "\tbeq") opr.func = 28;
        else if (oop == "\tbne") opr.func = 29;
        else if (oop == "\tbge") opr.func = 30;
        else if (oop == "\tble") opr.func = 31;
        else if (oop == "\tbgt") opr.func = 32;
        else if (oop == "\tblt") opr.func = 33;
        for (int j = 0; j < 2; ++j){
            char c[5];
            int k = 0;
            while (l[i] == ' ') i++;
            while (l[i] != ',' && l[i] != '\0'){
                c[k] = l[i];
                i++, k++;
            }
            i++;
            if (c[0] == '$'){
                if (j == 0) opr.rsrc1 = trans(c, k);
                else if (j == 1) opr.rsrc2 = trans(c, k);
            }
            else{
                int k0 = 0, sym = 1;
                if (c[0] == '-'){sym = -1; k0++;}
                int sum = 0;
                while (k0 < k) sum = sum * 10 + c[k0++] - 48;
                opr.src = sum * sym;
            }
        }
        while (l[i] == ' ') i++;
        while (l[i] != '\0') {opr.labelname = opr.labelname + l[i]; i++;}
    }
    else if (oop == "\tbeqz" || oop == "\tbnez" || oop == "\tblez" || oop == "\tbgez" || oop == "\tbgtz" || oop == "\tbltz"){
        if (oop == "\tbeqz") opr.func = 34;
        else if (oop == "\tbnez") opr.func = 35;
        else if (oop == "\tblez") opr.func = 36;
        else if (oop == "\tbgez") opr.func = 37;
        else if (oop == "\tbgtz") opr.func = 38;
        else if (oop == "\tbltz") opr.func = 39;
        char c[5];
        int k = 0;
        while (l[i] == ' ') i++;
        while (l[i] != ',' && l[i] != '\0'){
            c[k] = l[i];
            i++, k++;
        }
        i++;
        opr.rsrc1 = trans(c, k);
        while (l[i] == ' ') i++;
        while (l[i] != '\0') {opr.labelname = opr.labelname + l[i]; i++;}
    }
    else if (oop == "\tjr" || oop == "\tjalr" || oop == "\tmfhi" || oop == "\tmflo"){
        if (oop == "\tjr") opr.func = 41;
        else if (oop == "\tjalr") opr.func = 43;
        else if (oop == "\tmfhi") opr.func = 52;
        else if (oop == "\tmflo") opr.func = 53;
        char c[5];
        int k = 0;
        while (l[i] == ' ')
            i++;
        while (l[i] != ',' && l[i] != '\0'){
            c[k] = l[i];
            i++, k++;
        }
        opr.rdest = trans(c, k);
    }
    else if (oop == "\tla" || oop == "\tlb" || oop == "\tlh" || oop == "\tlw" || oop == "\tsb" || oop == "\tsh" || oop == "\tsw"){
        if (oop == "\tla") opr.func = 44;
        else if (oop == "\tlb") opr.func = 45;
        else if (oop == "\tlh") opr.func = 46;
        else if (oop == "\tlw") opr.func = 47;
        else if (oop == "\tsb") opr.func = 48;
        else if (oop == "\tsh") opr.func = 49;
        else if (oop == "\tsw") opr.func = 50;
        char c[5];
        int k = 0;
        while (l[i] == ' ') i++;
        while (l[i] != ','){
            c[k] = l[i];
            i++, k++;
        }
        i += 2;
        opr.rdest = trans(c, k);
        k = 0;
        if (l[l.length() - 1] == ')'){
            while (l[i] == ' ') i++;
            int sym = 1;
            if (l[i] == '-') {sym = -1; i++;}
            int sum = 0;
            while (l[i] != '(') sum = sum * 10 + l[i++] - 48;
            opr.src = sum * sym;
            i++;
            while (l[i] == ' ') i++;
            while (l[i] != ')'){
                c[k] = l[i];
                i++, k++;
            }
            opr.rsrc1 = trans(c, k);
        }
        else{
            while (l[i] == ' ') i++;
            while (l[i] != '\0') {opr.labelname = opr.labelname + l[i]; i++;}
        }
    }
    else if (oop == "\tnop") opr.func = 54;
    else if (oop == "\tsyscall")opr.func = 55;
    return opr;
}

int linecnt =  0;

string stodata(){
    string line;
    while (getline(fin, line) && line != "\t.text"){
        linecnt ++;
        if (line == "\t.data" || line == "\t" || line == "") continue;
        fromooptoFc(line, 0);
    }
    linecnt ++;
    return line;
}

string stotext(){
    string line;
    while (getline(fin, line) && line != "\t.data"){
        linecnt ++;
        if (line == "\t.text" || line == "\t" || line == "") continue;
        Fc res = fromooptoFc(line, 1);
        res.iniline = linecnt;
        if (res.func){
            textope[textamo++] = res;
            //cout << textope[textamo-1].func << ' ' << textope[textamo-1].labelname << '\n';
        }
    }
    linecnt ++;
    return line;
}

void sto(){
    string line;
    getline(fin, line);
    linecnt ++;
    while(!fin.eof()){
        if (line == "\t.data") line = stodata();
        else if (line == "\t.text") line = stotext();
    }
//    for (int i = 0; i < st.up; ++i){
//        cout << (int)st.storage[i] << " ";
//    }
}

class flow{
    long IF_ID, temper[1000000] = {0};
    Fc ID_EX;
    int EX_MA_kind = -1, num0 = 0, num1 = 0, num2 = 0, num3 = 0, num4 = 0, calc = 0;
    char* EX_MA_c;
    bool EX_MA_go = 0;
    long EX_MA_gotolabel = 0, EX_MA_registernum = 0, EX_MA_res = 0, EX_MA_res2 = 0;
    long MA_RB = -1, MA_RB_res1 = -1, MA_RB_res2 = -1;
    bool locked[5];
public:
    flow (){
        IF_ID = -1; MA_RB = -1; EX_MA_c = nullptr; regs.reg[37].data = getin;
    }
    void cal(){
        calc = 0;
        for (int i = 0; i < 5; ++i){
            if (!locked[i])
                calc++;
        }
    }
    void IF(){
        if (!locked[0] && calc != 0) {
            num0++;
            if (num0 < calc) calc = num0;
            IF_ID = getin++;
            if (textope[IF_ID].func == 55 || (textope[IF_ID].func > 26 && textope[IF_ID].func < 44))
                locked[0] = 1;
            calc--;
        }
        if (IF_ID != -1) cout << '[' << textope[IF_ID].iniline << ']' << '\n';
//        if (IF_ID != -1) cout << '[' << IF_ID<< ']' << '\n';

    }
    void ID(){
        if (IF_ID != -1 && !locked[1] && calc != 0) {
            temper[++num1] = IF_ID;
            ID_EX = textope[IF_ID];
            if (num1 < calc) calc = num1;
            for (int i = 1; i < calc; ++i){
                if (temper[num1 - i] != -1 && (textope[temper[num1 - i]].rdest == ID_EX.rsrc1 || textope[temper[num1 - i]].rdest == ID_EX.rsrc2 || textope[temper[num1 - i]].rdest == ID_EX.rdest)){
                    locked[0] = 1;
                    locked[1] = 1;
                }
            }
            IF_ID = -1;
            calc--;
        }
    }
    void EX(){
        EX_MA_go = 0, EX_MA_kind = -1;
        EX_MA_gotolabel = -1, EX_MA_registernum = 0, EX_MA_res = 0, EX_MA_res2 = 0;
        EX_MA_registernum = ID_EX.rdest;
        EX_MA_gotolabel = textmap[ID_EX.labelname];
        if (ID_EX.func != -1 && !locked[2] && calc != 0) {
//            for (int i = 0; i < 5; ++i){
//                cout << locked[i] << ' ';
//            }
//            cout << '\n';
            for (int i = 0; i < 40; ++i){
                cout << i  << ' ' << regs.reg[i].data << "| |";
            }
            cout << '\n';
            ++num2;
            if (num2 < calc) calc = num2;
            if (ID_EX.func > 0 && ID_EX.func < 27) EX_MA_kind = 1;//cal
            if (ID_EX.func > 26 && ID_EX.func < 44) {
                EX_MA_kind = 6;//go to label
                EX_MA_gotolabel = textmap[ID_EX.labelname];
            }
            if (ID_EX.func == 8 || ID_EX.func == 9 || ID_EX.func == 12 || ID_EX.func == 13) EX_MA_kind = 5; // lo hi
            if (ID_EX.func > 43 && ID_EX.func < 48) EX_MA_kind = 2;// load
            if (ID_EX.func > 47 && ID_EX.func < 51) {//store
                EX_MA_kind = 3;
                EX_MA_res = regs.reg[ID_EX.rdest].data;
                EX_MA_gotolabel = datamap[ID_EX.labelname];
            }
            if (ID_EX.func > 50 && ID_EX.func < 54) EX_MA_kind = 1;//move
            if (ID_EX.func == 54) EX_MA_kind = 4;//nop
            if (ID_EX.func == 55) EX_MA_kind = 0;
            if (ID_EX.func == 1 || ID_EX.func == 2 || ID_EX.func == 3) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data + regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data + ID_EX.src;
            } else if (ID_EX.func == 4 || ID_EX.func == 5) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data - regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data - ID_EX.src;
            } else if (ID_EX.func == 6 || ID_EX.func == 7) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data * regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data * ID_EX.src;
            } else if (ID_EX.func == 8 || ID_EX.func == 9) {
                if (ID_EX.rsrc2 != -1) {
                    EX_MA_res = (long) ((regs.reg[ID_EX.rdest].data * regs.reg[ID_EX.rsrc2].data) & 0xFFFFFFFF);
                    EX_MA_res2 = (long) (((regs.reg[ID_EX.rdest].data * regs.reg[ID_EX.rsrc2].data) >> 32) &
                                         0xFFFFFFFF);
                } else {
                    EX_MA_res = (long) ((regs.reg[ID_EX.rdest].data * ID_EX.src) & 0xFFFFFFFF);
                    EX_MA_res2 = (long) (((regs.reg[ID_EX.rdest].data * ID_EX.src) >> 32) & 0xFFFFFFFF);
                }
            } else if (ID_EX.func == 10 || ID_EX.func == 11) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data / regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data / ID_EX.src;
            } else if (ID_EX.func == 12 || ID_EX.func == 13) {
                if (ID_EX.rsrc2 != -1) {
                    EX_MA_res = regs.reg[ID_EX.rdest].data / regs.reg[ID_EX.rsrc2].data;
                    EX_MA_res2 = regs.reg[ID_EX.rdest].data % regs.reg[ID_EX.rsrc2].data;
                } else {
                    EX_MA_res = regs.reg[ID_EX.rdest].data / ID_EX.src;
                    EX_MA_res2 = regs.reg[ID_EX.rdest].data % ID_EX.src;
                }
            } else if (ID_EX.func == 14 || ID_EX.func == 15) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data ^ regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data ^ ID_EX.src;
            } else if (ID_EX.func == 16 || ID_EX.func == 17) {
                EX_MA_res = -regs.reg[ID_EX.rsrc1].data;
            } else if (ID_EX.func == 18 || ID_EX.func == 19) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = regs.reg[ID_EX.rsrc1].data % regs.reg[ID_EX.rsrc2].data;
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data % ID_EX.src;
            } else if (ID_EX.func == 20) {
                EX_MA_res = ID_EX.src;
            } else if (ID_EX.func == 21) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data == regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data == ID_EX.src);
            } else if (ID_EX.func == 22) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data >= regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data >= ID_EX.src);
            } else if (ID_EX.func == 23) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data > regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data > ID_EX.src);
            } else if (ID_EX.func == 24) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data <= regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data <= ID_EX.src);
            } else if (ID_EX.func == 25) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data < regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data < ID_EX.src);
            } else if (ID_EX.func == 26) {
                if (ID_EX.rsrc2 != -1) EX_MA_res = (regs.reg[ID_EX.rsrc1].data != regs.reg[ID_EX.rsrc2].data);
                else EX_MA_res = (regs.reg[ID_EX.rsrc1].data != ID_EX.src);
            } else if (ID_EX.func == 27 || ID_EX.func == 40) EX_MA_go = 1;
            else if (ID_EX.func == 28) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data == regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data == ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 29) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data != regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data != ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 30) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data >= regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data >= ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 31) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data <= regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data <= ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 32) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data > regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data > ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 33) {
                if ((ID_EX.rsrc2 != -1 && (regs.reg[ID_EX.rsrc1].data < regs.reg[ID_EX.rsrc2].data)) ||
                    (ID_EX.rsrc2 == -1 && (regs.reg[ID_EX.rsrc1].data < ID_EX.src)))
                    EX_MA_go = 1;
            } else if (ID_EX.func == 34) {
                if (regs.reg[ID_EX.rsrc1].data == 0) EX_MA_go = 1;
            } else if (ID_EX.func == 35) {
                if (regs.reg[ID_EX.rsrc1].data != 0) EX_MA_go = 1;
            } else if (ID_EX.func == 36) {
                if (regs.reg[ID_EX.rsrc1].data <= 0) EX_MA_go = 1;
            } else if (ID_EX.func == 37) {
                if (regs.reg[ID_EX.rsrc1].data >= 0) EX_MA_go = 1;
            } else if (ID_EX.func == 38) {
                if (regs.reg[ID_EX.rsrc1].data > 0) EX_MA_go = 1;
            } else if (ID_EX.func == 39) {
                if (regs.reg[ID_EX.rsrc1].data < 0) EX_MA_go = 1;
            } else if (ID_EX.func == 41) {
                EX_MA_go = 1;
                EX_MA_gotolabel = regs.reg[ID_EX.rdest].data;
            } else if (ID_EX.func == 42) {
                EX_MA_go = 1;
                regs.reg[31].data = temper[num2] + 1;
            } else if (ID_EX.func == 43) {
                EX_MA_go = 1;
                regs.reg[31].data = temper[num2] + 1;
                EX_MA_gotolabel = regs.reg[ID_EX.rdest].data;
            } else if (ID_EX.func == 44) {//to change (others)
                if (ID_EX.rsrc1 == -1) EX_MA_res = datamap[ID_EX.labelname];
                else EX_MA_res = regs.reg[ID_EX.rsrc1].data + ID_EX.src;
            } else if (ID_EX.func == 45 || ID_EX.func == 46 || ID_EX.func == 47 || ID_EX.func == 48 ||
                       ID_EX.func == 49 || ID_EX.func == 50) {//to change
                if (ID_EX.rsrc1 == -1) EX_MA_gotolabel = datamap[ID_EX.labelname];
                else EX_MA_gotolabel = regs.reg[ID_EX.rsrc1].data + ID_EX.src;
                EX_MA_res = regs.reg[ID_EX.rdest].data;
            } else if (ID_EX.func == 51) {
                EX_MA_res = regs.reg[ID_EX.rsrc1].data;
            } else if (ID_EX.func == 52) {
                EX_MA_res = regs.reg[34].data;
            } else if (ID_EX.func == 53) {
                EX_MA_res = regs.reg[33].data;
            } else if (ID_EX.func == 55) {
                if (regs.reg[2].data == 1)
                    printf("%ld", regs.reg[4].data);
                else if (regs.reg[2].data == 4) {
                    EX_MA_gotolabel = regs.reg[4].data;
                    EX_MA_kind = 10;
                } else if (regs.reg[2].data == 5) {
                    //scanf("%ld", &regs.reg[2].data);
                    fcin >> regs.reg[2].data;
                    //cout << "regs.reg[2].data" << regs.reg[2].data << '\n';
                } else if (regs.reg[2].data == 8) {
                    EX_MA_kind = 11;
                    EX_MA_res = regs.reg[5].data;
                    char *tmp = new char[EX_MA_res];
                    //scanf("%s", tmp);
                    fcin >> tmp;
                    EX_MA_gotolabel = regs.reg[4].data;
                    EX_MA_c = tmp;
                } else if (regs.reg[2].data == 9) {
                    EX_MA_kind = 12;
                    EX_MA_res = regs.reg[4].data;
                    EX_MA_registernum = 2;
                } else if (regs.reg[2].data == 10) exit(0);
                else if (regs.reg[2].data == 17) exit((int) regs.reg[4].data);
            }
            textope[temper[num2]].gotolabel = EX_MA_gotolabel;
            textope[temper[num2]].res1 = EX_MA_res;
            textope[temper[num2]].res2 = EX_MA_res2;
            textope[temper[num2]].EX_MA_kind = EX_MA_kind;
            textope[temper[num2]].EX_MA_reg = EX_MA_registernum;
            textope[temper[num2]].EX_MA_go = EX_MA_go;
            for (int i = 1; i < calc; ++i){
                if (temper[num2 - i] != -1 && EX_MA_gotolabel != -1 && EX_MA_gotolabel == textope[temper[num2 - i]].gotolabel){
                    locked[0] = 1;
                    locked[1] = 1;
                    locked[2] = 1;
                }
            }
            ID_EX.func = -1;
            calc--;
        }
    }
    void MA(){
        if (EX_MA_kind != -1 && calc != 0) {
            num3++;
            if (textope[temper[num3]].EX_MA_kind == 2) {
                if (textope[temper[num3]].func == 45) {
                    MA_RB = st.storage[textope[temper[num3]].gotolabel];
                }
                if (textope[temper[num3]].func == 46) {
                    MA_RB = (long) (((st.storage[textope[temper[num3]].gotolabel] & 0xFF) << 8) |
                                    (st.storage[textope[temper[num3]].gotolabel + 1] & 0xFF));
                }
                if (textope[temper[num3]].func == 47) {
                    MA_RB = (long) (((st.storage[textope[temper[num3]].gotolabel] & 0xFF) << 24)
                                    | ((st.storage[textope[temper[num3]].gotolabel + 1] & 0xFF) << 16)
                                    | ((st.storage[textope[temper[num3]].gotolabel + 2] & 0xFF) << 8)
                                    | (st.storage[textope[temper[num3]].gotolabel + 3] & 0xFF));
                    //cout << "lw" << MA_RB << ' ';
                }
            } else if (textope[temper[num3]].EX_MA_kind == 3) {
                if (textope[temper[num3]].func == 48) {
                    st.storage[textope[temper[num3]].gotolabel] = EX_MA_res;
                }
                if (textope[temper[num3]].func == 49) {
                    st.storage[textope[temper[num3]].gotolabel] = (char) ((textope[temper[num3]].res1 & 0xFF00) >> 8);
                    st.storage[textope[temper[num3]].gotolabel + 1] = (char) (textope[temper[num3]].res1 & 0xFF);
                }
                if (textope[temper[num3]].func == 50) {
                    st.storage[textope[temper[num3]].gotolabel] = (char) ((textope[temper[num3]].res1 >> 24) & 0xFF);
                    st.storage[textope[temper[num3]].gotolabel + 1] = (char) ((textope[temper[num3]].res1 >> 16) & 0xFF);
                    st.storage[textope[temper[num3]].gotolabel + 2] = (char) ((textope[temper[num3]].res1 >> 8) & 0xFF);
                    st.storage[textope[temper[num3]].gotolabel + 3] = (char) (textope[temper[num3]].res1 & 0xFF);

                    //cout << "sw" << EX_MA_res << ' ';
                }
            } else if (textope[temper[num3]].EX_MA_kind == 10) {
                char p[100000] = {'\0'};
                int q = 0;
                while (st.storage[EX_MA_gotolabel + q] != '\0') {
                    p[q] = st.storage[EX_MA_gotolabel + q];
                    q++;
                }
                //cout << '(' << IF_ID << ')';
                printf("%s", p);
            } else if (textope[temper[num3]].EX_MA_kind == 11) {
                int i = 0;
                while (i < strlen(EX_MA_c)) {
                    st.storage[textope[temper[num3]].gotolabel + i] = EX_MA_c[i];
                    i++;
                }
                delete[]EX_MA_c;
            } else if (textope[temper[num3]].EX_MA_kind == 12) {
                MA_RB = st.up;
                st.up += textope[temper[num3]].res1;
            }
            if(MA_RB == -1) MA_RB = 0;
            EX_MA_kind = -1;
            calc--;
        }
    }
    void RB(){
        if (MA_RB == -1 || calc == 0) return;
        num4++;
        if (num4 < calc) calc = num4;
        if (textope[temper[num4]].EX_MA_kind == 1){
            regs.reg[textope[temper[num4]].EX_MA_reg].data = textope[temper[num4]].res1;
        }
        else if (textope[temper[num4]].EX_MA_kind == 2){
            if (textope[temper[num4]].func == 44) regs.reg[textope[temper[num4]].rdest].data = textope[temper[num4]].res1;
            else regs.reg[EX_MA_registernum].data = MA_RB;
        }
        else if (textope[temper[num4]].EX_MA_kind == 5){
            regs.reg[33].data = textope[temper[num4]].res1;
            regs.reg[34].data = textope[temper[num4]].res2;
        }
        else if (textope[temper[num4]].EX_MA_kind == 6){
            if (textope[temper[num4]].EX_MA_go){
                regs.reg[37].data = textope[temper[num4]].gotolabel;
                getin = regs.reg[37].data;
            }
        }
        else if (textope[temper[num4]].EX_MA_kind == 12){
            regs.reg[2].data = MA_RB;
        }
        if (!textope[temper[num4]].EX_MA_go){
            regs.reg[37].data++;
        }
        MA_RB = -1;
//        for (int i = 0; i < 40; ++i){
//            cout << i << ' ' << regs.reg[i].data << '||';
//        }
//        cout << '\n';
    }

    void unlock(){
        if (MA_RB == -1 && EX_MA_kind == -1){
            locked[2] = 0;
            if (ID_EX.func == -1){
                locked[1] = 0;
                if (IF_ID == -1)
                    locked[0] = 0;
            }
        }
    }
};
flow stream;


#endif /* Header_h */

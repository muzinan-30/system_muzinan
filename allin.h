#pragma once
// 封装头文件
#include<iostream>
#include<string>
#include<vector>
#include <fstream>
//#include <windows.h>

#include "pch.h"

using namespace std;
vector<string> classical = {"Caesar cipher","Keyword cipher","Affine cipher",
"Multiliteral cipher","Vigenere cipher",/*"Autokey ciphertext",*/"Autokey plaintext","Playfair cipher",
"Permutation cipher","Column permutation cipher","Double-Transposition cipher"
};

namespace streamcipher 
{
    class RC4
    {
    public:
        void SetStable(char* K, int keylen);
        void Transform(char* output, const char* data, int len);
        void TranFile(const char* filename, char* K);
    private:
        unsigned char S[256];
    };

    class CA
    {
    public:
        void SetRule(int rule);
        void Change(char* cell, int n);
        void SetSream(char* cell, int cellnum, int len);
        /*void*/string Transform(char* output, const char* data);
        void TranFile(const char* filename, char* cell, int rule, int cellnum);
    private:
        int tranrule[8] = { 0,0,0,0,0,0,0,0 };
        vector<char> Kstream;
        string result="";
    };
};





#include"pch.h"
#include "allin.h"

void streamcipher::RC4::SetStable(char* K, int keylen)
{
    for (int i = 0; i < 256; i++)
    {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + S[i] + K[i % keylen]) % 256;
        swap(S[i], S[j]);
    }
}


void streamcipher::RC4::Transform(char* output, const char* data, int len)
{
    int i = 0, j = 0;
    for (int k = 0; k < len; k++)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        unsigned char key = S[(S[i] + S[j]) % 256];
        output[k] = key ^ data[k];
    }
}


void streamcipher::RC4::TranFile(const char* filename, char* K)
{
    ifstream input;
    input.open(filename, ios::out | ios::binary);
    if (!input)
    {
        exit(1);
    }
    string str = "";
    char c;
    while ((c = input.get()) && c != EOF) { 
        str += c;
    }
    char output[256] = "";
    int keylen = sizeof(K);
    RC4 rc4;
    rc4.SetStable(K, keylen);
    string outstr = "";
    const char* readfile = str.data();
    char data[256] = "";
    int num = 0, len = strlen(readfile);
    for (int i = 0; i < len; i++)
    {
        data[num] = readfile[i];
        num++;
        if (num >= 256 || i == len - 1)
        {
            num = 0;
            rc4.Transform(output, data, strlen(data));
            for (int j = 0; j < 256; j++)
            {
                data[j] = 'Z^';
            }
            outstr += output;
        }
    }

    input.close();
    ofstream outfile;
    outfile.open(filename, ios::out | ios::trunc | ios::binary);
    const char* outchar = outstr.data();
    for (int i = 0; i < strlen(outchar); i++)
    {
        outfile.put(outchar[i]);
    }
    outfile.close();
}




//生成规则
void streamcipher::CA::SetRule(int rule)
{
    for (int i = 0; i < 8; i++)
    {
        tranrule[i] = 0;
    }
    for (int i = 7; i >= 0; i--)
    {
        //转换二进制，生成置换规则
        tranrule[i] = rule % 2;
        rule = (rule - tranrule[i]) / 2;
    }
}
//CA置换
void streamcipher::CA::Change(char* cell, int n)
{
    int front = n - 1, after = n + 1;
    if (front < 0)
    {
        front = strlen(cell) - 1;
    }
    if (after > 0)
    {
        after = 0;
    }
    int num = 0;
    if (cell[front] == '1')
    {
        num = num * 2 + 1;
    }
    if (cell[n] == '1')
    {
        num = num * 2 + 1 * 2;
    }
    if (cell[after] == '1')
    {
        num = num * 2 + 1;
    }
    cell[n] = tranrule[num] + '0';
}
//生成密钥流
void streamcipher::CA::SetSream(char* cell, int cellnum, int len)
{
    int celllen = strlen(cell);
    for (int i = 0; i < len; i++)
    {
        Kstream.push_back(cell[cellnum]);
        for (int j = 0; j < celllen; j++)
        {
            Change(cell, j);
        }
    }
}
//进行转换
string streamcipher::CA::Transform(char* output, const char* data)
{
    int len = strlen(data);
    
    for (int i = 0; i < len; i++)
    {
        output[i] = data[i] ^ Kstream[i];
        result += data[i] ^ Kstream[i];
    }
    return result;
}
//文件内容转换
//传入文件名，密钥,规则，种子
void streamcipher::CA::TranFile(const char* filename, char* cell, int rule, int cellnum)
{
    cout << "filename" << filename << endl;
    cout << "cell" << cell << endl;
    cout << "rule" << rule << endl;
    cout << "cellnum" << cellnum << endl;
    ifstream input;
    input.open(filename, ios::out | ios::binary);
    if (!input)
    {
        cout << "数据集标注的文件不存在，请检查路径！" << endl;
        exit(1);
    }
    string str = "";
    char c;
    while ((c = input.get()) && c != EOF) { //一直读到文件结束
        str += c;
    }
    const char* data = str.data();
    int len = strlen(data);
    cout << len << endl;
    char* output = new char[len];
    cout << "明文" << data << endl;
    //以上是相关的需要数据
    //明文，种子，规则数字，选择密钥流的生成位置

    //运用CA类进行密钥流的生成与加解密
    CA ca;
    ca.SetRule(rule);
    ca.SetSream(cell, cellnum, len);
    ca.Transform(output, data);
    input.close();
    ofstream outfile;
    outfile.open(filename, ios::out | ios::trunc | ios::binary);
    for (int i = 0; i < len; i++)
    {
        outfile.put(output[i]);
    }
    outfile.close();
}

//int main()
//{
//    char data[] = "Here is a test";
//    char cell[] = "0010100";
//    char output[sizeof(data)] = "";
//    int rule = 14;
//    int cellnum;
//    cout << "输入所选种子生成器的第几位生成密钥（小于等于" << sizeof(cell) << "，规则为14)";
//    cin >> cellnum;
//    cellnum--;
//    //以上是相关的需要数据
//    //明文，种子，规则数字，选择密钥流的生成位置
//    printf("明文:%s\n", data);
//    int len = sizeof(data);
//    //运用CA类进行密钥流的生成与加解密
//    streamcipher::CA ca;
//    ca.SetRule(rule);
//    ca.SetSream(cell, cellnum, len);
//    ca.Transform(output, data);
//    printf("密文: %s\n", output);
//    ca.Transform(output, output);
//    printf("解密后明文: %s\n", output);
//
//
//    CA cafile;
//    //文件的加解密
//    cafile.TranFile("文本.txt", cell, rule, cellnum);
//
//    return 0;
//}

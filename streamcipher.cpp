
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




//���ɹ���
void streamcipher::CA::SetRule(int rule)
{
    for (int i = 0; i < 8; i++)
    {
        tranrule[i] = 0;
    }
    for (int i = 7; i >= 0; i--)
    {
        //ת�������ƣ������û�����
        tranrule[i] = rule % 2;
        rule = (rule - tranrule[i]) / 2;
    }
}
//CA�û�
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
//������Կ��
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
//����ת��
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
//�ļ�����ת��
//�����ļ�������Կ,��������
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
        cout << "���ݼ���ע���ļ������ڣ�����·����" << endl;
        exit(1);
    }
    string str = "";
    char c;
    while ((c = input.get()) && c != EOF) { //һֱ�����ļ�����
        str += c;
    }
    const char* data = str.data();
    int len = strlen(data);
    cout << len << endl;
    char* output = new char[len];
    cout << "����" << data << endl;
    //��������ص���Ҫ����
    //���ģ����ӣ��������֣�ѡ����Կ��������λ��

    //����CA�������Կ����������ӽ���
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
//    cout << "������ѡ�����������ĵڼ�λ������Կ��С�ڵ���" << sizeof(cell) << "������Ϊ14)";
//    cin >> cellnum;
//    cellnum--;
//    //��������ص���Ҫ����
//    //���ģ����ӣ��������֣�ѡ����Կ��������λ��
//    printf("����:%s\n", data);
//    int len = sizeof(data);
//    //����CA�������Կ����������ӽ���
//    streamcipher::CA ca;
//    ca.SetRule(rule);
//    ca.SetSream(cell, cellnum, len);
//    ca.Transform(output, data);
//    printf("����: %s\n", output);
//    ca.Transform(output, output);
//    printf("���ܺ�����: %s\n", output);
//
//
//    CA cafile;
//    //�ļ��ļӽ���
//    cafile.TranFile("�ı�.txt", cell, rule, cellnum);
//
//    return 0;
//}

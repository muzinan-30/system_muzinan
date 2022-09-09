#include"pch.h"

#include<iostream>
#include<fstream>
#include<string>
#include <sstream>      //要使用stringstream流应包含此头文件
#include <vector>
using namespace std;

const int N = 50;



static std::string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

namespace classicalcipher
{

	//列置换密码的实现
	//列置换
	//处理密钥
	static int* dealKeyword(std::string key)
	{

		for (int i = 0; i < key.size(); i++)
			key[i] = toupper(key[i]);
		int* k = new int[key.length()];
		int* index = new int[key.length()];
		for (int i = 0; i < key.length(); i++)
		{
			index[i] = alpha.find_first_of(key[i]);
		}
		for (int i = 0; i < key.size(); i++)
		{
			int temp = index[i];
			int flag = 1;
			for (int j = 0; j < key.size(); j++) {
				if (temp == index[j] && i > j) flag++;
				if (temp > index[j]) flag++;
			}
			k[i] = flag;
		}
		return k;
	}
	//处理明文
	static char** dealP(string P, const int colNum)
	{
		int rowNum = 0;
		int flag = colNum - P.length() % colNum;
		cout << "flag" << flag;
		if (P.length() % colNum == 0)
			rowNum = P.length() / colNum;
		else
		{
			rowNum = P.length() / colNum + 1;
			for (int i = 1; i <= flag; i++)
			{
				//使用&进行填充
				P = P + '&';
			}
		}
		cout << P;
		char** matrix = new  char* [rowNum];
		for (int i = 0; i < rowNum; i++)
			matrix[i] = new char[colNum];
		int count = 0;
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				matrix[i][j] = P[count++];
			}
		}
		return matrix;
	}
	//列置换
	static char** cpc_exchange(char** matrix, int* k, int row, int col)
	{
		char** newmatrix = new  char* [row];
		for (int i = 0; i < row; i++)
			newmatrix[i] = new char[col];
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int index = k[j] - 1;
				newmatrix[i][index] = matrix[i][j];
			}
		}
		return newmatrix;
	}
	//处理密文
	static char** dealC(const string C, const int colNum)
	{
		int row = C.length() / colNum;
		char** matrix = new  char* [row];
		for (int i = 0; i < row; i++)
			matrix[i] = new char[colNum];
		int count = 0;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < colNum; j++) {
				matrix[i][j] = C[count++];
			}
		}
		return matrix;
	}
	//反转密钥
	static int* reserveK(const string& key)
	{
		int* k = dealKeyword(key);
		int* res = new int[key.length()];
		for (int i = 0; i < key.length(); i++)
		{
			int flag = 0;
			for (int j = 0; j < key.length(); j++)
			{
				if (k[j] == (i + 1)) break;
				else flag++;
			}
			res[i] = flag + 1;
		}
		return res;
	}
	//加密方法
	static string cpc_encrypt(string p, string key)
	{
		int* k = dealKeyword(key);
		int colNum = key.length();
		int rowNum = p.length() % colNum == 0 ? p.length() / colNum : p.length() / colNum + 1;
		char** matrix = dealP(p, colNum);
		char** newmatrix = cpc_exchange(matrix, k, rowNum, colNum);
		string s;
		//按照行取出
		for (int i = 0; i < rowNum; i++)
		{
			for (int j = 0; j < colNum; j++)
			{
				s += newmatrix[i][j];
			}
		}

		return s;
	}
	//解密方法
	static string cpc_decrypt(string c, const string key)
	{
		int* k = reserveK(key);
		int colNum = key.length();
		int rowNum = c.length() / colNum;
		char** matrix = dealC(c, colNum);
		char** newmatrix = cpc_exchange(matrix, k, rowNum, colNum);
		string p;
		//按照行取出
		for (int i = 0; i < rowNum; i++)
		{
			for (int j = 0; j < colNum; j++)
			{
				p += newmatrix[i][j];
			}
		}
		return p;
	}
	//文件加密
	static void cpc_encryptFile(char* filename, string key)
	{
		ifstream inFile;
		ofstream outFile;
		ostringstream buf;
		inFile.open(filename);
		if (!inFile.is_open()) {
			cout << "Could not open the file:" << filename << endl;
			cout << "Program terminating!\n";
			exit(EXIT_FAILURE);
		}
		string s;
		/*char ch;
		while (!inFile.eof()&&inFile.get(ch))
		{
			buf.put(ch);
		}
		s = buf.str();*/
		getline(inFile, s);
		cout << s.length();
		cout << s << endl;;
		string res = cpc_encrypt(s, key);
		outFile.open("cpc_outfile.txt");
		outFile << res;
		inFile.close();
		outFile.close();
	}
	//文件解密
	static void cpc_decryptFile(char* filename, string key)
	{
		ifstream inFile;
		ofstream outFile;
		ostringstream buf;
		inFile.open(filename);
		if (!inFile.is_open()) {
			cout << "Could not open the file:" << filename << endl;
			cout << "Program terminating!\n";
			exit(EXIT_FAILURE);
		}
		string s;
		char ch;
		while (!inFile.eof() && inFile.good())
		{
			inFile.get(ch);
			buf.put(ch);
		}
		s = buf.str();
		string res = cpc_decrypt(s, key);
		outFile.open("cpc_infile.txt");
		outFile << res;
		inFile.close();
		outFile.close();
	}


	//置换密码
	//处理密钥
	//static  int* dealKey(string s)
	//{
	//	int* k = new int[s.length()];
	//	int* res = new int[s.length()];
	//	for (int i = 0; i < s.size(); i++)  s[i] = toupper(s[i]);
	//	for (int i = 0; i < s.size(); i++)
	//	{
	//		k[i] = alpha.find_first_of(s[i]);
	//	}

	//	for (int i = 0; i < s.size(); i++)
	//	{
	//		int flag = 0;
	//		for (int j = 0; j < s.size(); j++)
	//		{
	//			if (k[j] >= k[i]) flag++;
	//		}
	//		//cout << flag;
	//		res[i] = flag;
	//	}

	//	return res;
	//}
	//加密
	static  string pc_encrpty(string s, string key)
	{

		int* k = dealKeyword(key);
		//for (int i = 0; i < key.length(); i++) cout << k[i];
		if (s.length() % key.length() != 0)
		{
			for (int i = 0; i < (key.length() - s.length() % key.length()); i++)
				s += '&';
		}
		string s1;
		for (int i = 0; i < s.length(); i += key.length())
		{
			char* temp = new char[key.length()];
			for (int j = 0; j < key.length(); j++)
			{
				temp[k[j] - 1] = s[i + j];
			}
			for (int j = 0; j < key.length(); j++)
			{
				s1 += temp[j];
			}
		}
		return s1;
	}
	//密钥处理
	static int* reserveKey(string key)
	{
		int* k = dealKeyword(key);
		int* res = new int[key.length()];
		for (int i = 0; i < key.length(); i++)
		{
			int flag = 0;
			for (int j = 0; j < key.length(); j++)
			{
				if (k[j] == (i + 1)) break;
				else flag++;
			}
			res[i] = flag + 1;
			//cout << res[i];
		}
		return res;
	}
	//解密
	static string pc_decrpty(string s, string key)
	{
		int* k = reserveKey(key);
		string s1;
		for (int i = 0; i < s.length(); i += key.length())
		{
			char* temp = new char[key.length()];
			for (int j = 0; j < key.length(); j++)
			{
				temp[k[j] - 1] = s[i + j];

			}
			for (int j = 0; j < key.length(); j++)
			{
				s1 += temp[j];
			}
		}

		int index = s1.find_first_of('&');
		if (index != string::npos)
		{
			s1.erase(index);
		}
		return s1;
	}


	//double 置换
	static string dcpc_encrpty(string p, string key1, string key2)
	{
		return  cpc_encrypt(cpc_encrypt(p, key1), key2);
	}
	static string dcpc_decrpty(string c, string key1, string key2)
	{
		return  cpc_decrypt(cpc_decrypt(c, key2), key1);
	}


	//凯撒密码

//凯撒密码的加密算法,str表示要加密的字符串，offset表示偏移量
	void Caesar_encryption(char* str, int offset) {
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] = ((str[i] - 'A') + offset) % 26 + 'A';
			}
			else if (str[i] >= 'a' && str[i] <= 'z')
			{
				str[i] = ((str[i] - 'a') + offset) % 26 + 'a';
			}
		}
		//cout << "加密结果为：" << str << endl;
	}

//凯撒密码的解密算法,str表示要解密的字符串，offset表示偏移量
	void Caesar_decryption(char* str, int offset) {
		int b_offset;
		b_offset = 26 - offset;
		for (int i = 0; i < strlen(str); i++)
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
			{
				str[i] = ((str[i] - 'A') + b_offset) % 26 + 'A';
			}
			else if (str[i] >= 'a' && str[i] <= 'z')
			{
				str[i] = ((str[i] - 'a') + b_offset) % 26 + 'a';
			}
		}
		//cout << "解密结果为：" << str << endl;
	}

	//affine cipher
	int find_s(int a) {
		for (int i = 1; i < 26; i++) {
			if ((a * i) % 26 == 1) {
				return i;
			}
		}
	}

	string affine_encrypt(int a, int b, string message) {
		string result;
		for (int i = 0; i < message.size(); i++) {
			char ch = message[i];
			if (ch >= 'a' && ch <= 'z')
			{
				result+=(char)((((ch - 97) *a +b)%26) + 97);
			}
			else if (ch >= 'A' && ch <= 'Z')
			{
				result+= (char)((((ch - 65)*a + b)%26) + 65);
			}
		}
		return result;
	}
	string affine_decrypt(int a, int b, string cipher) {
		int s = find_s(a);
		for (int i = 0; i < cipher.size(); i++) {
			char ch = cipher[i];
			if (ch>= 'a' && ch <= 'z')
			{
				cipher[i] = (((ch - 'a') - b + 26) * s) % 26 + 'a';
			}
			else if (ch >= 'A' && ch <= 'Z')
			{
				cipher[i] = (((ch - 'A') - b + 26) * s) % 26 + 'A';
			}
		}
		return cipher;
	}

	//keyword cipher
	string table(string key, int len)
	{
		string table;
		//char table[26];
		int count = 0;
		int len_1 = 0;
		char key1[20];
		key1[0] = key[0];
		//去重操作
		for (int i = 1; i < len; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (key[i] == key[j]) {
					len_1++; break;
				}
				else key1[i] = key[i];
			}
		}


		len = len - len_1;
		for (int i = 0; i < len + 1; i++)
		{
			if (i < len) table += key[i];
			if (i >= len)
			{
				for (int j = 0; j < 26; j++)
				{
					for (int k = 0; k < len; k++)
					{
						if (j + 97 == key[k]) break;
						else count++;
					}
					if (count == len) {
						table += j + 97;  i++;
					}
					count = 0;
				}
			}
		}
		return table;
	}
	string keyword_encryption(string p, string key)
	{
		string cipher;
		string tab = table(key, key.size());
		for (int i = 0; i < p.size(); i++)
		{
			cipher += tab[p[i] - 97];
		}
		return cipher;
	}
	string keyword_decryption(string c, string key)
	{
		
		//char* plain = (char*)malloc(len_c * sizeof(char));
		string plain;
		string tab = table(key, key.size());
		for (int i = 0; i <c.size(); i++)
		{
			for (int j = 0; j < 26; j++)
			{
				if (tab[j] == c[i]) plain += 97 + j;
			}
		}
		return plain;
	}



	//vignere密码 
	//加密 
	string vignere_encrypt(string p, string k)
	{
		string c = "";
		int lk = k.size(), pl = p.size(), s = 0;
		for (int i = 0; i < pl; i++)
		{
			//其它字符 
			if (p[i] >= 'a' && p[i] <= 'z')
			{
				int j = (i - s) % lk;
				c += (p[i] - 'a' + k[j] - 'a') % 26 + 'a';

			}
			else if (p[i] >= 'A' && p[i] <= 'Z')
			{
				int j = (i - s) % lk;
				c += (p[i] - 'A' + k[j] - 'a') % 26 + 'A';
			}
			else
			{
				c += p[i];
				s++;
			}
		}
		return c;
	}
	//解密
	string vignere_decrypt(string c, string k)
	{
		string p = "";
		int lk = k.size(), cl = c.size(), s = 0;
		for (int i = 0; i < cl; i++)
		{
			//其它字符 
			if (c[i] >= 'a' && c[i] <= 'z')
			{
				int j = (i - s) % lk;
				p += (c[i] - 'a' + 26 - (k[j] - 'a')) % 26 + 'a';
			}
			else if (c[i] >= 'A' && c[i] <= 'Z')
			{
				int j = (i - s) % lk;
				p += (c[i] - 'A' + 26 - (k[j] - 'a')) % 26 + 'a';
			}
			else
			{
				p += c[i];
				s++;
			}
		}
		return p;
	}


	//Multiliteral
	char keytable[5][5] = { 'a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };
	string Multiliteral_encryption(string plaintext, string key)
	{
		int len = plaintext.size();
		string ciphertext;
		for (int i = 0; i < len; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					if (keytable[j][k] == plaintext[i])
					{
						ciphertext += key[j];
						ciphertext += key[k];
					}
				}
			}
		}
		return ciphertext;
	}
	string Multiliteral_decryption(string ciphertext, string key)
	{
		int l = 0;
		int len = ciphertext.size();
		string plaintext;
		for (int i = 0; i < len; i += 2)
		{
			for (int j = 0; j < 5; j++)
			{
				if (ciphertext[i] == key[j])
				{
					for (int k = 0; k < 5; k++)
					{
						if (ciphertext[i + 1] == key[k])
						{
							plaintext += keytable[j][k];
						}
					}

				}

			}
		}

		return plaintext;
	}


	//autoplain
	string autoplain_encrypt(char* key, const char* ptext)
	{
		string cipher;
		for (int i = 0; i < strlen(ptext); i++)
		{
			if (i < strlen(key))
				cipher += char((key[i] - 'a' + ptext[i] - 'a') % 26 + 'a');
			else
				cipher += char((ptext[i - strlen(key)] - 'a' + ptext[i] - 'a') % 26 + 'a');
		}
		return cipher;
	}

	string autoplain_decrypt(char* key, const char* ctext)
	{
		string plain;
		for (int i = 0; i < strlen(ctext); i++)
		{
			if (i < strlen(key))
				plain += (ctext[i] + 26 - key[i]) % 26 + 'a';
			else
				plain += (ctext[i] + 26 - plain[i - strlen(key)]) % 26 + 'a';
		}
		return plain;
	}
	void autoplain_encryptfile(char* key, const char* filename)
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
		const char* data = str.data();
		int len = strlen(data);
		//char* output = new char[len];
		string output=autoplain_encrypt(key, data);

		input.close();
		ofstream outfile;
		outfile.open(filename, ios::out | ios::trunc | ios::binary);
		for (int i = 0; i < len; i++)
		{
			outfile.put(output[i]);
		}
		outfile.close();
	}

	void autoplain_decryptfile(char* key, const char* filename)
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
		const char* data = str.data();
		int len = strlen(data);
		//char* output = new char[len];

		string output=autoplain_decrypt(key, data);

		input.close();
		ofstream outfile;
		outfile.open(filename, ios::out | ios::trunc | ios::binary);
		/*for (int i = 0; i < len; i++)
		{
			outfile.put(output[i]);
		}*/
		outfile << output;
		outfile.close();
	}



	//auto cipher
	string plaintext;
	string ciphertext;
	string keyword;
	char Vigenere_table[26][26];//vigenere表
	void Vigenere_Init();//初始化vigenere表
	string enAutocipher(string a, string b);//加密函数
	string readFileIntoString(char* filename);//文件读取函数

	string readFileIntoString(char* filename)
	{
		ifstream ifile(filename);
		//将文件读入到ostringstream对象buf中
		ostringstream buf;
		char ch;
		while (buf && ifile.get(ch))
			buf.put(ch);
		//返回与流对象buf关联的字符串
		return buf.str();
	}
	string enAutocipher(string a, string b) {
		ciphertext = "";
		plaintext = a;
		keyword = b;
		Vigenere_Init();
		for (int i = 0; i < plaintext.size(); i++) {
			int x = keyword[i] - 97;
			int y = plaintext[i] - 97;
			ciphertext += Vigenere_table[x][y];
			keyword += ciphertext[i];
		}
		return ciphertext;
	}

	void Vigenere_Init() {

		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				Vigenere_table[i][j] = 97 + (i + j) % 26;   //明文为小写字母
			}
		}
		return;
	}

	string deAutocipher(string a, string b) {
		plaintext = "";
		ciphertext = a;
		keyword = b;
		for (int i = 0; i < ciphertext.size(); i++) {
			int x = keyword[i] - 97;
			int y = ciphertext[i] - 97;
			cout << x << " " << y << endl;
			int z = y - x;
			while (z < 0) z += 26;
			z += 97;
			char temp = z;
			plaintext += temp;
			keyword += ciphertext[i];
		}
		return  plaintext;
	}
}


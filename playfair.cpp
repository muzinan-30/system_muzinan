#include"pch.h"

#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include <sstream>
using namespace std;
int word[26] = { 0 };//26����ĸ�����������Ϊ1���Դ���ȷ��ɸ���ؼ����е��ظ��� 
string keyword;//�ؼ���
string  map[5][5];//5*5����
string null_number = "q";
string table[26];//������Ÿ�����ĸ��5*5map�ϵ����꣬table��ÿһ����λ��������ʮ���Ƶ����� 
string plaintext;
int row[26] = { 0 }, line[26] = { 0 };//��¼����ĸ��map�ϵ�λ�� 
string ciphertext;
string readFileIntoString(char* filename);
string readFileIntoString(char* filename)
{
	ifstream ifile(filename);
	//���ļ����뵽ostringstream����buf��
	ostringstream buf;
	char ch;
	while (buf && ifile.get(ch))
		buf.put(ch);
	//������������buf�������ַ���
	return buf.str();
}

void Init_plaintext(string plaintext) {
	for (int i = 0; i < plaintext.size(); i++) {
		if (plaintext[i] == 'j') plaintext[i] = 'i';//��j��i���� 
		if (plaintext[i] == plaintext[i + 1]) plaintext.insert(i + 1, null_number);//�����������ַ������м����nullnumber��q 
	}
	if (plaintext.size() % 2 != 0) plaintext += "q";//������������������油��null_number
	return;
}

void slim(string keyword) {
	int i = 0;
	string key = "";
	word[9] = 1;
	for (i = 0; i < keyword.size(); i++) {
		int temp = keyword[i] - 'a';
		if (word[temp] == 1)
			continue;
		else {
			word[temp] = 1;
			key += keyword[i];
		}
	}
	keyword = key;
}

void Init_table(string keyword) {
	int size = 0;
	int begin = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (size < keyword.size()) {
				map[i][j] = keyword[size];
				row[keyword[size] - 'a'] = i;//��¼asci��Ϊkeyword[size]-'a'����ĸ��map �ĺ����� 
				line[keyword[size] - 'a'] = j;//��¼������ 
				size++;
			}
			else {

				for (; begin < 26; begin++) {
					if (word[begin] == 0) {
						char temp = 'a' + begin;
						map[i][j] = temp;
						row[begin] = i;
						line[begin] = j;
						begin++;
						break;
					}
				}

			}
		}
	}
}

string enplayfair(string plaintext, string keyword) {
	ciphertext = "";
	slim(keyword);
	Init_table(keyword);
	Init_plaintext(plaintext);
	int num = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < plaintext.size() / 2; i++) {

		int row1 = row[plaintext[num] - 'a'], line1 = line[plaintext[num++] - 'a'];
		int row2 = row[plaintext[num] - 'a'], line2 = line[plaintext[num++] - 'a'];

		if (row1 == row2) {
			ciphertext += map[row1][(line1 + 1) % 5];
			ciphertext += map[row2][(line2 + 1) % 5];
		}
		else if (line1 == line2) {
			ciphertext += map[(row1 + 1) % 5][line1];
			ciphertext += map[(row2 + 1) % 5][line2];
		}
		else {
			ciphertext += map[row1][line2];
			ciphertext += map[row2][line1];
		}
	}
	return ciphertext;
}

string deplayfair(string plaintext,string keyword) {

	ciphertext = "";
	slim(keyword);
	Init_table(keyword);
	int num = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}

	for (int i = 0; i < plaintext.size() / 2; i++) {

		int row1 = row[plaintext[num] - 'a'], line1 = line[plaintext[num++] - 'a'];
		int row2 = row[plaintext[num] - 'a'], line2 = line[plaintext[num++] - 'a'];
		/*	cout<<"("<<row1<<","<<line1<<")"<<endl;
			cout<<"("<<row2<<","<<line2<<")"<<endl;*/
		if (row1 == row2) {
			ciphertext += map[row1][(line1 - 1) % 5];
			ciphertext += map[row2][(line2 - 1) % 5];
		}
		else if (line1 == line2) {
			ciphertext += map[(row1 - 1) % 5][line1];
			ciphertext += map[(row2 - 1) % 5][line2];
		}
		else {
			ciphertext += map[row1][line2];
			ciphertext += map[row2][line1];
		}
	}
	return  ciphertext;
}
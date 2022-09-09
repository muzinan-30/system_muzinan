#include"pch.h"

#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
#include <sstream>
using namespace std;
int word[26] = { 0 };//26个字母，如果出现置为1，以此来确保筛出关键字中的重复项 
string keyword;//关键字
string  map[5][5];//5*5矩阵
string null_number = "q";
string table[26];//用来存放各个字母在5*5map上的坐标，table的每一个单位都是两个十进制的数字 
string plaintext;
int row[26] = { 0 }, line[26] = { 0 };//记录各字母在map上的位置 
string ciphertext;
string readFileIntoString(char* filename);
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

void Init_plaintext(string plaintext) {
	for (int i = 0; i < plaintext.size(); i++) {
		if (plaintext[i] == 'j') plaintext[i] = 'i';//将j用i代替 
		if (plaintext[i] == plaintext[i + 1]) plaintext.insert(i + 1, null_number);//出现连续的字符，在中间插入nullnumber：q 
	}
	if (plaintext.size() % 2 != 0) plaintext += "q";//如果明文是奇数，后面补充null_number
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
				row[keyword[size] - 'a'] = i;//记录asci码为keyword[size]-'a'的字母在map 的横坐标 
				line[keyword[size] - 'a'] = j;//记录纵坐标 
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
#include"pch.h"

#include<iostream>
#include<fstream>
#include<string>
#include <sstream>      //要使用stringstream流应包含此头文件
#include<cmath>
#include<algorithm>
#include<cstring>
#include<malloc.h>
#include<fstream>
using namespace std;

namespace DESEN
{
	string p;//十六进制明文
	string plaintext;//二进制明文
	string pl = "                                                 ", pr = "                                                 ";//32位明文左右部分 
	string Key;//十六进制密钥
	string key;//64位二进制密钥
	string xkey;//用于异或操作的56位密钥 
	int pc_1[] = { 56,48,40,32,24,16,8,
				  0,57,49,41,33,25,17,
				  9,1,58,50,42,34,26,
				  18,10,2,59,51,43,35,
				  62,54,46,38,30,22,14,
				  6,61,53,45,37,29,21,
				  13,5,60,52,44,36,28,
				  20,12,4,27,19,11,3 };
	int IP_1[] = { 57,49,41,33,25,17,9,1,
					 59,51,43,35,27,19,11,3,
					 61,53,45,37,29,21,13,5,
					 63,55,47,39,31,23,15,7,
					 56,48,40,32,24,16,8,0,
					 58,50,42,34,26,18,10,2,
					 60,52,44,36,28,20,12,4,
					 62,54,46,38,30,22,14,6 };

	int E_box[] = { 31, 0, 1, 2, 3, 4,
					  3,  4, 5, 6, 7, 8,
					  7,  8,9,10,11,12,
					  11,12,13,14,15,16,
					  15,16,17,18,19,20,
					  19,20,21,22,23,24,
					  23,24,25,26,27,28,
					  27,28,29,30,31, 0 };
	int s_box[8][4][16] =//S1
	{ {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
	  {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
	  {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
	  {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
		//S2
		{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
		//S3
		{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		  {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
		//S4
		{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
		//S5
		{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
		//S6
		{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
		//S7
		{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
		//S8
		{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}} };

	int Pbox[] = { 15,6,19,20,28,11,27,16,
				  0,14,22,25,4,17,30,9,
				  1,7,23,13,31,26,2,8,
				  18,12,29,5,21,10,3,24 };
	int pc_2[] = { 13,16,10,23,0,4,
			2,27,14,5,20,9,
			22,18,11,3,25,7,
			15,6,26,19,12,1,
			40,51,30,36,46,54,
			29,39,50,44,32,47,
			43,48,38,55,33,52,
			45,41,49,35,28,31 };
	int IP_2[64] = { 39,7,47,15,55,23,63,31,
					38,6,46,14,54,22,62,30,
					37,5,45,13,53,21,61,29,
					36,4,44,12,52,20,60,28,
					35,3,43,11,51,19,59,27,
					34,2,42,10,50,18,58,26,
					33,1,41,9,49,17,57,25,
					32,0,40,8,48,16,56,24 };
	string keyl = "", keyr = "";//28位左右密钥			               
	string hex_bin(string a);//十六进制转化为二进制 
	void IP1();//IP置换函数 
	void slice_p();//分割明文 
	void e_box();//E_box函数 
	string Xor(string a, string b);//逐bit异或函数 ,都是48位数据 
	int bin_dec(string a);//把6bit字符串转化为十进制 
	string  dec_bin(int a);//把十进制数转化为二进制字符串 
	void S_box();//S_box函数
	void P_box();//P_box函数 
	void PC_1();//密钥的pc_1置换 并生成左右两部分密钥 
	void Shift_Row();//循环左移函数 
	string PC_2();//密钥的pc_2置换 
	string enDES(string aa, string bb);//DES加密函数 
	void IP2();//IP2置换函数 
	string hex(string st2);//二进制转化为十六进制 
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
	string hex(string st2)//将64位二进制码转换为16位16进制码
	{

		string st = "";
		int a[4] = { 8,4,2,1 };
		int buf;

		for (int i = 0; i < 16; i++)
		{
			buf = 0;
			for (int j = 0; j < 4; j++)
			{
				buf = buf + (st2[i * 4 + j] == '1' ? a[j] : 0);   //先把二进制转化为十进制 
			}
			switch (buf) {
			case 0: st += "0"; break;
			case 1: st += "1"; break;
			case 2: st += "2"; break;
			case 3: st += "3"; break;
			case 4: st += "4"; break;
			case 5: st += "5"; break;
			case 6: st += "6"; break;
			case 7: st += "7"; break;
			case 8: st += "8"; break;
			case 9: st += "9"; break;
			case 10: st += "A"; break;
			case 11: st += "B"; break;
			case 12: st += "C"; break;
			case 13: st += "D"; break;
			case 14: st += "E"; break;
			case 15: st += "F"; break;
			}
		}
		return st;
	}


	void IP2() {
		string temp = "";
		for (int i = 0; i < 64; i++) {
			temp += plaintext[IP_2[i]];
		}
		plaintext = temp;
		return;
	}
	
	string PC_2() {
		string a = keyl + keyr;
		string temp1 = "";
		for (int i = 0; i < 48; i++) {
			temp1 += a[pc_2[i]];
		}
		return temp1;
	}

	void Shift_Row() {
		string temp1 = "", temp2 = "";
		for (int i = 1; i < 28; i++) temp1 += keyl[i];
		for (int i = 1; i < 28; i++) temp2 += keyr[i];
		temp1 += keyl[0];
		temp2 += keyr[0];
		keyl = temp1;
		keyr = temp2;
		return;
	}

	void PC_1() {
		string temp1 = "";
		for (int i = 0; i < 56; i++) {
			temp1 += key[pc_1[i]];
		}
		key = temp1;
		for (int i = 0; i < 28; i++)  keyl += key[i];
		for (int i = 28; i < 56; i++) keyr += key[i];

		return;
	}


	void P_box() {
		string temp = "";
		for (int i = 0; i < 32; i++) {
			temp += pr[Pbox[i]];
		}
		pr = temp;
		return;
	}


	string  dec_bin(int a) {

		string temp = "";
		int key = 8;
		int i;
		for (i = 0; i < 4; i++) {
			temp += (key & a) ? "1" : "0";
			key >>= 1;
		}
		return temp;
	}


	int bin_dec(string a) {

		int temp = 0;
		for (int i = 0; i < a.size(); i++) {
			temp += pow(2, a.size() - 1 - i) * (a[i] - '0');
		}
		return temp;
	}

	void S_box() {

		string ans = "";
		string s_slice[8] = { "        ","        " ,"        " ,"        " ,"        " ,"        " ,"        " ,"        " };//把48bit的右半部分明文分成8个6比特的字符串 
		int pos = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				s_slice[i][j] = pr[pos];
				pos++;

			}
		}

		string temp = "";
		for (int i = 0; i < 8; i++) {
			string a = "", b = "";
			if (s_slice[i][0] == '1') a += "1";
			else a += "0";
			if (s_slice[i][5] == '1') a += "1";
			else a += "0";

			if (s_slice[i][1] == '1') b += "1";
			else b += "0";
			if (s_slice[i][2] == '1') b += "1";
			else b += "0";
			if (s_slice[i][3] == '1') b += "1";
			else b += "0";
			if (s_slice[i][4] == '1') b += "1";
			else b += "0";

			int x, y;
			x = bin_dec(a);

			y = bin_dec(b);

			int store = s_box[i][x][y];

			ans += dec_bin(store);

		}

		pr = ans;
		return;
	}


	string Xor(string a, string b) {

		string temp = "";

		for (int i = 0; i < 48; i++) {
			if (a[i] == b[i]) temp += "0";
			else temp += "1";
		}

		return temp;
	}

	void e_box() {

		string temp = "";
		for (int i = 0; i < 48; i++) {
			temp += pr[E_box[i]];
		}
		pr = temp;
		return;
	}

	void slice_p() {
		pl = "";
		pr = "";
		for (int i = 0; i < 32; i++)
			pl += plaintext[i];
		for (int i = 32; i < 64; i++)
			pr += plaintext[i];
		return;
	}

	void IP1() {

		string temp = "";
		for (int i = 0; i < 64; i++) {
			temp += plaintext[IP_1[i]];
		}
		plaintext = temp;
		return;
	}

	string hex_bin(string a)//将16位16进制码转换为64位二进制码(不足8位高位补0)
	{

		string ans = "";
		for (int i = 0; i < 16; i++)
		{
			switch (a[i])   // swith语句对十六机制转化为二进制 
			{
			case '0':ans += "0000"; break;
			case '1':ans += "0001"; break;
			case '2':ans += "0010"; break;
			case '3':ans += "0011"; break;
			case '4':ans += "0100"; break;
			case '5':ans += "0101"; break;
			case '6':ans += "0110"; break;
			case '7':ans += "0111"; break;
			case '8':ans += "1000"; break;
			case '9':ans += "1001"; break;
			case 'A':ans += "1010"; break;
			case 'B':ans += "1011"; break;
			case 'C':ans += "1100"; break;
			case 'D':ans += "1101"; break;
			case 'E':ans += "1110"; break;
			case 'F':ans += "1111"; break;
			}
		}
		return ans;   //结果返回 
	}

string enDES(string aa, string bb) {


			p = aa;
			Key = bb;

			plaintext = hex_bin(p);

			key = hex_bin(Key);

			IP1();//初始置换 

			PC_1();//去掉校验位 

			slice_p();//明文分成左右两部分 



			string l, r;
			for (int t = 0; t < 16; t++) {


				l = pl;
				r = pr;
				pl = r;
				e_box();//ebox对右部分明文进行扩充

				/*密钥生成*/
				switch (t) {
				case 0: Shift_Row(); break;
				case 1:Shift_Row(); break;
				case 8:Shift_Row(); break;
				case 15:Shift_Row(); break;
				default:	Shift_Row();
					Shift_Row();
					break;
				}

				string temp_key = PC_2();

				string york = "";
				for (int i = 0; i < 48; i++) {
					if (temp_key[i] == pr[i]) york += "0";
					else york += "1";
				}

				pr = york;

				//S盒压缩 
				S_box();
				P_box();//p盒置换

				//更新明文：


				string o = "";

				for (int i = 0; i < 32; i++) {
					if (pr[i] == l[i]) o += "0";
					else o += "1";
				}
				pr = o;
			}

			plaintext = pr + pl;
			IP2();
		//cout << hex(plaintext);
		return hex(plaintext);
	}
}

namespace DESDE
{
	using namespace std;
	string p;//十六进制明文
	string plaintext;//二进制明文
	string pl = "", pr = "";//32位明文左右部分 
	string Key;//十六进制密钥
	string key;//64位二进制密钥
	string xkey;//用于异或操作的56位密钥 
	int pc_1[] = { 56,48,40,32,24,16,8,
				  0,57,49,41,33,25,17,
				  9,1,58,50,42,34,26,
				  18,10,2,59,51,43,35,
				  62,54,46,38,30,22,14,
				  6,61,53,45,37,29,21,
				  13,5,60,52,44,36,28,
				  20,12,4,27,19,11,3 };
	int IP_1[] = { 57,49,41,33,25,17,9,1,
					 59,51,43,35,27,19,11,3,
					 61,53,45,37,29,21,13,5,
					 63,55,47,39,31,23,15,7,
					 56,48,40,32,24,16,8,0,
					 58,50,42,34,26,18,10,2,
					 60,52,44,36,28,20,12,4,
					 62,54,46,38,30,22,14,6 };

	int E_box[] = { 31, 0, 1, 2, 3, 4,
					  3,  4, 5, 6, 7, 8,
					  7,  8,9,10,11,12,
					  11,12,13,14,15,16,
					  15,16,17,18,19,20,
					  19,20,21,22,23,24,
					  23,24,25,26,27,28,
					  27,28,29,30,31, 0 };
	int s_box[8][4][16] =//S1
	{ {{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
	  {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
	  {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
	  {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}},
		//S2
		{{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}},
		//S3
		{{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		  {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}},
		//S4
		{{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}},
		//S5
		{{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}},
		//S6
		{{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}},
		//S7
		{{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}},
		//S8
		{{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}} };

	int Pbox[] = { 15,6,19,20,28,11,27,16,
				  0,14,22,25,4,17,30,9,
				  1,7,23,13,31,26,2,8,
				  18,12,29,5,21,10,3,24 };
	int pc_2[] = { 13,16,10,23,0,4,
			2,27,14,5,20,9,
			22,18,11,3,25,7,
			15,6,26,19,12,1,
			40,51,30,36,46,54,
			29,39,50,44,32,47,
			43,48,38,55,33,52,
			45,41,49,35,28,31 };
	int IP_2[64] = { 39,7,47,15,55,23,63,31,
					38,6,46,14,54,22,62,30,
					37,5,45,13,53,21,61,29,
					36,4,44,12,52,20,60,28,
					35,3,43,11,51,19,59,27,
					34,2,42,10,50,18,58,26,
					33,1,41,9,49,17,57,25,
					32,0,40,8,48,16,56,24 };
	string keyl = "", keyr = "";//28位左右密钥
	string store_k[16];
	string hex_bin(string a);//十六进制转化为二进制 
	void IP1();//IP置换函数 
	void slice_p();//分割明文 
	void e_box();//E_box函数 
	string Xor(string a, string b);//逐bit异或函数 ,都是48位数据 
	int bin_dec(string a);//把6bit字符串转化为十进制 
	string  dec_bin(int a);//把十进制数转化为二进制字符串 
	void S_box();//S_box函数
	void P_box();//P_box函数 
	void PC_1();//密钥的pc_1置换 并生成左右两部分密钥 
	void Shift_Row();//循环左移函数 
	string PC_2();//密钥的pc_2置换 
	string enDES(string aa, string bb);//DES加密函数 
	void IP2();//IP2置换函数 
	string hex(string st2);//二进制转化为十六进制 
	string readFileIntoString(char* filename);//读取文件

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

	string hex(string st2)//将64位二进制码转换为16位16进制码
	{

		string st = "";
		int a[4] = { 8,4,2,1 };
		int buf;

		for (int i = 0; i < 16; i++)
		{
			buf = 0;
			for (int j = 0; j < 4; j++)
			{
				buf = buf + (st2[i * 4 + j] == '1' ? a[j] : 0);   //先把二进制转化为十进制 
			}
			switch (buf) {
			case 0: st += "0"; break;
			case 1: st += "1"; break;
			case 2: st += "2"; break;
			case 3: st += "3"; break;
			case 4: st += "4"; break;
			case 5: st += "5"; break;
			case 6: st += "6"; break;
			case 7: st += "7"; break;
			case 8: st += "8"; break;
			case 9: st += "9"; break;
			case 10: st += "A"; break;
			case 11: st += "B"; break;
			case 12: st += "C"; break;
			case 13: st += "D"; break;
			case 14: st += "E"; break;
			case 15: st += "F"; break;
			}
		}
		return st;
	}


	void IP2() {
		string temp = "";
		for (int i = 0; i < 64; i++) {
			temp += plaintext[IP_2[i]];
		}
		plaintext = temp;
		return;
	}
	string enDES(string aa, string bb) {

		p = aa;
		Key = bb;

		plaintext = hex_bin(p);

		key = hex_bin(Key);

		IP1();//初始置换 

		PC_1();//去掉校验位 

		slice_p();//明文分成左右两部分 

		for (int i = 0; i < 16; i++) {
			switch (i) {
			case 0: Shift_Row(); break;
			case 1:Shift_Row(); break;
			case 8:Shift_Row(); break;
			case 15:Shift_Row(); break;
			default:	Shift_Row();
				Shift_Row();
				break;
			}

			store_k[i] = PC_2();
		}

		string l, r;
		for (int t = 0; t < 16; t++) {


			l = pl;
			r = pr;
			pl = r;
			e_box();//ebox对右部分明文进行扩充

			/*密钥生成*/


			string york = "";
			for (int i = 0; i < 48; i++) {
				if (store_k[15 - t][i] == pr[i]) york += "0";
				else york += "1";
			}

			pr = york;

			//S盒压缩 
			S_box();
			P_box();//p盒置换

			//更新明文：


			string o = "";

			for (int i = 0; i < 32; i++) {
				if (pr[i] == l[i]) o += "0";
				else o += "1";
			}
			pr = o;
		}

		plaintext = pr + pl;
		IP2();
		return hex(plaintext);
	}

	string PC_2() {
		string a = keyl + keyr;
		string temp1 = "";
		for (int i = 0; i < 48; i++) {
			temp1 += a[pc_2[i]];
		}
		return temp1;
	}

	void Shift_Row() {
		string temp1 = "", temp2 = "";
		for (int i = 1; i < 28; i++) temp1 += keyl[i];
		for (int i = 1; i < 28; i++) temp2 += keyr[i];
		temp1 += keyl[0];
		temp2 += keyr[0];
		keyl = temp1;
		keyr = temp2;
		return;
	}

	void PC_1() {
		string temp1 = "";
		for (int i = 0; i < 56; i++) {
			temp1 += key[pc_1[i]];
		}
		key = temp1;
		for (int i = 0; i < 28; i++)  keyl += key[i];
		for (int i = 28; i < 56; i++) keyr += key[i];

		return;
	}


	void P_box() {
		string temp = "";
		for (int i = 0; i < 32; i++) {
			temp += pr[Pbox[i]];
		}
		pr = temp;
		return;
	}


	string  dec_bin(int a) {

		string temp = "";
		int key = 8;
		int i;
		for (i = 0; i < 4; i++) {
			temp += (key & a) ? "1" : "0";
			key >>= 1;
		}
		return temp;
	}


	int bin_dec(string a) {

		int temp = 0;
		for (int i = 0; i < a.size(); i++) {
			temp += pow(2, a.size() - 1 - i) * (a[i] - '0');
		}
		return temp;
	}


	void S_box() {

		string ans = "";
		string s_slice[8] = { "        ","        " ,"        " ,"        " ,"        " ,"        " ,"        " ,"        " };//把48bit的右半部分明文分成8个6比特的字符串 
		int pos = 0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 6; j++) {
				s_slice[i][j] = pr[pos++];

			}
		}

		string temp = "";
		for (int i = 0; i < 8; i++) {
			string a = "", b = "";
			if (s_slice[i][0] == '1') a += "1";
			else a += "0";
			if (s_slice[i][5] == '1') a += "1";
			else a += "0";

			if (s_slice[i][1] == '1') b += "1";
			else b += "0";
			if (s_slice[i][2] == '1') b += "1";
			else b += "0";
			if (s_slice[i][3] == '1') b += "1";
			else b += "0";
			if (s_slice[i][4] == '1') b += "1";
			else b += "0";

			int x, y;
			x = bin_dec(a);

			y = bin_dec(b);

			int store = s_box[i][x][y];

			ans += dec_bin(store);

		}

		pr = ans;
		return;
	}


	string Xor(string a, string b) {

		string temp = "";

		for (int i = 0; i < 48; i++) {
			if (a[i] == b[i]) temp += "0";
			else temp += "1";
		}

		return temp;
	}

	void e_box() {

		string temp = "";
		for (int i = 0; i < 48; i++) {
			temp += pr[E_box[i]];
		}
		pr = temp;
		return;
	}

	void slice_p() {
		pl = "";
		pr = "";
		for (int i = 0; i < 32; i++)
			pl += plaintext[i];
		for (int i = 32; i < 64; i++)
			pr += plaintext[i];
		return;
	}

	void IP1() {

		string temp = "";
		for (int i = 0; i < 64; i++) {
			temp += plaintext[IP_1[i]];
		}
		plaintext = temp;
		return;
	}

	string hex_bin(string a)//将16位16进制码转换为64位二进制码(不足8位高位补0)
	{

		string ans = "";
		for (int i = 0; i < 16; i++)
		{
			switch (a[i])   // swith语句对十六机制转化为二进制 
			{
			case '0':ans += "0000"; break;
			case '1':ans += "0001"; break;
			case '2':ans += "0010"; break;
			case '3':ans += "0011"; break;
			case '4':ans += "0100"; break;
			case '5':ans += "0101"; break;
			case '6':ans += "0110"; break;
			case '7':ans += "0111"; break;
			case '8':ans += "1000"; break;
			case '9':ans += "1001"; break;
			case 'A':ans += "1010"; break;
			case 'B':ans += "1011"; break;
			case 'C':ans += "1100"; break;
			case 'D':ans += "1101"; break;
			case 'E':ans += "1110"; break;
			case 'F':ans += "1111"; break;
			}
		}
		return ans;   //结果返回 
	}

}

namespace AESEN
{
	string p[4][4];//十六进制明文 128位，16字节的明文矩阵 
	char* plaintext;//128位明文
	char* key;//128位bit的初始密钥 
	string K[4][4];//十六进制初始密钥，128位，16字节的密钥矩阵
	string SBOX[16][16] = {
		{"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76"},
		{"CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0"},
		{"B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15"},
		{"04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75"},
		{"09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84"},
		{"53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF"},
		{"D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8"},
		{"51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2"},
		{"CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73"},
		{"60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB"},
		{"E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79"},
		{"E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08"},
		{"BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A"},
		{"70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E"},
		{"E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF"},
		{"8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"},
	};
	string mix[4][4] = {
		{"02","03","01","01"},
		{"01","02","03","01"},
		{"01","01","02","03"},
		{"03","01","01","02"},
	};
	string rcon[4][10] = {
		{"01","02","04","08","10","20","40","80","1B","36"},
		{"00","00","00","00","00","00","00","00","00","00"},
		{"00","00","00","00","00","00","00","00","00","00"},
		{"00","00","00","00","00","00","00","00","00","00"},
	};
	char* hex(char* temp);//二进制转化为十六进制函数
	void Init_matrix(char* temp, char* temq);//初始化十六进制矩阵p和k  
	string Xor(string a, string b);//按字节异或操作 
	string S_box(string a);//Subtitution permutation
	void Shift_Row();//行移位函数 
	string multiple(string a, string b);//列混合乘法函数 
	void Mix_Column();//列混合函数 
	int times = 0;//记录轮数，从0开始，到9结束，mod4余0则为4的倍数 
	void Key_generate();//密钥扩展函数 
	string enAES(char  aa[65], char  bb[65]);//AES加密函数 


	//int main() {

	//	char a[65];
	//	char b[65];

	//	cout << "输入明文 :" << endl;
	//	cin >> a;
	//	cout << "输入密钥 :" << endl;
	//	cin >> b;

	//	enAES(a, b);//执行函数
	//	return 0;
	//}

	string enAES(char aa[65], char bb[65]) {

		string result;
		plaintext = (char*)malloc(sizeof(char) * 65);
		key = (char*)malloc(sizeof(char) * 65);

		for (int i = 0; i < 64; i++) {
			plaintext[i] = aa[i];
			key[i] = bb[i];
		}


		//转化为16进制 
	//	plaintext=hex(plaintext);
	//	key=hex(key);

		//初始化矩阵p和k
		Init_matrix(plaintext, key);


		//KeyAdd与初始密钥矩阵异或操作 
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				p[i][j] = Xor(p[i][j], K[i][j]);

		//前九轮循环 
		for (int i = 1; i <= 9; i++, times++) {

			//Substitution
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					p[i][j] = S_box(p[i][j]);
			}

			//向左循环移位函数
			Shift_Row();

			//列混合函数
			Mix_Column();

			//SubKeyAdd
			/*第一步生成子密钥*/
			Key_generate();
			/*第二部对应位置做异或*/
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					p[i][j] = Xor(p[i][j], K[i][j]);
			}
			//循环直至进行到第十轮循环结束 
		}

		//第十轮循环
		//Substitution
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				p[i][j] = S_box(p[i][j]);
		}

		//向左循环移位函数
		Shift_Row();
		//SubKeyAdd
		/*第一步生成子密钥*/
		Key_generate();
		/*第二部对应位置做异或*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				p[i][j] = Xor(p[i][j], K[i][j]);
		}
		cout << "密文为：" << endl;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
			{
				cout << p[j][i];
				result += p[j][i];
			}
		}
		return result;
	}



	void Key_generate() {//产生本轮子密钥 
		string subkey[4][4];
		//是4的倍数
		/*向上循环移位*/
		string temp[5];
		int j = 0;
		temp[3] = K[0][3];
		temp[0] = K[1][3];
		temp[1] = K[2][3];
		temp[2] = K[3][3];

		for (int i = 0; i < 4; i++) {
			temp[i] = S_box(temp[i]);

		}

		for (int i = 0; i < 4; i++) {
			temp[i] = Xor(temp[i], K[i][0]);
			temp[i] = Xor(temp[i], rcon[i][times]);
		}
		for (int i = 0; i < 4; i++) subkey[i][0] = temp[i];
		//不是4的倍数时 
		for (int i = 0; i <= 3; i++) {
			for (j = 1; j <= 3; j++) {
				subkey[i][j] = Xor(K[i][j], subkey[i][j - 1]);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				K[i][j] = subkey[i][j];

			}

		}

		return;
	}


	string multiple(string b, string a) {//输出是一个字节大小的字符串 
		string str1 = "0000", ta = "";
		string ans = "";

		switch (b[1]) {
		case '0': str1 += "0000"; break;
		case '1': str1 += "0001"; break;
		case '2': str1 += "0010"; break;
		case '3': str1 += "0011"; break;
		}

		switch (a[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':ta = "0000"; break;
		case '1':ta = "0001"; break;
		case '2':ta = "0010"; break;
		case '3':ta = "0011"; break;
		case '4':ta = "0100"; break;
		case '5':ta = "0101"; break;
		case '6':ta = "0110"; break;
		case '7':ta = "0111"; break;
		case '8':ta = "1000"; break;
		case '9':ta = "1001"; break;
		case 'A':ta = "1010"; break;
		case 'B':ta = "1011"; break;
		case 'C':ta = "1100"; break;
		case 'D':ta = "1101"; break;
		case 'E':ta = "1110"; break;
		case 'F':ta = "1111"; break;
		}
		switch (a[1]) {
		case '0':ta += "0000"; break;
		case '1':ta += "0001"; break;
		case '2':ta += "0010"; break;
		case '3':ta += "0011"; break;
		case '4':ta += "0100"; break;
		case '5':ta += "0101"; break;
		case '6':ta += "0110"; break;
		case '7':ta += "0111"; break;
		case '8':ta += "1000"; break;
		case '9':ta += "1001"; break;
		case 'A':ta += "1010"; break;
		case 'B':ta += "1011"; break;
		case 'C':ta += "1100"; break;
		case 'D':ta += "1101"; break;
		case 'E':ta += "1110"; break;
		case 'F':ta += "1111"; break;
		}//参与运算的两个字符串转化为二进制。 
		switch (b[1]) {
		case '1': ans = a; return ans; break;
		case '2':
			if (ta[0] == '0') {
				for (int i = 1; i <= 7; i++) ans += ta[i];
				ans += '0';
			}
			else {
				for (int i = 1; i <= 7; i++) ans += ta[i];
				ans += '0';
				string tr = "";
				string qq = "00011011";
				for (int i = 0; i < 8; i++) {
					if (ans[i] == qq[i]) tr += "0";
					else tr += "1";
				}
				ans = tr;
			}
			break;
		case '3':

			string temp = multiple("02", a);
			string tb = "";
			switch (temp[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			for (int i = 0; i < 8; i++) {
				if (ta[i] == tb[i]) ans += "0";
				else ans += "1";
			}

			break;
		}

		string re = "";
		int buf;
		int z[4] = { 8,4,2,1 };
		for (int i = 0; i < 2; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {
				buf = buf + (ans[i * 4 + j] == '1' ? z[j] : 0); //把二进制首先转化为十六进制 
			}
			switch (buf) {
			case 0: re += "0"; break;
			case 1: re += "1"; break;
			case 2: re += "2"; break;
			case 3: re += "3"; break;
			case 4: re += "4"; break;
			case 5: re += "5"; break;
			case 6: re += "6"; break;
			case 7: re += "7"; break;
			case 8: re += "8"; break;
			case 9: re += "9"; break;
			case 10: re += "A"; break;
			case 11: re += "B"; break;
			case 12: re += "C"; break;
			case 13: re += "D"; break;
			case 14: re += "E"; break;
			case 15: re += "F"; break;
			}
		}

		return re;

	}
	void Mix_Column() {//列混合函数 
		string q[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				q[i][j] = multiple(mix[i][0], p[0][j]);
				q[i][j] = Xor(q[i][j], multiple(mix[i][1], p[1][j]));
				q[i][j] = Xor(q[i][j], multiple(mix[i][2], p[2][j]));
				q[i][j] = Xor(q[i][j], multiple(mix[i][3], p[3][j]));
			}
		}
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				p[i][j] = q[i][j];
		return;
	}

	void Shift_Row() {//循环左移，第i行循环左移i个字节单位 
		for (int i = 0; i < 4; i++) {//变量i记录行数 
			for (int j = 0; j < i; j++) {//变量j记录每一行循环的字节单位是多少 
				string temp = p[i][0];//记录第0列 
				for (int k = 1; k < 4; k++) {
					p[i][k - 1] = p[i][k];//除了第0列，所有列向左移动 
				}
				p[i][3] = temp;//补齐第0列的循环左移 
			}
		}
		return;
	}

	string S_box(string a) {//S_box函数针对的是每一个一字节字符串 
		int x, y;
		switch (a[0]) {//首先将十六进制转化为十进制
		case '0':x = 0; break;
		case '1':x = 1; break;
		case '2':x = 2; break;
		case '3':x = 3; break;
		case '4':x = 4; break;
		case '5':x = 5; break;
		case '6':x = 6; break;
		case '7':x = 7; break;
		case '8':x = 8; break;
		case '9':x = 9; break;
		case 'A':x = 10; break;
		case 'B':x = 11; break;
		case 'C':x = 12; break;
		case 'D':x = 13; break;
		case 'E':x = 14; break;
		case 'F':x = 15; break;
		}
		switch (a[1]) {
		case '0':y = 0; break;
		case '1':y = 1; break;
		case '2':y = 2; break;
		case '3':y = 3; break;
		case '4':y = 4; break;
		case '5':y = 5; break;
		case '6':y = 6; break;
		case '7':y = 7; break;
		case '8':y = 8; break;
		case '9':y = 9; break;
		case 'A':y = 10; break;
		case 'B':y = 11; break;
		case 'C':y = 12; break;
		case 'D':y = 13; break;
		case 'E':y = 14; break;
		case 'F':y = 15; break;
		}
		string ans;
		ans = SBOX[x][y];
		return ans;
	}


	string Xor(string a, string b) {//输入参数是明文和密钥矩阵对应的一个字节的字符串 
		string ta, tb;
		string ans = "";
		switch (a[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':ta = "0000"; break;
		case '1':ta = "0001"; break;
		case '2':ta = "0010"; break;
		case '3':ta = "0011"; break;
		case '4':ta = "0100"; break;
		case '5':ta = "0101"; break;
		case '6':ta = "0110"; break;
		case '7':ta = "0111"; break;
		case '8':ta = "1000"; break;
		case '9':ta = "1001"; break;
		case 'A':ta = "1010"; break;
		case 'B':ta = "1011"; break;
		case 'C':ta = "1100"; break;
		case 'D':ta = "1101"; break;
		case 'E':ta = "1110"; break;
		case 'F':ta = "1111"; break;
		}
		switch (a[1]) {
		case '0':ta += "0000"; break;
		case '1':ta += "0001"; break;
		case '2':ta += "0010"; break;
		case '3':ta += "0011"; break;
		case '4':ta += "0100"; break;
		case '5':ta += "0101"; break;
		case '6':ta += "0110"; break;
		case '7':ta += "0111"; break;
		case '8':ta += "1000"; break;
		case '9':ta += "1001"; break;
		case 'A':ta += "1010"; break;
		case 'B':ta += "1011"; break;
		case 'C':ta += "1100"; break;
		case 'D':ta += "1101"; break;
		case 'E':ta += "1110"; break;
		case 'F':ta += "1111"; break;
		}
		switch (b[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':tb = "0000"; break;
		case '1':tb = "0001"; break;
		case '2':tb = "0010"; break;
		case '3':tb = "0011"; break;
		case '4':tb = "0100"; break;
		case '5':tb = "0101"; break;
		case '6':tb = "0110"; break;
		case '7':tb = "0111"; break;
		case '8':tb = "1000"; break;
		case '9':tb = "1001"; break;
		case 'A':tb = "1010"; break;
		case 'B':tb = "1011"; break;
		case 'C':tb = "1100"; break;
		case 'D':tb = "1101"; break;
		case 'E':tb = "1110"; break;
		case 'F':tb = "1111"; break;
		}
		switch (b[1]) {
		case '0':tb += "0000"; break;
		case '1':tb += "0001"; break;
		case '2':tb += "0010"; break;
		case '3':tb += "0011"; break;
		case '4':tb += "0100"; break;
		case '5':tb += "0101"; break;
		case '6':tb += "0110"; break;
		case '7':tb += "0111"; break;
		case '8':tb += "1000"; break;
		case '9':tb += "1001"; break;
		case 'A':tb += "1010"; break;
		case 'B':tb += "1011"; break;
		case 'C':tb += "1100"; break;
		case 'D':tb += "1101"; break;
		case 'E':tb += "1110"; break;
		case 'F':tb += "1111"; break;
		}
		//进行按位异或
		for (int i = 0; i < 9; i++) {
			ans += (ta[i] == tb[i]) ? "0" : "1";
		}
		//将ans转化为十六进制
		string re = "";
		int buf;
		int ty[4] = { 8,4,2,1 };
		for (int i = 0; i < 2; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {
				buf = buf + (ans[i * 4 + j] == '1' ? ty[j] : 0); //把二进制首先转化为十六进制 
			}
			switch (buf) {
			case 0: re += "0"; break;
			case 1: re += "1"; break;
			case 2: re += "2"; break;
			case 3: re += "3"; break;
			case 4: re += "4"; break;
			case 5: re += "5"; break;
			case 6: re += "6"; break;
			case 7: re += "7"; break;
			case 8: re += "8"; break;
			case 9: re += "9"; break;
			case 10: re += "A"; break;
			case 11: re += "B"; break;
			case 12: re += "C"; break;
			case 13: re += "D"; break;
			case 14: re += "E"; break;
			case 15: re += "F"; break;
			}
		}
		return re;
	}
	void Init_matrix(char* temp, char* temq) {//输入的字符串指针是32个字符 ,temp参数是明文，temq是密钥 
		int i = 0, r = 0;
		for (int j = 0; j < 4; j++) {

			for (int k = 0; k < 4; k++) {
				p[k][j] = temp[i++];
				p[k][j] += temp[i++];
				K[k][j] = temq[r++];
				K[k][j] += temq[r++];
			}
		}
		return;
	}


	char* hex(char* temp) {//把输入的二进制字符串转化为十六进制字符串 
		char* str;
		str = (char*)malloc(sizeof(char) * 33);//用于存放转化后的十六进制字符 
		int a[4] = { 8,4,2,1 };
		int buf;//临时数用来存放临时十进制数 
		for (int i = 0; i < 32; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {//把二进制首先转化为十六进制 
				buf = buf + (temp[i * 4 + j] == '1' ? a[j] : 0);
			}
			switch (buf) {
			case 0: str[i] = '0'; break;
			case 1: str[i] = '1'; break;
			case 2: str[i] = '2'; break;
			case 3: str[i] = '3'; break;
			case 4: str[i] = '4'; break;
			case 5: str[i] = '5'; break;
			case 6: str[i] = '6'; break;
			case 7: str[i] = '7'; break;
			case 8: str[i] = '8'; break;
			case 9: str[i] = '9'; break;
			case 10: str[i] = 'A'; break;
			case 11: str[i] = 'B'; break;
			case 12: str[i] = 'C'; break;
			case 13: str[i] = 'D'; break;
			case 14: str[i] = 'E'; break;
			case 15: str[i] = 'F'; break;
			}
		}
		str[33] = '\0';
		return str;
	}
}

namespace AESDE
{
	string aSBOX[16][16] = {
	{"63","7C","77","7B","F2","6B","6F","C5","30","01","67","2B","FE","D7","AB","76"},
	{"CA","82","C9","7D","FA","59","47","F0","AD","D4","A2","AF","9C","A4","72","C0"},
	{"B7","FD","93","26","36","3F","F7","CC","34","A5","E5","F1","71","D8","31","15"},
	{"04","C7","23","C3","18","96","05","9A","07","12","80","E2","EB","27","B2","75"},
	{"09","83","2C","1A","1B","6E","5A","A0","52","3B","D6","B3","29","E3","2F","84"},
	{"53","D1","00","ED","20","FC","B1","5B","6A","CB","BE","39","4A","4C","58","CF"},
	{"D0","EF","AA","FB","43","4D","33","85","45","F9","02","7F","50","3C","9F","A8"},
	{"51","A3","40","8F","92","9D","38","F5","BC","B6","DA","21","10","FF","F3","D2"},
	{"CD","0C","13","EC","5F","97","44","17","C4","A7","7E","3D","64","5D","19","73"},
	{"60","81","4F","DC","22","2A","90","88","46","EE","B8","14","DE","5E","0B","DB"},
	{"E0","32","3A","0A","49","06","24","5C","C2","D3","AC","62","91","95","E4","79"},
	{"E7","C8","37","6D","8D","D5","4E","A9","6C","56","F4","EA","65","7A","AE","08"},
	{"BA","78","25","2E","1C","A6","B4","C6","E8","DD","74","1F","4B","BD","8B","8A"},
	{"70","3E","B5","66","48","03","F6","0E","61","35","57","B9","86","C1","1D","9E"},
	{"E1","F8","98","11","69","D9","8E","94","9B","1E","87","E9","CE","55","28","DF"},
	{"8C","A1","89","0D","BF","E6","42","68","41","99","2D","0F","B0","54","BB","16"},
	};//正Sbox函数 
	string SBOX[16][16] = {
		{"52","09","6A","D5","30","36","A5","38","BF","40","A3","9E","81","F3","D7","FB"},
		{"7C","E3","39","82","9B","2F","FF","87","34","8E","43","44","C4","DE","E9","CB"},
		{"54","7B","94","32","A6","C2","23","3D","EE","4C","95","0B","42","FA","C3","4E"},
		{"08","2E","A1","66","28","D9","24","B2","76","5B","A2","49","6D","8B","D1","25"},
		{"72","F8","F6","64","86","68","98","16","D4","A4","5C","CC","5D","65","B6","92"},
		{"6C","70","48","50","FD","ED","B9","DA","5E","15","46","57","A7","8D","9D","84"},
		{"90","D8","AB","00","8C","BC","D3","0A","F7","E4","58","05","B8","B3","45","06"},
		{"D0","2C","1E","8F","CA","3F","0F","02","C1","AF","BD","03","01","13","8A","6B"},
		{"3A","91","11","41","4F","67","DC","EA","97","F2","CF","CE","F0","B4","E6","73"},
		{"96","AC","74","22","E7","AD","35","85","E2","F9","37","E8","1C","75","DF","6E"},
		{"47","F1","1A","71","1D","29","C5","89","6F","B7","62","0E","AA","18","BE","1B"},
		{"FC","56","3E","4B","C6","D2","79","20","9A","DB","C0","FE","78","CD","5A","F4"},
		{"1F","DD","A8","33","88","07","C7","31","B1","12","10","59","27","80","EC","5F"},
		{"60","51","7F","A9","19","B5","4A","0D","2D","E5","7A","9F","93","C9","9C","EF"},
		{"A0","E0","3B","4D","AE","2A","F5","B0","C8","EB","BB","3C","83","53","99","61"},
		{"17","2B","04","7E","BA","77","D6","26","E1","69","14","63","55","21","0C","7D"},
	};//逆SBOX 
	string mix[4][4] = {
		{"0E","0B","0D","09"},
		{"09","0E","0B","0D"},
		{"0D","09","0E","0B"},
		{"0B","0D","09","0E"},
	};//逆混淆矩阵 
	string rcon[4][10] = {
		{"01","02","04","08","10","20","40","80","1B","36"},
		{"00","00","00","00","00","00","00","00","00","00"},
		{"00","00","00","00","00","00","00","00","00","00"},
		{"00","00","00","00","00","00","00","00","00","00"},
	};
	char* ciphertext, * key;
	string K[4][4];//存储密钥 
	string p[4][4];//存储密文 
	string store_k[11][4][4];//存储11轮密钥，顺序按正向加密的顺序存储 
	int times = 0, keyt = 1;//11轮密钥 


	string aS_box(string a);//正Sbox函数只会在子密钥生成函数使用 
	string S_box(string a);//Subtitution permutation逆向的 
	string Xor(string a, string b);//按字节异或操作
	void Init_matrix(char* temp, char* temq);//输入的字符串指针是32个字符 ,temp参数是密文，temq是密钥 
	string multiple(string b, string a);//特殊的矩阵乘法 
	void Mix_Column();//逆向列混淆 
	string deAES(char aa[65], char bb[65]);//解密算法函数 
	void Shift_Row();
	void Key_generate();//密钥生成 
	string In_multiple(string b, string a);

	string deAES(char aa[65], char bb[65]) {

		string result;
		ciphertext = (char*)malloc(sizeof(char) * 64);
		key = (char*)malloc(sizeof(char) * 64);

		for (int i = 0; i < 64; i++) {
			ciphertext[i] = aa[i];
			key[i] = bb[i];
		}

		Init_matrix(ciphertext, key);

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				store_k[0][i][j] = K[i][j];
		}
		//生成并保存子密钥共十轮 
		for (int i = 0; i < 10; i++, times++, keyt++) {
			Key_generate();
		}


		//特殊的第一个循环
		/*轮密钥加第11轮*/
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				p[i][j] = Xor(store_k[10][i][j], p[i][j]);
			}
		}

		/*9轮循环*/
		for (int time = 1; time <= 9; time++) {

			Shift_Row();//逆向行位移

		//逆向字节代换 
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++)
					p[i][j] = S_box(p[i][j]);
			}

			//轮密钥加 
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					p[i][j] = Xor(store_k[10 - time][i][j], p[i][j]);
				}
			}



			//逆向列混淆 
			Mix_Column();

		}

		Shift_Row();//逆向行位移
			//逆向字节代换 

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << p[i][j] << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				p[i][j] = S_box(p[i][j]);
		}
		//最后一轮
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				p[i][j] = Xor(store_k[0][i][j], p[i][j]);

			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				cout << p[j][i];
				result += p[j][i];
			}
		}
		return result;
	}

	void Mix_Column() {//列混合函数 
		string q[4][4];
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				q[i][j] = In_multiple(mix[i][0], p[0][j]);
				q[i][j] = Xor(q[i][j], In_multiple(mix[i][1], p[1][j]));
				q[i][j] = Xor(q[i][j], In_multiple(mix[i][2], p[2][j]));
				q[i][j] = Xor(q[i][j], In_multiple(mix[i][3], p[3][j]));
			}
		}
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				p[i][j] = q[i][j];
		return;
	}

	string multiple(string b, string a) {//输出是一个字节大小的字符串 
		string str1 = "0000", ta = "";
		string ans = "";

		switch (b[1]) {
		case '0': str1 += "0000"; break;
		case '1': str1 += "0001"; break;
		case '2': str1 += "0010"; break;
		case '3': str1 += "0011"; break;
		}

		switch (a[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':ta = "0000"; break;
		case '1':ta = "0001"; break;
		case '2':ta = "0010"; break;
		case '3':ta = "0011"; break;
		case '4':ta = "0100"; break;
		case '5':ta = "0101"; break;
		case '6':ta = "0110"; break;
		case '7':ta = "0111"; break;
		case '8':ta = "1000"; break;
		case '9':ta = "1001"; break;
		case 'A':ta = "1010"; break;
		case 'B':ta = "1011"; break;
		case 'C':ta = "1100"; break;
		case 'D':ta = "1101"; break;
		case 'E':ta = "1110"; break;
		case 'F':ta = "1111"; break;
		}
		switch (a[1]) {
		case '0':ta += "0000"; break;
		case '1':ta += "0001"; break;
		case '2':ta += "0010"; break;
		case '3':ta += "0011"; break;
		case '4':ta += "0100"; break;
		case '5':ta += "0101"; break;
		case '6':ta += "0110"; break;
		case '7':ta += "0111"; break;
		case '8':ta += "1000"; break;
		case '9':ta += "1001"; break;
		case 'A':ta += "1010"; break;
		case 'B':ta += "1011"; break;
		case 'C':ta += "1100"; break;
		case 'D':ta += "1101"; break;
		case 'E':ta += "1110"; break;
		case 'F':ta += "1111"; break;
		}//参与运算的两个字符串转化为二进制。 

		switch (b[1]) {
		case '1': ans = a; return ans; break;
		case '2':
			if (ta[0] == '0') {
				for (int i = 1; i <= 7; i++) ans += ta[i];
				ans += '0';
			}
			else {
				for (int i = 1; i <= 7; i++) ans += ta[i];
				ans += '0';
				string tr = "";
				string qq = "00011011";
				for (int i = 0; i < 8; i++) {
					if (ans[i] == qq[i]) tr += "0";
					else tr += "1";
				}
				ans = tr;
			}
			break;
		case '3':

			string temp = multiple("02", a);
			string tb = "";
			switch (temp[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			for (int i = 0; i < 8; i++) {
				if (ta[i] == tb[i]) ans += "0";
				else ans += "1";
			}

			break;
		}

		string re = "";
		int buf;
		int ar[4] = { 8,4,2,1 };
		for (int i = 0; i < 2; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {
				buf = buf + (ans[i * 4 + j] == '1' ? ar[j] : 0); //把二进制首先转化为十六进制 
			}
			switch (buf) {
			case 0: re += "0"; break;
			case 1: re += "1"; break;
			case 2: re += "2"; break;
			case 3: re += "3"; break;
			case 4: re += "4"; break;
			case 5: re += "5"; break;
			case 6: re += "6"; break;
			case 7: re += "7"; break;
			case 8: re += "8"; break;
			case 9: re += "9"; break;
			case 10: re += "A"; break;
			case 11: re += "B"; break;
			case 12: re += "C"; break;
			case 13: re += "D"; break;
			case 14: re += "E"; break;
			case 15: re += "F"; break;
			}
		}

		return re;
	}

	string In_multiple(string b, string a) {//输出是一个字节大小的字符串 
		string ans = "";
		string temp1 = "", temp2 = "", temp = "";
		string tb = "", tc = "", ta = "";
		switch (a[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':ta = "0000"; break;
		case '1':ta = "0001"; break;
		case '2':ta = "0010"; break;
		case '3':ta = "0011"; break;
		case '4':ta = "0100"; break;
		case '5':ta = "0101"; break;
		case '6':ta = "0110"; break;
		case '7':ta = "0111"; break;
		case '8':ta = "1000"; break;
		case '9':ta = "1001"; break;
		case 'A':ta = "1010"; break;
		case 'B':ta = "1011"; break;
		case 'C':ta = "1100"; break;
		case 'D':ta = "1101"; break;
		case 'E':ta = "1110"; break;
		case 'F':ta = "1111"; break;
		}
		switch (a[1]) {
		case '0':ta += "0000"; break;
		case '1':ta += "0001"; break;
		case '2':ta += "0010"; break;
		case '3':ta += "0011"; break;
		case '4':ta += "0100"; break;
		case '5':ta += "0101"; break;
		case '6':ta += "0110"; break;
		case '7':ta += "0111"; break;
		case '8':ta += "1000"; break;
		case '9':ta += "1001"; break;
		case 'A':ta += "1010"; break;
		case 'B':ta += "1011"; break;
		case 'C':ta += "1100"; break;
		case 'D':ta += "1101"; break;
		case 'E':ta += "1110"; break;
		case 'F':ta += "1111"; break;
		}//参与运算的两个字符串转化为二进制。 
		switch (b[1]) {
		case '9':
			temp = multiple("02", a);
			temp = multiple("02", temp);
			temp = multiple("02", temp);
			switch (temp[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == ta[i]) ans += "0";
				else ans += "1";
			}
			break;
		case 'B':
			temp1 = multiple("02", a);
			temp1 = multiple("02", temp1);
			temp1 = multiple("02", temp1);
			temp2 = multiple("02", a);
			switch (temp1[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp1[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			switch (temp2[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tc = "0000"; break;
			case '1':tc = "0001"; break;
			case '2':tc = "0010"; break;
			case '3':tc = "0011"; break;
			case '4':tc = "0100"; break;
			case '5':tc = "0101"; break;
			case '6':tc = "0110"; break;
			case '7':tc = "0111"; break;
			case '8':tc = "1000"; break;
			case '9':tc = "1001"; break;
			case 'A':tc = "1010"; break;
			case 'B':tc = "1011"; break;
			case 'C':tc = "1100"; break;
			case 'D':tc = "1101"; break;
			case 'E':tc = "1110"; break;
			case 'F':tc = "1111"; break;
			}
			switch (temp2[1]) {
			case '0':tc += "0000"; break;
			case '1':tc += "0001"; break;
			case '2':tc += "0010"; break;
			case '3':tc += "0011"; break;
			case '4':tc += "0100"; break;
			case '5':tc += "0101"; break;
			case '6':tc += "0110"; break;
			case '7':tc += "0111"; break;
			case '8':tc += "1000"; break;
			case '9':tc += "1001"; break;
			case 'A':tc += "1010"; break;
			case 'B':tc += "1011"; break;
			case 'C':tc += "1100"; break;
			case 'D':tc += "1101"; break;
			case 'E':tc += "1110"; break;
			case 'F':tc += "1111"; break;
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == ta[i]) tb[i] = '0';
				else tb[i] = '1';
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == tc[i]) ans += "0";
				else ans += "1";
			}

			break;
		case 'D':
			temp1 = multiple("02", a);
			temp1 = multiple("02", temp1);
			temp1 = multiple("02", temp1);
			temp2 = multiple("02", a);
			temp2 = multiple("02", temp2);
			switch (temp1[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp1[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			switch (temp2[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tc = "0000"; break;
			case '1':tc = "0001"; break;
			case '2':tc = "0010"; break;
			case '3':tc = "0011"; break;
			case '4':tc = "0100"; break;
			case '5':tc = "0101"; break;
			case '6':tc = "0110"; break;
			case '7':tc = "0111"; break;
			case '8':tc = "1000"; break;
			case '9':tc = "1001"; break;
			case 'A':tc = "1010"; break;
			case 'B':tc = "1011"; break;
			case 'C':tc = "1100"; break;
			case 'D':tc = "1101"; break;
			case 'E':tc = "1110"; break;
			case 'F':tc = "1111"; break;
			}
			switch (temp2[1]) {
			case '0':tc += "0000"; break;
			case '1':tc += "0001"; break;
			case '2':tc += "0010"; break;
			case '3':tc += "0011"; break;
			case '4':tc += "0100"; break;
			case '5':tc += "0101"; break;
			case '6':tc += "0110"; break;
			case '7':tc += "0111"; break;
			case '8':tc += "1000"; break;
			case '9':tc += "1001"; break;
			case 'A':tc += "1010"; break;
			case 'B':tc += "1011"; break;
			case 'C':tc += "1100"; break;
			case 'D':tc += "1101"; break;
			case 'E':tc += "1110"; break;
			case 'F':tc += "1111"; break;
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == ta[i]) tb[i] = '0';
				else tb[i] = '1';
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == tc[i]) ans += "0";
				else ans += "1";
			}
			break;
		case 'E':
			temp1 = multiple("02", a);
			temp1 = multiple("02", temp1);
			temp1 = multiple("02", temp1);
			temp2 = multiple("02", a);
			temp2 = multiple("02", temp2);
			temp = multiple("02", a);
			switch (temp1[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tb = "0000"; break;
			case '1':tb = "0001"; break;
			case '2':tb = "0010"; break;
			case '3':tb = "0011"; break;
			case '4':tb = "0100"; break;
			case '5':tb = "0101"; break;
			case '6':tb = "0110"; break;
			case '7':tb = "0111"; break;
			case '8':tb = "1000"; break;
			case '9':tb = "1001"; break;
			case 'A':tb = "1010"; break;
			case 'B':tb = "1011"; break;
			case 'C':tb = "1100"; break;
			case 'D':tb = "1101"; break;
			case 'E':tb = "1110"; break;
			case 'F':tb = "1111"; break;
			}
			switch (temp1[1]) {
			case '0':tb += "0000"; break;
			case '1':tb += "0001"; break;
			case '2':tb += "0010"; break;
			case '3':tb += "0011"; break;
			case '4':tb += "0100"; break;
			case '5':tb += "0101"; break;
			case '6':tb += "0110"; break;
			case '7':tb += "0111"; break;
			case '8':tb += "1000"; break;
			case '9':tb += "1001"; break;
			case 'A':tb += "1010"; break;
			case 'B':tb += "1011"; break;
			case 'C':tb += "1100"; break;
			case 'D':tb += "1101"; break;
			case 'E':tb += "1110"; break;
			case 'F':tb += "1111"; break;
			}
			switch (temp2[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':tc = "0000"; break;
			case '1':tc = "0001"; break;
			case '2':tc = "0010"; break;
			case '3':tc = "0011"; break;
			case '4':tc = "0100"; break;
			case '5':tc = "0101"; break;
			case '6':tc = "0110"; break;
			case '7':tc = "0111"; break;
			case '8':tc = "1000"; break;
			case '9':tc = "1001"; break;
			case 'A':tc = "1010"; break;
			case 'B':tc = "1011"; break;
			case 'C':tc = "1100"; break;
			case 'D':tc = "1101"; break;
			case 'E':tc = "1110"; break;
			case 'F':tc = "1111"; break;
			}
			switch (temp2[1]) {
			case '0':tc += "0000"; break;
			case '1':tc += "0001"; break;
			case '2':tc += "0010"; break;
			case '3':tc += "0011"; break;
			case '4':tc += "0100"; break;
			case '5':tc += "0101"; break;
			case '6':tc += "0110"; break;
			case '7':tc += "0111"; break;
			case '8':tc += "1000"; break;
			case '9':tc += "1001"; break;
			case 'A':tc += "1010"; break;
			case 'B':tc += "1011"; break;
			case 'C':tc += "1100"; break;
			case 'D':tc += "1101"; break;
			case 'E':tc += "1110"; break;
			case 'F':tc += "1111"; break;
			}
			switch (temp[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
			case '0':ta = "0000"; break;
			case '1':ta = "0001"; break;
			case '2':ta = "0010"; break;
			case '3':ta = "0011"; break;
			case '4':ta = "0100"; break;
			case '5':ta = "0101"; break;
			case '6':ta = "0110"; break;
			case '7':ta = "0111"; break;
			case '8':ta = "1000"; break;
			case '9':ta = "1001"; break;
			case 'A':ta = "1010"; break;
			case 'B':ta = "1011"; break;
			case 'C':ta = "1100"; break;
			case 'D':ta = "1101"; break;
			case 'E':ta = "1110"; break;
			case 'F':ta = "1111"; break;
			}
			switch (temp[1]) {
			case '0':ta += "0000"; break;
			case '1':ta += "0001"; break;
			case '2':ta += "0010"; break;
			case '3':ta += "0011"; break;
			case '4':ta += "0100"; break;
			case '5':ta += "0101"; break;
			case '6':ta += "0110"; break;
			case '7':ta += "0111"; break;
			case '8':ta += "1000"; break;
			case '9':ta += "1001"; break;
			case 'A':ta += "1010"; break;
			case 'B':ta += "1011"; break;
			case 'C':ta += "1100"; break;
			case 'D':ta += "1101"; break;
			case 'E':ta += "1110"; break;
			case 'F':ta += "1111"; break;
			}//参与运算的两个字符串转化为二进制。 
			for (int i = 0; i < 8; i++) {
				if (tb[i] == ta[i]) tb[i] = '0';
				else tb[i] = '1';
			}
			for (int i = 0; i < 8; i++) {
				if (tb[i] == tc[i]) ans += "0";
				else ans += "1";
			}
			break;
		}

		string re = "";
		int buf;
		int rta[4] = { 8,4,2,1 };
		for (int i = 0; i < 2; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {
				buf = buf + (ans[i * 4 + j] == '1' ? rta[j] : 0); //把二进制首先转化为十六进制 
			}
			switch (buf) {
			case 0: re += "0"; break;
			case 1: re += "1"; break;
			case 2: re += "2"; break;
			case 3: re += "3"; break;
			case 4: re += "4"; break;
			case 5: re += "5"; break;
			case 6: re += "6"; break;
			case 7: re += "7"; break;
			case 8: re += "8"; break;
			case 9: re += "9"; break;
			case 10: re += "A"; break;
			case 11: re += "B"; break;
			case 12: re += "C"; break;
			case 13: re += "D"; break;
			case 14: re += "E"; break;
			case 15: re += "F"; break;
			}
		}

		return re;

	}
	void Shift_Row() {//循环右移，第i行循环左移i个字节单位 
		for (int i = 0; i < 4; i++) {//变量i记录行数 
			for (int j = 0; j < i; j++) {//变量j记录每一行循环的字节单位是多少 
				string temp = p[i][3];//记录第0列 
				for (int k = 3; k > 0; k--) {
					p[i][k] = p[i][k - 1];//除了第0列，所有列向右移动 
				}
				p[i][0] = temp;//补齐第0列的循环右移 
			}
		}
		return;
	}

	void Init_matrix(char* temp, char* temq) {//输入的字符串指针是32个字符 ,temp参数是明文，temq是密钥 
		int i = 0, r = 0;
		for (int j = 0; j < 4; j++) {

			for (int k = 0; k < 4; k++) {
				p[k][j] = temp[i++];
				p[k][j] += temp[i++];
				K[k][j] = temq[r++];
				K[k][j] += temq[r++];
			}
		}
		return;
	}
	string Xor(string a, string b) {//输入参数是明文和密钥矩阵对应的一个字节的字符串 
		string ta, tb;
		string ans = "";
		switch (a[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':ta = "0000"; break;
		case '1':ta = "0001"; break;
		case '2':ta = "0010"; break;
		case '3':ta = "0011"; break;
		case '4':ta = "0100"; break;
		case '5':ta = "0101"; break;
		case '6':ta = "0110"; break;
		case '7':ta = "0111"; break;
		case '8':ta = "1000"; break;
		case '9':ta = "1001"; break;
		case 'A':ta = "1010"; break;
		case 'B':ta = "1011"; break;
		case 'C':ta = "1100"; break;
		case 'D':ta = "1101"; break;
		case 'E':ta = "1110"; break;
		case 'F':ta = "1111"; break;
		}
		switch (a[1]) {
		case '0':ta += "0000"; break;
		case '1':ta += "0001"; break;
		case '2':ta += "0010"; break;
		case '3':ta += "0011"; break;
		case '4':ta += "0100"; break;
		case '5':ta += "0101"; break;
		case '6':ta += "0110"; break;
		case '7':ta += "0111"; break;
		case '8':ta += "1000"; break;
		case '9':ta += "1001"; break;
		case 'A':ta += "1010"; break;
		case 'B':ta += "1011"; break;
		case 'C':ta += "1100"; break;
		case 'D':ta += "1101"; break;
		case 'E':ta += "1110"; break;
		case 'F':ta += "1111"; break;
		}
		switch (b[0]) {//首先将十六进制转化为二进制再进行按字节进行运算 
		case '0':tb = "0000"; break;
		case '1':tb = "0001"; break;
		case '2':tb = "0010"; break;
		case '3':tb = "0011"; break;
		case '4':tb = "0100"; break;
		case '5':tb = "0101"; break;
		case '6':tb = "0110"; break;
		case '7':tb = "0111"; break;
		case '8':tb = "1000"; break;
		case '9':tb = "1001"; break;
		case 'A':tb = "1010"; break;
		case 'B':tb = "1011"; break;
		case 'C':tb = "1100"; break;
		case 'D':tb = "1101"; break;
		case 'E':tb = "1110"; break;
		case 'F':tb = "1111"; break;
		}
		switch (b[1]) {
		case '0':tb += "0000"; break;
		case '1':tb += "0001"; break;
		case '2':tb += "0010"; break;
		case '3':tb += "0011"; break;
		case '4':tb += "0100"; break;
		case '5':tb += "0101"; break;
		case '6':tb += "0110"; break;
		case '7':tb += "0111"; break;
		case '8':tb += "1000"; break;
		case '9':tb += "1001"; break;
		case 'A':tb += "1010"; break;
		case 'B':tb += "1011"; break;
		case 'C':tb += "1100"; break;
		case 'D':tb += "1101"; break;
		case 'E':tb += "1110"; break;
		case 'F':tb += "1111"; break;
		}
		//进行按位异或
		for (int i = 0; i < 9; i++) {
			ans += (ta[i] == tb[i]) ? "0" : "1";
		}
		//将ans转化为十六进制
		string re = "";
		int buf;
		int tq[4] = { 8,4,2,1 };
		for (int i = 0; i < 2; i++) {
			buf = 0;
			for (int j = 0; j < 4; j++) {
				buf = buf + (ans[i * 4 + j] == '1' ? tq[j] : 0); //把二进制首先转化为十六进制 
			}
			switch (buf) {
			case 0: re += "0"; break;
			case 1: re += "1"; break;
			case 2: re += "2"; break;
			case 3: re += "3"; break;
			case 4: re += "4"; break;
			case 5: re += "5"; break;
			case 6: re += "6"; break;
			case 7: re += "7"; break;
			case 8: re += "8"; break;
			case 9: re += "9"; break;
			case 10: re += "A"; break;
			case 11: re += "B"; break;
			case 12: re += "C"; break;
			case 13: re += "D"; break;
			case 14: re += "E"; break;
			case 15: re += "F"; break;
			}
		}
		return re;
	}
	string aS_box(string a) {
		int x=0, y=0;
		switch (a[0]) {//首先将十六进制转化为十进制
		case '0':x = 0; break;
		case '1':x = 1; break;
		case '2':x = 2; break;
		case '3':x = 3; break;
		case '4':x = 4; break;
		case '5':x = 5; break;
		case '6':x = 6; break;
		case '7':x = 7; break;
		case '8':x = 8; break;
		case '9':x = 9; break;
		case 'A':x = 10; break;
		case 'B':x = 11; break;
		case 'C':x = 12; break;
		case 'D':x = 13; break;
		case 'E':x = 14; break;
		case 'F':x = 15; break;
		}
		switch (a[1]) {
		case '0':y = 0; break;
		case '1':y = 1; break;
		case '2':y = 2; break;
		case '3':y = 3; break;
		case '4':y = 4; break;
		case '5':y = 5; break;
		case '6':y = 6; break;
		case '7':y = 7; break;
		case '8':y = 8; break;
		case '9':y = 9; break;
		case 'A':y = 10; break;
		case 'B':y = 11; break;
		case 'C':y = 12; break;
		case 'D':y = 13; break;
		case 'E':y = 14; break;
		case 'F':y = 15; break;
		}
		string ans;
		ans = aSBOX[x][y];
		return ans;
	}
	string S_box(string a) {//S_box函数针对的是每一个一字节字符串 
		int x, y;
		switch (a[0]) {//首先将十六进制转化为十进制
		case '0':x = 0; break;
		case '1':x = 1; break;
		case '2':x = 2; break;
		case '3':x = 3; break;
		case '4':x = 4; break;
		case '5':x = 5; break;
		case '6':x = 6; break;
		case '7':x = 7; break;
		case '8':x = 8; break;
		case '9':x = 9; break;
		case 'A':x = 10; break;
		case 'B':x = 11; break;
		case 'C':x = 12; break;
		case 'D':x = 13; break;
		case 'E':x = 14; break;
		case 'F':x = 15; break;
		}
		switch (a[1]) {
		case '0':y = 0; break;
		case '1':y = 1; break;
		case '2':y = 2; break;
		case '3':y = 3; break;
		case '4':y = 4; break;
		case '5':y = 5; break;
		case '6':y = 6; break;
		case '7':y = 7; break;
		case '8':y = 8; break;
		case '9':y = 9; break;
		case 'A':y = 10; break;
		case 'B':y = 11; break;
		case 'C':y = 12; break;
		case 'D':y = 13; break;
		case 'E':y = 14; break;
		case 'F':y = 15; break;
		}
		string ans;
		ans = SBOX[x][y];
		return ans;
	}
	void Key_generate() {//产生本轮子密钥 
		string subkey[4][4];
		//是4的倍数
		/*向上循环移位*/
		string temp[5];
		int j = 0;
		temp[3] = K[0][3];
		temp[0] = K[1][3];
		temp[1] = K[2][3];
		temp[2] = K[3][3];

		for (int i = 0; i < 4; i++) {
			temp[i] = aS_box(temp[i]);

		}

		for (int i = 0; i < 4; i++) {
			temp[i] = Xor(temp[i], K[i][0]);
			temp[i] = Xor(temp[i], rcon[i][times]);
		}
		for (int i = 0; i < 4; i++) subkey[i][0] = temp[i];
		//不是4的倍数时 
		for (int i = 0; i <= 3; i++) {
			for (j = 1; j <= 3; j++) {
				subkey[i][j] = Xor(K[i][j], subkey[i][j - 1]);
			}
		}
		for (int i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				K[i][j] = subkey[i][j];
				store_k[keyt][i][j] = K[i][j];
			}

		}

		return;
	}

}
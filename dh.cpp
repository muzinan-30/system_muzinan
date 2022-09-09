#include "pch.h"

#include<winsock2.h> //网络库头文件
#pragma comment(lib,"ws2_32.lib")//库文件
#include<iostream>
#include <fstream>
#include<time.h>
#include<string>
#include <sstream>      //要使用stringstream流应包含此头文件
#include<cmath>
#include<algorithm>
#include<cstring>
#include<malloc.h>
#include<fstream>
#include<cstdio>
#include <ctype.h>



using namespace std;

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

bool enfile(char* filename, string key)
{
	string cipher = enDES(readFileIntoString(filename), key);
	ofstream outfile;
	outfile.open(filename);
	if (!outfile.is_open())
	{
		return false;
	}
	outfile << cipher;

	outfile.close();
	return true;
}

//MD5
//UINT4 defines a four byte word
typedef unsigned int UINT4;
typedef unsigned char* POINTER;
//define four auxiliary functions
#define F(x,y,z) (((x)&(y))|((~x)&(z)))
#define G(x,y,z) (((x)&(z))|((y)&(~z)))
#define H(x,y,z) ((x)^(y)^(z))
#define I(x,y,z) ((y)^((x)|(~z)))

#define  ROTATE_LEFT(x,n) (((x)<<(n))| ((x)>>(32-(n))))

using std::string;
using std::cin;
using std::cout;
using std::endl;

//
void FF(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 m, UINT4 s, UINT4 t)
{

	a = b + ROTATE_LEFT((a + F(b, c, d) + m + t), s);
}
void GG(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 m, UINT4 s, UINT4 t)
{
	a = b + ROTATE_LEFT((a + G(b, c, d) + m + t), s);
}
void HH(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 m, UINT4 s, UINT4 t)
{
	a = b + ROTATE_LEFT((a + H(b, c, d) + m + t), s);
}
void II(UINT4& a, UINT4 b, UINT4 c, UINT4 d, UINT4 m, UINT4 s, UINT4 t)
{
	a = b + ROTATE_LEFT((a + I(b, c, d) + m + t), s);
}


typedef struct {
	UINT4 state[4];                                   /* state (ABCD) */
	UINT4 count[2];        /* number of bits, modulo 2^64 (lsb first) */
	unsigned char buffer[64];                         /* input buffer */
} MD5_CTX;

//Initialize MD Buffer
void MD5Init(MD5_CTX* context)
{
	context->count[0] = context->count[1] = 0;
	/* Load magic initialization constants.
   */
	context->state[0] = 0x67452301;
	context->state[1] = 0xefcdab89;
	context->state[2] = 0x98badcfe;
	context->state[3] = 0x10325476;
}

//k[i]=4294967296*abs(sin(i))
const unsigned int t[] = {
		0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
		0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,0x698098d8,
		0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,
		0xa679438e,0x49b40821,0xf61e2562,0xc040b340,0x265e5a51,
		0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
		0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,
		0xfcefa3f8,0x676f02d9,0x8d2a4c8a,0xfffa3942,0x8771f681,
		0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,
		0xbebfbc70,0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
		0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,0xf4292244,
		0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,
		0xffeff47d,0x85845dd1,0x6fa87e4f,0xfe2ce6e0,0xa3014314,
		0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };
//循环左移位数
const unsigned int  s[] = {
	7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
	5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
	4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
	6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21 };

static unsigned char PADDING[] =
{
 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static void MD5_memcpy(POINTER output, POINTER input, unsigned int len)
{
	unsigned int i;
	for (i = 0; i < len; i++)
		output[i] = input[i];
}

static void MD5_memset(POINTER output, int value, unsigned int len)
{
	unsigned int i;
	for (i = 0; i < len; i++)
		((char*)output)[i] = (char)value;
}

static void MD5_print(unsigned char digest[16])
{
	unsigned int i;
	for (i = 0; i < 16; i++)
	{
		printf("%02x", digest[i]);
	}
}
//8->32
static void Decode(UINT4* output, unsigned char* input, unsigned int len)
{
	unsigned int i, j;

	for (i = 0, j = 0; j < len; j += 4, i++)
	{
		output[i] = ((UINT4)input[j]) | (((UINT4)input[j + 1]) << 8) | (((UINT4)input[j + 2]) << 16) | (((UINT4)input[j + 3]) << 24);
	}
}
//32->8
static void Encode(unsigned char* output, UINT4* input, unsigned int len)
{
	unsigned int i, j;
	for (i = 0, j = 0; j < len; i++, j += 4)
	{
		output[j] = (unsigned char)(input[i] & 0xff);
		output[j + 1] = (unsigned char)((input[i] >> 8) & 0xff);
		output[j + 2] = (unsigned  char)((input[i] >> 16) & 0xff);
		output[j + 3] = (unsigned char)((input[i] >> 24) & 0xff);

	}
}
//md5基本转换
static void  MD5Transform(UINT4 state[4], unsigned char block[64])
{
	UINT4 a = state[0], b = state[1], c = state[2], d = state[3], M[16];
	Decode(M, block, 64);
	int i = 0;
	FF(a, b, c, d, M[0], s[i], t[i]); i++;
	FF(d, a, b, c, M[1], s[i], t[i]); i++;
	FF(c, d, a, b, M[2], s[i], t[i]); i++;
	FF(b, c, d, a, M[3], s[i], t[i]); i++;
	FF(a, b, c, d, M[4], s[i], t[i]); i++;
	FF(d, a, b, c, M[5], s[i], t[i]); i++;
	FF(c, d, a, b, M[6], s[i], t[i]); i++;
	FF(b, c, d, a, M[7], s[i], t[i]); i++;
	FF(a, b, c, d, M[8], s[i], t[i]); i++;
	FF(d, a, b, c, M[9], s[i], t[i]); i++;
	FF(c, d, a, b, M[10], s[i], t[i]); i++;
	FF(b, c, d, a, M[11], s[i], t[i]); i++;
	FF(a, b, c, d, M[12], s[i], t[i]); i++;
	FF(d, a, b, c, M[13], s[i], t[i]); i++;
	FF(c, d, a, b, M[14], s[i], t[i]); i++;
	FF(b, c, d, a, M[15], s[i], t[i]); i++;

	GG(a, b, c, d, M[1], s[i], t[i]); i++;
	GG(d, a, b, c, M[6], s[i], t[i]); i++;
	GG(c, d, a, b, M[11], s[i], t[i]); i++;
	GG(b, c, d, a, M[0], s[i], t[i]); i++;
	GG(a, b, c, d, M[5], s[i], t[i]); i++;
	GG(d, a, b, c, M[10], s[i], t[i]); i++;
	GG(c, d, a, b, M[15], s[i], t[i]); i++;
	GG(b, c, d, a, M[4], s[i], t[i]); i++;
	GG(a, b, c, d, M[9], s[i], t[i]); i++;
	GG(d, a, b, c, M[14], s[i], t[i]); i++;
	GG(c, d, a, b, M[3], s[i], t[i]); i++;
	GG(b, c, d, a, M[8], s[i], t[i]); i++;
	GG(a, b, c, d, M[13], s[i], t[i]); i++;
	GG(d, a, b, c, M[2], s[i], t[i]); i++;
	GG(c, d, a, b, M[7], s[i], t[i]); i++;
	GG(b, c, d, a, M[12], s[i], t[i]); i++;

	HH(a, b, c, d, M[5], s[i], t[i]); i++;
	HH(d, a, b, c, M[8], s[i], t[i]); i++;
	HH(c, d, a, b, M[11], s[i], t[i]); i++;
	HH(b, c, d, a, M[14], s[i], t[i]); i++;
	HH(a, b, c, d, M[1], s[i], t[i]); i++;
	HH(d, a, b, c, M[4], s[i], t[i]); i++;
	HH(c, d, a, b, M[7], s[i], t[i]); i++;
	HH(b, c, d, a, M[10], s[i], t[i]); i++;
	HH(a, b, c, d, M[13], s[i], t[i]); i++;
	HH(d, a, b, c, M[0], s[i], t[i]); i++;
	HH(c, d, a, b, M[3], s[i], t[i]); i++;
	HH(b, c, d, a, M[6], s[i], t[i]); i++;
	HH(a, b, c, d, M[9], s[i], t[i]); i++;
	HH(d, a, b, c, M[12], s[i], t[i]); i++;
	HH(c, d, a, b, M[15], s[i], t[i]); i++;
	HH(b, c, d, a, M[2], s[i], t[i]); i++;

	II(a, b, c, d, M[0], s[i], t[i]); i++;
	II(d, a, b, c, M[7], s[i], t[i]); i++;
	II(c, d, a, b, M[14], s[i], t[i]); i++;
	II(b, c, d, a, M[5], s[i], t[i]); i++;
	II(a, b, c, d, M[12], s[i], t[i]); i++;
	II(d, a, b, c, M[3], s[i], t[i]); i++;
	II(c, d, a, b, M[10], s[i], t[i]); i++;
	II(b, c, d, a, M[1], s[i], t[i]); i++;
	II(a, b, c, d, M[8], s[i], t[i]); i++;
	II(d, a, b, c, M[15], s[i], t[i]); i++;
	II(c, d, a, b, M[6], s[i], t[i]); i++;
	II(b, c, d, a, M[13], s[i], t[i]); i++;
	II(a, b, c, d, M[4], s[i], t[i]); i++;
	II(d, a, b, c, M[11], s[i], t[i]); i++;
	II(c, d, a, b, M[2], s[i], t[i]); i++;
	II(b, c, d, a, M[9], s[i], t[i]); i++;

	state[0] += a;
	state[1] += b;
	state[2] += c;
	state[3] += d;

	MD5_memset((POINTER)M, 0, sizeof(M));
}

void MD5_Update(MD5_CTX* context, unsigned char* input, unsigned int inputLen)
{
	unsigned int i, index, partLen;

	index = (UINT4)((context->count[0] >> 3) & 0x3F);


	//
	if ((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
	{
		context->count[1]++;
	}

	context->count[1] += ((UINT4)inputLen >> 29);

	partLen = 64 - index;

	if (inputLen >= partLen)
	{
		MD5_memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
		MD5Transform(context->state, context->buffer);


		for (i = partLen; i + 63 < inputLen; i += 64)
			MD5Transform(context->state, &input[i]);

		index = 0;
	}
	else
		i = 0;

	MD5_memcpy
	((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen - i);

}

string toHex(UINT4 num)
{
	int x;
	string tp;
	char HexArray[] = "0123456789abcdef";
	string str = "";
	for (int i = 0; i < 4; i++)
	{
		tp = "";
		x = ((num >> i * 8) % (1 << 8)) & 0xff;
		for (int j = 0; j < 2; j++)
		{
			tp.insert(0, 1, HexArray[x % 16]);
			x /= 16;
		}
		str += tp;
	}
	return str;
}
string MD5_Final(unsigned char digest[16], MD5_CTX* context)
{
	unsigned char bits[8];
	unsigned int index, padLen;
	Encode(bits, context->count, 8);


	//填充操作
	index = (unsigned int)((context->count[0] >> 3) & 0x3f);
	padLen = (index < 56) ? (56 - index) : (120 - index);
	MD5_Update(context, PADDING, padLen);


	//长度
	MD5_Update(context, bits, 8);


	string s = "";
	for (int i = 0; i < 4; i++)
		s += toHex(context->state[i]);
	cout << s;
	//摘要中的存储状态
	Encode(digest, context->state, 16);

	MD5_memset((POINTER)context, 0, sizeof(*context));

	return s;
}



string MDString(char* string)
{
	MD5_CTX context;
	char* digest = new char[16];
	unsigned int len = strlen(string);

	MD5Init(&context);
	MD5_Update(&context, (unsigned char*)string, len);
	std::string  s = MD5_Final((unsigned char*)digest, &context);

	//MD5_print((unsigned char*)digest);

	return s;
}
string sendfile(char* filename,long long num)
	{
		string s;
		stringstream ss1;
		ss1 << num;
		ss1 >> s;
		string key = MDString((char*)s.c_str());
		//截半
		for (int i = 0; i < key.size(); i++) key[i] = toupper(key[i]);
		key.erase(16);
		enfile(filename, key);

		//初始化DLL
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) == 0)
		{
			//std::cout << "打开成功网络库成功" << std::endl;
		}
		else
		{
			exit(1);
		}

		unsigned int clientfd;


		if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		{
			//std::cout << "socket created failed.\n" << std::endl;
		}

		struct sockaddr_in servaddr;
		servaddr.sin_family = AF_INET;
		servaddr.sin_port = htons(6666);
		servaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


		if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		{
			//std::cout << "connect error\n";	
		}


		//std::cout << "connecting\n" << std::endl;

		//char filename[50];
		//读取文件取出共享的数据
		//std::cout << "输入你要上传的文件：" << std::endl;
		//std::cin >> filename;


		std::ifstream inFile;
		inFile.open(filename, std::ios::in | std::ios::out);
		if (!inFile.is_open()) {// std::cout << " open failed" << std::endl;
		}

		send(clientfd, filename, strlen(filename), 0);

		char buffer[BUFSIZ] = {};
		while (!inFile.eof())
		{
			inFile.getline(buffer, BUFSIZ);
			//std::cout << "Client send " << buffer << std::endl;
			if (SOCKET_ERROR == send(clientfd, buffer, sizeof(buffer), 0))
			{
				//std::cout << "send error" << std::endl;
			}
			else
			{
				//std::cout << "send success" << std::endl;
			}
			memset(buffer, '\0', sizeof(buffer));
		}
		inFile.close();

		memset(buffer, '\0', sizeof(buffer));
		strcpy(buffer, "^");
		if (send(clientfd, buffer, sizeof(buffer), 0) < 0)
		{

		}
		else
		{
			//std::cout << "over send" << std::endl;
		}


		//接受服务器返回的数
		char szBuffer[BUFSIZ] = { 0 };
		if (recv(clientfd, szBuffer, BUFSIZ, 0) > 0) {}
		
		//std::cout << "The status received from the server is:" << szBuffer << std::endl;

		//关闭套接字
		closesocket(clientfd);

		//终止使用 DLL
		WSACleanup();
		return key;
	}

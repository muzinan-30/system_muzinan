// CClassicalDlg.cpp: 实现文件
#include "pch.h"
#include "system_muzinan.h"
#include "CClassicalDlg.h"

#include "classicalcipher.cpp"
#include "playfair.cpp"
#include<vector>

// CClassicalDlg

IMPLEMENT_DYNCREATE(CClassicalDlg, CFormView)

vector<string> classical = { "Caesar cipher","Keyword cipher","Affine cipher",
"Multiliteral cipher","Vigenere cipher",/*"Autokey ciphertext",*/"Autokey plaintext","Playfair cipher",
"Permutation cipher","Column permutation cipher","Double-Transposition cipher" };

CClassicalDlg::CClassicalDlg()
	: CFormView(IDD_CLASSICAL)
	, m_classtxt1(_T(""))
	, m_classtxt2(_T(""))
	, m_classkey(_T(""))
	,funcSelect(_T(""))
	, m_classfilepath(_T(""))
{

}

CClassicalDlg::~CClassicalDlg()
{
}

void CClassicalDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_classical1);
	DDX_Text(pDX, IDC_EDIT2, m_classtxt1);
	DDX_Text(pDX, IDC_EDIT1, m_classtxt2);
	DDX_Text(pDX, IDC_EDIT3, m_classkey);
	DDX_Text(pDX, IDC_EDIT4, m_classfilepath);
	DDX_Control(pDX, IDC_CLASSFILE, m_classfile);
	DDX_Control(pDX, IDC_EDIT2, m_classicalplain);
}

BEGIN_MESSAGE_MAP(CClassicalDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CClassicalDlg::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CClassicalDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClassicalDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CLASSFILE, &CClassicalDlg::OnBnClickedClassfile)
END_MESSAGE_MAP()


// CClassicalDlg 诊断

#ifdef _DEBUG
void CClassicalDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CClassicalDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG

// CClassicalDlg 消息处理程序

void CClassicalDlg::OnInitialUpdate()
{

	
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	//初始化下拉框选项
	//string -> CString
	for (vector<string>::iterator it = classical.begin(); it != classical.end(); it++)
		m_classical1.AddString(CString(it->c_str()));


	m_classical1.SetCurSel(0);

	OnCbnSelchangeCombo1();

	//设置图标
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);

	m_classfile.SetIcon(icon);


	//设置字体
	m_oFont.CreatePointFont(100, _T("微软雅黑"));
	m_classicalplain.SetFont(&m_oFont);



}

//加密操作
void CClassicalDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	string cipher;
	
	UpdateData(TRUE);

	//string to int
	stringstream stream;

	//CString to string
	std::string plain(CW2A(m_classtxt1.GetString()));
	string key(CW2A(m_classkey.GetString()));

	if (fileflag)
	{
		if (funcSelect == _T("Column permutation cipher"))
		{
			classicalcipher::cpc_encryptFile(filename, key);
			MessageBox(_T("加密完成"));
		}
		else if (funcSelect == _T("Permutation cipher"))
		{

		}
		else if (funcSelect == _T("Double-Transposition cipher"))
		{

		}
		else if (funcSelect == _T("Caesar cipher"))
		{

		}
		else if (funcSelect == _T("Keyword cipher"))
		{

		}
		else if (funcSelect == _T("Affine cipher"))
		{

		}
		else if (funcSelect == _T("Multiliteral cipher"))
		{

		}
		else if (funcSelect == _T("Vigenere cipher"))
		{

		}
		else if (funcSelect == _T("Autokey ciphertext"))
		{
			cipher = classicalcipher::enAutocipher(classicalcipher::readFileIntoString(filename), classicalcipher::readFileIntoString((char*)key.c_str()));
			m_classtxt2 = CString(cipher.c_str());
		}
		else if (funcSelect == _T("Autokey plaintext"))
		{
			char* k = (char*)key.data();
			classicalcipher::autoplain_encryptfile(k, filename);
			MessageBox(_T("加密完成"));
		}
		else 
		{
			enplayfair(readFileIntoString(filename), key);
			MessageBox(_T("加密完成"));
		}
	}
	else
	{
		if (funcSelect == _T("Column permutation cipher"))
		{
			cipher = classicalcipher::cpc_encrypt(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Permutation cipher"))
		{
			cipher = classicalcipher::pc_encrpty(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Double-Transposition cipher"))
		{
			string key2 = key.substr(key.find_first_of(' ')+1);
			MessageBox(CString(key2.c_str()));
			key.erase(key.find_first_of(' '));
			MessageBox(CString(key.c_str()));

			cipher = classicalcipher::dcpc_encrpty(plain, key, key2);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Caesar cipher"))
		{ 
			char str[N] = {};
			stream << key;
			int offset;
			stream >> offset;
			strcpy(str, plain.c_str());
			classicalcipher::Caesar_encryption(str, offset);
			m_classtxt2 = (CString(str));
		}
		else if (funcSelect == _T("Keyword cipher"))
		{
			cipher = classicalcipher::keyword_encryption(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Affine cipher"))
		{
			string key2 = key.substr(key.find_first_of(' ') + 1);
			key.erase(key.find_first_of(' '));
			//MessageBox(CString(key.c_str()));
			//MessageBox(CString(key2.c_str()));
			int a, b;
			stream << key;
			stream >> a;
			stringstream ss1;
			ss1 << key2;
			ss1 >> b;
			//MessageBox(CString(plain.c_str()));
			cipher = classicalcipher::affine_encrypt(a, b, plain);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Multiliteral cipher"))
		{
			cipher = classicalcipher::Multiliteral_encryption(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Vigenere cipher"))
		{
			cipher = classicalcipher::vignere_encrypt(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else if (funcSelect == _T("Autokey ciphertext"))
		{
			cipher = classicalcipher::enAutocipher(plain, key);
			m_classtxt2 = CString(cipher.c_str());
		}
		else if (funcSelect == _T("Autokey plaintext"))
		{
			const char* p = plain.data();
			char* k = (char*)key.data();
			cipher = classicalcipher::autoplain_encrypt(k, p);
			m_classtxt2 = (CString(cipher.c_str()));
		}
		else
		{
			cipher=enplayfair(plain, key);
			m_classtxt2 = (CString(cipher.c_str()));
		}

	}

	//重置标识符
	fileflag = false;

	//同步数据
	UpdateData(FALSE);
}

void CClassicalDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//切换算法 触发事件

	//先获取名称
	int index = m_classical1.GetCurSel();
	m_classical1.GetLBText(index, funcSelect);
	//MessageBox(funcSelect);
}

//解密操作
void CClassicalDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取控件信息
	UpdateData(TRUE);

	string plain;

	//string to int
	stringstream stream;

	//CString to string
	std::string cipher(CW2A(m_classtxt1.GetString()));
	string key(CW2A(m_classkey.GetString()));
	if(fileflag)
	{ 
		if (funcSelect == _T("Column permutation cipher"))
		{
			classicalcipher::cpc_decryptFile(filename,key);
			MessageBox(_T("解密完成"));
			
		}
		else if (funcSelect == _T("Permutation cipher"))
		{
			
		}
		else if (funcSelect == _T("Double-Transposition cipher"))
		{

		}
		else if (funcSelect == _T("Caesar cipher"))
		{

		}
		else if (funcSelect == _T("Keyword cipher"))
		{

		}
		else if (funcSelect == _T("Affine cipher"))
		{

		}
		else if (funcSelect == _T("Multiliteral cipher"))
		{

		}
		else if (funcSelect == _T("Vigenere cipher"))
		{

		}
		else if (funcSelect == _T("Autokey ciphertext"))
		{
			cipher = classicalcipher::deAutocipher(classicalcipher::readFileIntoString(filename), classicalcipher::readFileIntoString((char*)key.c_str()));
			m_classtxt2 = CString(cipher.c_str());
		}
		else if (funcSelect == _T("Autokey plaintext"))
		{
			char* k = (char*)key.data();
			MessageBox(CString(k));
			classicalcipher::autoplain_decryptfile(k, filename);
			MessageBox(_T("解密完成"));
		}
		else
		{

		}
	}
	else
	{
		if (funcSelect == _T("Column permutation cipher"))
		{
			plain = classicalcipher::cpc_decrypt(cipher, key);
			int index = plain.find_first_of('&');
			if (index != string::npos)
			{
				plain.erase(index);
			}
			//MessageBox(CString(plain.c_str()));
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Permutation cipher"))
		{
			plain = classicalcipher::pc_decrpty(cipher, key);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Double-Transposition cipher"))
		{
			string key2 = key.substr(key.find_first_of(' ') + 1);
			MessageBox(CString(key2.c_str()));
			key.erase(key.find_first_of(' '));
			MessageBox(CString(key.c_str()));

			plain= classicalcipher::dcpc_decrpty(cipher, key, key2);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Caesar cipher"))
		{
			char str[N] = {};
			stream << key;
			int offset;
			stream >> offset;
			strcpy(str, cipher.c_str());
			classicalcipher::Caesar_decryption(str, offset);
			m_classtxt2 = (CString(str));
		}
		else if (funcSelect == _T("Keyword cipher"))
		{
			plain = classicalcipher::keyword_decryption(cipher, key);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Affine cipher"))
		{
			string key2 = key.substr(key.find_first_of(' ') + 1);
			//MessageBox(CString(key2.c_str()));
			key.erase(key.find_first_of(' '));
			//MessageBox(CString(key.c_str()));
			int a, b;
			stream << key;
			stream >> a;
			stringstream ss1;
			ss1 << key2;
			ss1 >> b;
			plain = classicalcipher::affine_decrypt(a, b,cipher);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Multiliteral cipher"))
		{
			plain = classicalcipher::Multiliteral_decryption(cipher, key);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Vigenere cipher"))
		{
			plain = classicalcipher::vignere_decrypt(cipher, key);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else if (funcSelect == _T("Autokey ciphertext"))
		{
			plain = classicalcipher::deAutocipher(cipher, key);
			m_classtxt2 = CString(plain.c_str());
		}
		else if (funcSelect == _T("Autokey plaintext"))
		{
			const char* c = cipher.data();
			char* k = (char*)key.data();
			plain = classicalcipher::autoplain_decrypt(k, c);
			m_classtxt2 = (CString(plain.c_str()));
		}
		else
		{
			plain = deplayfair(cipher, key);
			m_classtxt2 = (CString(plain.c_str()));
		}
	}
	
	//重置标识符
	fileflag = false;
	//同步到控件
	UpdateData(FALSE);
}

void CClassicalDlg::OnBnClickedClassfile()
{
	
	CString filter;
	CString str;
	filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if (dlg.DoModal() == IDOK)
	{

		str = dlg.GetPathName();
		//AfxMessageBox(str);
	}

	UpdateData(TRUE);

	//Cstring 转 char*
	int len = WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), NULL, 0, NULL, NULL);
	filename = new char[len + 1];
	memset(filename, 0, sizeof((char*)(len + 1)));
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), filename, len, NULL, NULL);
	filename[len] = '\0';

	m_classfilepath = str;
	fileflag = true;
	//MessageBox(CString(res.c_str()));

	UpdateData(FALSE);
}

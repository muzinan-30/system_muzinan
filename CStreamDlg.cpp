// CStreamDlg.cpp: 实现文件
//

#include "pch.h"
#include "allin.h"
#include "system_muzinan.h"
#include "CStreamDlg.h"


// CStreamDlg

IMPLEMENT_DYNCREATE(CStreamDlg, CFormView)

CStreamDlg::CStreamDlg()
	: CFormView(IDD_STREAM)
	, m_streamkey(_T(""))
	, m_rc4filepath(_T(""))
	, m_cacell(_T(""))
	, m_cacellnum(0)
	, m_carule(0)
	, m_cafilepath(_T(""))
	, m_catxt1(_T(""))
	, m_catxt2(_T(""))
	, m_rc4txt1(_T(""))
	, m_rc4txt2(_T(""))
{

}

CStreamDlg::~CStreamDlg()
{
}

void CStreamDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, m_streamkey);
	DDX_Control(pDX, IDC_BUTTON3, m_rc4file);
	DDX_Text(pDX, IDC_EDIT4, m_rc4filepath);
	DDX_Text(pDX, IDC_EDIT7, m_cacell);
	DDX_Text(pDX, IDC_EDIT8, m_cacellnum);
	DDX_Text(pDX, IDC_EDIT10, m_carule);
	DDX_Text(pDX, IDC_EDIT9, m_cafilepath);
	DDX_Control(pDX, IDC_BUTTON6, m_csfile);
	DDX_Text(pDX, IDC_EDIT12, m_catxt1);
	DDX_Text(pDX, IDC_EDIT13, m_catxt2);
	DDX_Text(pDX, IDC_EDIT5, m_rc4txt1);
	DDX_Text(pDX, IDC_EDIT6, m_rc4txt2);
}

BEGIN_MESSAGE_MAP(CStreamDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CStreamDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CStreamDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CStreamDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CStreamDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CStreamDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CStreamDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CStreamDlg 诊断

#ifdef _DEBUG
void CStreamDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CStreamDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CStreamDlg 消息处理程序



//加密操作
void CStreamDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	string cipher;
	UpdateData(TRUE);

	//string to int
	//stringstream stream;

	//CString to string
	std::string plain(CW2A(m_rc4txt1.GetString()));
	string key(CW2A(m_streamkey.GetString()));

	char K[BUFSIZ] = {};
	strcpy(K, key.c_str());

	char data[BUFSIZ] = {};
	strcpy(data, plain.c_str());

	if (fileflag) {
		streamcipher::RC4 rc4file;
		rc4file.TranFile(filename, K);
		MessageBox(_T("加密完成"));
	}
	else {
		//char output[BUFSIZ] = " ";
		len = strlen(data);
		streamcipher::RC4 rc4encrypt;
		rc4encrypt.SetStable(K, key.size());
		rc4encrypt.Transform(output, data, strlen(data));
		m_rc4txt2 = CString(output);
	}

	UpdateData(FALSE);
}



//rc4解密的操作
void CStreamDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	std::string cipher(CW2A(m_rc4txt1.GetString()));
	string key(CW2A(m_streamkey.GetString()));

	char K[BUFSIZ] = {};
	strcpy(K, key.c_str());
	MessageBox(CString(K));

	char data[BUFSIZ] = {};
	strcpy(data, cipher.c_str());
	MessageBox(CString(data));

	//char output[BUFSIZ] = " ";
	streamcipher::RC4 rc4encrypt;
	rc4encrypt.SetStable(K, key.size());
	rc4encrypt.Transform(output, output, len);

	m_rc4txt2 = CString(output);

	UpdateData(FALSE);

}

//rc4打开文件
void CStreamDlg::OnBnClickedButton3()
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

	//MessageBox(CString(res.c_str()));

	fileflag = true;

	m_rc4filepath = str;

	UpdateData(FALSE);
}


void CStreamDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);
	m_rc4file.SetIcon(icon);
	m_csfile.SetIcon(icon);

	// TODO: 在此添加专用代码和/或调用基类
}



//ca加密操作
void CStreamDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	string cipher;
	UpdateData(TRUE);

	//string to int
	//stringstream stream;

	//CString to string
	std::string plain(CW2A(m_catxt1.GetString()));
	string key(CW2A(m_streamkey.GetString()));
	string cell(CW2A(m_cacell.GetString()));

	char K[BUFSIZ] = {};
	strcpy(K, key.c_str());

	char data[BUFSIZ] = {};
	strcpy(data, plain.c_str());

	if (fileflag) {
		char* c = (char*)cell.data();
		streamcipher::CA cafile;
		m_cacellnum--;
		cafile.SetRule(m_carule);
		cafile.SetSream(c, m_cacellnum , plain.size());
		cafile.Transform(output, data);
		cafile.TranFile(filename, c,m_carule,m_cacellnum);
		MessageBox(_T("加密完成"));
	}
	else {
		//char output[BUFSIZ] = " ";
		calen = plain.size();
		MessageBox(CString(plain.c_str()));
		const char* p = plain.data();
		char* c = (char*)cell.data();
		m_cacellnum--;
		streamcipher::CA ca;
		ca.SetRule(m_carule);
		ca.SetSream(c, m_cacellnum, plain.size());
		cipher=ca.Transform(caoutput, p);
		m_catxt2 = CString(cipher.c_str());
		MessageBox(CString(cipher.c_str()));
	}

	UpdateData(FALSE);
}


//ca解密操作
void CStreamDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);

	std::string cipher(CW2A(m_rc4txt1.GetString()));
	string key(CW2A(m_streamkey.GetString()));
	string cell(CW2A(m_cacell.GetString()));

	const char* p = cipher.data();
	char* c = (char*)cell.data();
	m_cacellnum--;
	streamcipher::CA ca;
	ca.SetRule(m_carule);
	ca.SetSream(c, m_cacellnum, /*plain.size()*/calen);
	cipher = ca.Transform(caoutput, caoutput);
	m_catxt2 = CString(cipher.c_str());

	UpdateData(FALSE);
}

//ca打开文件
void CStreamDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
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

	//MessageBox(CString(res.c_str()));

	fileflag = true;

	m_cafilepath = str;

	UpdateData(FALSE);
}

// CBlockDlg.cpp: 实现文件
//

#include "pch.h"
#include "system_muzinan.h"
#include "CBlockDlg.h"

#include"blockcipher.cpp"
// CBlockDlg

IMPLEMENT_DYNCREATE(CBlockDlg, CFormView)

CBlockDlg::CBlockDlg()
	: CFormView(IDD_BLOCK)
	, m_blocktxt1(_T(""))
	, m_blocktxt2(_T(""))
	, m_blockkey(_T(""))
	, m_blockfilepath(_T(""))
{
}

CBlockDlg::~CBlockDlg()
{
}

void CBlockDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_blocktxt1);
	DDX_Text(pDX, IDC_EDIT1, m_blocktxt2);
	DDX_Text(pDX, IDC_EDIT3, m_blockkey);
	DDX_Text(pDX, IDC_EDIT4, m_blockfilepath);
	DDX_Control(pDX, IDC_BUTTON3, m_blockfile);
	DDX_Control(pDX, IDC_COMBO1, m_block1);
}

BEGIN_MESSAGE_MAP(CBlockDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CBlockDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CBlockDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CBlockDlg::OnBnClickedButton3)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CBlockDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBlockDlg 诊断

#ifdef _DEBUG
void CBlockDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CBlockDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBlockDlg 消息处理程序



//加密操作
void CBlockDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	std::string cipher;

	UpdateData(TRUE);

	//string to int

	//CString to string
	std::string plain(CW2A(m_blocktxt1.GetString()));
	std::string key(CW2A(m_blockkey.GetString()));

	if (fileflag)
	{
		if (funcSelect == _T("DES"))
		{
			//classicalcipher::cpc_encryptFile(filename, key);
			string cipher=DESEN::enDES(DESEN::readFileIntoString(filename), key);
			m_blocktxt2= CString(cipher.c_str());
			MessageBox(_T("加密完成"));
		}
		else
		{
			 
		}
	}
	else
	{
		if (funcSelect == _T("DES"))
		{
			//classicalcipher::cpc_encryptFile(filename, key);
			cipher=DESEN::enDES(plain, key);
			m_blocktxt2 = CString(cipher.c_str());
		}
		else
		{
			char a[65];
			char b[65];
			strcpy(a, plain.c_str());
			strcpy(b, key.c_str());
			cipher = AESEN::enAES(a, b);
			m_blocktxt2 = CString(cipher.c_str());
		}
	}


	//重置标识符
	fileflag = false;

	//同步数据
	UpdateData(FALSE);
}



//解密操作
void CBlockDlg::OnBnClickedButton2()
{
	
	UpdateData(TRUE);

	std::string cipher(CW2A(m_blocktxt1.GetString()));
	string key(CW2A(m_blockkey.GetString()));
	string plain;

	if (fileflag)
	{
		if (funcSelect == _T("DES"))
		{
			plain = DESDE::enDES(DESEN::readFileIntoString(filename), key);
			m_blocktxt1 = CString(plain.c_str());
			MessageBox(_T("解密完成"));
		}
		else
		{

		}
	}
	else
	{
		if (funcSelect == _T("DES"))
		{
			//classicalcipher::cpc_encryptFile(filename, key);
			MessageBox(CString(cipher.c_str()));
			MessageBox(CString(key.c_str()));
			plain=DESDE::enDES(cipher, key);
			m_blocktxt2 = CString(plain.c_str());
		}
		else
		{
			char a[65];
			char b[65];
			strcpy(a, cipher.c_str());
			strcpy(b, key.c_str());
			plain = AESDE::deAES(a, b);
			m_blocktxt2 = CString(plain.c_str());
		}
	}

	//重置标识符
	fileflag = false;

	//同步数据
	UpdateData(FALSE);
}


//打开文件
void CBlockDlg::OnBnClickedButton3()
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

	m_blockfilepath = str;
	fileflag = true;
	//MessageBox(CString(res.c_str()));

	UpdateData(FALSE);

}


void CBlockDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类】

	//初始化下拉框选项
	//string -> CString
	for (std::vector<std::string>::iterator it =block.begin(); it != block.end(); it++)
		m_block1.AddString(CString(it->c_str()));


	m_block1.SetCurSel(0);

	OnCbnSelchangeCombo1();


	//设置图标
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);

	m_blockfile.SetIcon(icon);
}


void CBlockDlg::OnCbnSelchangeCombo1()
{

	int index = m_block1.GetCurSel();
	m_block1.GetLBText(index, funcSelect);
}

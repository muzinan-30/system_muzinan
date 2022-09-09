// CPublicKeyDlg.cpp: 实现文件
//

#include "pch.h"
#include "system_muzinan.h"
#include "CPublicKeyDlg.h"


#include"publickey.cpp"
// CPublicKeyDlg

IMPLEMENT_DYNCREATE(CPublicKeyDlg, CFormView)

CPublicKeyDlg::CPublicKeyDlg()
	: CFormView(IDD_PUBLICKEY)
	, m_rsatxt1(_T(""))
	, m_rsatxt2(_T(""))
	, m_rsapublic(_T(""))
	, m_privatekey(_T(""))
{

}

CPublicKeyDlg::~CPublicKeyDlg()
{
}

void CPublicKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_rsatxt1);
	DDX_Text(pDX, IDC_EDIT2, m_rsatxt2);
	DDX_Text(pDX, IDC_EDIT3, m_rsapublic);
	DDX_Text(pDX, IDC_EDIT4, m_privatekey);
}

BEGIN_MESSAGE_MAP(CPublicKeyDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CPublicKeyDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPublicKeyDlg 诊断

#ifdef _DEBUG
void CPublicKeyDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPublicKeyDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPublicKeyDlg 消息处理程序


void CPublicKeyDlg::OnBnClickedButton1()
{
	
	UpdateData(TRUE);

	char binary[50];

	int e = RSA::get()[2];
	int n = RSA::get()[0];
	int d = RSA::get()[3];
	MessageBox(m_rsatxt1);
	memcpy(binary,LPCTSTR(m_rsatxt1), m_rsatxt1.GetLength() * sizeof(TCHAR));

	int M2 = RSA::binary2(binary);
	unsigned long long C = RSA::encryption(M2);
	unsigned long long M = RSA::decryption(C);

	std::stringstream ss; 
	ss << C;
	m_rsatxt2 = CString(ss.str().c_str());

	std::string publickey;
	ss.str("");
	ss << e;
	publickey += ss.str();
	ss.str("");
	ss << n;
	publickey += " ";
	publickey += ss.str();

	std::string privatekey;
	ss.str("");
	ss << d;
	privatekey += ss.str();
	privatekey += " ";
	ss.str("");
	ss << n;
	privatekey += ss.str();

	m_rsapublic = CString(publickey.c_str());
	m_privatekey = CString(privatekey.c_str());
	UpdateData(FALSE);
}

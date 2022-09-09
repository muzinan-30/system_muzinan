// CCdhDlg.cpp: 实现文件
//

#include "pch.h"
#include "system_muzinan.h"
#include "CCdhDlg.h"
#include "../cryptography_train/DH.h"

#include <sstream>

#include "dh.cpp"
// CCdhDlg

IMPLEMENT_DYNCREATE(CCdhDlg, CFormView)

CCdhDlg::CCdhDlg()
	: CFormView(IDD_CDH)
	, m_dhfilepath(_T(""))
	, m_dhB(0)
	, m_dhkey(0)
	, m_dhdeskey(_T(""))
{

}

CCdhDlg::~CCdhDlg()
{
}

void CCdhDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_dhfile);
	DDX_Text(pDX, IDC_EDIT3, m_dhfilepath);
	DDX_Text(pDX, IDC_EDIT1, m_dhB);
	DDX_Text(pDX, IDC_EDIT2, m_dhkey);
	DDX_Text(pDX, IDC_EDIT4, m_dhdeskey);
}

BEGIN_MESSAGE_MAP(CCdhDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CCdhDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CCdhDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CCdhDlg::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCdhDlg 诊断

#ifdef _DEBUG
void CCdhDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCdhDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCdhDlg 消息处理程序




//进行密钥协商
void CCdhDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);


	unsigned int clientfd;


	if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << "socket created failed.\n" << endl;
	};

	struct sockaddr_in servaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	servaddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
	{
		std::cout << "connect error\n";
	}


	cout << "connecting\n" << endl;

	//f
	ll a;
	ll p;
	//读取文件取出共享的数据
	ifstream inFile;
	inFile.open("prime.txt");
	if (!inFile.is_open()) { cout << " open failed" << endl; }
	inFile >> p;
	inFile >> a;
	inFile.close();

	srand((unsigned)time(NULL));
	ll B = rand() % p;
	ll Yb = dh::q_pow(a, B, p);
	cout << "Client selection:" << B << "send " << Yb << endl;

	m_dhB = B;

	//stringstream ss;
	//ss << Yb;
	//MessageBox(CString(ss.str().c_str()));

	//接受服务器返回的数
	char szBuffer[BUFSIZ] = { 0 };
	recv(clientfd, szBuffer, BUFSIZ, 0);
	cout << "The data received from the server is:" << szBuffer << endl;

	char ch[100] = {};
	itoa(Yb, ch, 10);
	char* str = ch;

	if (SOCKET_ERROR == send(clientfd, str, strlen(str) + sizeof(char), 0))
	{
		cout << "send error" << endl;
	}
	else
	{
		cout << "send success" << endl;
	}
	memset(str, sizeof(str), 0);

	int Ya = 0;
	for (int i = 0; szBuffer[i] != '\0'; i++)
	{
		Ya *= 10;
		Ya += szBuffer[i] - '0';
	}

	//stringstream ss1;
	//ss1 << Ya;
	//MessageBox(CString(ss1.str().c_str()));
	//stringstream ss2;
	//ss2 << B;
	//MessageBox(CString(ss2.str().c_str()));
	//stringstream ss3;
	//ss3 << p;
	//MessageBox(CString(ss3.str().c_str()));
	ll K = dh::q_pow(Ya, B, p);
	cout << "The negotiated key is:" << K << endl;

	m_dhkey = K;

	//关闭套接字
	closesocket(clientfd);

	//终止使用 DLL
	WSACleanup();

	UpdateData(FALSE);
}

//发送文件
void CCdhDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	string deskey = sendfile(filename, m_dhkey);
	MessageBox(CString(deskey.c_str()));
	m_dhdeskey = CString(deskey.c_str());
	AfxMessageBox(_T("发送完成"));
	UpdateData(FALSE);
}

//打开文件
void CCdhDlg::OnBnClickedButton2()
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

	m_dhfilepath = str;
	//MessageBox(CString(res.c_str()));

	UpdateData(FALSE);
}


void CCdhDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//设置图标
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);
	m_dhfile.SetIcon(icon);
}




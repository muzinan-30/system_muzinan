// CMd5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "system_muzinan.h"
#include "CMd5Dlg.h"

#include "md5.cpp"

// CMd5Dlg

IMPLEMENT_DYNCREATE(CMd5Dlg, CFormView)

CMd5Dlg::CMd5Dlg()
	: CFormView(IDD_MD5)
	, m_md5string(_T(""))
	, m_md5filepath(_T(""))
	, m_md5value(_T(""))
{
	//HBITMAP   hBitmap;
	//hBitmap = LoadBitmap(AfxGetInstanceHandle(),
	//	MAKEINTRESOURCE(IDB_BITMAP4));
	//((CButton*)GetDlgItem(IDC_BUTTON2))->SetBitmap(hBitmap);

}

CMd5Dlg::~CMd5Dlg()
{
}

void CMd5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_md5string);
	DDX_Text(pDX, IDC_EDIT3, m_md5filepath);
	DDX_Text(pDX, IDC_EDIT1, m_md5value);
	DDX_Control(pDX, IDC_MD5FILE, m_md5file);
}

BEGIN_MESSAGE_MAP(CMd5Dlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CMd5Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_MD5FILE, &CMd5Dlg::OnBnClickedMd5file)
END_MESSAGE_MAP()


// CMd5Dlg 诊断

#ifdef _DEBUG
void CMd5Dlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMd5Dlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMd5Dlg 消息处理程序
void CMd5Dlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_BITMAP4);

	BITMAP bmp;
	bitmap.GetBitmap(&bmp);



	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON2);

	m_md5file.SetIcon(icon);

	//m_button2.MoveWindow(20, 20, bmp.bmWidth, bmp.bmHeight);
	// TODO: 在此添加专用代码和/或调用基类
}

void CMd5Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	//CString2char*
	//散列函数
	//MessageBox(m_md5string);
	
	//Cstring 转 char*
	int len = WideCharToMultiByte(CP_ACP, 0, m_md5string, m_md5string.GetLength(), NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, sizeof((char*)(len + 1)));
	WideCharToMultiByte(CP_ACP, 0, m_md5string, m_md5string.GetLength(), str, len, NULL, NULL);
	str[len] = '\0';


	std::string res=md5::MDString(str);
	
	m_md5string.ReleaseBuffer();
	//MessageBox(CString(res.c_str()));
	m_md5value = res.c_str();

	UpdateData(FALSE);
}


void CMd5Dlg::OnBnClickedMd5file()
{
	// TODO: 在此添加控件通知处理程序代码
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
	char* filename = new char[len + 1];
	memset(filename, 0, sizeof((char*)(len + 1)));
	WideCharToMultiByte(CP_ACP, 0, str, str.GetLength(), filename, len, NULL, NULL);
	filename[len] = '\0';

	std::string res = md5::MDFile(filename);

	m_md5string.ReleaseBuffer();
	//MessageBox(CString(res.c_str()));
	m_md5value = res.c_str();
	m_md5filepath = str;

	UpdateData(FALSE);
}


void CMd5Dlg::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: 在此添加专用代码和/或调用基类

	CRect rect;
	CPaintDC dc(this);
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(141, 182, 205));
	dc.FillPath();

	//背景图片 能够自适应窗口
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP_BACKGROUND);   //IDB_BITMAP_BACKGROUND是你自己的图对应的ID 
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	CFormView::OnPrint(pDC, pInfo);
}


void CMd5Dlg::OnDraw(CDC*  pDC)
{
	// TODO: 在此添加专用代码和/或调用基类
	//CDocument* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//CBitmap bitmap;
	//bitmap.LoadBitmap(IDB_BITMAP_BACKGROUND);//将位图装入内存
	//CDC MemDC;
	//MemDC.CreateCompatibleDC(pDC);//创建内存设备环境
	//CBitmap* OldBitmap = MemDC.SelectObject(&bitmap);
	//BITMAP bm;  //创建BITMAP结构变量
	//bitmap.GetBitmap(&bm);//获取位图信息
	//pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &MemDC, 0, 0, SRCCOPY);//显示位图  开始的四个参数可以设置源位图在目标图上显示的位置，（0,0）表示从最左上角开始显示
	//pDC->SelectObject(OldBitmap);  //恢复设备环境

}

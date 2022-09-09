
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "system_muzinan.h"
#include "CSelectView.h"
#include "CDisplayView.h"
#include "MainFrm.h"

#include "CClassicalDlg.h"
#include "CMd5Dlg.h"
#include "CStreamDlg.h"
#include "CPublicKeyDlg.h"
#include "CCdhDlg.h"
#include "CBlockDlg.h"

#include<iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	//ON_MESSAGE是自定义的消息
//产生NM_X消息，自动调用onMyChange函数
//注意不要加冒号
ON_MESSAGE(NM_A, onMyChange)
ON_MESSAGE(NM_B, onMyChange)
ON_MESSAGE(NM_C, onMyChange)
ON_MESSAGE(NM_D, onMyChange)
ON_MESSAGE(NM_E, onMyChange)
ON_MESSAGE(NM_F, onMyChange)
ON_MESSAGE(NM_G, onMyChange)

ON_COMMAND(ID_32771, &CMainFrame::On32771)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));



	//设置图标
	SetClassLong(m_hWnd, GCLP_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));
	//设置标题，副标题
	SetTitle(_T("1.0"));
	//设置窗体的大小
	MoveWindow(0, 0, 1200, 800);
	//设置居中显示
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


//实现切分界面的函数，分成左右两部分
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	m_splitter.CreateStatic(this, 1, 2);

	//设置切分的左右两边要显示的内容
	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 800), pContext);
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(1000, 800), pContext);

	return TRUE;
}

LRESULT CMainFrame::onMyChange(WPARAM wParam, LPARAM lParam)
{
	//将新的界面挂载到界面中
	CCreateContext Content;
	if (wParam == NM_A) {
		Content.m_pNewViewClass = RUNTIME_CLASS(CClassicalDlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CClassicalDlg), CSize(1000, 800), &Content);
		CClassicalDlg* pNewView = (CClassicalDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else if (wParam == NM_B) {
	 	Content.m_pNewViewClass = RUNTIME_CLASS(CStreamDlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CStreamDlg), CSize(1000, 800), &Content);
		CStreamDlg* pNewView = (CStreamDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else if (wParam == NM_C) {
		Content.m_pNewViewClass = RUNTIME_CLASS(CBlockDlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CBlockDlg), CSize(1000, 800), &Content);
		CBlockDlg* pNewView = (CBlockDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else if (wParam == NM_D) {
		Content.m_pNewViewClass = RUNTIME_CLASS(CPublicKeyDlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CPublicKeyDlg), CSize(1000, 800), &Content);
		CPublicKeyDlg* pNewView = (CPublicKeyDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else if (wParam == NM_E) {
		//MessageBox(_T("散列函数界面挂载"));
		Content.m_pNewViewClass = RUNTIME_CLASS(CMd5Dlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CMd5Dlg), CSize(1000, 800), &Content);
		CMd5Dlg* pNewView = (CMd5Dlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else if (wParam == NM_F) {
		Content.m_pNewViewClass = RUNTIME_CLASS(CCdhDlg);
		Content.m_pCurrentFrame = this;
		Content.m_pLastView = (CFormView*)m_splitter.GetPane(0, 1);
		m_splitter.DeleteView(0, 1);
		m_splitter.CreateView(0, 1, RUNTIME_CLASS(CCdhDlg), CSize(1000, 800), &Content);
		CCdhDlg* pNewView = (CCdhDlg*)m_splitter.GetPane(0, 1);
		m_splitter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_splitter.SetActivePane(0, 1);
	}
	else {

	}
	return 0;
}




void CMainFrame::On32771()
{
	// TODO: 在此添加命令处理程序代码
	// 
	//打开文件目录
	CString filter;
	filter = "文本文件(*.txt)|*.txt|C++文件(*.h,*.cpp)|*.h;*.cpp||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	if (dlg.DoModal() == IDOK)
	{
		CString str;
		str = dlg.GetPathName();
		AfxMessageBox(str);
	}
}

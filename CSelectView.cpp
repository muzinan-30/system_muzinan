// CSelectView.cpp: 实现文件
//


#include "pch.h"
#include "system_muzinan.h"
#include "CSelectView.h"
#include "MainFrm.h"


// CSelectView

IMPLEMENT_DYNCREATE(CSelectView, CTreeView)

CSelectView::CSelectView()
{

}

CSelectView::~CSelectView()
{
}

BEGIN_MESSAGE_MAP(CSelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CSelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// CSelectView 诊断

#ifdef _DEBUG
void CSelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CSelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
void CSelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//初始化代码
	//获取树的控件
	m_treeCtrl = &GetTreeCtrl();

	//准备图片集合
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON1);

	m_imageList.Create(30, 30, ILC_COLOR32, 1, 1);
	m_imageList.Add(icon);
	m_treeCtrl->SetImageList(&m_imageList, TVSIL_NORMAL);

	//添加节点
	m_treeCtrl->InsertItem(_T("古典密码"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("流密码"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("分块密码"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("公钥密码"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("单向散列函数"), 0, 0, NULL);
	m_treeCtrl->InsertItem(_T("DH密钥交换"), 0, 0, NULL);
	//m_treeCtrl->InsertItem(_T("实验七"), 0, 0, NULL);

}
#endif
#endif //_DEBUG


// CSelectView 消息处理程序
void CSelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	//获取当前选中项
	HTREEITEM item = m_treeCtrl->GetSelectedItem();

	//获取内容
	CString str = m_treeCtrl->GetItemText(item);

	if (str == _T("古典密码")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_A, (WPARAM)NM_A, (LPARAM)0);
	}
	else  if (str == _T("流密码")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_B, (WPARAM)NM_B, (LPARAM)0);
	}
	else  if (str == _T("分块密码")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_C, (WPARAM)NM_C, (LPARAM)0);
	}
	else  if (str == _T("公钥密码")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_D, (WPARAM)NM_D, (LPARAM)0);
	}
	else  if (str == _T("单向散列函数")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_E, (WPARAM)NM_E, (LPARAM)0);
		//MessageBox(_T("散列函数界面挂载"));
	}
	else  if (str == _T("DH密钥交换")) {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_F, (WPARAM)NM_F, (LPARAM)0);
	}
	else {
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_G, (WPARAM)NM_G, (LPARAM)0);
	}

}

// CDisplayView.cpp: 实现文件
//

#include "pch.h"
#include "system_muzinan.h"
#include "CDisplayView.h"


// CDisplayView

IMPLEMENT_DYNCREATE(CDisplayView, CFormView)

CDisplayView::CDisplayView()
	: CFormView(IDD_CDisplayView)
{

}

CDisplayView::~CDisplayView()
{
}

void CDisplayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDisplayView, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CDisplayView 诊断

#ifdef _DEBUG
void CDisplayView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDisplayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDisplayView 消息处理程序


HBRUSH CDisplayView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	m_bmp.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP_BACKGROUND));   
	//这里将位图加载进资源后，再Load
	m_brush.CreatePatternBrush(&m_bmp);
	if (nCtlColor == CTLCOLOR_DLG)
	{
		return m_brush;
	}

	return hbr;
}


// system_muzinanView.cpp: CsystemmuzinanView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "system_muzinan.h"
#endif

#include "system_muzinanDoc.h"
#include "system_muzinanView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsystemmuzinanView

IMPLEMENT_DYNCREATE(CsystemmuzinanView, CView)

BEGIN_MESSAGE_MAP(CsystemmuzinanView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CsystemmuzinanView 构造/析构

CsystemmuzinanView::CsystemmuzinanView() noexcept
{
	// TODO: 在此处添加构造代码

}

CsystemmuzinanView::~CsystemmuzinanView()
{
}

BOOL CsystemmuzinanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CsystemmuzinanView 绘图

void CsystemmuzinanView::OnDraw(CDC* /*pDC*/)
{
	CsystemmuzinanDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CsystemmuzinanView 打印

BOOL CsystemmuzinanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CsystemmuzinanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CsystemmuzinanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CsystemmuzinanView 诊断

#ifdef _DEBUG
void CsystemmuzinanView::AssertValid() const
{
	CView::AssertValid();
}

void CsystemmuzinanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsystemmuzinanDoc* CsystemmuzinanView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsystemmuzinanDoc)));
	return (CsystemmuzinanDoc*)m_pDocument;
}
#endif //_DEBUG


// CsystemmuzinanView 消息处理程序

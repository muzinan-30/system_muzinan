
// system_muzinanView.h: CsystemmuzinanView 类的接口
//

#pragma once


class CsystemmuzinanView : public CView
{
protected: // 仅从序列化创建
	CsystemmuzinanView() noexcept;
	DECLARE_DYNCREATE(CsystemmuzinanView)

// 特性
public:
	CsystemmuzinanDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CsystemmuzinanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // system_muzinanView.cpp 中的调试版本
inline CsystemmuzinanDoc* CsystemmuzinanView::GetDocument() const
   { return reinterpret_cast<CsystemmuzinanDoc*>(m_pDocument); }
#endif


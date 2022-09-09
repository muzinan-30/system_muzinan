
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

//自己定义的消息
//不要加冒号在后面
#define NM_A  (WM_USER+100)
#define NM_B  (WM_USER+101)
#define NM_C  (WM_USER+102)
#define NM_D  (WM_USER+103)
#define NM_E  (WM_USER+104)
#define NM_F  (WM_USER+105)
#define NM_G (WM_USER+106)


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	//切分窗口函数
	CSplitterWnd m_splitter;
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

	// 挂载函数
	afx_msg LRESULT onMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void On32771();
};



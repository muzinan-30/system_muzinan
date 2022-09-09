#pragma once



// CMd5Dlg 窗体视图

class CMd5Dlg : public CFormView
{
	DECLARE_DYNCREATE(CMd5Dlg)

protected:
	CMd5Dlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CMd5Dlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MD5 };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	// md5散列字符串
	CString m_md5string;
	// 文件路径
	CString m_md5filepath;
	// 得到的md5值
	CString m_md5value;
public:
	afx_msg void OnBnClickedButton1();

	virtual void OnInitialUpdate();


	afx_msg void OnBnClickedMd5file();
	CButton m_md5file;
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnDraw(CDC* /*pDC*/);
};



#pragma once



// CClassicalDlg 窗体视图

class CClassicalDlg : public CFormView
{
	DECLARE_DYNCREATE(CClassicalDlg)

protected:
	CClassicalDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CClassicalDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASSICAL };
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
	CComboBox m_classical1;
	// 古典密码学文本输入框1
	CString m_classtxt1;
	// 古典密码文本输入框2
	CString m_classtxt2;
	// 古典密码keyword
	CString m_classkey;

	CString funcSelect;
public:
	virtual void OnInitialUpdate();
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedButton2();
private:
	// 古典加解密文件的文件路径
	CString m_classfilepath;
	// 打开文件
	CButton m_classfile;
	char* filename;
	bool  fileflag=false;
public:
	afx_msg void OnBnClickedClassfile();
private:
	// 用于设置编辑框属性的变量
	CEdit m_classicalplain;
protected:
	CFont m_oFont;
};



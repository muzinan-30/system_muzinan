#pragma once



// CStreamDlg 窗体视图

class CStreamDlg : public CFormView
{
	DECLARE_DYNCREATE(CStreamDlg)

protected:
	CStreamDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CStreamDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STREAM };
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
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:

	// RC4的key
	CString m_streamkey;
	// 打开rc4文件
	CButton m_rc4file;

	char* filename;
	bool  fileflag = false;
public:
	afx_msg void OnBnClickedButton3();
	virtual void OnInitialUpdate();
private:
	// 流密码的文件路径
	CString m_rc4filepath;
	// CA的cell
	CString m_cacell;
public:
	// CA的cellnum
	int m_cacellnum;
private:
	// CA的rule
	int m_carule;
	// CA文件路径
	CString m_cafilepath;
	// 打开ca文件
	CButton m_csfile;
public:
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
private:
	// ca框1
	CString m_catxt1;
	// ca框2
	CString m_catxt2;
	CString m_rc4txt1;
	CString m_rc4txt2;

	int len=0;
	int calen = 0;
	char output[BUFSIZ] = " ";

	char caoutput[BUFSIZ] = " ";
	char* rc4cipehr;
	CBrush m_brush;
};



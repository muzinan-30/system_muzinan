#pragma once



// CPublicKeyDlg 窗体视图

class CPublicKeyDlg : public CFormView
{
	DECLARE_DYNCREATE(CPublicKeyDlg)

protected:
	CPublicKeyDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CPublicKeyDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PUBLICKEY };
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
	
private:
	CString m_rsatxt2;
	// 公钥
	CString m_rsapublic;
	// 私钥
	CString m_privatekey;
	CString m_rsatxt1;
};



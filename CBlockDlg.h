#pragma once


#include<vector>
#include<string>
// CBlockDlg 窗体视图

class CBlockDlg : public CFormView
{
	DECLARE_DYNCREATE(CBlockDlg)

protected:
	CBlockDlg();           // 动态创建所使用的受保护的构造函数
	virtual ~CBlockDlg();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLOCK };
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
	// 分块加密的txt1
	CString m_blocktxt1;
	CString m_blocktxt2;
	// 分块加密的密钥
	CString m_blockkey;
	// 分块密码文件路径
	CString m_blockfilepath;
	// 打开文件
	CButton m_blockfile;
	CString funcSelect;
	char* filename;
	bool  fileflag = false;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
private:
	// 选择加密方法
	CComboBox m_block1;
	std::vector<std::string> block = {"DES","AES"};
public:
	virtual void OnInitialUpdate();

	afx_msg void OnCbnSelchangeCombo1();
};



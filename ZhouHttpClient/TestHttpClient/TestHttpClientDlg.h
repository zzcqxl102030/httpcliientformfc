
// TestHttpClientDlg.h: 头文件
//

#pragma once


// CTestHttpClientDlg 对话框
class CTestHttpClientDlg : public CDialogEx
{
// 构造
public:
	CTestHttpClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TESTHTTPCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonTestnormal();
	afx_msg void OnBnClickedButtonUploadlocal();
	afx_msg void OnBnClickedButtonUploadmemory();
	afx_msg void OnBnClickedButtonUploadlocalOnekey();
	afx_msg void OnBnClickedButtonDownloadfile();
	afx_msg void OnBnClickedButtonUploadmemoryOnekey();
};

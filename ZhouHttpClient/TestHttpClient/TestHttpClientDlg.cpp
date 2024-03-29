﻿
// TestHttpClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "TestHttpClient.h"
#include "TestHttpClientDlg.h"
#include "afxdialogex.h"
#include "HttpClientUtils.h"
#include "Point.h"
#include "http/HttpClient.h"
#include "http/UploadFiles.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestHttpClientDlg 对话框



CTestHttpClientDlg::CTestHttpClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TESTHTTPCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestHttpClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestHttpClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TESTNORMAL, &CTestHttpClientDlg::OnBnClickedButtonTestnormal)
	ON_BN_CLICKED(IDC_BUTTON_UPLOADLOCAL, &CTestHttpClientDlg::OnBnClickedButtonUploadlocal)
	ON_BN_CLICKED(IDC_BUTTON_UPLOADMEMORY, &CTestHttpClientDlg::OnBnClickedButtonUploadmemory)
	ON_BN_CLICKED(IDC_BUTTON_UPLOADLOCAL_ONEKEY, &CTestHttpClientDlg::OnBnClickedButtonUploadlocalOnekey)
	ON_BN_CLICKED(IDC_BUTTON_DOWNLOADFILE, &CTestHttpClientDlg::OnBnClickedButtonDownloadfile)
	ON_BN_CLICKED(IDC_BUTTON_UPLOADMEMORY_ONEKEY, &CTestHttpClientDlg::OnBnClickedButtonUploadmemoryOnekey)
END_MESSAGE_MAP()


// CTestHttpClientDlg 消息处理程序

BOOL CTestHttpClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTestHttpClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestHttpClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTestHttpClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestHttpClientDlg::OnBnClickedButtonTestnormal()
{
	MyPoint* pt = new MyPoint();
	pt->x = 2;
	pt->y = 5;
	USES_CONVERSION;
	HttpClientUtils *httpclientUtil = new HttpClientUtils(JSON_HTTP,
		"http://192.168.31.84:8088/authenticate/test",pt);
	RespTest *rt = new RespTest();
	httpclientUtil->AddHeader("Authorization: Bearer 142a6b46-cd81-4c08-bda1-050d57fc7ffc");
	httpclientUtil->DoHttp(rt);
	CString strResult = A2W(rt->toJson().c_str());
	MessageBox(strResult);
	// TODO: 在此添加控件通知处理程序代码
}


void CTestHttpClientDlg::OnBnClickedButtonUploadlocal()
{
	// TODO: 在此添加控件通知处理程序代码
	MyPoint *pt= new MyPoint();
	pt->x = 2;
	pt->y = 5;
	USES_CONVERSION;
	//如果要上传文件的化要执行如下代码 ----------start
	vector<FilesVec*> vecFiles;
	FilesVec* localFile1 = new FilesVec();
	localFile1->fileName = "D:/work/0000-67098-0Z80F7.pdf";
	localFile1->key = "ss";
	vecFiles.push_back(localFile1);
	FilesVec* localFile2 = new FilesVec();
	localFile2->fileName = "D:/work/3D/qibaishi.png";
	localFile2->key = "gg";
	vecFiles.push_back(localFile2);
	//如果要上传文件的化要执行如上代码----------- end
	HttpClientUtils *httpclientUtil = new HttpClientUtils(UPLOADFILE_HTTP,
		"http://127.0.0.1:8703/GetPointLocal",pt,true, vecFiles);	
	httpclientUtil->DoHttp(pt);
	CString strResult = A2W(pt->toJson().c_str());
	MessageBox(strResult);
}

void CTestHttpClientDlg::OnBnClickedButtonUploadlocalOnekey()
{
	// TODO: 在此添加控件通知处理程序代码
	MyPoint *pt = new MyPoint();
	pt->x = 2;
	pt->y = 5;
	USES_CONVERSION;
	vector<FilesVec*> vecFiles;
	FilesVec* localFile1 = new FilesVec();
	localFile1->fileName = "D:/work/0000-67098-0Z80F7.pdf";
	vecFiles.push_back(localFile1);
	FilesVec* localFile2 = new FilesVec();
	localFile2->fileName = "D:/work/3D/qibaishi.png";
	vecFiles.push_back(localFile2);
	HttpClientUtils *httpclientUtil = new HttpClientUtils(UPLOADFILE_HTTP, 
		"http://127.0.0.1:8703/GetPointOnekey",pt,true,vecFiles);
	httpclientUtil->DoHttp(pt);
	CString strResult = A2W(pt->toJson().c_str());
	MessageBox(strResult);
}

void CTestHttpClientDlg::OnBnClickedButtonUploadmemory()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CTestHttpClientDlg::OnBnClickedButtonUploadmemoryOnekey()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTestHttpClientDlg::OnBnClickedButtonDownloadfile()
{
	// TODO: 在此添加控件通知处理程序代码
	MyPoint* pt = new MyPoint();
	pt->x = 2;
	pt->y = 5;
	USES_CONVERSION;
	HttpClientUtils *httpclientUtil = new HttpClientUtils(DOWNLOAD_HTTP,
		"http://192.168.31.10:8888/group1/M00/00/99/wKgfCmJEKcmAT_JWABbkjk139kc725.jpg");
	httpclientUtil->savePath = "D:/httpsave.jpg";
	httpclientUtil->DoHttp(nullptr);
	if (PathFileExists(L"D:/httpsave.jpg"))
	{
		MessageBox(L"file dowload success!");
	}
}

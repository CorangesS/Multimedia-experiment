
// t3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "t3.h"
#include "t3Dlg.h"
#include "afxdialogex.h"
#include <afxdlgs.h>

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


// Ct3Dlg 对话框



Ct3Dlg::Ct3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_T3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Ct3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC, m_MyImageControl);
}

BEGIN_MESSAGE_MAP(Ct3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Ct3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Ct3Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Ct3Dlg 消息处理程序

BOOL Ct3Dlg::OnInitDialog()
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

void Ct3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Ct3Dlg::OnPaint()
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
HCURSOR Ct3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Ct3Dlg::OnBnClickedButton1()
{
	// TODO: Add your command handler code here
	char szFileFilter[] =
		"Mp4 File(*.mp4)|*.mp4|"
		"Mp3 File(*.mp3)|*.mp3|"
		"Wma File(*.wma)|*.wma|"
		"Video File(*.dat)|*.dat|"
		"Wave File(*.wav)|*.wav|"
		"AVI File(*.avi)|*.avi|"
		"Movie File(*.mov)|*.mov|"
		"Media File(*.mmm)|*.mmm|"
		"Mid File(*.mid;*,rmi)|*.mid;*.rmi|"
		"MPEG File(*.mpeg)|*.mpeg|"
		"All File(*.*)|*.*||";
	CFileDialog FileDlg(BOOL(1), (LPCTSTR) NULL, (LPCTSTR) NULL, (DWORD) OFN_HIDEREADONLY, (LPCTSTR)szFileFilter,(CWnd*) this, (DWORD) 0, (BOOL) TRUE);
	if (FileDlg.DoModal() == IDOK)
	{
		PathName = FileDlg.GetPathName();
	}

	int x = 0; // 新位置的 x 坐标
	int y = 0; // 新位置的 y 坐标
	int width = 200; // 控件的新宽度
	int height = 200; // 控件的新高度
	m_MyImageControl.SetWindowPos(NULL, x, y, width, height, SWP_NOZORDER);

	//使用 LoadImage 加载其他格式的图片：
	HBITMAP hBitmap = (HBITMAP)::LoadImage(
		AfxGetInstanceHandle(), // 应用程序的实例句柄
		PathName,               // 图像文件路径
		IMAGE_BITMAP,           // 指定图像类型为位图
		0,                      // 使用图像的实际宽度
		0,                      // 使用图像的实际高度
		LR_LOADFROMFILE | LR_CREATEDIBSECTION // 加载标志
	);
	if (hBitmap)
	{
		m_MyImageControl.SetBitmap(hBitmap);
		// 注意：加载的图片需要在不再使用时手动释放
		// ::DeleteObject(hBitmap);
	}
	UpdateWindow();
}

void Ct3Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int x = 0; // 新位置的 x 坐标
	int y = 0; // 新位置的 y 坐标
	int width = 400; // 控件的新宽度
	int height = 400; // 控件的新高度
	m_MyImageControl.SetWindowPos(&CWnd::wndTop, x, y, width, height, SWP_NOMOVE);

	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), _T("./res/test6.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	if (hBitmap)
	{
		m_MyImageControl.SetBitmap(hBitmap);
		// 注意：加载的图片需要在不再使用时手动释放
		// ::DeleteObject(hBitmap);
	}
	UpdateWindow();
}

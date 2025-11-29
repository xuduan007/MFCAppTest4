
// MFCApplication2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "VerificationDialog.h"
#include "afxdialogex.h"
#include <afxtempl.h>

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


// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	// 初始化随机数种子
	srand((unsigned)time(nullptr));
	
	// 初始化成员变量
	m_nCorrectCount = 0;
	m_nIncorrectCount = 0;
	m_bTimerRunning = FALSE;
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_LOGIN_BUTTON, &CMFCApplication2Dlg::OnBnClickedLoginButton)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载欢迎图片
	CStatic* pWelcomeImage = (CStatic*)GetDlgItem(IDC_WELCOME_IMAGE);
	if (pWelcomeImage)
	{
		CBitmap bmp;
		if (bmp.LoadBitmap(IDB_BITMAP1)) // 使用现有的位图资源
		{
			pWelcomeImage->SetBitmap(bmp);
		}
	}

	// 设置定时器，每3秒触发一次
	SetTimer(1, 3000, nullptr);
	m_bTimerRunning = TRUE;

	// 生成初始随机数
	GenerateRandomNumber();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);	
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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

	CRect rect(100, 0, 200, 300);
	//GetClientRect(&rect);
	GetDlgItem(IDC_STATIC)->MoveWindow(&rect);

	CBitmap bitmap;
	//加载指定位图资源 Bmp图片ID
	bitmap.LoadBitmap(IDB_BITMAP1);
	//获取对话框上的句柄 图片控件ID
	CStatic* p = (CStatic*)GetDlgItem(IDC_STATIC);
	//设置静态控件窗口风格为位图居中显示
	p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	//将图片设置到Picture控件上
	p->SetBitmap(bitmap);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CMFCApplication2Dlg::OnBnClickedButton1()
{
	/*
	CString text;
	CWnd* wnd = GetDlgItem(IDC_SHOW);
	wnd->GetWindowText(text);
	wnd->SetWindowText(text + _T("Hello, MFC!"));
	*/
		
}

// 定时器处理函数
void CMFCApplication2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// 每3秒生成一个新的随机数
		GenerateRandomNumber();
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

// 生成6位随机数
void CMFCApplication2Dlg::GenerateRandomNumber()
{
	// 生成100000到999999之间的随机数
	int nRandom = rand() % 900000 + 100000;
	
	// 转换为6位字符串
	m_strRandomNumber.Format(_T("%06d"), nRandom);
	
	// 更新UI显示
	CStatic* pRandomNumber = (CStatic*)GetDlgItem(IDC_RANDOM_NUMBER);
	if (pRandomNumber)
	{
		pRandomNumber->SetWindowText(m_strRandomNumber);
	}
}

// 登录按钮点击事件
void CMFCApplication2Dlg::OnBnClickedLoginButton()
{
	// 获取用户输入
	CEdit* pInputEdit = (CEdit*)GetDlgItem(IDC_INPUT_EDIT);
	if (!pInputEdit)
		return;
	
	CString strInput;
	pInputEdit->GetWindowText(strInput);
	
	// 检查输入是否为6位数字
	if (strInput.GetLength() != 6)
	{
		MessageBox(_T("请输入6位数字！"), _T("提示"), MB_OK | MB_ICONWARNING);
		return;
	}
	
	// 比较输入和随机数
	if (strInput == m_strRandomNumber)
	{
		ShowVerificationResult(TRUE);
	}
	else
	{
		ShowVerificationResult(FALSE);
	}
	
	// 清空输入框
	pInputEdit->SetWindowText(_T(""));
}

// 显示校验结果
void CMFCApplication2Dlg::ShowVerificationResult(BOOL bSuccess)
{
	if (bSuccess)
	{
		// 正确次数加1
		m_nCorrectCount++;
		
		// 更新正确次数显示
		CStatic* pCorrectCount = (CStatic*)GetDlgItem(IDC_CORRECT_COUNT);
		if (pCorrectCount)
		{
			CString strText;
			strText.Format(_T("正确次数: %d"), m_nCorrectCount);
			pCorrectCount->SetWindowText(strText);
		}
	}
	else
	{
		// 失败次数加1
		m_nIncorrectCount++;
		
		// 更新失败次数显示
		CStatic* pIncorrectCount = (CStatic*)GetDlgItem(IDC_INCORRECT_COUNT);
		if (pIncorrectCount)
		{
			CString strText;
			strText.Format(_T("失败次数: %d"), m_nIncorrectCount);
			pIncorrectCount->SetWindowText(strText);
		}
	}
	
	// 显示提示对话框
	CVerificationDialog dlg(bSuccess);
	dlg.DoModal();
}


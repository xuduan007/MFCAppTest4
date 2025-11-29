
// MFCApplication2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
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


// CCustomMessageBox 实现
CCustomMessageBox::CCustomMessageBox(const CString& message, COLORREF textColor, CWnd* pParent)
	: CDialogEx(IDD_CUSTOM_MESSAGE_BOX, pParent), m_message(message), m_textColor(textColor)
{
}

BOOL CCustomMessageBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_messageText.SetWindowText(m_message);
	return TRUE;
}

CCustomMessageBox::~CCustomMessageBox()
{
}

void CCustomMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESSAGE_TEXT, m_messageText);
}

BEGIN_MESSAGE_MAP(CCustomMessageBox, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CCustomMessageBox::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_MESSAGE_TEXT)
	{
		pDC->SetTextColor(m_textColor);
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}

	return hbr;
}

// CCaptchaDlg 实现
CCaptchaDlg::CCaptchaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CAPTCHA_DIALOG, pParent)
{
}

void CCaptchaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAPTCHA_DISPLAY, m_captchaDisplay);
	DDX_Control(pDX, IDC_CAPTCHA_INPUT, m_captchaInput);
}

BEGIN_MESSAGE_MAP(CCaptchaDlg, CDialogEx)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_CAPTCHA_INPUT, &CCaptchaDlg::OnEnChangeCaptchaInput)
	ON_BN_CLICKED(IDC_CLOSE_CAPTCHA, &CCaptchaDlg::OnBnClickedCloseCaptcha)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CCaptchaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置欢迎主题图片
	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC);
	pStatic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	pStatic->SetBitmap(bitmap);

	// 生成初始验证码
	GenerateCaptchaCode();
	
	// 设置验证码显示的字体和颜色
	CFont font;
	font.CreatePointFont(120, _T("Arial"));
	m_captchaDisplay.SetFont(&font);

	// 设置输入框只能输入数字
	m_captchaInput.LimitText(6);

	// 启动定时器，每3秒更新一次验证码
	SetTimer(1, 3000, nullptr);

	return TRUE;
}

HBRUSH CCaptchaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	return hbr;
}

void CCaptchaDlg::GenerateCaptchaCode()
{
	// 生成6位随机数字
	CString code;
	for (int i = 0; i < 6; i++)
	{
		code += static_cast<TCHAR>(_T('0') + rand() % 10);
	}
	m_captchaCode = code;
	m_captchaDisplay.SetWindowText(code);
}

void CCaptchaDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		GenerateCaptchaCode();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CCaptchaDlg::OnEnChangeCaptchaInput()
{
	CString input;
	m_captchaInput.GetWindowText(input);
	
	if (input.GetLength() == 6)
	{
		CMFCApplication2Dlg* pMainDlg = (CMFCApplication2Dlg*)GetParent();
		if (input == m_captchaCode)
{
	// 验证成功
	CCustomMessageBox dlg(_T("验证正确"), RGB(0, 255, 0), this);
	dlg.DoModal();
	pMainDlg->UpdateStatistics(true);
	m_captchaInput.SetWindowText(_T(""));
	GenerateCaptchaCode();
}
else
{
	// 验证失败
	CCustomMessageBox dlg(_T("验证失败，请重新输入"), RGB(255, 0, 0), this);
	dlg.DoModal();
	pMainDlg->UpdateStatistics(false);
	m_captchaInput.SetWindowText(_T(""));
}
	}
}

void CCaptchaDlg::OnBnClickedCloseCaptcha()
{
	KillTimer(1);
	EndDialog(IDCANCEL);
}

// CStatisticsDlg 实现
CStatisticsDlg::CStatisticsDlg(int correctCount, int wrongCount, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATISTICS_DIALOG, pParent), m_correctCount(correctCount), m_wrongCount(wrongCount)
{
}

void CStatisticsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CORRECT_COUNT, m_correctDisplay);
	DDX_Control(pDX, IDC_WRONG_COUNT, m_wrongDisplay);
}

BEGIN_MESSAGE_MAP(CStatisticsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CLOSE_STATISTICS, &CStatisticsDlg::OnBnClickedCloseStatistics)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CStatisticsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置统计信息
	CString correctStr, wrongStr;
	correctStr.Format(_T("%d"), m_correctCount);
	wrongStr.Format(_T("%d"), m_wrongCount);
	m_correctDisplay.SetWindowText(correctStr);
	m_wrongDisplay.SetWindowText(wrongStr);

	return TRUE;
}

HBRUSH CStatisticsDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_CORRECT_COUNT)
	{
		pDC->SetTextColor(RGB(0, 255, 0));
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}
	else if (pWnd->GetDlgCtrlID() == IDC_WRONG_COUNT)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
		return (HBRUSH)GetStockObject(WHITE_BRUSH);
	}

	return hbr;
}

void CStatisticsDlg::OnBnClickedCloseStatistics()
{
	EndDialog(IDCANCEL);
}

// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent), m_correctCount(0), m_wrongCount(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
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
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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

// CMFCApplication2Dlg 新功能实现
void CMFCApplication2Dlg::UpdateStatistics(bool isCorrect)
{
	if (isCorrect)
		m_correctCount++;
	else
		m_wrongCount++;
}

void CMFCApplication2Dlg::OnBnClickedButton3()
{
	CCaptchaDlg dlg(this);
	dlg.DoModal();
}

void CMFCApplication2Dlg::OnBnClickedButton4()
{
	CStatisticsDlg dlg(m_correctCount, m_wrongCount, this);
	dlg.DoModal();
}


// TimeDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "TimeDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 类静态成员变量声明

// CTimeDialog 对话框

CTimeDialog::CTimeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_TIME, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nTimerID = 0;
	m_nLastSum = -1;
}

void CTimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimeDialog, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTimeDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// CTimeDialog 消息处理程序

BOOL CTimeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);	// 设置小图标

	// 启动定时器，每秒更新一次时间
	m_nTimerID = SetTimer(1, 1000, nullptr);

	// 初始化时间显示
	UpdateTimeDisplay();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		// 关于对话框处理
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。
void CTimeDialog::OnPaint()
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
HCURSOR CTimeDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_nTimerID)
	{
		UpdateTimeDisplay();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CTimeDialog::OnBnClickedOk()
{
	// 停止定时器
	if (m_nTimerID != 0)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}

	CDialogEx::OnOK();
}

void CTimeDialog::UpdateTimeDisplay()
{
	// 获取当前时间
	CTime currentTime = CTime::GetCurrentTime();
	CString strTime = currentTime.Format(_T("%H:%M:%S"));

	// 更新时间显示
	SetDlgItemText(IDC_STATIC_TIME, strTime);

	// 计算小时、分钟、秒的和
	int nHour = currentTime.GetHour();
	int nMinute = currentTime.GetMinute();
	int nSecond = currentTime.GetSecond();
	int nSum = nHour + nMinute + nSecond;

	// 检查是否到达5的倍数，并且不是重复触发
	if (nSum % 5 == 0 && nSum != m_nLastSum)
	{
		// 更新提醒显示
		SetDlgItemText(IDC_STATIC_REMINDER, _T("到达5倍时间"));

		// 增加全局统计计数
		CMFCApplication2Dlg::m_nFiveMultipleCount++;

		// 更新最后触发的和
		m_nLastSum = nSum;
	}
	else if (nSum % 5 != 0)
	{
		// 清除提醒显示
		SetDlgItemText(IDC_STATIC_REMINDER, _T(""));
		m_nLastSum = -1;
	}
}

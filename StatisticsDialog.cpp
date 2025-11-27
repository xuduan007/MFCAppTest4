// StatisticsDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "StatisticsDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 类静态成员变量声明

// CStatisticsDialog 对话框

CStatisticsDialog::CStatisticsDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STATISTICS, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStatisticsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStatisticsDialog, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CStatisticsDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// CStatisticsDialog 消息处理程序

BOOL CStatisticsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);	// 设置小图标

	// 显示统计信息
	CString strStatistics;
	strStatistics.Format(_T("%d次"), CMFCApplication2Dlg::m_nFiveMultipleCount);
	SetDlgItemText(IDC_STATIC_STATISTICS, strStatistics);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStatisticsDialog::OnSysCommand(UINT nID, LPARAM lParam)
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
void CStatisticsDialog::OnPaint()
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
HCURSOR CStatisticsDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStatisticsDialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

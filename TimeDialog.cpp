// TimeDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "TimeDialog.h"
#include "afxdialogex.h"

// 静态变量初始化
int CTimeDialog::s_totalReminderCount = 0;

// CTimeDialog 对话框

CTimeDialog::CTimeDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_TIME_DIALOG, pParent)
    , m_currentTime(_T(""))
    , m_reminderCount(0)
{
    m_timerID = 0;
}

CTimeDialog::~CTimeDialog()
{
    if (m_timerID != 0)
    {
        KillTimer(m_timerID);
    }
}

void CTimeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TIME_STATIC, m_currentTime);
}

BEGIN_MESSAGE_MAP(CTimeDialog, CDialogEx)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CTimeDialog::OnBnClickedCloseButton)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CTimeDialog 消息处理程序

BOOL CTimeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);    // 设置大图标
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);   // 设置小图标

    // 设置定时器，每秒刷新一次
    m_timerID = SetTimer(1, 1000, nullptr);

    // 初始更新时间
    OnTimer(1);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeDialog::OnTimer(UINT_PTR nIDEvent)
{
    // 获取当前时间
    CTime currentTime = CTime::GetCurrentTime();
    m_currentTime = currentTime.Format(_T("%H:%M:%S"));

    // 检查是否到达5倍时间
    int hour = currentTime.GetHour();
    int minute = currentTime.GetMinute();
    int second = currentTime.GetSecond();

    if ((hour + minute + second) % 5 == 0)
    {
        // 显示提醒
        MessageBox(_T("到达5倍时间"), _T("提醒"), MB_OK | MB_ICONINFORMATION);
        m_reminderCount++;
        s_totalReminderCount++;
    }

    // 更新时间显示
    UpdateData(FALSE);

    CDialogEx::OnTimer(nIDEvent);
}

void CTimeDialog::OnBnClickedCloseButton()
{
    // 关闭对话框
    OnCancel();
}

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

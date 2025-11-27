// TimeDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "TimeDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CTimeDialog::m_nCount = 0;

// CTimeDialog 对话框

CTimeDialog::CTimeDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_TIME, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimeDialog, CDialogEx)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDOK, &CTimeDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// CTimeDialog 消息处理程序

BOOL CTimeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标
    SetIcon(m_hIcon, TRUE);    // 设置大图标
    SetIcon(m_hIcon, FALSE);   // 设置小图标

    // 启动定时器，每秒刷新一次
    m_nTimerID = SetTimer(1, 1000, nullptr);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTimeDialog::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        // 获取当前时间
        CTime timeNow;
        timeNow = CTime::GetCurrentTime();
        CString strTime = timeNow.Format(_T("%H:%M:%S"));

        // 显示当前时间
        SetDlgItemText(IDC_STATIC_TIME, strTime);

        // 计算小时、分钟、秒之和
        int nHour = timeNow.GetHour();
        int nMinute = timeNow.GetMinute();
        int nSecond = timeNow.GetSecond();
        int nSum = nHour + nMinute + nSecond;

        // 检查是否为5的倍数
        if (nSum % 5 == 0)
        {
            // 显示提醒
            MessageBox(_T("到达5倍时间"), _T("提醒"), MB_ICONINFORMATION);
            m_nCount++;
        }
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CTimeDialog::OnBnClickedOk()
{
    // 停止定时器
    KillTimer(m_nTimerID);
    CDialogEx::OnOK();
}

void CTimeDialog::OnCancel()
{
    // 停止定时器
    KillTimer(m_nTimerID);
    // 隐藏对话框而不是销毁它
    ShowWindow(SW_HIDE);
}

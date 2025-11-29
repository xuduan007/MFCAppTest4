// CountDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "CountDialog.h"
#include "afxdialogex.h"

// CCountDialog 对话框

CCountDialog::CCountDialog(int count, CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_COUNT_DIALOG, pParent)
    , m_count(count)
{
}

void CCountDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCountDialog, CDialogEx)
    ON_BN_CLICKED(IDC_CLOSE_BUTTON_2, &CCountDialog::OnBnClickedCloseButton)
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CCountDialog 消息处理程序

BOOL CCountDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);    // 设置大图标
    SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);   // 设置小图标

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCountDialog::OnBnClickedCloseButton()
{
    // 关闭对话框
    OnCancel();
}

void CCountDialog::OnPaint()
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

        // 绘制统计信息
        CPaintDC dc(this);
        CString countText;
        countText.Format(_T("到达5倍时间总共发生了 %d 次"), m_count);
        
        // 设置字体颜色
        if (m_count > 8)
        {
            dc.SetTextColor(RGB(255, 0, 0)); // 红色
        }
        else
        {
            dc.SetTextColor(RGB(0, 255, 0)); // 绿色
        }
        
        // 绘制文本
        dc.DrawText(countText, CRect(0, 0, 200, 100), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }
}

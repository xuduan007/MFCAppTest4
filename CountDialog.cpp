// CountDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "CountDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCountDialog 对话框

CCountDialog::CCountDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_COUNT, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCountDialog, CDialogEx)
    ON_BN_CLICKED(IDOK, &CCountDialog::OnBnClickedOk)
END_MESSAGE_MAP()

// CCountDialog 消息处理程序

BOOL CCountDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标
    SetIcon(m_hIcon, TRUE);    // 设置大图标
    SetIcon(m_hIcon, FALSE);   // 设置小图标

    // 获取到达5倍时间的次数并显示
    int nCount = CTimeDialog::GetCount();
    CString strCount;
    strCount.Format(_T("%d次"), nCount);
    SetDlgItemText(IDC_STATIC_COUNT, strCount);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCountDialog::OnBnClickedOk()
{
    CDialogEx::OnOK();
}

void CCountDialog::OnCancel()
{
    // 隐藏对话框而不是销毁它
    ShowWindow(SW_HIDE);
}

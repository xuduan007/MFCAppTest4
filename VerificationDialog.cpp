// VerificationDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "VerificationDialog.h"
#include "afxdialogex.h"


// CVerificationDialog 对话框

CVerificationDialog::CVerificationDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VERIFICATION_DIALOG, pParent)
{
	m_bSuccess = TRUE;
}

CVerificationDialog::CVerificationDialog(BOOL bSuccess, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VERIFICATION_DIALOG, pParent)
{
	m_bSuccess = bSuccess;
}

void CVerificationDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVerificationDialog, CDialogEx)
END_MESSAGE_MAP()


// CVerificationDialog 消息处理程序

BOOL CVerificationDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置对话框标题
	if (m_bSuccess)
	{
		SetWindowText(_T("校验结果"));
	}
	else
	{
		SetWindowText(_T("校验结果"));
	}

	// 获取静态文本控件
	CStatic* pStaticText = (CStatic*)GetDlgItem(IDC_STATIC_TEXT);
	if (pStaticText)
	{
		// 设置文本内容
		if (m_bSuccess)
		{
			pStaticText->SetWindowText(_T("校验正确！"));
			pStaticText->SetTextColor(RGB(0, 128, 0)); // 绿色
		}
		else
		{
			pStaticText->SetWindowText(_T("校验失败，请重新输入！"));
			pStaticText->SetTextColor(RGB(255, 0, 0)); // 红色
		}
	}

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}


// MFCApplication2Dlg.h: 头文件
//

#pragma once

// 前向声明
class CTimeDialog;
class CCountDialog;


// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CMFCApplication2Dlg(); // 析构函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CTimeDialog* m_pNonModalTimeDlg; // 非模态时间对话框指针
	CCountDialog* m_pCountDlg; // 计数对话框指针

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonModal();
	afx_msg void OnBnClickedButtonNonmodal();
	afx_msg void OnBnClickedButtonCount();
};

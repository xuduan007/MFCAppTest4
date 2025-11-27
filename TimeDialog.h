// TimeDialog.h: 头文件
//

#pragma once


// CTimeDialog 对话框
class CTimeDialog : public CDialogEx
{
// 构造
public:
	CTimeDialog(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TIME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	UINT_PTR m_nTimerID;
	int m_nLastSum;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()

	// 更新时间显示和检查5倍时间
	void UpdateTimeDisplay();
};

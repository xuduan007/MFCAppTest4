// TimeDialog.h: 头文件
//

#pragma once
#include "afxres.h"

// 前向声明
class CMFCApplication2Dlg;

// CTimeDialog 对话框
class CTimeDialog : public CDialogEx
{
// 构造
public:
    CTimeDialog(CWnd* pParent = nullptr);   // 标准构造函数
    ~CTimeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_TIME_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;
    UINT_PTR m_timerID;
    CString m_currentTime;
    int m_reminderCount;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedCloseButton();
    DECLARE_MESSAGE_MAP()

public:
    static int s_totalReminderCount;  // 静态变量，用于统计所有对话框的提醒次数
    afx_msg void OnPaint();
};

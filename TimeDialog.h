// TimeDialog.h: 头文件
//

#pragma once

// CTimeDialog 对话框
class CTimeDialog : public CDialogEx
{
// 构造
public:
    CTimeDialog(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_TIME };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;
    UINT_PTR m_nTimerID;
    static int m_nCount; // 到达5倍时间的次数

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnBnClickedOk();
    afx_msg void OnCancel();
    DECLARE_MESSAGE_MAP()

public:
    static int GetCount() { return m_nCount; }
    static void ResetCount() { m_nCount = 0; }
};

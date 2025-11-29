// CountDialog.h: 头文件
//

#pragma once

// CCountDialog 对话框
class CCountDialog : public CDialogEx
{
// 构造
public:
    CCountDialog(int count, CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_COUNT_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;
    int m_count;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedCloseButton();
    afx_msg void OnPaint();
    DECLARE_MESSAGE_MAP()
};

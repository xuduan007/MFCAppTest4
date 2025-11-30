// ImageFlipDlg.h: 头文件
//

#pragma once


// CImageFlipDlg 对话框
class CImageFlipDlg : public CDialogEx
{
// 构造
public:
    CImageFlipDlg(CWnd* pParent = nullptr);    // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_IMAGE_FLIP_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonFlipVertical();
    afx_msg void OnBnClickedButtonFlipHorizontal();

private:
    CBitmap m_bmpOriginal;    // 原始图片
    CBitmap m_bmpResult;      // 翻转后的图片
    void FlipImageVertical(); // 上下翻转图片
    void FlipImageHorizontal(); // 左右翻转图片
    void DisplayImage(HBITMAP hBitmap, int nStaticID); // 显示图片到静态控件
};

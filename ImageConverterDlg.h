// ImageConverterDlg.h: 头文件
//

#pragma once

// CImageConverterDlg 对话框
class CImageConverterDlg : public CDialogEx
{
// 构造
public:
    CImageConverterDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_IMAGE_CONVERTER_DIALOG };
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
    afx_msg void OnBnClickedConvertToJpg();
    afx_msg void OnBnClickedConvertToPng();

private:
    CStatic m_originalImage;  // 原始图片控件
    CStatic m_convertedImage; // 转换后图片控件
    CImage m_image;            // 原始图片对象
};

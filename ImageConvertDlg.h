// ImageConvertDlg.h: 头文件
//

#pragma once
#include <atlimage.h>

// CImageConvertDlg 对话框
class CImageConvertDlg : public CDialogEx
{
// 构造
public:
    CImageConvertDlg(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_IMAGE_CONVERT_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedButtonConvertToJpg();
    afx_msg void OnBnClickedButtonConvertToPng();
    DECLARE_MESSAGE_MAP()

private:
    // 加载原始图片
    void LoadOriginalImage();

    // 显示图片在指定的静态控件中
    void DisplayImage(CStatic* pStaticCtrl, CImage& image);

    // 保存图片为指定格式
    BOOL SaveImageAsFormat(CImage& image, LPCTSTR lpszFilePath, LPCTSTR lpszFormat);

    CImage m_OriginalImage;    // 原始图片
    CImage m_ConvertedImage;   // 转换后的图片
};

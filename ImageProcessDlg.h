// ImageProcessDlg.h: 头文件
//

#pragma once


// CImageProcessDlg 对话框
class CImageProcessDlg : public CDialogEx
{
// 构造
public:
	CImageProcessDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGE_PROCESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	// 成员变量
	CBitmap m_originalBitmap;
	CBitmap m_processedBitmap;
	int m_brightnessValue;

	// 自定义方法
	void IncreaseContrast(CDC* pDC, CBitmap* pSrcBitmap, CBitmap* pDestBitmap, int contrastValue);
	void AdjustBrightness(CDC* pDC, CBitmap* pSrcBitmap, CBitmap* pDestBitmap, int brightnessValue);

public:
	afx_msg void OnBnClickedProcessControlButton();
	afx_msg void OnNMCustomdrawBrightnessSlider(NMHDR* pNMHDR, LRESULT* pResult);
};

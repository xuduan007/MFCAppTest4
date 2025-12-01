// ImageProcessDlg.h: 头文件
//

#pragma once

#include "afxwin.h"

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
	CBitmap m_originalBitmap;
	CBitmap m_processedBitmap;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonContrast();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

	// 辅助函数
	void LoadOriginalImage();
	CBitmap* IncreaseContrast(CBitmap* pBitmap);
	CBitmap* AdjustBrightness(CBitmap* pBitmap, int brightness);
};

// ImageProcessDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ImageProcessDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProcessDlg 对话框


CImageProcessDlg::CImageProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGE_PROCESS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_brightnessValue = 0;
}

void CImageProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageProcessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PROCESS_CONTROL_BUTTON, &CImageProcessDlg::OnBnClickedProcessControlButton)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_BRIGHTNESS_SLIDER, &CImageProcessDlg::OnNMCustomdrawBrightnessSlider)
END_MESSAGE_MAP()


// CImageProcessDlg 消息处理程序

BOOL CImageProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// 加载原始图片
	m_originalBitmap.LoadBitmap(IDB_BITMAP1);

	// 在左侧显示原始图片
	CStatic* pOriginalImage = (CStatic*)GetDlgItem(IDC_ORIGINAL_IMAGE);
	pOriginalImage->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
	pOriginalImage->SetBitmap(m_originalBitmap);

	// 初始化滑块控件
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_BRIGHTNESS_SLIDER);
	pSlider->SetRange(-100, 100);
	pSlider->SetPos(0);

	// 初始化右侧图片控件，但不设置图片（初始不显示）
	CStatic* pProcessedImage = (CStatic*)GetDlgItem(IDC_PROCESSED_IMAGE);
	pProcessedImage->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// 直接调用基类的OnSysCommand处理系统命令
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageProcessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CImageProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 增加对比度的函数
void CImageProcessDlg::IncreaseContrast(CDC* pDC, CBitmap* pSrcBitmap, CBitmap* pDestBitmap, int contrastValue)
{
	// 获取位图信息
	BITMAP bm;
	pSrcBitmap->GetBitmap(&bm);

	// 创建内存设备上下文
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(pSrcBitmap);

	// 创建目标位图
	pDestBitmap->CreateCompatibleBitmap(pDC, bm.bmWidth, bm.bmHeight);
	CDC destDC;
	destDC.CreateCompatibleDC(pDC);
	CBitmap* pOldDestBitmap = destDC.SelectObject(pDestBitmap);

	// 复制位图
	destDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

	// 调整对比度
	float contrast = (259.0f * (contrastValue + 255)) / (255.0f * (259 - contrastValue));

	for (int y = 0; y < bm.bmHeight; y++)
	{
		for (int x = 0; x < bm.bmWidth; x++)
		{
			COLORREF color = destDC.GetPixel(x, y);
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);

			// 应用对比度调整
			r = static_cast<BYTE>(max(0, min(255, contrast * (r - 128) + 128)));
			g = static_cast<BYTE>(max(0, min(255, contrast * (g - 128) + 128)));
			b = static_cast<BYTE>(max(0, min(255, contrast * (b - 128) + 128)));

			destDC.SetPixel(x, y, RGB(r, g, b));
		}
	}

	// 清理
	destDC.SelectObject(pOldDestBitmap);
	memDC.SelectObject(pOldBitmap);
}

// 调整亮度的函数
void CImageProcessDlg::AdjustBrightness(CDC* pDC, CBitmap* pSrcBitmap, CBitmap* pDestBitmap, int brightnessValue)
{
	// 获取位图信息
	BITMAP bm;
	pSrcBitmap->GetBitmap(&bm);

	// 创建内存设备上下文
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(pSrcBitmap);

	// 创建目标位图
	CDC destDC;
	destDC.CreateCompatibleDC(pDC);
	CBitmap* pOldDestBitmap = destDC.SelectObject(pDestBitmap);

	// 复制位图
	destDC.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

	// 调整亮度
	for (int y = 0; y < bm.bmHeight; y++)
	{
		for (int x = 0; x < bm.bmWidth; x++)
		{
			COLORREF color = destDC.GetPixel(x, y);
			BYTE r = GetRValue(color);
			BYTE g = GetGValue(color);
			BYTE b = GetBValue(color);

			// 应用亮度调整
			r = static_cast<BYTE>(max(0, min(255, r + brightnessValue)));
			g = static_cast<BYTE>(max(0, min(255, g + brightnessValue)));
			b = static_cast<BYTE>(max(0, min(255, b + brightnessValue)));

			destDC.SetPixel(x, y, RGB(r, g, b));
		}
	}

	// 清理
	destDC.SelectObject(pOldDestBitmap);
	memDC.SelectObject(pOldBitmap);
}

// 增加对比度按钮点击处理
void CImageProcessDlg::OnBnClickedProcessControlButton()
{
	CDC* pDC = GetDC();
	
	// 增加对比度20
	IncreaseContrast(pDC, &m_originalBitmap, &m_processedBitmap, 20);
	
	// 显示处理后的图片
	CStatic* pProcessedImage = (CStatic*)GetDlgItem(IDC_PROCESSED_IMAGE);
	pProcessedImage->SetBitmap(m_processedBitmap);
	
	ReleaseDC(pDC);
}

// 滑块事件处理
void CImageProcessDlg::OnNMCustomdrawBrightnessSlider(NMHDR* pNMHDR, LRESULT* pResult)
{
	// 获取滑块位置
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_BRIGHTNESS_SLIDER);
	m_brightnessValue = pSlider->GetPos();
	
	CDC* pDC = GetDC();
	
	// 首先应用对比度
	CBitmap tempBitmap;
	IncreaseContrast(pDC, &m_originalBitmap, &tempBitmap, 20);
	
	// 然后应用亮度调整
	AdjustBrightness(pDC, &tempBitmap, &m_processedBitmap, m_brightnessValue);
	
	// 显示处理后的图片
	CStatic* pProcessedImage = (CStatic*)GetDlgItem(IDC_PROCESSED_IMAGE);
	pProcessedImage->SetBitmap(m_processedBitmap);
	
	ReleaseDC(pDC);
	
	*pResult = 0;
}

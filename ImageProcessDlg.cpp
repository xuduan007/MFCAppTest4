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
}

void CImageProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageProcessDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONTRAST, &CImageProcessDlg::OnBnClickedButtonContrast)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

// CImageProcessDlg 消息处理程序

BOOL CImageProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标
	SetIcon(m_hIcon, TRUE);		// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// 加载原始图片
	LoadOriginalImage();

	// 初始化滑块控件
	CSliderCtrl* pSlider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_BRIGHTNESS);
	if (pSlider != nullptr)
	{
		pSlider->SetRange(-100, 100);
		pSlider->SetPos(0);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageProcessDlg::LoadOriginalImage()
{
	// 加载原始图片
	m_originalBitmap.LoadBitmap(IDB_BITMAP1);

	// 显示原始图片
	CStatic* pStaticOriginal = (CStatic*)GetDlgItem(IDC_STATIC_ORIGINAL);
	if (pStaticOriginal != nullptr)
	{
		pStaticOriginal->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		pStaticOriginal->SetBitmap(m_originalBitmap);
	}
}

void CImageProcessDlg::OnBnClickedButtonContrast()
{
	// 增加对比度
	m_processedBitmap.DeleteObject();
	m_processedBitmap.Attach(IncreaseContrast(&m_originalBitmap)->Detach());

	// 显示处理后的图片
	CStatic* pStaticProcessed = (CStatic*)GetDlgItem(IDC_STATIC_PROCESSED);
	if (pStaticProcessed != nullptr)
	{
		pStaticProcessed->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
		pStaticProcessed->SetBitmap(m_processedBitmap);
	}
}

void CImageProcessDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar->GetDlgCtrlID() == IDC_SLIDER_BRIGHTNESS)
	{
		CSliderCtrl* pSlider = (CSliderCtrl*)pScrollBar;
		int brightness = pSlider->GetPos();

		// 调整亮度
		m_processedBitmap.DeleteObject();
		m_processedBitmap.Attach(AdjustBrightness(&m_originalBitmap, brightness)->Detach());

		// 显示处理后的图片
		CStatic* pStaticProcessed = (CStatic*)GetDlgItem(IDC_STATIC_PROCESSED);
		if (pStaticProcessed != nullptr)
		{
			pStaticProcessed->SetBitmap(m_processedBitmap);
		}
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

CBitmap* CImageProcessDlg::IncreaseContrast(CBitmap* pBitmap)
{
	// 获取原始图片的设备上下文
	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);

	// 获取图片尺寸
	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	// 创建新的位图
	CBitmap* pNewBitmap = new CBitmap();
	pNewBitmap->CreateCompatibleBitmap(pDC, width, height);
	CDC newMemDC;
	newMemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldNewBitmap = newMemDC.SelectObject(pNewBitmap);

	// 增加对比度（20%）
	float contrast = 1.2f;
	float offset = 128 * (1 - contrast);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			COLORREF color = memDC.GetPixel(x, y);
			int r = (int)(GetRValue(color) * contrast + offset);
			int g = (int)(GetGValue(color) * contrast + offset);
			int b = (int)(GetBValue(color) * contrast + offset);

			// 确保颜色值在0-255之间
			r = max(0, min(255, r));
			g = max(0, min(255, g));
			b = max(0, min(255, b));

			newMemDC.SetPixel(x, y, RGB(r, g, b));
		}
	}

	// 清理
	memDC.SelectObject(pOldBitmap);
	newMemDC.SelectObject(pOldNewBitmap);
	ReleaseDC(pDC);

	return pNewBitmap;
}

CBitmap* CImageProcessDlg::AdjustBrightness(CBitmap* pBitmap, int brightness)
{
	// 获取原始图片的设备上下文
	CDC* pDC = GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(pBitmap);

	// 获取图片尺寸
	BITMAP bm;
	pBitmap->GetBitmap(&bm);
	int width = bm.bmWidth;
	int height = bm.bmHeight;

	// 创建新的位图
	CBitmap* pNewBitmap = new CBitmap();
	pNewBitmap->CreateCompatibleBitmap(pDC, width, height);
	CDC newMemDC;
	newMemDC.CreateCompatibleDC(pDC);
	CBitmap* pOldNewBitmap = newMemDC.SelectObject(pNewBitmap);

	// 调整亮度
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			COLORREF color = memDC.GetPixel(x, y);
			int r = GetRValue(color) + brightness;
			int g = GetGValue(color) + brightness;
			int b = GetBValue(color) + brightness;

			// 确保颜色值在0-255之间
			r = max(0, min(255, r));
			g = max(0, min(255, g));
			b = max(0, min(255, b));

			newMemDC.SetPixel(x, y, RGB(r, g, b));
		}
	}

	// 清理
	memDC.SelectObject(pOldBitmap);
	newMemDC.SelectObject(pOldNewBitmap);
	ReleaseDC(pDC);

	return pNewBitmap;
}

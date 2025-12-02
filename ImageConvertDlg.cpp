// ImageConvertDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ImageConvertDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageConvertDlg 对话框

CImageConvertDlg::CImageConvertDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_IMAGE_CONVERT_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageConvertDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageConvertDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_CONVERT_TO_JPG, &CImageConvertDlg::OnBnClickedButtonConvertToJpg)
    ON_BN_CLICKED(IDC_BUTTON_CONVERT_TO_PNG, &CImageConvertDlg::OnBnClickedButtonConvertToPng)
END_MESSAGE_MAP()

// CImageConvertDlg 消息处理程序

BOOL CImageConvertDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标
    SetIcon(m_hIcon, TRUE);        // 设置大图标
    SetIcon(m_hIcon, FALSE);       // 设置小图标

    // 加载原始图片
    LoadOriginalImage();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageConvertDlg::LoadOriginalImage()
{
    // 加载资源中的位图
    CBitmap bitmap;
    if (bitmap.LoadBitmap(IDB_BITMAP1))
    {
        // 将CBitmap转换为CImage
        BITMAP bmp;
        bitmap.GetBitmap(&bmp);

        m_OriginalImage.Create(bmp.bmWidth, bmp.bmHeight, bmp.bmBitsPixel);

        CDC* pDC = CDC::FromHandle(m_OriginalImage.GetDC());
        CDC memDC;
        memDC.CreateCompatibleDC(pDC);
        CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

        pDC->BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &memDC, 0, 0, SRCCOPY);

        memDC.SelectObject(pOldBitmap);
        m_OriginalImage.ReleaseDC();

        // 在左侧静态控件中显示原始图片
        CStatic* pStaticOriginal = (CStatic*)GetDlgItem(IDC_STATIC_ORIGINAL_IMAGE);
        DisplayImage(pStaticOriginal, m_OriginalImage);
    }
}

void CImageConvertDlg::DisplayImage(CStatic* pStaticCtrl, CImage& image)
{
    if (!pStaticCtrl || image.IsNull())
        return;

    // 获取静态控件的矩形区域
    CRect rect;
    pStaticCtrl->GetClientRect(&rect);

    // 调整图片大小以适应控件
    CImage scaledImage;
    scaledImage.Create(rect.Width(), rect.Height(), image.GetBPP());

    CDC* pDC = CDC::FromHandle(scaledImage.GetDC());
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOldBitmap = static_cast<CBitmap*>(memDC.SelectObject(image));

    // 使用StretchBlt来缩放图片
    pDC->SetStretchBltMode(COLORONCOLOR);
    pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, image.GetWidth(), image.GetHeight(), SRCCOPY);

    memDC.SelectObject(pOldBitmap);
    scaledImage.ReleaseDC();

    // 将图片设置到静态控件中
    pStaticCtrl->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
    pStaticCtrl->SetBitmap((HBITMAP)scaledImage.Detach());
}

BOOL CImageConvertDlg::SaveImageAsFormat(CImage& image, LPCTSTR lpszFilePath, LPCTSTR lpszFormat)
{
    if (image.IsNull())
        return FALSE;

    // 保存图片为指定格式
    HRESULT hr = image.Save(lpszFilePath, Gdiplus::ImageFormatPNG);

    if (lstrcmp(lpszFormat, _T("JPG")) == 0 || lstrcmp(lpszFormat, _T("JPEG")) == 0)
    {
        hr = image.Save(lpszFilePath, Gdiplus::ImageFormatJPEG);
    }
    else if (lstrcmp(lpszFormat, _T("PNG")) == 0)
    {
        hr = image.Save(lpszFilePath, Gdiplus::ImageFormatPNG);
    }

    return SUCCEEDED(hr);
}

void CImageConvertDlg::OnBnClickedButtonConvertToJpg()
{
    // 选择保存文件的路径
    CFileDialog fileDlg(FALSE, _T("jpg"), _T("converted_image.jpg"), 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
        _T("JPEG 图片 (*.jpg)|*.jpg|所有文件 (*.*)|*.*||"), this);

    if (fileDlg.DoModal() == IDOK)
    {
        CString strFilePath = fileDlg.GetPathName();

        // 保存图片为JPG格式
        if (SaveImageAsFormat(m_OriginalImage, strFilePath, _T("JPG")))
        {
            // 加载并显示转换后的图片
            if (m_ConvertedImage.Load(strFilePath) == S_OK)
            {
                CStatic* pStaticConverted = (CStatic*)GetDlgItem(IDC_STATIC_CONVERTED_IMAGE);
                DisplayImage(pStaticConverted, m_ConvertedImage);

                // 显示成功提示
                AfxMessageBox(_T("图片已成功转换为JPG格式并保存！"), MB_ICONINFORMATION);
            }
        }
        else
        {
            AfxMessageBox(_T("图片转换失败！"), MB_ICONERROR);
        }
    }
}

void CImageConvertDlg::OnBnClickedButtonConvertToPng()
{
    // 选择保存文件的路径
    CFileDialog fileDlg(FALSE, _T("png"), _T("converted_image.png"), 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
        _T("PNG 图片 (*.png)|*.png|所有文件 (*.*)|*.*||"), this);

    if (fileDlg.DoModal() == IDOK)
    {
        CString strFilePath = fileDlg.GetPathName();

        // 保存图片为PNG格式
        if (SaveImageAsFormat(m_OriginalImage, strFilePath, _T("PNG")))
        {
            // 加载并显示转换后的图片
            if (m_ConvertedImage.Load(strFilePath) == S_OK)
            {
                CStatic* pStaticConverted = (CStatic*)GetDlgItem(IDC_STATIC_CONVERTED_IMAGE);
                DisplayImage(pStaticConverted, m_ConvertedImage);

                // 显示成功提示
                AfxMessageBox(_T("图片已成功转换为PNG格式并保存！"), MB_ICONINFORMATION);
            }
        }
        else
        {
            AfxMessageBox(_T("图片转换失败！"), MB_ICONERROR);
        }
    }
}

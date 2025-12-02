// ImageConverterDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ImageConverterDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageConverterDlg 对话框

CImageConverterDlg::CImageConverterDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_IMAGE_CONVERTER_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageConverterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_ORIGINAL, m_originalImage);
    DDX_Control(pDX, IDC_STATIC_CONVERTED, m_convertedImage);
}

BEGIN_MESSAGE_MAP(CImageConverterDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_CONVERT_TO_JPG, &CImageConverterDlg::OnBnClickedConvertToJpg)
    ON_BN_CLICKED(IDC_BUTTON_CONVERT_TO_PNG, &CImageConverterDlg::OnBnClickedConvertToPng)
END_MESSAGE_MAP()

// CImageConverterDlg 消息处理程序

BOOL CImageConverterDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。
    // IDM_ABOUTBOX 必须在系统命令范围内。
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);            // 设置大图标
    SetIcon(m_hIcon, FALSE);        // 设置小图标

    // 加载原始图片
    CBitmap bitmap;
    if (bitmap.LoadBitmap(IDB_BITMAP1))
    {
        // 设置原始图片控件的风格和图片
        m_originalImage.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
        m_originalImage.SetBitmap(bitmap.Detach());
    }

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageConverterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    // 移除关于对话框的处理，因为CAboutDlg未在当前文件中声明
    CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageConverterDlg::OnPaint()
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

// 当用户拖动最小化窗口时系统调用此函数取得光标
// 显示。
HCURSOR CImageConverterDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CImageConverterDlg::OnBnClickedConvertToJpg()
{
    // 加载原始图片
    CBitmap bitmap;
    if (!bitmap.LoadBitmap(IDB_BITMAP1))
    {
        MessageBox(_T("加载图片失败！"), _T("错误"), MB_ICONERROR);
        return;
    }

    // 将CBitmap转换为CImage
    CImage image;
    CDC dc; 
    dc.CreateCompatibleDC(nullptr); 
    CBitmap* pOldBitmap = dc.SelectObject(&bitmap); 
    
    BITMAP bmpInfo; 
    bitmap.GetBitmap(&bmpInfo); 
    
    image.Create(bmpInfo.bmWidth, bmpInfo.bmHeight, bmpInfo.bmBitsPixel); 
    image.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dc, 0, 0, SRCCOPY); 
    
    dc.SelectObject(pOldBitmap); 

    // 获取当前目录
    TCHAR szCurrentDir[MAX_PATH]; 
    GetCurrentDirectory(MAX_PATH, szCurrentDir); 

    // 保存为 JPG 格式
    CString strFilePath; 
    strFilePath.Format(_T("%s\\converted_image.jpg"), szCurrentDir); 
    if (image.Save(strFilePath, Gdiplus::ImageFormatJPEG) != S_OK) 
    {
        MessageBox(_T("保存 JPG 图片失败！"), _T("错误"), MB_ICONERROR); 
        return; 
    } 

    // 显示转换后的 JPG 图片
    CImage convertedImage; 
    if (convertedImage.Load(strFilePath) == S_OK) 
    {
        m_convertedImage.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); 
        m_convertedImage.SetBitmap(convertedImage.Detach()); 
    } 

    MessageBox(_T("图片已成功转换为 JPG 格式！"), _T("成功"), MB_ICONINFORMATION); 
}

void CImageConverterDlg::OnBnClickedConvertToPng() 
{
    // 加载原始图片
    CBitmap bitmap; 
    if (!bitmap.LoadBitmap(IDB_BITMAP1)) 
    {
        MessageBox(_T("加载图片失败！"), _T("错误"), MB_ICONERROR); 
        return; 
    } 

    // 将CBitmap转换为CImage
    CImage image; 
    CDC dc; 
    dc.CreateCompatibleDC(nullptr); 
    CBitmap* pOldBitmap = dc.SelectObject(&bitmap); 
    
    BITMAP bmpInfo; 
    bitmap.GetBitmap(&bmpInfo); 
    
    image.Create(bmpInfo.bmWidth, bmpInfo.bmHeight, bmpInfo.bmBitsPixel); 
    image.BitBlt(0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, &dc, 0, 0, SRCCOPY); 
    
    dc.SelectObject(pOldBitmap); 

    // 获取当前目录
    TCHAR szCurrentDir[MAX_PATH]; 
    GetCurrentDirectory(MAX_PATH, szCurrentDir); 

    // 保存为 PNG 格式
    CString strFilePath; 
    strFilePath.Format(_T("%s\\converted_image.png"), szCurrentDir); 
    if (image.Save(strFilePath, Gdiplus::ImageFormatPNG) != S_OK) 
    {
        MessageBox(_T("保存 PNG 图片失败！"), _T("错误"), MB_ICONERROR); 
        return; 
    } 

    // 显示转换后的 PNG 图片
    CImage convertedImage; 
    if (convertedImage.Load(strFilePath) == S_OK) 
    {
        m_convertedImage.ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE); 
        m_convertedImage.SetBitmap(convertedImage.Detach()); 
    } 

    MessageBox(_T("图片已成功转换为 PNG 格式！"), _T("成功"), MB_ICONINFORMATION); 
}

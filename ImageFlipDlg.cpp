// ImageFlipDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ImageFlipDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageFlipDlg 对话框

CImageFlipDlg::CImageFlipDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_IMAGE_FLIP_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageFlipDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageFlipDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_FLIP_VERTICAL, &CImageFlipDlg::OnBnClickedButtonFlipVertical)
    ON_BN_CLICKED(IDC_BUTTON_FLIP_HORIZONTAL, &CImageFlipDlg::OnBnClickedButtonFlipHorizontal)
END_MESSAGE_MAP()


// CImageFlipDlg 消息处理程序

BOOL CImageFlipDlg::OnInitDialog()
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
    m_bmpOriginal.LoadBitmap(IDB_BITMAP1);

    // 显示原始图片
    DisplayImage(m_bmpOriginal, IDC_STATIC_ORIGINAL);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageFlipDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    CDialogEx::OnSysCommand(nID, lParam);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CImageFlipDlg::OnPaint()
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
HCURSOR CImageFlipDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CImageFlipDlg::OnBnClickedButtonFlipVertical()
{
    // 上下翻转图片
    FlipImageVertical();
    // 显示翻转后的图片
    DisplayImage(m_bmpResult, IDC_STATIC_RESULT);
}

void CImageFlipDlg::OnBnClickedButtonFlipHorizontal()
{
    // 左右翻转图片
    FlipImageHorizontal();
    // 显示翻转后的图片
    DisplayImage(m_bmpResult, IDC_STATIC_RESULT);
}

void CImageFlipDlg::FlipImageVertical()
{
    // 获取原始图片的信息
    BITMAP bmpInfo;
    m_bmpOriginal.GetBitmap(&bmpInfo);

    // 创建设备上下文
    CDC dcSrc, dcDest;
    dcSrc.CreateCompatibleDC(nullptr);
    dcDest.CreateCompatibleDC(nullptr);

    // 选择原始图片到源DC
    CBitmap* pOldBmpSrc = dcSrc.SelectObject(&m_bmpOriginal);

    // 创建目标图片
    m_bmpResult.DeleteObject();
    m_bmpResult.CreateCompatibleBitmap(&dcSrc, bmpInfo.bmWidth, bmpInfo.bmHeight);
    CBitmap* pOldBmpDest = dcDest.SelectObject(&m_bmpResult);

    // 上下翻转绘制
    for (int y = 0; y < bmpInfo.bmHeight; y++)
    {
        dcDest.BitBlt(0, bmpInfo.bmHeight - 1 - y, bmpInfo.bmWidth, 1, &dcSrc, 0, y, SRCCOPY);
    }

    // 恢复原始DC
    dcSrc.SelectObject(pOldBmpSrc);
    dcDest.SelectObject(pOldBmpDest);
}

void CImageFlipDlg::FlipImageHorizontal()
{
    // 获取原始图片的信息
    BITMAP bmpInfo;
    m_bmpOriginal.GetBitmap(&bmpInfo);

    // 创建设备上下文
    CDC dcSrc, dcDest;
    dcSrc.CreateCompatibleDC(nullptr);
    dcDest.CreateCompatibleDC(nullptr);

    // 选择原始图片到源DC
    CBitmap* pOldBmpSrc = dcSrc.SelectObject(&m_bmpOriginal);

    // 创建目标图片
    m_bmpResult.DeleteObject();
    m_bmpResult.CreateCompatibleBitmap(&dcSrc, bmpInfo.bmWidth, bmpInfo.bmHeight);
    CBitmap* pOldBmpDest = dcDest.SelectObject(&m_bmpResult);

    // 左右翻转绘制
    for (int x = 0; x < bmpInfo.bmWidth; x++)
    {
        dcDest.BitBlt(bmpInfo.bmWidth - 1 - x, 0, 1, bmpInfo.bmHeight, &dcSrc, x, 0, SRCCOPY);
    }

    // 恢复原始DC
    dcSrc.SelectObject(pOldBmpSrc);
    dcDest.SelectObject(pOldBmpDest);
}

void CImageFlipDlg::DisplayImage(HBITMAP hBitmap, int nStaticID)
{
    // 获取静态控件
    CStatic* pStatic = (CStatic*)GetDlgItem(nStaticID);
    if (pStatic == nullptr)
        return;

    // 设置静态控件的风格
    pStatic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);

    // 设置图片到静态控件
    pStatic->SetBitmap(hBitmap);
}

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
    ON_BN_CLICKED(IDC_FLIP_VERTICAL, &CImageFlipDlg::OnBnClickedFlipVertical)
    ON_BN_CLICKED(IDC_FLIP_HORIZONTAL, &CImageFlipDlg::OnBnClickedFlipHorizontal)
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
    m_originalBitmap.LoadBitmap(IDB_BITMAP1);

    // 显示原始图片在左侧
    CStatic* pOriginalStatic = (CStatic*)GetDlgItem(IDC_ORIGINAL_IMAGE);
    pOriginalStatic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
    pOriginalStatic->SetBitmap(m_originalBitmap);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CImageFlipDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
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

void CImageFlipDlg::OnBnClickedFlipVertical()
{
    // 垂直翻转图片
    FlipBitmapVertical(m_originalBitmap, m_flippedBitmap);

    // 显示翻转后的图片在右侧
    CStatic* pFlippedStatic = (CStatic*)GetDlgItem(IDC_FLIPPED_IMAGE);
    pFlippedStatic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
    pFlippedStatic->SetBitmap(m_flippedBitmap);
}

void CImageFlipDlg::OnBnClickedFlipHorizontal()
{
    // 水平翻转图片
    FlipBitmapHorizontal(m_originalBitmap, m_flippedBitmap);

    // 显示翻转后的图片在右侧
    CStatic* pFlippedStatic = (CStatic*)GetDlgItem(IDC_FLIPPED_IMAGE);
    pFlippedStatic->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
    pFlippedStatic->SetBitmap(m_flippedBitmap);
}

void CImageFlipDlg::FlipBitmapVertical(CBitmap& srcBitmap, CBitmap& destBitmap)
{
    // 获取源图片的信息
    BITMAP bm;
    srcBitmap.GetBitmap(&bm);

    // 创建目标图片
    destBitmap.DeleteObject();
    destBitmap.CreateCompatibleBitmap(&m_flippedDC, bm.bmWidth, bm.bmHeight);

    // 创建源和目标 DC
    CDC srcDC, destDC;
    srcDC.CreateCompatibleDC(&m_flippedDC);
    destDC.CreateCompatibleDC(&m_flippedDC);

    // 选择位图到 DC
    CBitmap* pOldSrcBitmap = srcDC.SelectObject(&srcBitmap);
    CBitmap* pOldDestBitmap = destDC.SelectObject(&destBitmap);

    // 垂直翻转图片
    for (int y = 0; y < bm.bmHeight; y++)
    {
        destDC.BitBlt(0, bm.bmHeight - y - 1, bm.bmWidth, 1, &srcDC, 0, y, SRCCOPY);
    }

    // 恢复原来的位图
    srcDC.SelectObject(pOldSrcBitmap);
    destDC.SelectObject(pOldDestBitmap);
}

void CImageFlipDlg::FlipBitmapHorizontal(CBitmap& srcBitmap, CBitmap& destBitmap)
{
    // 获取源图片的信息
    BITMAP bm;
    srcBitmap.GetBitmap(&bm);

    // 创建目标图片
    destBitmap.DeleteObject();
    destBitmap.CreateCompatibleBitmap(&m_flippedDC, bm.bmWidth, bm.bmHeight);

    // 创建源和目标 DC
    CDC srcDC, destDC;
    srcDC.CreateCompatibleDC(&m_flippedDC);
    destDC.CreateCompatibleDC(&m_flippedDC);

    // 选择位图到 DC
    CBitmap* pOldSrcBitmap = srcDC.SelectObject(&srcBitmap);
    CBitmap* pOldDestBitmap = destDC.SelectObject(&destBitmap);

    // 水平翻转图片
    for (int x = 0; x < bm.bmWidth; x++)
    {
        destDC.BitBlt(bm.bmWidth - x - 1, 0, 1, bm.bmHeight, &srcDC, x, 0, SRCCOPY);
    }

    // 恢复原来的位图
    srcDC.SelectObject(pOldSrcBitmap);
    destDC.SelectObject(pOldDestBitmap);
}


// MFCApplication2Dlg.h: 头文件
//

#pragma once


// 验证码对话框类
class CCustomMessageBox : public CDialogEx
{
public:
	CCustomMessageBox(const CString& message, COLORREF textColor, CWnd* pParent = nullptr);
	virtual ~CCustomMessageBox();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	CString m_message;
	COLORREF m_textColor;
	CStatic m_messageText;
};

// 验证码对话框类

class CCaptchaDlg : public CDialogEx
{
public:
	CCaptchaDlg(CWnd* pParent = nullptr);
	
	enum { IDD = IDD_CAPTCHA_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeCaptchaInput();
	afx_msg void OnBnClickedCloseCaptcha();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	CString m_captchaCode;
	CStatic m_captchaDisplay;
	CEdit m_captchaInput;
	void GenerateCaptchaCode();
};

// 统计信息对话框类
class CStatisticsDlg : public CDialogEx
{
public:
	CStatisticsDlg(int correctCount, int wrongCount, CWnd* pParent = nullptr);
	
	enum { IDD = IDD_STATISTICS_DIALOG };

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnBnClickedCloseStatistics();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	int m_correctCount;
	int m_wrongCount;
	CStatic m_correctDisplay;
	CStatic m_wrongDisplay;
};

// CMFCApplication2Dlg 对话框
class CMFCApplication2Dlg : public CDialogEx
{
// 构造
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

// 实现
protected:
	HICON m_hIcon;
	int m_correctCount;
	int m_wrongCount;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	void OnSize(UINT nType, int cx, int cy);
	void UpdateStatistics(bool isCorrect);
};


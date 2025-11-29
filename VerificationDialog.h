// VerificationDialog.h: 头文件
//

#pragma once


// CVerificationDialog 对话框
class CVerificationDialog : public CDialogEx
{
// 构造
public:
	CVerificationDialog(CWnd* pParent = nullptr);	// 标准构造函数
	CVerificationDialog(BOOL bSuccess, CWnd* pParent = nullptr); // 带参数的构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERIFICATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bSuccess;
};

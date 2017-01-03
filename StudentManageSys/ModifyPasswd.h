#pragma once
#include "Function.h"
#include "afxwin.h"
#include "Confirm.h"
// ModifyPasswd 对话框

class ModifyPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyPasswd)

public:
	ModifyPasswd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ModifyPasswd();

// 对话框数据
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	Function m_function;
	CMFCButton* m_button1;
	CMFCButton* m_button2;
	CFont font,font1;
	CString m_Loginname,m_Loginpasswd;   //用于存储当前登陆用户名和密码
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CEdit m_repasswd;   //控件关联
	CEdit m_passwd;    //控件关联
	afx_msg void OnBnClickedRadio21();
	afx_msg void OnBnClickedRadio22();
	CString m_strpasswd;
	CString m_strrepasswd;
	CButton m_ShowPasswd;
	CButton m_HidePasswd;
};

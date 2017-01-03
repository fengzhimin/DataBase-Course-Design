#pragma once
#include "afxwin.h"
#include "Function.h"

// FindPasswd 对话框

class FindPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(FindPasswd)

public:
	FindPasswd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~FindPasswd();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFont font_1,font_2;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic m_User;
	CStatic m_question;
	CString m_answer;
	CString question;
	CString User;
	CString answer;
	CString Passwd;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	Function Find_function;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

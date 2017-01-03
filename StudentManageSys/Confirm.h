#pragma once

#include "Function.h"
#include "afxwin.h"
// Confirm 对话框

class Confirm : public CDialogEx
{
	DECLARE_DYNAMIC(Confirm)

public:
	Confirm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Confirm();

// 对话框数据
	enum { IDD = IDD_DIALOG8 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	Function m_function;
	CMFCButton* m_button1;
	CMFCButton* m_button2;
	CFont m_font;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	CString m_passwd,m_static;	
	CString m_confirm;    //关联控件
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_Cconfirm;    //关联控件
};

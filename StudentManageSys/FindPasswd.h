#pragma once
#include "afxwin.h"
#include "Function.h"

// FindPasswd �Ի���

class FindPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(FindPasswd)

public:
	FindPasswd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~FindPasswd();

// �Ի�������
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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

#pragma once
#include "Function.h"
#include "afxwin.h"
#include "Confirm.h"
// ModifyPasswd �Ի���

class ModifyPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(ModifyPasswd)

public:
	ModifyPasswd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ModifyPasswd();

// �Ի�������
	enum { IDD = IDD_DIALOG9 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	Function m_function;
	CMFCButton* m_button1;
	CMFCButton* m_button2;
	CFont font,font1;
	CString m_Loginname,m_Loginpasswd;   //���ڴ洢��ǰ��½�û���������
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CEdit m_repasswd;   //�ؼ�����
	CEdit m_passwd;    //�ؼ�����
	afx_msg void OnBnClickedRadio21();
	afx_msg void OnBnClickedRadio22();
	CString m_strpasswd;
	CString m_strrepasswd;
	CButton m_ShowPasswd;
	CButton m_HidePasswd;
};

#pragma once

#include "Function.h"
#include "afxwin.h"
#include "Confirm.h"
// SetUser �Ի���

class SetUser : public CDialogEx
{
	DECLARE_DYNAMIC(SetUser)

public:
	SetUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SetUser();
// �Ի�������
	enum { IDD = IDD_MODIFY_Info };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CFont m_font,m_font1;
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_Loginname,m_Loginpasswd,m_Loginstype;
	CString m_name;    //�����ؼ�
	CString m_question;    //�����ؼ�
	CString m_answer;
	Function m_function;
	CMFCButton* m_modify;
	CMFCButton* m_cancel;
	CButton m_modifyquestion;
	CString m_stuid;    //�����ؼ�
	int m_point,point1;  //���ڱ���Ƿ������޸� 0��ʾû�� 1��ʾ�޸Ĺ�
	CString m_newquestion;   //�����ؼ�
	CString m_newanswer;    //�����ؼ�
	CEdit m_edit_newquestion;
	CEdit m_editnewanswer;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

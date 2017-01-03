#pragma once
#include "afxwin.h"
#include "Function.h"

// Register �Ի���

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Register();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString Reg_Name;
	CString Reg_Passwd;
	CString Reg_rePasswd;
	CComboBox m_question;
	CString m_answer;
	CFont font_1, font_2;
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	_ConnectionPtr Reg_pConnection;
	_RecordsetPtr Reg_pRecordset;
	CButton m_ShowPasswd;
	CButton m_HidePasswd;
	afx_msg void OnBnClickedRadioShow();
	afx_msg void OnBnClickedRadioHide();
	CEdit m_Passwd;
	CEdit m_rePasswd;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	Function Reg_function;
	CMFCButton* button_Register;
	CMFCButton* button_Cancel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_edit;
	CEdit m_edit_answer;
	CEdit m_edit_name;
	int m_point;    //���ڱ���ǹ���Ա���ѧ����������ѧ��������� 1��ʾ����Ա 0��ʾѧ�� Ĭ��Ϊ0
	CString m_str;   //���ڱ�ǰ�ť�ı����ǹ���Ա���ѧ����������ѧ���������  Ĭ��Ϊ�������
	CString m_str1;   //���ڱ�ʾ��ť����ʾ��   Ĭ��Ϊ�������û�
	CString m_str2;   //���ڱ�ʾȡ����ť����ʾ  Ĭ��Ϊȡ�����û�����
	CString m_stu_id;
	CComboBox m_Stype;
	CString m_str_Stype;
	afx_msg void OnCbnSelchangeCombo3();
};

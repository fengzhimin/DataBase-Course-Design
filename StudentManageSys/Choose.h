#pragma once
#include "afxwin.h"


// Choose �Ի���

class Choose : public CDialogEx
{
	DECLARE_DYNAMIC(Choose)

public:
	Choose(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Choose();

// �Ի�������
	enum { IDD = IDD_DIALOG11 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_id;
	CString m_name;
	int point;   //���ڱ����ע��ѧ����Ϣ���ǽ�ʦ��Ϣ 1:ѧ��   2: ��ʦ
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();

	CString m_stype;
	afx_msg void OnCbnSelchangeComboCh1();
	CComboBox m_edit_stype;
};

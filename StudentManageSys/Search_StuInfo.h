#pragma once
#include "afxwin.h"
#include "Function.h"

// Search_StuInfo �Ի���

class Search_StuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(Search_StuInfo)

public:
	Search_StuInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Search_StuInfo();

// �Ի�������
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CEdit Stu_Info;
	CString str_Info;   //��¼�����ѧ��ѧ�Ż�����
	CString m_str;   //��¼�ǰ���ʲô��ʽ���е�����
	int m_Teacher_Student;   //���ڼ�¼�ǲ�ѯѧ���α��ǽ�ʦ�α�  0��ʾ��ѯѧ�� 1��ʾ��ѯ��ʦ
	CFont font;
	Function m_function;
	CMFCButton* m_button1;
	CMFCButton* m_button2;
	virtual BOOL OnInitDialog();
	CComboBox m_Stype;
	_ConnectionPtr m_connection;
	_RecordsetPtr m_recordset;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

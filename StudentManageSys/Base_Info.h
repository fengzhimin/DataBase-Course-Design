#pragma once
#include "afxwin.h"


// Base_Info �Ի���

class Base_Info : public CDialogEx
{
	DECLARE_DYNAMIC(Base_Info)

public:
	Base_Info(CString str_name,CString str_id,int i,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Base_Info();

// �Ի�������
	enum { IDD = IDD_DIALOG10 };
	CFont m_font;
	CString m_str_id;   //���ڼ�¼Ҫ�����ѧ��
	int point;   //���ڱ��ע������
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_Name;
	CString m_Age;
	CString m_sex;
	CString m_mingzhu;
	CString m_zhengzhi;
	CString m_shenfeng;
	CString m_suozaidi;
	CString m_biyan;
	CString m_xueli;
	CString m_xuexiao;
	CString m_xueyuan;
	CString m_biyexuexiao;
	CString m_zhuanye;
	CString m_nianji;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CComboBox m_Cxingbian;
	CComboBox m_Czhengzhi;
	CComboBox m_Cshenfeng;
	CComboBox m_Cxueli;
	void Insert_info(_ConnectionPtr& m_connect,_RecordsetPtr& m_record);
	CString m_gerentechang;
};

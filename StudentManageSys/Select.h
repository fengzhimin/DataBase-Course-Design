#pragma once


// Select �Ի���

class Select : public CDialogEx
{
	DECLARE_DYNAMIC(Select)

public:
	Select(CString str1,CString str2,CString str3,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Select();

// �Ի�������
	enum { IDD = IDD_DIALOG12 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CString m_str_stype;  //��ʶ��ѯ����
	CString m_stype;    
	CString m_button;   //��ǰ�ť�Ĺ���
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_id;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_newpasswd;
};

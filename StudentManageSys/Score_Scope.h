#pragma once


// Score_Scope �Ի���

class Score_Scope : public CDialogEx
{
	DECLARE_DYNAMIC(Score_Scope)

public:
	Score_Scope(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Score_Scope();

// �Ի�������
	enum { IDD = IDD_DIALOG16 };
	CFont m_font;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_min;
	CString m_max;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};

#pragma once


// Search_StuScore �Ի���

class Search_StuScore : public CDialogEx
{
	DECLARE_DYNAMIC(Search_StuScore)

public:
	Search_StuScore(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Search_StuScore();

// �Ի�������
	enum { IDD = IDD_DIALOG15 };
	CFont m_font;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_id;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
};

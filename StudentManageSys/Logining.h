#pragma once
#include "Function.h"

// Logining �Ի���

class Logining : public CDialogEx
{
	DECLARE_DYNAMIC(Logining)

public:
	Logining(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Logining();

// �Ի�������
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	CFont font;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnPaint();
	Function Log_function;
	CMFCButton* Cancel_Button;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

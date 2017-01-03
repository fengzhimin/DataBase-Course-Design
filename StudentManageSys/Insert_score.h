#pragma once
#include "afxwin.h"


// Insert_score 对话框

class Insert_score : public CDialogEx
{
	DECLARE_DYNAMIC(Insert_score)

public:
	Insert_score(CString str,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Insert_score();

// 对话框数据
	enum { IDD = IDD_DIALOG14 };
	CFont m_font;
	CString m_teacher_id;
	CString strSQL;
	_ConnectionPtr M_pConnection;
	_RecordsetPtr M_pRecord;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_id;
	CString m_score;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

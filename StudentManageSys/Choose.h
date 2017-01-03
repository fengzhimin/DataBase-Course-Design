#pragma once
#include "afxwin.h"


// Choose 对话框

class Choose : public CDialogEx
{
	DECLARE_DYNAMIC(Choose)

public:
	Choose(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Choose();

// 对话框数据
	enum { IDD = IDD_DIALOG11 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_id;
	CString m_name;
	int point;   //用于标记是注册学生信息还是教师信息 1:学生   2: 教师
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();

	CString m_stype;
	afx_msg void OnCbnSelchangeComboCh1();
	CComboBox m_edit_stype;
};

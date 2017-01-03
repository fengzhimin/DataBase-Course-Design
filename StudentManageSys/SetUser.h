#pragma once

#include "Function.h"
#include "afxwin.h"
#include "Confirm.h"
// SetUser 对话框

class SetUser : public CDialogEx
{
	DECLARE_DYNAMIC(SetUser)

public:
	SetUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SetUser();
// 对话框数据
	enum { IDD = IDD_MODIFY_Info };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	CFont m_font,m_font1;
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_Loginname,m_Loginpasswd,m_Loginstype;
	CString m_name;    //关联控件
	CString m_question;    //关联控件
	CString m_answer;
	Function m_function;
	CMFCButton* m_modify;
	CMFCButton* m_cancel;
	CButton m_modifyquestion;
	CString m_stuid;    //关联控件
	int m_point,point1;  //用于标记是否做了修改 0表示没有 1表示修改过
	CString m_newquestion;   //关联控件
	CString m_newanswer;    //关联控件
	CEdit m_edit_newquestion;
	CEdit m_editnewanswer;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

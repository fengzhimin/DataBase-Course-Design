#pragma once

#include "Function.h"
#include "afxcmn.h"
// Stu_Info 对话框

class Stu_Info : public CDialogEx
{
	DECLARE_DYNAMIC(Stu_Info)

public:
	Stu_Info(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Stu_Info();

// 对话框数据
	enum { IDD = IDD_DIALOG_StuInfo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRect m_rect;
	Function Stu_function;
	CString str_Name;    //用于记录当前登录的用户
	CString str_Command;   //用于存储执行的SQL语句
	CRect rect;
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void ChangeSize(UINT nID, int x, int y);   //改变窗口的时候控件也随之改变
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_list;
	CListCtrl m_list1;
	int point;  //用于标识学生信息是否已经录入
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

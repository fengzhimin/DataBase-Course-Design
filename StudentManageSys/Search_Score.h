#pragma once
#include "afxcmn.h"
#include "Function.h"

// Search_Score 对话框

class Search_Score : public CDialogEx
{
	DECLARE_DYNAMIC(Search_Score)

public:
	Search_Score(CString str,int i = 0,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Search_Score();

// 对话框数据
	enum { IDD = IDD_DIALOG13 };
	CRect m_rect;
	CRect rect;
	int point;   //标记是学生查看成绩还是教师查看成绩  0:学生  1：教师
	Function Stu_function;
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	CString str_Command;
	CString str_id;
	CString min,max;   //用于查询成绩分布式使用
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl m_list;
};

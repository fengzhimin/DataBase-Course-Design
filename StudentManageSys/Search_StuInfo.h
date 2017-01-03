#pragma once
#include "afxwin.h"
#include "Function.h"

// Search_StuInfo 对话框

class Search_StuInfo : public CDialogEx
{
	DECLARE_DYNAMIC(Search_StuInfo)

public:
	Search_StuInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Search_StuInfo();

// 对话框数据
	enum { IDD = IDD_DIALOG6 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	CEdit Stu_Info;
	CString str_Info;   //记录输入的学生学号或姓名
	CString m_str;   //记录是按照什么方式进行的收索
	int m_Teacher_Student;   //用于记录是查询学生课表还是教师课表  0表示查询学生 1表示查询教师
	CFont font;
	Function m_function;
	CMFCButton* m_button1;
	CMFCButton* m_button2;
	virtual BOOL OnInitDialog();
	CComboBox m_Stype;
	_ConnectionPtr m_connection;
	_RecordsetPtr m_recordset;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#pragma once
#include "afxwin.h"
#include "Function.h"

// Register 对话框

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Register();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Reg_Name;
	CString Reg_Passwd;
	CString Reg_rePasswd;
	CComboBox m_question;
	CString m_answer;
	CFont font_1, font_2;
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonCancel();
	virtual BOOL OnInitDialog();
	_ConnectionPtr Reg_pConnection;
	_RecordsetPtr Reg_pRecordset;
	CButton m_ShowPasswd;
	CButton m_HidePasswd;
	afx_msg void OnBnClickedRadioShow();
	afx_msg void OnBnClickedRadioHide();
	CEdit m_Passwd;
	CEdit m_rePasswd;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	Function Reg_function;
	CMFCButton* button_Register;
	CMFCButton* button_Cancel;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
	CEdit m_edit;
	CEdit m_edit_answer;
	CEdit m_edit_name;
	int m_point;    //用于标记是管理员添加学生操作还是学生激活操作 1表示管理员 0表示学生 默认为0
	CString m_str;   //用于标记按钮的标题是管理员添加学生操作还是学生激活操作  默认为激活操作
	CString m_str1;   //用于表示按钮的提示符   默认为激活新用户
	CString m_str2;   //用于表示取消按钮的提示  默认为取消新用户激活
	CString m_stu_id;
	CComboBox m_Stype;
	CString m_str_Stype;
	afx_msg void OnCbnSelchangeCombo3();
};

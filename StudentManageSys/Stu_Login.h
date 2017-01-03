#pragma once
#include "afxwin.h"
#include "Logining.h"
#include "Function.h"
// Stu_Login 对话框

class Stu_Login : public CDialogEx
{
	DECLARE_DYNAMIC(Stu_Login)

public:
	Stu_Login(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Stu_Login();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_LName;
	CString m_LPasswd;
	CString str_stype;    //记录登陆用户类型
	CComboBox m_LStyple;
	CString m_str_name;   //用于记录当前登陆账号对应的用户名
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonForget();
	afx_msg void OnBnClickedButtonLogin();
	
	_ConnectionPtr m_pConnection;
	_RecordsetPtr pRecordset;
	
	int m_LoginCount;
	CButton m_RememberPasswd;
	CButton m_AutoLogin;
	
	CMFCButton* Login_Button;
	CMFCButton* Cancel_Button;
	CMFCButton* Register_Button;
	CMFCButton* Forget_Button;
	Function function_button;    //创建按钮
	CFont font;      //设置按钮字体的颜色
	CStdioFile m_Remember_Auto;
	afx_msg void OnBnClickedCheck1();
	CBrush m_brBk;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
};

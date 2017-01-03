#pragma once
#include "afxwin.h"
#include "Logining.h"
#include "Function.h"
// Stu_Login �Ի���

class Stu_Login : public CDialogEx
{
	DECLARE_DYNAMIC(Stu_Login)

public:
	Stu_Login(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Stu_Login();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_LName;
	CString m_LPasswd;
	CString str_stype;    //��¼��½�û�����
	CComboBox m_LStyple;
	CString m_str_name;   //���ڼ�¼��ǰ��½�˺Ŷ�Ӧ���û���
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
	Function function_button;    //������ť
	CFont font;      //���ð�ť�������ɫ
	CStdioFile m_Remember_Auto;
	afx_msg void OnBnClickedCheck1();
	CBrush m_brBk;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnCbnSelchangeCombo1();
};

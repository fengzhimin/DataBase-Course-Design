#pragma once


// Select 对话框

class Select : public CDialogEx
{
	DECLARE_DYNAMIC(Select)

public:
	Select(CString str1,CString str2,CString str3,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Select();

// 对话框数据
	enum { IDD = IDD_DIALOG12 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	CString m_str_stype;  //标识查询类型
	CString m_stype;    
	CString m_button;   //标记按钮的功能
	_ConnectionPtr m_connect;
	_RecordsetPtr m_record;
	CString m_id;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString m_newpasswd;
};

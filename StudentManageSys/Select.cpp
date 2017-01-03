// Select.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Select.h"
#include "afxdialogex.h"


// Select 对话框

IMPLEMENT_DYNAMIC(Select, CDialogEx)

Select::Select(CString str1,CString str2,CString str3,CWnd* pParent /*=NULL*/)
	: CDialogEx(Select::IDD, pParent)
	, m_id(_T(""))
	, m_newpasswd(_T(""))
{
	m_str_stype = str1;
	m_stype = str2;
	m_button = str3;
	m_font.CreatePointFont(120, L"宋体");
}

Select::~Select()
{
	m_connect->Close();
	m_font.DeleteObject();
}

void Select::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_newpasswd);
}


BEGIN_MESSAGE_MAP(Select, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Select::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Select::OnBnClickedButton2)
END_MESSAGE_MAP()


// Select 消息处理程序


BOOL Select::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_SELECT)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_SELECT2)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_SELECT)->SetWindowTextW(m_str_stype);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON1)->SetWindowTextW(m_button);
	if(m_str_stype == L"输入学生的学号：" || m_str_stype == L"输入教师的编号：")
	{
		GetDlgItem(IDC_STATIC_SELECT2)->SetWindowTextW(L"输入新的密码：");
		GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
	}
	::CoInitialize(NULL);
	try
	{
		m_connect.CreateInstance(__uuidof(Connection));
		m_connect->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
		m_connect->Open("", "", "", adConnectUnspecified);
		m_connect->DefaultDatabase = "USER";
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

//查询
void Select::OnBnClickedButton1()
{
	UpdateData();
	if(m_str_stype == L"输入学生的学号：" || m_str_stype == L"输入教师的编号：")
	{
		if(m_newpasswd == L"")
		{
			MessageBox(L"请输入新的密码！");
			return;
		}
	}
	if(m_id == L"")
	{
		if(m_str_stype == L"输入学生的学号：")
			MessageBox(L"请输入要查询学生的学号！");
		else
			if(m_str_stype == L"输入教师的编号：")
				MessageBox(L"请输入要查询教师的编号！");
			else
				if(m_str_stype == L"输入学生的学号：")
					MessageBox(L"请输入学生的学号！");
				else
					MessageBox(L"请输入教师的编号！");
		return;
	}
	else
	{

		CString strSQL = L"select * from User_Passwd where 学号 = '" + m_id + L"' and 用户类型 = '" + m_stype + L"'";
		m_record = m_connect->Execute(_bstr_t(strSQL), NULL, adCmdText);
		if(!m_record->adoEOF)
		{
			if(m_newpasswd.GetLength() < 6 || m_newpasswd.GetLength() > 16)
			{
				MessageBox(L"密码长度应在6-15个字符之间");
				m_newpasswd = L"";
				UpdateData(0);
			}
			else
				CDialog::OnOK();
		}
		else
		{
			MessageBox(L"您输入的账号不存在！");
			m_id = L"";
			m_newpasswd = L"";
			UpdateData(0);
		}
	}
}


void Select::OnBnClickedButton2()
{
	CDialog::OnCancel();
}

// Choose.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Choose.h"
#include "afxdialogex.h"


// Choose 对话框

IMPLEMENT_DYNAMIC(Choose, CDialogEx)

Choose::Choose(CWnd* pParent /*=NULL*/)
	: CDialogEx(Choose::IDD, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_stype(_T(""))
{
	m_font.CreatePointFont(120, L"宋体");
	point = 0;
}

Choose::~Choose()
{
	m_font.DeleteObject();
	m_connect->Close();
}

void Choose::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_CBString(pDX, IDC_COMBO_CH1, m_stype);
	DDX_Control(pDX, IDC_COMBO_CH1, m_edit_stype);
}


BEGIN_MESSAGE_MAP(Choose, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &Choose::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Choose::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_CH1, &Choose::OnCbnSelchangeComboCh1)
END_MESSAGE_MAP()


// Choose 消息处理程序


void Choose::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void Choose::OnBnClickedButton1()
{
	UpdateData();
	if(m_id == L"" || m_name == L"")
	{
		MessageBox(L"学号或姓名不能为空！");
		return;
	}
	CString	str = L"select * from Stu_Info where 学号 = '" + m_id + L"'";
	m_record = m_connect->Execute(_bstr_t(str), NULL, adCmdText);
	if(!m_record->adoEOF)
	{
		MessageBox(L"对不起！您输入的账号已经被录入信息！");
		m_id = m_name = L"";
		UpdateData(0);
		return ;
	}
	else
	{
		CString strSQL = L"select * from Register where 学号 = '" + m_id + L"'";
			m_record = m_connect->Execute(_bstr_t(strSQL), NULL, adCmdText);
		if(m_record->adoEOF)
		{
			MessageBox(L"对不起！您输入的账号还没有被注册！\r\n请先注册！");
			return ;
		}
		strSQL = m_record->GetCollect("用户名");
		if(strSQL == m_name)
		{
			CDialog::OnOK();
			if(m_stype == L"学生")
				point = 1;
			else
				point = 2;
			return;
		}
		else
		{
			MessageBox(L"您输入的姓名不存在！");
			return;
		}
	}
}


BOOL Choose::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC_CH1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_CH2)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_CH3)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);
	GetDlgItem(IDC_COMBO_CH1)->SetFont(&m_font);
	m_edit_stype.AddString(L"学生");
	m_edit_stype.AddString(L"教师");
	m_edit_stype.SetCurSel(1);
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


void Choose::OnCbnSelchangeComboCh1()
{
	m_id = m_name = L"";
	UpdateData();
	if(m_stype == L"学生")
	{
		GetDlgItem(IDC_STATIC_CH1)->SetWindowTextW(L"学号：");
		GetDlgItem(IDC_STATIC_CH2)->SetWindowTextW(L"姓名：");
	}
	else
	{
		GetDlgItem(IDC_STATIC_CH1)->SetWindowTextW(L"教师编号：");
		GetDlgItem(IDC_STATIC_CH2)->SetWindowTextW(L"教师姓名：");
	}
	UpdateData(0);
}

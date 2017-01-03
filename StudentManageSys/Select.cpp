// Select.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Select.h"
#include "afxdialogex.h"


// Select �Ի���

IMPLEMENT_DYNAMIC(Select, CDialogEx)

Select::Select(CString str1,CString str2,CString str3,CWnd* pParent /*=NULL*/)
	: CDialogEx(Select::IDD, pParent)
	, m_id(_T(""))
	, m_newpasswd(_T(""))
{
	m_str_stype = str1;
	m_stype = str2;
	m_button = str3;
	m_font.CreatePointFont(120, L"����");
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


// Select ��Ϣ�������


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
	if(m_str_stype == L"����ѧ����ѧ�ţ�" || m_str_stype == L"�����ʦ�ı�ţ�")
	{
		GetDlgItem(IDC_STATIC_SELECT2)->SetWindowTextW(L"�����µ����룺");
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

//��ѯ
void Select::OnBnClickedButton1()
{
	UpdateData();
	if(m_str_stype == L"����ѧ����ѧ�ţ�" || m_str_stype == L"�����ʦ�ı�ţ�")
	{
		if(m_newpasswd == L"")
		{
			MessageBox(L"�������µ����룡");
			return;
		}
	}
	if(m_id == L"")
	{
		if(m_str_stype == L"����ѧ����ѧ�ţ�")
			MessageBox(L"������Ҫ��ѯѧ����ѧ�ţ�");
		else
			if(m_str_stype == L"�����ʦ�ı�ţ�")
				MessageBox(L"������Ҫ��ѯ��ʦ�ı�ţ�");
			else
				if(m_str_stype == L"����ѧ����ѧ�ţ�")
					MessageBox(L"������ѧ����ѧ�ţ�");
				else
					MessageBox(L"�������ʦ�ı�ţ�");
		return;
	}
	else
	{

		CString strSQL = L"select * from User_Passwd where ѧ�� = '" + m_id + L"' and �û����� = '" + m_stype + L"'";
		m_record = m_connect->Execute(_bstr_t(strSQL), NULL, adCmdText);
		if(!m_record->adoEOF)
		{
			if(m_newpasswd.GetLength() < 6 || m_newpasswd.GetLength() > 16)
			{
				MessageBox(L"���볤��Ӧ��6-15���ַ�֮��");
				m_newpasswd = L"";
				UpdateData(0);
			}
			else
				CDialog::OnOK();
		}
		else
		{
			MessageBox(L"��������˺Ų����ڣ�");
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

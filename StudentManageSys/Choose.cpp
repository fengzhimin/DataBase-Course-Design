// Choose.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Choose.h"
#include "afxdialogex.h"


// Choose �Ի���

IMPLEMENT_DYNAMIC(Choose, CDialogEx)

Choose::Choose(CWnd* pParent /*=NULL*/)
	: CDialogEx(Choose::IDD, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_stype(_T(""))
{
	m_font.CreatePointFont(120, L"����");
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


// Choose ��Ϣ�������


void Choose::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void Choose::OnBnClickedButton1()
{
	UpdateData();
	if(m_id == L"" || m_name == L"")
	{
		MessageBox(L"ѧ�Ż���������Ϊ�գ�");
		return;
	}
	CString	str = L"select * from Stu_Info where ѧ�� = '" + m_id + L"'";
	m_record = m_connect->Execute(_bstr_t(str), NULL, adCmdText);
	if(!m_record->adoEOF)
	{
		MessageBox(L"�Բ�����������˺��Ѿ���¼����Ϣ��");
		m_id = m_name = L"";
		UpdateData(0);
		return ;
	}
	else
	{
		CString strSQL = L"select * from Register where ѧ�� = '" + m_id + L"'";
			m_record = m_connect->Execute(_bstr_t(strSQL), NULL, adCmdText);
		if(m_record->adoEOF)
		{
			MessageBox(L"�Բ�����������˺Ż�û�б�ע�ᣡ\r\n����ע�ᣡ");
			return ;
		}
		strSQL = m_record->GetCollect("�û���");
		if(strSQL == m_name)
		{
			CDialog::OnOK();
			if(m_stype == L"ѧ��")
				point = 1;
			else
				point = 2;
			return;
		}
		else
		{
			MessageBox(L"����������������ڣ�");
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
	m_edit_stype.AddString(L"ѧ��");
	m_edit_stype.AddString(L"��ʦ");
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
	if(m_stype == L"ѧ��")
	{
		GetDlgItem(IDC_STATIC_CH1)->SetWindowTextW(L"ѧ�ţ�");
		GetDlgItem(IDC_STATIC_CH2)->SetWindowTextW(L"������");
	}
	else
	{
		GetDlgItem(IDC_STATIC_CH1)->SetWindowTextW(L"��ʦ��ţ�");
		GetDlgItem(IDC_STATIC_CH2)->SetWindowTextW(L"��ʦ������");
	}
	UpdateData(0);
}

// Base_Info.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Base_Info.h"
#include "afxdialogex.h"


// Base_Info �Ի���

IMPLEMENT_DYNAMIC(Base_Info, CDialogEx)
//��������
Base_Info::Base_Info(CString str_name,CString str_id,int i,CWnd* pParent /*=NULL*/)
	: CDialogEx(Base_Info::IDD, pParent)
	, m_Name(_T(""))
	, m_Age(_T(""))
	, m_sex(_T(""))
	, m_mingzhu(_T(""))
	, m_zhengzhi(_T(""))
	, m_shenfeng(_T(""))
	, m_suozaidi(_T(""))
	, m_biyan(_T(""))
	, m_xueli(_T(""))
	, m_xuexiao(_T(""))
	, m_xueyuan(_T(""))
	, m_biyexuexiao(_T(""))
	, m_zhuanye(_T(""))
	, m_nianji(_T(""))
	, m_gerentechang(_T(""))
{
	m_Name = str_name;
	m_str_id = str_id;
	point = i;
	m_font.CreatePointFont(120, L"����");
}

Base_Info::~Base_Info()
{
	m_font.DeleteObject();
}

void Base_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Name);
	DDX_Text(pDX, IDC_EDIT_B1, m_Age);
	DDX_CBString(pDX, IDC_COMBO_B1, m_sex);
	DDX_Text(pDX, IDC_EDIT_B2, m_mingzhu);
	DDX_CBString(pDX, IDC_COMBO_B2, m_zhengzhi);
	DDX_CBString(pDX, IDC_COMBO_B3, m_shenfeng);
	DDX_Text(pDX, IDC_EDIT_B3, m_suozaidi);
	DDX_Text(pDX, IDC_EDIT_B4, m_biyan);
	DDX_CBString(pDX, IDC_COMBO_B4, m_xueli);
	DDX_Text(pDX, IDC_EDIT_B5, m_xuexiao);
	DDX_Text(pDX, IDC_EDIT_B6, m_xueyuan);
	DDX_Text(pDX, IDC_EDIT_B7, m_biyexuexiao);
	DDX_Text(pDX, IDC_EDIT_B8, m_zhuanye);
	DDX_Text(pDX, IDC_EDIT_B9, m_nianji);
	DDX_Control(pDX, IDC_COMBO_B1, m_Cxingbian);
	DDX_Control(pDX, IDC_COMBO_B2, m_Czhengzhi);
	DDX_Control(pDX, IDC_COMBO_B3, m_Cshenfeng);
	DDX_Control(pDX, IDC_COMBO_B4, m_Cxueli);
	DDX_Text(pDX, IDC_EDIT_B10, m_gerentechang);
}


BEGIN_MESSAGE_MAP(Base_Info, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Base_Info::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Base_Info::OnBnClickedButton2)
END_MESSAGE_MAP()


// Base_Info ��Ϣ�������


BOOL Base_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);
	for(int i = 1076;i < 1098;i++)
		GetDlgItem(i)->SetFont(&m_font);
	m_Cxingbian.AddString(L"��");
	m_Cxingbian.AddString(L"Ů");
	m_Cxingbian.SetCurSel(0);
	m_Czhengzhi.AddString(L"Ⱥ��");
	m_Czhengzhi.AddString(L"������Ա");
	m_Czhengzhi.AddString(L"��Ա");
	m_Czhengzhi.SetCurSel(0);
	if(point == 1)
		m_Cshenfeng.AddString(L"ѧ��");
	else
	{
		GetDlgItem(IDC_STATIC_B3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_B7)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_B9)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_B10)->ShowWindow(SW_HIDE);
		m_Cshenfeng.AddString(L"��ʦ");
	}
	m_Cxueli.AddString(L"ר��");
	m_Cxueli.AddString(L"����");
	m_Cxueli.AddString(L"�о���");
	m_Cxueli.AddString(L"��ʿ��");
	m_Cxueli.AddString(L"������");
	m_Cxueli.AddString(L"����");
	m_Cxueli.SetCurSel(0);
	UpdateData(); 
	return TRUE;  // return TRUE unless you set the focus to a control
}



void Base_Info::OnBnClickedButton1()
{
	UpdateData();
	
	for(int i = 0;i < m_Age.GetLength();++i)
		if(m_Age.GetAt(i) < 48 || m_Age.GetAt(i) > 57)
		{
			MessageBox(L"�Բ���������������ʽ����ȷ��\n��ȷ�������ʽΪ0-9������ɣ�");
			return;
		}
	if(point == 2)
	{
		if(m_Age == L"" || m_mingzhu == L"" || m_xuexiao == L"" || m_xueyuan == L"" || m_biyexuexiao == L"" || m_zhuanye == L"")
		{
			MessageBox(L"�����Ǻŵ���Ϊ�����");
			return;
		}
		CDialog::OnOK();
		return;
	}
	else
		if(m_Age == L"" || m_mingzhu == L"" || m_biyan == L"" || m_xuexiao == L"" || m_xueyuan == L"" || m_biyexuexiao == L"" || m_zhuanye == L"" || m_nianji == L"")
		{
			MessageBox(L"�����Ǻŵ���Ϊ�����");
			return;
		}
	for(int i = 0;i < 4;++i)
		if(m_biyan.GetAt(i) < 48 || m_biyan.GetAt(i) > 57)
		{
			MessageBox(L"�Բ���������ı�ҵ��ݸ�ʽ����ȷ��");
			return;
		}
	if(m_biyan.GetAt(4) != 24180 || m_biyan.GetAt(7) != 26376 || m_biyan.GetAt(10) != 21495)
	{
		MessageBox(L"�Բ���������ı�ҵ��ݸ�ʽ����ȷ��");
		return;
	}
	
	for(int i = 0;i < 2;++i)
		if(m_biyan.GetAt(5+3*i) < 48 || m_biyan.GetAt(5+3*i) > 57 || m_biyan.GetAt(6+3*i) < 48 || m_biyan.GetAt(6+3*i) > 57)
		{
			MessageBox(L"�Բ���������ı�ҵ��ݸ�ʽ����ȷ��");
			return;
		}
	for(int i = 0;i < 4;++i)
		if(m_nianji.GetAt(i) < 48 || m_nianji.GetAt(i) > 57)
		{
			MessageBox(L"�Բ�����������ꡢ�༶��ʽ����ȷ��");
			return;
		}
	if(m_nianji.GetAt(4) != 32423 || m_nianji.GetAt(7) != 29677)
	{
		MessageBox(L"�Բ�����������ꡢ�༶��ʽ����ȷ��");
		return;
	}
	if(m_nianji.GetAt(5) < 48 || m_nianji.GetAt(6) < 48 || m_nianji.GetAt(5) > 57 || m_nianji.GetAt(6) > 57)
	{
		MessageBox(L"�Բ�����������ꡢ�༶��ʽ����ȷ��");
		return;
	}
	CDialog::OnOK();
}


void Base_Info::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void Base_Info::Insert_info(_ConnectionPtr& m_connect,_RecordsetPtr& m_record)
{
	CString strSQL = L"insert into Stu_Info values ('" + m_str_id + L"'," + m_Age + L",'" + m_sex + L"','" + m_mingzhu + L"','" + m_zhengzhi + L"','" + m_shenfeng + L"','" + m_suozaidi + 
		L"','" + m_biyan + L"','" + m_xueli + L"','" + m_xuexiao + L"','" + m_xueyuan + L"','" + m_biyexuexiao + L"','" + m_zhuanye + L"','" + m_nianji + L"','" + m_gerentechang + L"')";
	try
	{
		m_connect->Execute(_bstr_t(strSQL), NULL, adCmdText);
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		return ;
	}
	strSQL = L"�˺�Ϊ��" + m_str_id + L" ���û���Ϣ¼��ɹ���";
}
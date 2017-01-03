// Search_StuScore.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_StuScore.h"
#include "afxdialogex.h"


// Search_StuScore �Ի���

IMPLEMENT_DYNAMIC(Search_StuScore, CDialogEx)

Search_StuScore::Search_StuScore(CWnd* pParent /*=NULL*/)
	: CDialogEx(Search_StuScore::IDD, pParent)
	, m_id(_T(""))
{
	m_font.CreatePointFont(130, L"����");
}

Search_StuScore::~Search_StuScore()
{
	m_font.DeleteObject();
}

void Search_StuScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
}


BEGIN_MESSAGE_MAP(Search_StuScore, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Search_StuScore::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Search_StuScore::OnBnClickedButton2)
END_MESSAGE_MAP()


// Search_StuScore ��Ϣ�������

//��ѯ
void Search_StuScore::OnBnClickedButton1()
{
	UpdateData();
	if(m_id == L"")
	{
		MessageBox(L"������ѧ��ѧ�ţ�");
		return;
	}
	else
		CDialog::OnOK();
}

//ȡ��
void Search_StuScore::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


BOOL Search_StuScore::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_STATIC_STUDENT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);


	return TRUE;  // return TRUE unless you set the focus to a control
}

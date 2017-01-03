// Score_Scope.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Score_Scope.h"
#include "afxdialogex.h"


// Score_Scope 对话框

IMPLEMENT_DYNAMIC(Score_Scope, CDialogEx)

Score_Scope::Score_Scope(CWnd* pParent /*=NULL*/)
	: CDialogEx(Score_Scope::IDD, pParent)
	, m_min(_T(""))
	, m_max(_T(""))
{
	m_font.CreatePointFont(120, L"宋体");
}

Score_Scope::~Score_Scope()
{
	m_font.DeleteObject();
}

void Score_Scope::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_min);
	DDX_Text(pDX, IDC_EDIT2, m_max);
}


BEGIN_MESSAGE_MAP(Score_Scope, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Score_Scope::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Score_Scope::OnBnClickedButton2)
END_MESSAGE_MAP()


// Score_Scope 消息处理程序


BOOL Score_Scope::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_SCOPE1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_SCOPE2)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
	GetDlgItem(IDC_EDIT2)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);

	return TRUE;  // return TRUE unless you set the focus to a control

}

//查询
void Score_Scope::OnBnClickedButton1()
{
	UpdateData();
	int min =  _ttoi(m_min);
	int max =  _ttoi(m_max);
	if(min > max)
	{
		MessageBox(L"对不起！您输入的下限值大于上限值！");
		m_min = m_max = L"";
		UpdateData(0);
		return;
	}
	else
		CDialog::OnOK();

}

//取消
void Score_Scope::OnBnClickedButton2()
{
	CDialog::OnCancel();
}

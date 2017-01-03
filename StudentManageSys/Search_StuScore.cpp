// Search_StuScore.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_StuScore.h"
#include "afxdialogex.h"


// Search_StuScore 对话框

IMPLEMENT_DYNAMIC(Search_StuScore, CDialogEx)

Search_StuScore::Search_StuScore(CWnd* pParent /*=NULL*/)
	: CDialogEx(Search_StuScore::IDD, pParent)
	, m_id(_T(""))
{
	m_font.CreatePointFont(130, L"宋体");
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


// Search_StuScore 消息处理程序

//查询
void Search_StuScore::OnBnClickedButton1()
{
	UpdateData();
	if(m_id == L"")
	{
		MessageBox(L"请输入学生学号！");
		return;
	}
	else
		CDialog::OnOK();
}

//取消
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

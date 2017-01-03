// FindPasswd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "FindPasswd.h"
#include "afxdialogex.h"


// FindPasswd �Ի���

IMPLEMENT_DYNAMIC(FindPasswd, CDialogEx)

FindPasswd::FindPasswd(CWnd* pParent /*=NULL*/)
	: CDialogEx(FindPasswd::IDD, pParent)
	, m_answer(_T(""))
{

}

FindPasswd::~FindPasswd()
{
	font_1.DeleteObject();
	font_2.DeleteObject();
}

void FindPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Name, m_User);
	DDX_Control(pDX, IDC_STATIC_question, m_question);
	DDX_Text(pDX, IDC_EDIT_Answer, m_answer);
}


BEGIN_MESSAGE_MAP(FindPasswd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &FindPasswd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &FindPasswd::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// FindPasswd ��Ϣ�������


BOOL FindPasswd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	font_1.CreatePointFont(180, L"����");
	font_2.CreatePointFont(150, L"����");
	GetDlgItem(IDC_STATIC1)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC2)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC3)->SetFont(&font_1);
	GetDlgItem(IDC_BUTTON1)->SetFont(&font_1);
	GetDlgItem(IDC_BUTTON2)->SetFont(&font_1);
	m_User.SetFont(&font_2);
	m_question.SetFont(&font_2);
	GetDlgItem(IDC_EDIT_Answer)->SetFont(&font_2);
	m_question.SetWindowTextW(question);
	m_User.SetWindowTextW(User);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void FindPasswd::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void FindPasswd::OnBnClickedButton1()
{
	UpdateData();
	if (m_answer == answer)
	{
		MessageBox(L"�����û���Ϊ��" + User + L"\n" + L"����Ϊ��" + Passwd);
		CDialog::OnOK();
	}
	else
	{
		MessageBox(L"�Բ���������Ĵ𰸲���ȷ��");
		m_answer = L"";
		UpdateData(FALSE);
	}
}



HBRUSH FindPasswd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (CTLCOLOR_STATIC == nCtlColor)//��̬���ֿؼ�
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}


void FindPasswd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect   rect;
	GetClientRect(&rect);
	Find_function.LoadBackgroud(dc, IDB_BITMAP_Search, rect);
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
}


BOOL FindPasswd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
    { 
		switch(pMsg->wParam)
        { case VK_RETURN: return TRUE; //���λس�
          case VK_ESCAPE: return TRUE; //����Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

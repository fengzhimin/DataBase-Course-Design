// Logining.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Logining.h"
#include "afxdialogex.h"

// Logining �Ի���

IMPLEMENT_DYNAMIC(Logining, CDialogEx)

Logining::Logining(CWnd* pParent /*=NULL*/)
	: CDialogEx(Logining::IDD, pParent)
{
	Cancel_Button = new CMFCButton;
	font.CreatePointFont(180, L"����");
}

Logining::~Logining()
{
	delete Cancel_Button;
	font.DeleteObject();
}

void Logining::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Logining, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &Logining::OnBnClickedButton1)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// Logining ��Ϣ�������


void Logining::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	KillTimer(1);
	CDialog::OnOK();
	CDialogEx::OnTimer(nIDEvent);
}


BOOL Logining::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	SetTimer(1, 1000, NULL);
	
	CRect rect = CRect(60, 280, 160, 320);
	Log_function.Create_Button(Cancel_Button, L"ȡ��", L"ȡ���û���¼", this, IDC_BUTTON1, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void Logining::OnBnClickedButton1()
{
	CDialog::OnCancel();
}


void Logining::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	Log_function.LoadBackgroud(dc, IDB_BITMAP_Logining, rect);
	
}



BOOL Logining::PreTranslateMessage(MSG* pMsg)
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

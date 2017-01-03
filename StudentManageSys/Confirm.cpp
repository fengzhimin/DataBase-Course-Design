// Confirm.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Confirm.h"
#include "afxdialogex.h"


// Confirm �Ի���

IMPLEMENT_DYNAMIC(Confirm, CDialogEx)

Confirm::Confirm(CWnd* pParent /*=NULL*/)
	: CDialogEx(Confirm::IDD, pParent)
	, m_confirm(_T(""))
{
	m_button1 = new CMFCButton;
	m_button2 = new CMFCButton;
	m_passwd = L"";
	m_static = L"";
	m_font.CreatePointFont(150, L"����");
}

Confirm::~Confirm()
{
	delete m_button1,m_button2;
	m_font.DeleteObject();
}

void Confirm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_confirm);
	DDX_Control(pDX, IDC_EDIT1, m_Cconfirm);
}


BEGIN_MESSAGE_MAP(Confirm, CDialogEx)
	ON_BN_CLICKED(IDC_CONFIRM_SAVE, &Confirm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CONFIRM_NOSAVE, &Confirm::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Confirm ��Ϣ�������


HBRUSH Confirm::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (CTLCOLOR_STATIC == nCtlColor)//��̬���ֿؼ�
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}
	return hbr;
}


void Confirm::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	m_function.LoadBackgroud(dc, IDB_BITMAP_CONFIRM, rect);
}


BOOL Confirm::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_CONFIRM)->SetFont(&m_font);
	CRect rect = CRect(70,100,170,150);
	m_function.Create_Button(m_button1, L"ȷ��", L"��֤����", this, IDC_CONFIRM_SAVE, m_font, rect, RGB(221,222,222), RGB(49,49,49), RGB(0, 0, 0));
	rect = CRect(200, 100, 300, 150);
	m_function.Create_Button(m_button2,L"����",L"�˳�",this, IDC_CONFIRM_NOSAVE, m_font, rect, RGB(221,222,222), RGB(49,49,49), RGB(0, 0, 0));
	GetDlgItem(IDC_STATIC_CONFIRM)->SetWindowTextW(m_static);
	if(m_static == L"�����뵱ǰ���룺")
		m_Cconfirm.SetPasswordChar('#');
	return TRUE;  // return TRUE unless you set the focus to a control
}

void Confirm::OnBnClickedButton1()
{
	UpdateData(TRUE);
	if(m_confirm == m_passwd)
		CDialog::OnOK();
	else
	{
		MessageBox(L"�Բ�������������벻��ȷ��");
		m_confirm = L"";
		UpdateData(FALSE);
	}
}

void Confirm::OnBnClickedButton2()
{
	CDialog::OnCancel();
}

BOOL Confirm::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
    { 
		switch(pMsg->wParam)
        { 
		  case VK_RETURN: return TRUE; //���λس�
          case VK_ESCAPE: return TRUE; //����Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

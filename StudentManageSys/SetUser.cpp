// SetUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "SetUser.h"
#include "afxdialogex.h"


// SetUser �Ի���

IMPLEMENT_DYNAMIC(SetUser, CDialogEx)

SetUser::SetUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(SetUser::IDD, pParent)
	, m_name(_T(""))
	, m_stuid(_T(""))
	, m_question(_T(""))
	, m_answer(_T(""))
	, m_newquestion(_T(""))
	, m_newanswer(_T(""))
{
	m_modify = new CMFCButton;
	m_cancel = new CMFCButton;
	m_point = 0;
	point1 = 0;
}

SetUser::~SetUser()
{
	m_font.DeleteObject();
	m_font1.DeleteObject();
	delete m_modify,m_cancel;
	m_connect->Close();
}

void SetUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_3, m_question);
	DDX_Control(pDX, IDC_CHECK2, m_modifyquestion);
	DDX_Text(pDX, IDC_EDIT1_6, m_name);
	DDX_Text(pDX, IDC_EDIT1_7, m_stuid);
	DDX_Text(pDX, IDC_EDIT1_4, m_newquestion);
	DDX_Text(pDX, IDC_EDIT1_5, m_newanswer);
	DDX_Control(pDX, IDC_EDIT1_4, m_edit_newquestion);
	DDX_Control(pDX, IDC_EDIT1_5, m_editnewanswer);
}


BEGIN_MESSAGE_MAP(SetUser, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK2, &SetUser::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SetUser::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_NOSAVE, &SetUser::OnBnClickedButton2)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// SetUser ��Ϣ�������

//�޸��ܱ�����
void SetUser::OnBnClickedCheck2()
{
	if(point1 == 0)
	{
		Confirm m_confirm;
		m_confirm.m_passwd = m_answer;
		m_confirm.m_static = L"��ǰ�ܱ��𰸣�";
		int confirm = m_confirm.DoModal();
		if(confirm == IDCANCEL)
		{
			m_modifyquestion.SetCheck(0);
			return;
		}
		else
			point1 = 1;
	}
	m_point = 1;
	if(m_modifyquestion.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT1_4)->EnableWindow(1);
	    GetDlgItem(IDC_EDIT1_5)->EnableWindow(1);
	}
	else
	{
		GetDlgItem(IDC_EDIT1_4)->SetWindowTextW(L"");
	    GetDlgItem(IDC_EDIT1_5)->SetWindowTextW(L"");
		GetDlgItem(IDC_EDIT1_4)->EnableWindow(0);
	    GetDlgItem(IDC_EDIT1_5)->EnableWindow(0);
		point1 = 0;
	}
}


BOOL SetUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_font.CreatePointFont(175, L"����");
	for(int i = 1057;i <= 1062; i++)
		GetDlgItem(i)->SetFont(&m_font);
	m_font1.CreatePointFont(150, L"����");
	GetDlgItem(IDC_EDIT1_6)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_7)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_3)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_4)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_5)->SetFont(&m_font1);
	CRect rect = CRect(200,290,290,328);
	m_function.Create_Button(m_modify, L"����", L"�޸ĸ����˺���Ϣ", this, IDC_BUTTON_SAVE, m_font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0,0,0));
	rect = CRect(360, 290, 450, 328);
	m_function.Create_Button(m_cancel,L"ȡ��",L"�����޸�",this, IDC_BUTTON_NOSAVE, m_font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0,0,0));

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
		MessageBox(e.Description());
		CDialog::OnCancel();
	}
	CString str_command;
	str_command = L"select * from Register R,User_Passwd U where R.ѧ�� = '" + m_Loginname + L"' and R.ѧ�� = U.ѧ��";
	m_record = m_connect->Execute(_bstr_t(str_command), NULL, adCmdText);
	m_name = m_record->GetCollect("�û���");
	m_stuid = m_record->GetCollect("ѧ��");
	m_question = m_record->GetCollect("����");
	m_answer = m_record->GetCollect("��");
	//GetDlgItem(IDC_EDIT1_6)->EnableWindow(1);
	//GetDlgItem(IDC_EDIT1_7)->EnableWindow(1);
	UpdateData(0);
	//Invalidate();
	//GetDlgItem(IDC_EDIT1_6)->EnableWindow(0);
	//GetDlgItem(IDC_EDIT1_7)->EnableWindow(0);
	m_edit_newquestion.SetLimitText(20);
	m_editnewanswer.SetLimitText(10);
	return TRUE;
}


HBRUSH SetUser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (IDC_CHECK1 == pWnd->GetDlgCtrlID() || IDC_CHECK2 == pWnd->GetDlgCtrlID())
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		BITMAP bmp;
		CBitmap bkImg;
		bkImg.LoadBitmap(IDB_BITMAP_SETUSER);
		bkImg.GetBitmap(&bmp);
		memDC.SelectObject(&bkImg);

		CRect rcRdo;
		pWnd->GetWindowRect(&rcRdo);
		ScreenToClient(&rcRdo);

		pDC->BitBlt(0, 0, rcRdo.Width(), rcRdo.Height(),
			&memDC, rcRdo.left, rcRdo.top, SRCCOPY);
		memDC.DeleteDC();

		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}

	if (CTLCOLOR_STATIC == nCtlColor)//��̬���ֿؼ�
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}

	return hbr;
}


void SetUser::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	m_function.LoadBackgroud(dc, IDB_BITMAP_SETUSER, rect);
}
//���水ť
void SetUser::OnBnClickedButton1()
{
	if(m_point == 0)
	{
		MessageBox(L"��û�����κεĸ��ģ�");
		return;
	}
	Confirm m_confirm;
	m_confirm.m_passwd = m_Loginpasswd;
	m_confirm.m_static = L"�����뵱ǰ���룺";
	int confirm = m_confirm.DoModal();
	if(confirm == IDOK)
	{
		UpdateData(1);
		CString str_command;
		if(m_point == 1)    //�Ƿ��޸��ܱ�����
		{
			if(m_newquestion != L"")
			{
				if(m_newanswer != L"")
				{
					try
					{
						str_command = L"update dbo.Register set ���� = '" + m_newquestion + "',�� = '" + m_newanswer + L"' where ѧ�� = '" + m_Loginname + L"'";
						m_connect->Execute(_bstr_t(str_command), NULL, adCmdText);
					}
					catch (_com_error e)
			        {
						MessageBox(e.Description());
						return ;
					}
				}
				else
					MessageBox(L"�������µĴ𰸣�");
			}
			else
				MessageBox(L"�������µ��ܱ����⣡");
		}
		MessageBox(L"�˺������޸ĳɹ���");
		CDialog::OnOK();
	}
}
//ȡ����ť
void SetUser::OnBnClickedButton2()
{
	CDialog::OnCancel();
}

BOOL SetUser::PreTranslateMessage(MSG* pMsg)
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

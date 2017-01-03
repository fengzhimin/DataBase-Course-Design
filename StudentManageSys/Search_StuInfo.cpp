// Search_StuInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_StuInfo.h"
#include "afxdialogex.h"


// Search_StuInfo �Ի���

IMPLEMENT_DYNAMIC(Search_StuInfo, CDialogEx)

Search_StuInfo::Search_StuInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(Search_StuInfo::IDD, pParent)
{
	font.CreatePointFont(150, L"����");
	m_button1 = new CMFCButton;
	m_button2 = new CMFCButton;
	m_Teacher_Student = 0;
}

Search_StuInfo::~Search_StuInfo()
{
	font.DeleteObject();
	delete m_button1,m_button2;
}

void Search_StuInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Stu_Info);
	DDX_Control(pDX, IDC_COMBO1, m_Stype);
}


BEGIN_MESSAGE_MAP(Search_StuInfo, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Search_StuInfo::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &Search_StuInfo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Search_StuInfo::OnBnClickedButton1)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Search_StuInfo ��Ϣ�������


void Search_StuInfo::OnCbnSelchangeCombo1()
{
	m_Stype.GetWindowTextW(m_str);
	if(m_Teacher_Student == 0)
		if (m_str == L"����ѧ��")
		{
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"������ѧ����ѧ�ţ�");
			Stu_Info.SetWindowTextW(L"");
		}
		else
		{
			Stu_Info.SetWindowTextW(L"");
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"������ѧ����������");
		}
	else
		if (m_str == L"����ѧ��")
		{
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"�������ʦ�ı�ţ�");
			Stu_Info.SetWindowTextW(L"");
		}
		else
		{
			Stu_Info.SetWindowTextW(L"");
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"�������ʦ��������");
		}
	Invalidate();
}


BOOL Search_StuInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	m_Stype.AddString(L"��������");
	m_Stype.AddString(L"����ѧ��");
	m_Stype.SetCurSel(0);
	m_Stype.SetFont(&font);
	Stu_Info.SetFont(&font);
	if(m_Teacher_Student == 0)
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"������ѧ����������");
	else
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"�������ʦ��������");
	CRect rect = CRect(100,210,170,250);
	if(m_Teacher_Student == 0)
		m_function.Create_Button(m_button1, L"����", L"�鿴ѧ���Ŀγ̱�", this, IDC_BUTTON1, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	else
		m_function.Create_Button(m_button1, L"����", L"�鿴��ʦ�Ŀγ̱�", this, IDC_BUTTON1, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	rect = CRect(220,210,290,250);
	m_function.Create_Button(m_button2,L"ȡ��",L"������ѯ",this, IDC_BUTTON2, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void Search_StuInfo::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void Search_StuInfo::OnBnClickedButton1()
{
	CString str_command;
	m_Stype.GetWindowTextW(m_str);
	Stu_Info.GetWindowTextW(str_Info);
	if (str_Info == L"")
	{
		if (m_str == L"����ѧ��")
			MessageBox(L"������Ҫ��ѯ��ѧ��!");
		else
			MessageBox(L"������Ҫ��ѯ������!");
		return;
	}

	::CoInitialize(NULL);
	try
	{
		m_connection.CreateInstance(__uuidof(Connection));
		m_connection->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
		m_connection->Open("", "", "", adConnectUnspecified);
		m_connection->DefaultDatabase = "USER";
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}

	if (m_str == L"����ѧ��")
	{
		//���κ��Ӻ������ַ���½
		for(int i = 0;i < str_Info.GetLength();++i)
			if(str_Info.GetAt(i) < 48 || str_Info.GetAt(i) > 57)
			{
				MessageBox(L"�Բ����������ѧ�Ų����ã�\n��ȷ��ѧ��Ϊ0-9������ɣ�");
				Stu_Info.SetWindowTextW(L"");
				return;
			}
		if(m_Teacher_Student == 0)
			str_command = L"select r.ѧ�� from Register r,User_Passwd u where r.ѧ�� ='" + str_Info + L"' and r.ѧ�� = u.ѧ�� and u.�û����� = 'ѧ��'";
		else
			str_command = L"select r.ѧ�� from Register r,User_Passwd u where r.ѧ�� ='" + str_Info + L"' and r.ѧ�� = u.ѧ�� and u.�û����� = '��ʦ'";
		m_recordset = m_connection->Execute(_bstr_t(str_command),NULL,adCmdText);
		if (m_recordset->adoEOF)
		{
			if(m_Teacher_Student == 0)
				MessageBox(L"�Բ����������ѧ��ѧ�Ų����ڣ� \n���������룡");
			else
				MessageBox(L"�Բ���������Ľ�ʦѧ�Ų����ڣ� \n���������룡");
			Stu_Info.SetWindowTextW(L"");
			return;
		}
		else
			CDialog::OnOK();
	}
	else
	{
		if(m_Teacher_Student == 0)
			str_command = L"select count(r.ѧ��) as c from Register r,User_Passwd u where r.�û��� ='" + str_Info + L"' and r.ѧ�� = u.ѧ�� and u.�û����� = 'ѧ��'";
		else
			str_command = L"select count(r.ѧ��) as c from Register r,User_Passwd u where r.�û��� ='" + str_Info + L"' and r.ѧ�� = u.ѧ�� and u.�û����� = '��ʦ'";
		m_recordset = m_connection->Execute(_bstr_t(str_command), NULL, adCmdText);
		CString m_str_count;
		str_command = m_recordset->GetCollect("c");
		if(m_recordset->adoEOF || str_command == L"0")
		{
			if(m_Teacher_Student == 0)
				MessageBox(L"�Բ����������ѧ�����������ڣ� \n���������룡");
			else
				MessageBox(L"�Բ���������Ľ�ʦ���������ڣ� \n���������룡");
			Stu_Info.SetWindowTextW(L"");
			return;
		}
		else
		{
			if(str_command == L"1")
				CDialog::OnOK();
			else
			{
				if(m_Teacher_Student == 0)
					m_str_count = L"�Բ��𣡴��� " + str_command + L" ��ѧ�����������������������ͬ��\n�밴��ѧ�Ž��в�ѯ��";
				else
					m_str_count = L"�Բ��𣡴��� " + str_command + L" ����ʦ���������������������ͬ��\n�밴��ѧ�Ž��в�ѯ��";
				m_Stype.SetCurSel(1);
				MessageBox(m_str_count);
				Stu_Info.SetWindowTextW(L"");
			}
		}
	}
}


BOOL Search_StuInfo::PreTranslateMessage(MSG* pMsg)
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


void Search_StuInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	m_function.LoadBackgroud(dc, IDB_BITMAP_SELECT, rect);
}

HBRUSH Search_StuInfo::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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

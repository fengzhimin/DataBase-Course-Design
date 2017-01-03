// Register.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Register.h"
#include "afxdialogex.h"


// Register �Ի���

IMPLEMENT_DYNAMIC(Register, CDialogEx)

Register::Register(CWnd* pParent /*=NULL*/)
	: CDialogEx(Register::IDD, pParent)
	, Reg_Name(_T(""))
	, Reg_Passwd(_T(""))
	, Reg_rePasswd(_T(""))
	, m_answer(_T(""))
	, m_stu_id(_T(""))
	, m_str_Stype(_T(""))
{
	button_Register = new CMFCButton;
	button_Cancel = new CMFCButton;
	font_1.CreatePointFont(150, L"����");
	font_2.CreatePointFont(190, L"����");
	m_point = 0;
	m_str = L"�����˺�";
	m_str1 = L"�������û�";
	m_str2 = L"ȡ�����û�����";
}

Register::~Register()
{
	font_1.DeleteObject();
	font_2.DeleteObject();
	delete button_Register, button_Cancel;
}

void Register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Reg_Name);
	DDX_Control(pDX, IDC_COMBO1, m_question);
	DDX_Text(pDX, IDC_EDIT4, m_answer);
	DDX_Control(pDX, IDC_RADIO_SHOW, m_ShowPasswd);
	DDX_Control(pDX, IDC_RADIO_HIDE, m_HidePasswd);
	DDX_Control(pDX, IDC_EDIT2, m_Passwd);
	DDX_Control(pDX, IDC_EDIT3, m_rePasswd);
	DDX_Control(pDX, IDC_EDIT6, m_edit);
	DDX_Control(pDX, IDC_EDIT4, m_edit_answer);
	DDX_Control(pDX, IDC_EDIT1, m_edit_name);
	DDX_Text(pDX, IDC_EDIT5, m_stu_id);
	DDX_Control(pDX, IDC_COMBO3, m_Stype);
	DDX_CBString(pDX, IDC_COMBO3, m_str_Stype);
}


BEGIN_MESSAGE_MAP(Register, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &Register::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Register::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_RADIO_SHOW, &Register::OnBnClickedRadioShow)
	ON_BN_CLICKED(IDC_RADIO_HIDE, &Register::OnBnClickedRadioHide)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_CBN_SELCHANGE(IDC_COMBO1, &Register::OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Register::OnCbnSelchangeCombo3)
END_MESSAGE_MAP()


// Register ��Ϣ�������

void Register::OnBnClickedButtonRegister()
{
	UpdateData();
	CString str_question;
	m_question.GetWindowTextW(str_question);
	if(str_question == L"�Զ���")   //�ж��Ƿ�Ϊ�Զ�������
		m_edit.GetWindowTextW(str_question);
	m_Passwd.GetWindowTextW(Reg_Passwd);
	m_rePasswd.GetWindowTextW(Reg_rePasswd);
	if(m_point == 1)
	{
		if (Reg_Name != L"")
		{
			CString str_Check = L"select count(�û���) as s from Register where �û��� = '" + Reg_Name + L"'";
			try
			{
				Reg_pRecordset = Reg_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
				str_Check = Reg_pRecordset->GetCollect("s");
				if (str_Check != L"0")
				{
					CString str;
					str = L"���� " + str_Check + L" ���� " + Reg_Name + L" ͬ����ѧ����";
					MessageBox(str,L"��ʾ");
				}
			}
			catch (_com_error e)
			{
				MessageBox(e.Description());
				CDialog::OnCancel();
				return ;
			}
			
			if (Reg_Passwd != L"")
			{
				if (Reg_rePasswd != L"")
				{
					if (Reg_Passwd.GetLength() < 6 || Reg_Passwd.GetLength() > 15)
					{
						MessageBox(L"��������볤�Ȳ�����Ҫ��");
						Reg_Passwd = Reg_rePasswd = L"";
						m_Passwd.SetWindowTextW(Reg_Passwd);
						m_rePasswd.SetWindowTextW(Reg_rePasswd);
						return ;
					}
					if (Reg_Passwd == Reg_rePasswd)
					{
						if (str_question != L"")
						{
							if (m_answer != L"")
							{
								CString strSQL = L"insert into Register values ('" + Reg_Name + L"','" + str_question + L"','" + m_answer + L"','" + m_stu_id + L"',0)";
								Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
								strSQL = L"insert into User_Passwd values ('" + m_stu_id + L"','" + Reg_Passwd + L"'," + L"0" + L",'" + m_str_Stype + L"',0,0,0)";
								Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
								
								Reg_pConnection->Close();
								::CoUninitialize();
								MessageBox(L"ע��ɹ���\n���ĵ�¼��Ϊ��" + m_stu_id + L"\n" + L"����Ϊ��" + Reg_Passwd);
								CDialog::OnCancel();
							}
							else
								MessageBox(L"����������Ĵ𰸣�");
						}
						else
							MessageBox(L"��ѡ��������һ���������⣡");
					}
					else
					{
						MessageBox(L"�Բ�����������������벻һ�£�\n ���������룡");
						Reg_rePasswd = L"";
						m_rePasswd.SetWindowTextW(Reg_rePasswd);
					}
				}
				else
					MessageBox(L"������ȷ�����룡");
			}
			else
				MessageBox(L"���벻��Ϊ�գ�");
		}
		else
			MessageBox(L"�û�������Ϊ�գ�");
	}
	else
	{
		if (Reg_Name != L"" && m_stu_id != L"")
		{
			//���κ��Ӻ������ַ�����
			for(int i = 0;i < m_stu_id.GetLength();++i)
				if(m_stu_id.GetAt(i) < 48 || m_stu_id.GetAt(i) > 57)
				{
					MessageBox(L"�Բ���������ĵ�¼�������ã�\n��ȷ�ĵ�¼��Ϊ0-9������ɣ�");
					m_stu_id = L"";
					UpdateData(FALSE);
					return;
				}
			CString str_Check = L"select * from Register where �û��� = '" + Reg_Name + L"' and ѧ�� = '" + m_stu_id + L"'";
			try
			{
				Reg_pRecordset = Reg_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
				if(Reg_pRecordset->adoEOF)
				{
					MessageBox(L"�Բ����������ѧ����ʱ�����ڣ�");
					Reg_Name = m_stu_id = L"";
					UpdateData(0);
					return ;
				}
				else
					str_Check = Reg_pRecordset->GetCollect("����״̬");
			}
			catch (_com_error e)
			{
				MessageBox(e.Description());
				CDialog::OnCancel();
				return ;
			}
			if(str_Check == L"1")
			{
				MessageBox(L"�Բ������˺��Ѿ������");
				return;
			}
			if (Reg_Passwd != L"")
			{
				if (Reg_rePasswd != L"")
				{
					if (Reg_Passwd.GetLength() < 6 || Reg_Passwd.GetLength() > 15)
					{
						MessageBox(L"��������볤�Ȳ�����Ҫ��");
						Reg_Passwd = Reg_rePasswd = L"";
						m_Passwd.SetWindowTextW(Reg_Passwd);
						m_rePasswd.SetWindowTextW(Reg_rePasswd);
						return ;
					}
					if (Reg_Passwd == Reg_rePasswd)
					{
						if (str_question != L"")
						{
							if (m_answer != L"")
							{
								CString strSQL = L"update Register set ���� = '" + str_question + L"',�� = '" + m_answer + L"',����״̬ = 1 where ѧ�� = '" + m_stu_id + L"'";
								Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
								strSQL = L"update User_Passwd set ���� = '" + Reg_Passwd + L"',����״̬ = 1 where ѧ�� = '" + m_stu_id + L"'";
								Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
								Reg_pConnection->Close();
								::CoUninitialize();
								MessageBox(L"����ɹ���\n���ĵ�¼��Ϊ��" + m_stu_id + L"\n" + L"����Ϊ��" + Reg_Passwd);
								CDialog::OnCancel();
							}
							else
								MessageBox(L"����������Ĵ𰸣�");
						}
						else
							MessageBox(L"��ѡ��������һ���������⣡");
					}
					else
					{
						MessageBox(L"�Բ�����������������벻һ�£�\n ���������룡");
						Reg_rePasswd = L"";
						m_rePasswd.SetWindowTextW(Reg_rePasswd);
					}
				}
				else
					MessageBox(L"������ȷ�����룡");
			}
			else
				MessageBox(L"���벻��Ϊ�գ�");
		}
		else
			MessageBox(L"�û�����ѧ�Ų���Ϊ�գ�");
	}
}


void Register::OnBnClickedButtonCancel()
{
	CDialog::OnCancel();
}

BOOL Register::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	GetDlgItem(IDC_STATIC_Name)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_Passwd)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_RePasswd)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_question)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_answer)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_ID)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC_STYPE)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC1)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC)->SetFont(&font_1);
	CRect rect_Register = CRect(145,435,250,480);
	Reg_function.Create_Button(button_Register,m_str, m_str1, this, IDC_BUTTON_REGISTER, font_2, rect_Register, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Cancel = CRect(345, 435, 450, 480);
	Reg_function.Create_Button(button_Cancel, L"ȡ��",m_str2, this, IDC_BUTTON_CANCEL, font_2, rect_Cancel, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	m_question.AddString(L"�ҵĸ��а�������˭��");
	m_question.AddString(L"�ҵ�˭��");
	m_question.AddString(L"������ʲôʱ�䣿");
	m_question.AddString(L"�ҵ������Ƕ��٣�");
	m_question.AddString(L"�ҵ�ĸ�׽�ʲô��");
	m_question.AddString(L"�Զ���");
	m_question.SetCurSel(2);

	m_edit_answer.SetLimitText(10);   //��������Ĵ𰸳��Ȳ��ܳ���10���ַ�
	m_edit_name.SetLimitText(10);

	GetDlgItem(IDC_EDIT1)->SetFont(&font_1);
	m_Passwd.SetFont(&font_1);
	m_rePasswd.SetFont(&font_1);
	GetDlgItem(IDC_EDIT4)->SetFont(&font_1);
	GetDlgItem(IDC_EDIT_ID)->SetFont(&font_1);
	m_Stype.SetFont(&font_1);
	m_Stype.AddString(L"ѧ��");
	m_Stype.AddString(L"��ʦ");
	m_Stype.SetCurSel(1);

	m_ShowPasswd.SetCheck(0);
	m_HidePasswd.SetCheck(1);
	m_Passwd.SetPasswordChar('*');
	m_Passwd.SetLimitText(16);
	m_rePasswd.SetPasswordChar('*');
	m_rePasswd.SetLimitText(16);

	::CoInitialize(NULL);
	try
	{
		Reg_pConnection.CreateInstance(__uuidof(Connection));
		Reg_pConnection->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
		Reg_pConnection->Open("", "", "", adConnectUnspecified);
		Reg_pConnection->DefaultDatabase = "USER";
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		CDialog::OnCancel();
	}

	//��ʾ�ǹ���Ա���ѧ���˺�
	if(m_point == 1)
	{
		m_Passwd.SetWindowTextW(L"000000");
		m_rePasswd.SetWindowTextW(L"000000");
		m_edit_answer.SetWindowTextW(L"000000");
		//GetDlgItem(IDC_EDIT_ID)->EnableWindow(0);
		CString strSQL;
		strSQL = L"select max(ѧ��) as maxid from User_Passwd where �û����� = 'ѧ��'";
		Reg_pRecordset = Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
		strSQL = Reg_pRecordset->GetCollect("maxid");
		int stu_id = _ttoi(strSQL);
		m_stu_id.Format(L"%d",++stu_id);
		GetDlgItem(IDC_EDIT_ID)->SetWindowTextW(m_stu_id);
	}
	else
	{
		//ѧ���������
		GetDlgItem(IDC_STATIC_STYPE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBO3)->ShowWindow(SW_HIDE);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}



void Register::OnBnClickedRadioShow()
{
	m_Passwd.GetWindowTextW(Reg_Passwd);
	m_rePasswd.GetWindowTextW(Reg_rePasswd);
	if (m_ShowPasswd.GetCheck() == 1)
	{
		m_HidePasswd.SetCheck(0);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetPasswordChar('\0');
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetPasswordChar('\0');
	}
	else
	{
		m_HidePasswd.SetCheck(1);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetPasswordChar('*');
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetPasswordChar('*');
	}
	m_Passwd.SetWindowTextW(Reg_Passwd);
	m_rePasswd.SetWindowTextW(Reg_rePasswd);
}


void Register::OnBnClickedRadioHide()
{
	m_Passwd.GetWindowTextW(Reg_Passwd);
	m_rePasswd.GetWindowTextW(Reg_rePasswd);
	if (m_HidePasswd.GetCheck() == 1)
	{
		m_ShowPasswd.SetCheck(0);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetPasswordChar('*');
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetPasswordChar('*');
	}
	else
	{
		m_ShowPasswd.SetCheck(1);
		((CEdit*)GetDlgItem(IDC_EDIT2))->SetPasswordChar('\0');
		((CEdit*)GetDlgItem(IDC_EDIT3))->SetPasswordChar('\0');
	}
	m_Passwd.SetWindowTextW(Reg_Passwd);
	m_rePasswd.SetWindowTextW(Reg_rePasswd);
}


HBRUSH Register::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (IDC_RADIO_SHOW == pWnd->GetDlgCtrlID() || IDC_RADIO_HIDE == pWnd->GetDlgCtrlID())
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		BITMAP bmp;
		CBitmap bkImg;
		bkImg.LoadBitmap(IDB_BITMAP_Register);
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


void Register::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	Reg_function.LoadBackgroud(dc, IDB_BITMAP_Register, rect);
}


BOOL Register::PreTranslateMessage(MSG* pMsg)
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

//�ܱ�����
void Register::OnCbnSelchangeCombo1()
{
	CString str;
	m_question.GetWindowTextW(str);
	if(str == L"�Զ���")
	{
		m_edit.SetLimitText(20);
		m_edit.EnableWindow(1);  //�������б�򸲸���Ͽ�
		m_edit.ShowWindow(SW_SHOW);
		m_question.EnableWindow(0);
		m_question.ShowWindow(SW_HIDE);
	}
}

void Register::OnCbnSelchangeCombo3()
{
	UpdateData();
	CString strSQL;
	if(m_str_Stype == L"��ʦ")
		strSQL = L"select max(ѧ��) as maxid from User_Passwd where �û����� = '��ʦ'";
	else
		strSQL = L"select max(ѧ��) as maxid from User_Passwd where �û����� = 'ѧ��'";
	Reg_pRecordset = Reg_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
	strSQL = Reg_pRecordset->GetCollect("maxid");
	int stu_id = _ttoi(strSQL);
	m_stu_id.Format(L"%d",++stu_id);
	GetDlgItem(IDC_EDIT_ID)->SetWindowTextW(m_stu_id);
}

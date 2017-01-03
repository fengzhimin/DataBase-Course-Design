// Stu_Login.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Stu_Login.h"
#include "afxdialogex.h"
#include "Register.h"
#include "FindPasswd.h"

// Stu_Login �Ի���

IMPLEMENT_DYNAMIC(Stu_Login, CDialogEx)

Stu_Login::Stu_Login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Stu_Login::IDD, pParent)
	, m_LName(_T(""))
	, m_LPasswd(_T(""))
	, m_LoginCount(3)
{
	Login_Button = new CMFCButton;
	Cancel_Button = new CMFCButton;
	Register_Button = new CMFCButton;
	Forget_Button = new CMFCButton;
	font.CreatePointFont(180, L"����");
}

Stu_Login::~Stu_Login()
{
	delete Login_Button, Cancel_Button, Register_Button, Forget_Button;
	font.DeleteObject();
}

void Stu_Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_LName);
	DDX_Text(pDX, IDC_EDIT_PASSWD, m_LPasswd);
	DDX_Control(pDX, IDC_COMBO1, m_LStyple);
	DDX_Control(pDX, IDC_CHECK1, m_RememberPasswd);
	DDX_Control(pDX, IDC_CHECK2, m_AutoLogin);
}


BEGIN_MESSAGE_MAP(Stu_Login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &Stu_Login::OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &Stu_Login::OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_FORGET, &Stu_Login::OnBnClickedButtonForget)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &Stu_Login::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_CHECK1, &Stu_Login::OnBnClickedCheck1)
	ON_WM_CTLCOLOR()
ON_WM_ERASEBKGND()
ON_CBN_SELCHANGE(IDC_COMBO1, &Stu_Login::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// Stu_Login ��Ϣ�������


BOOL Stu_Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_Login);
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_LStyple.AddString(L"��ʦ");
	m_LStyple.AddString(L"ѧ��");
	m_LStyple.AddString(L"����Ա");
	m_LStyple.SetCurSel(2);
	m_AutoLogin.EnableWindow(0);
	//���õ�½���еĸ�����ť�ؼ�
	CRect rect_Login = CRect(153, 328, 263, 367);
	function_button.Create_Button(Login_Button, L"��½", L"�û���¼", this, IDC_BUTTON_LOGIN, font, rect_Login, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Cancel = CRect(353, 328, 463, 367);
	function_button.Create_Button(Cancel_Button, L"ȡ��", L"ȡ���û���¼", this, IDC_BUTTON_CANCEL, font, rect_Cancel, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Register = CRect(445, 83, 547, 117);
	function_button.Create_Button(Register_Button, L"����", L"�����û�", this, IDC_BUTTON_REGISTER, font, rect_Register, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Forget = CRect(445, 130, 547, 165);
	function_button.Create_Button(Forget_Button, L"��������", L"�һ�����", this, IDC_BUTTON_FORGET, font, rect_Forget, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	
	::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance(__uuidof(Connection));
		/*CString str_connect;
		str_connect.Format(_T("Provider = SQLOLEDB.1;User ID = sa;Password = fzm;server=10.253.173.39;Data Source = USER"));
		m_pConnection->Open((_bstr_t)str_connect, "", "", adConnectUnspecified);*/
		m_pConnection->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
		m_pConnection->Open("", "", "", adConnectUnspecified);
		m_pConnection->DefaultDatabase = "USER";
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		CDialog::OnCancel();
	}
	//�Զ���¼�ͼ�ס�����ʵ��
	CString str_Name, str_Passwd,str_Stype;
	if (!m_Remember_Auto.Open(L"remember_auto.txt", CFile::typeBinary | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
	{
		MessageBox(L"�����remember_auto.txt�ļ�ʱ����", L"����", MB_OK | MB_ICONWARNING);
		CDialog::OnCancel();
		return false;
	}
	else
	{
		if (m_Remember_Auto.ReadString(str_Name) && m_Remember_Auto.ReadString(str_Passwd) && m_Remember_Auto.ReadString(str_Stype))
		{
			CString str_ChangeName = str_Name.Left(str_Name.GetLength() - 1);  //ȥ���ַ�����β��\r�ַ�
			CString str_ChangePasswd = str_Passwd.Left(str_Passwd.GetLength() - 1);
			CString str_ChangeStyle = str_Stype.Left(str_Stype.GetLength() - 1);
			CString  str = L"select * from User_Passwd where ѧ�� = '" + str_ChangeName + L"'";
			pRecordset = m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			//��ֹ��Ϊ�޸�remember_auto.txt�ļ�
			if (!pRecordset->adoEOF)
			{
				m_LName = pRecordset->GetCollect("ѧ��");
				m_LPasswd = pRecordset->GetCollect("����");
				m_RememberPasswd.SetCheck(1);
				if (str_ChangeStyle == L"ѧ��")
				   m_LStyple.SetCurSel(2);
				else
					if (str_ChangeStyle == L"��ʦ")
					   m_LStyple.SetCurSel(1);
					else
						{
						   m_LStyple.SetCurSel(0);
						   GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_HIDE);
						}
				m_AutoLogin.EnableWindow(1);
				if (int(pRecordset->GetCollect("�Զ���¼")) == 1)
				{
					m_AutoLogin.SetCheck(1);
					//��ֹ��Ϊ�޸�remember_auto.txt�ļ�
					if (m_LPasswd == str_ChangePasswd)
					{
						Logining lg;
						this->ShowWindow(SW_HIDE);
						if (lg.DoModal() != IDCANCEL)
						{
							if (int(pRecordset->GetCollect("��½״̬")) == 1)
							{
								MessageBox(L"�Բ�����������˺����ڵ�½�У�");
								UpdateData(FALSE);
								m_Remember_Auto.Close();
								return FALSE;
							}
							str = L"update User_Passwd set ��½״̬ = 1 where ѧ�� = '" + m_LName + L"'";
							m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
							str = L"select * from Register where ѧ�� = '" + m_LName + L"'";
							pRecordset = m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
							m_str_name = pRecordset->GetCollect("�û���");
							MessageBox(L"��½�ɹ�!");
							/*CString m_str,str1;
							m_str = m_LName;
							str1 = pRecordset->GetCollect("�û�����");*/
							//this->ShowWindow(SW_SHOW);
							//CDialog::OnOK();  //�����Ի��� Ϊʲô��ʱm_LName��m_LPasswd������ֵΪ��
							//m_LName = m_str;
							//str_stype = str1;
							//��ӵ�½�ɹ������
						}
						else
							this->ShowWindow(SW_SHOW);
					}
					else
					{
						MessageBox(L"�Բ����������벻��ȷ��");
						m_LPasswd = str_ChangePasswd;
					}
				}
				UpdateData(FALSE);
			}
			else
			{
				MessageBox(L"�Բ�����������û�������ȷ��");
				m_LName = str_ChangeName;
				UpdateData(FALSE);
			}
		}
		m_Remember_Auto.Close();
		return TRUE;
	}
	
	//::CoInitialize(NULL);
	//HRESULT hr = NULL;
	//try
	//{
	//	hr = m_pConnection.CreateInstance("ADODB.Connection");///���� Connection ����   
	//
	//	if (SUCCEEDED(hr))
	//	{
	//		//��¼���ݿⲢ�������ݿ�DBCourse  
	//		//�����server����д��127.0.0.1��������δָ���Ĵ���Ӧ��д��Sql server��¼����ķ���������  
	//		m_pConnection->ConnectionString = "driver={SQL Server};server=10.253.173.39;uid=sa;pwd=fzm;";
	//		m_pConnection->Open("", "", "", adConnectUnspecified);
	//		m_pConnection->DefaultDatabase = "USER";
	//	}
	//	else
	//	{
	//		AfxMessageBox(TEXT("���� Connection ����ʧ��"));///��ʾ������Ϣ  
	//		return FALSE;
	//	}
	//}
	//catch (_com_error e)///��׽�쳣     
	//{
	//	CString errormessage;
	//	errormessage.Format(TEXT("�������ݿ�ʧ�� !\r\n ������Ϣ :%s(%ld)"), e.ErrorMessage(), e.Error());
	//	AfxMessageBox(errormessage);///��ʾ������Ϣ    
	//	return FALSE;
	//}
	//_bstr_t sql;
	//CString sql = L"select ����,���� from Test where ���� = '��־��'";
	//pRecordset.CreateInstance(__uuidof(Recordset));
	//try
	//{
	//	//pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	//	pRecordset = m_pConnection->Execute(_bstr_t(sql), NULL, adCmdText);
	//	
	//	while (!pRecordset->adoEOF)
	//	{
 //      // CString tem = (TCHAR*)(_bstr_t)pRecordset->GetFields()->GetItem("����")->Value;
	//	//CString tem1 = (TCHAR*)(_bstr_t)pRecordset->GetFields()->GetItem("����")->Value;
	//		CString tem = pRecordset->GetCollect("����");
	//	CString tem1 = pRecordset->GetCollect("����");
	//	MessageBox(L"�û����ǣ�" + tem + L"  " + "���룺" + tem1);
	//	pRecordset->MoveNext();
	//	}
	//	
	//}
	//catch (_com_error e)
	//{
	//	MessageBox(e.Description());
	//}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//ȡ����¼��ť
void Stu_Login::OnBnClickedButtonCancel()
{
	::CoUninitialize();
	m_pConnection->Close();
	CDialog::OnCancel();
}

//�����û�
void Stu_Login::OnBnClickedButtonRegister()
{
	this->ShowWindow(SW_HIDE);
	Register reg_user;
	reg_user.DoModal();
	this->ShowWindow(SW_SHOW);
}

//��������
void Stu_Login::OnBnClickedButtonForget()
{
	UpdateData();
	//���κ��Ӻ������ַ���½
	for(int i = 0;i < m_LName.GetLength();++i)
		if(m_LName.GetAt(i) < 48 || m_LName.GetAt(i) > 57)
		{
			MessageBox(L"�Բ���������ĵ�¼�������ã�\n��ȷ�ĵ�¼��Ϊ0-9������ɣ�");
			m_LName = L"";
			UpdateData(FALSE);
			return;
		}
	CString str_Check = L"select * from Register where ѧ�� = '" + m_LName + L"'";
	try
	{
		pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
		if(pRecordset->adoEOF)
		{
			MessageBox(L"�Բ����������ѧ�Ų����ڣ�");
			UpdateData(0);
			return ;
		}
		else
			str_Check = pRecordset->GetCollect("����״̬");
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		CDialog::OnCancel();
		return ;
	}
	if(str_Check == L"0")
	{
		MessageBox(L"�Բ��𣡸��˺ſ���û�б�������ȼ��");
		CDialog::OnCancel();
		return;
	}
	if (m_LName != L"")
	{
		CString str_Check = L"select * from Register R,User_Passwd U where R.ѧ�� = '" + m_LName + L"' and R.ѧ�� = U.ѧ��";
		try
		{
			pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
			if (pRecordset->adoEOF)
			{
				MessageBox(L"�Բ��𣡸��û������ڣ�");
				m_LName = m_LPasswd = L"";
				UpdateData(FALSE);
				return;
			}
			else
			{
				FindPasswd Fpasswd;
				Fpasswd.question = pRecordset->GetCollect("����");
				Fpasswd.User = pRecordset->GetCollect("ѧ��");
				Fpasswd.answer = pRecordset->GetCollect("��");
				Fpasswd.Passwd = pRecordset->GetCollect("����");
				Fpasswd.DoModal();
			}
		}
		catch (_com_error e)
		{
			MessageBox(e.Description());
			CDialog::OnCancel();
			return;
		}
	}
	else
		MessageBox(L"���������û�����");
}

//��¼��ť
void Stu_Login::OnBnClickedButtonLogin()
{	
	UpdateData();
	if (m_LName != L"")
	{
		if (m_LPasswd != L"")
		{
			Logining lg;
			this->ShowWindow(SW_HIDE);
			if (lg.DoModal() == IDCANCEL)
			{
				this->ShowWindow(SW_SHOW);
				return;
			}
			else
			{
				m_LStyple.GetWindowTextW(str_stype);
				//���κ��Ӻ������ַ���½
				for(int i = 0;i < m_LName.GetLength();++i)
					if(m_LName.GetAt(i) < 48 || m_LName.GetAt(i) > 57)
					{
						MessageBox(L"�Բ���������ĵ�¼�������ã�\n��ȷ�ĵ�¼��Ϊ0-9������ɣ�");
						m_LName = m_LPasswd = L"";
						UpdateData(FALSE);
						this->ShowWindow(SW_SHOW);
						return;
					}
				CString str_Check = L"select * from User_Passwd where ѧ�� = '" + m_LName + L"' and �û����� = '" + str_stype + L"' and ����״̬ = 1";
				try
				{
					pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
					if (pRecordset->adoEOF)
					{
						MessageBox(L"�Բ��𣡸��û������ڻ�����û�б����");
						m_LName = m_LPasswd = L"";
						UpdateData(FALSE);
						this->ShowWindow(SW_SHOW);
						return;
					}
					else
					{
						if (int(pRecordset->GetCollect("��½״̬")) == 1)
						{
							MessageBox(L"�Բ�����������˺����ڵ�½�У�");
							this->ShowWindow(SW_SHOW);
							return;
						}
						if (CString(pRecordset->GetCollect("����")) != m_LPasswd)
						{
							//�жϵ�½����
							if (--m_LoginCount != 0)
							{
								CString str;
								str.Format(L"%d", m_LoginCount);
								MessageBox(L"�Բ�������������벻��ȷ��\n������" + str + L"�ε�½���ᣡ");
								this->ShowWindow(SW_SHOW);
							}
							else
							{
								MessageBox(L"���벻��ȷ,�����µ�½��");
								CDialog::OnCancel();
							}
							m_LPasswd = L"";
							UpdateData(FALSE);
							return;
						}
						else
						{
							//��ס��¼ѡ��
							if (!m_Remember_Auto.Open(L"remember_auto.txt", CFile::typeBinary | CFile::modeCreate | CFile::modeReadWrite))
							{
								MessageBox(L"�����remember_auto.txt�ļ�ʱ����", L"����", MB_OK | MB_ICONWARNING);
								CDialog::OnCancel();
								return;
							}
							if (m_RememberPasswd.GetCheck())
							{
								m_Remember_Auto.WriteString(m_LName + L"\r\n");
								m_Remember_Auto.WriteString(m_LPasswd + L"\r\n");
								m_Remember_Auto.WriteString(str_stype + L"\r\n");
								str_Check = L"update User_Passwd set ��½״̬ = 1,��ס���� = 1,�Զ���¼ = 0 where ѧ�� = '" + m_LName + L"'";
								if (m_AutoLogin.GetCheck() == 1)
									str_Check = L"update User_Passwd set ��½״̬ = 1,��ס���� = 1,�Զ���¼ = 1 where ѧ�� = '" + m_LName + L"'";
							}
							else
								str_Check = L"update User_Passwd set ��½״̬ = 1,��ס���� = 0,�Զ���¼ = 0 where ѧ�� = '" + m_LName + L"'";
							m_Remember_Auto.Close();
							m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
							str_Check = L"select �û��� from Register where ѧ�� = '" + m_LName + L"'";
							pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
							m_str_name = pRecordset->GetCollect("�û���");
							m_pConnection->Close();
							MessageBox(L"��½�ɹ�!");
							CDialog::OnOK();
							//��ӵ�½�ɹ������
						}
					}
				}
				catch (_com_error e)
				{
					MessageBox(e.Description());
					CDialog::OnCancel();
					return;
				}
			}
		}
		else
			MessageBox(L"���벻��Ϊ�գ�");
	}
	else
		MessageBox(L"�������û�����");
}


void Stu_Login::OnBnClickedCheck1()
{
	if (m_RememberPasswd.GetCheck() == 1)
	    m_AutoLogin.EnableWindow(1);
	else
	{
		m_AutoLogin.SetCheck(0);
		m_AutoLogin.EnableWindow(0);
	}	
}



HBRUSH Stu_Login::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if (IDC_CHECK1 == pWnd->GetDlgCtrlID() || IDC_CHECK2 == pWnd->GetDlgCtrlID())
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		BITMAP bmp;
		CBitmap bkImg;
		bkImg.LoadBitmap(IDB_BITMAP_Login);
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
		pDC->SetTextColor(RGB(0, 0, 0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}
	//if (CTLCOLOR_BTN == nCtlColor)
	//{
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SetTextColor(RGB(255, 0, 0));
	//	pDC->SetBkColor(RGB(253, 234, 3));
	//	return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	//}

	return hbr;
}



BOOL Stu_Login::OnEraseBkgnd(CDC* pDC)
{
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	BITMAP bmp;
	CBitmap bkImg;
	bkImg.LoadBitmap(IDB_BITMAP_Login);
	bkImg.GetBitmap(&bmp);
	memDC.SelectObject(&bkImg);

	SetWindowPos(NULL, 0, 0, bmp.bmWidth, bmp.bmHeight, SWP_NOMOVE | SWP_NOZORDER);
	CRect rect;
	GetClientRect(&rect);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),
		&memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	memDC.DeleteDC();
	CenterWindow();
	return TRUE;
}


BOOL Stu_Login::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
    { switch(pMsg->wParam)
        { case VK_RETURN: return TRUE; //���λس�
          case VK_ESCAPE: return TRUE; //����Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

void Stu_Login::OnCbnSelchangeCombo1()
{
	CString str;
	m_LStyple.GetWindowTextW(str);
	if(str == L"����Ա")
		GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_HIDE);
	else
		GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_SHOW);
}


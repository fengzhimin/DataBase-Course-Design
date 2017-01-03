// Stu_Login.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Stu_Login.h"
#include "afxdialogex.h"
#include "Register.h"
#include "FindPasswd.h"

// Stu_Login 对话框

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
	font.CreatePointFont(180, L"宋体");
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


// Stu_Login 消息处理程序


BOOL Stu_Login::OnInitDialog()
{
	CDialog::OnInitDialog();

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BITMAP_Login);
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();
	// TODO:  在此添加额外的初始化
	m_LStyple.AddString(L"教师");
	m_LStyple.AddString(L"学生");
	m_LStyple.AddString(L"管理员");
	m_LStyple.SetCurSel(2);
	m_AutoLogin.EnableWindow(0);
	//设置登陆框中的各个按钮控件
	CRect rect_Login = CRect(153, 328, 263, 367);
	function_button.Create_Button(Login_Button, L"登陆", L"用户登录", this, IDC_BUTTON_LOGIN, font, rect_Login, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Cancel = CRect(353, 328, 463, 367);
	function_button.Create_Button(Cancel_Button, L"取消", L"取消用户登录", this, IDC_BUTTON_CANCEL, font, rect_Cancel, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Register = CRect(445, 83, 547, 117);
	function_button.Create_Button(Register_Button, L"激活", L"激活用户", this, IDC_BUTTON_REGISTER, font, rect_Register, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	CRect rect_Forget = CRect(445, 130, 547, 165);
	function_button.Create_Button(Forget_Button, L"忘记密码", L"找回密码", this, IDC_BUTTON_FORGET, font, rect_Forget, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	
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
	//自动登录和记住密码的实现
	CString str_Name, str_Passwd,str_Stype;
	if (!m_Remember_Auto.Open(L"remember_auto.txt", CFile::typeBinary | CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate))
	{
		MessageBox(L"程序打开remember_auto.txt文件时出错！", L"警告", MB_OK | MB_ICONWARNING);
		CDialog::OnCancel();
		return false;
	}
	else
	{
		if (m_Remember_Auto.ReadString(str_Name) && m_Remember_Auto.ReadString(str_Passwd) && m_Remember_Auto.ReadString(str_Stype))
		{
			CString str_ChangeName = str_Name.Left(str_Name.GetLength() - 1);  //去掉字符串结尾的\r字符
			CString str_ChangePasswd = str_Passwd.Left(str_Passwd.GetLength() - 1);
			CString str_ChangeStyle = str_Stype.Left(str_Stype.GetLength() - 1);
			CString  str = L"select * from User_Passwd where 学号 = '" + str_ChangeName + L"'";
			pRecordset = m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			//防止人为修改remember_auto.txt文件
			if (!pRecordset->adoEOF)
			{
				m_LName = pRecordset->GetCollect("学号");
				m_LPasswd = pRecordset->GetCollect("密码");
				m_RememberPasswd.SetCheck(1);
				if (str_ChangeStyle == L"学生")
				   m_LStyple.SetCurSel(2);
				else
					if (str_ChangeStyle == L"教师")
					   m_LStyple.SetCurSel(1);
					else
						{
						   m_LStyple.SetCurSel(0);
						   GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_HIDE);
						}
				m_AutoLogin.EnableWindow(1);
				if (int(pRecordset->GetCollect("自动登录")) == 1)
				{
					m_AutoLogin.SetCheck(1);
					//防止人为修改remember_auto.txt文件
					if (m_LPasswd == str_ChangePasswd)
					{
						Logining lg;
						this->ShowWindow(SW_HIDE);
						if (lg.DoModal() != IDCANCEL)
						{
							if (int(pRecordset->GetCollect("登陆状态")) == 1)
							{
								MessageBox(L"对不起！您输入的账号正在登陆中！");
								UpdateData(FALSE);
								m_Remember_Auto.Close();
								return FALSE;
							}
							str = L"update User_Passwd set 登陆状态 = 1 where 学号 = '" + m_LName + L"'";
							m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
							str = L"select * from Register where 学号 = '" + m_LName + L"'";
							pRecordset = m_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
							m_str_name = pRecordset->GetCollect("用户名");
							MessageBox(L"登陆成功!");
							/*CString m_str,str1;
							m_str = m_LName;
							str1 = pRecordset->GetCollect("用户类型");*/
							//this->ShowWindow(SW_SHOW);
							//CDialog::OnOK();  //结束对话框 为什么此时m_LName和m_LPasswd变量的值为空
							//m_LName = m_str;
							//str_stype = str1;
							//添加登陆成功后代码
						}
						else
							this->ShowWindow(SW_SHOW);
					}
					else
					{
						MessageBox(L"对不起！您的密码不正确！");
						m_LPasswd = str_ChangePasswd;
					}
				}
				UpdateData(FALSE);
			}
			else
			{
				MessageBox(L"对不起！您输入的用户名不正确！");
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
	//	hr = m_pConnection.CreateInstance("ADODB.Connection");///创建 Connection 对象   
	//
	//	if (SUCCEEDED(hr))
	//	{
	//		//登录数据库并连接数据库DBCourse  
	//		//这里的server不能写成127.0.0.1否则会出现未指定的错误，应该写成Sql server登录界面的服务器名称  
	//		m_pConnection->ConnectionString = "driver={SQL Server};server=10.253.173.39;uid=sa;pwd=fzm;";
	//		m_pConnection->Open("", "", "", adConnectUnspecified);
	//		m_pConnection->DefaultDatabase = "USER";
	//	}
	//	else
	//	{
	//		AfxMessageBox(TEXT("创建 Connection 对象失败"));///显示错误信息  
	//		return FALSE;
	//	}
	//}
	//catch (_com_error e)///捕捉异常     
	//{
	//	CString errormessage;
	//	errormessage.Format(TEXT("连接数据库失败 !\r\n 错误信息 :%s(%ld)"), e.ErrorMessage(), e.Error());
	//	AfxMessageBox(errormessage);///显示错误信息    
	//	return FALSE;
	//}
	//_bstr_t sql;
	//CString sql = L"select 姓名,密码 from Test where 姓名 = '冯志芳'";
	//pRecordset.CreateInstance(__uuidof(Recordset));
	//try
	//{
	//	//pRecordset->Open(_bstr_t(sql), m_pConnection.GetInterfacePtr(), adOpenStatic, adLockOptimistic, adCmdText);
	//	pRecordset = m_pConnection->Execute(_bstr_t(sql), NULL, adCmdText);
	//	
	//	while (!pRecordset->adoEOF)
	//	{
 //      // CString tem = (TCHAR*)(_bstr_t)pRecordset->GetFields()->GetItem("姓名")->Value;
	//	//CString tem1 = (TCHAR*)(_bstr_t)pRecordset->GetFields()->GetItem("密码")->Value;
	//		CString tem = pRecordset->GetCollect("姓名");
	//	CString tem1 = pRecordset->GetCollect("密码");
	//	MessageBox(L"用户名是：" + tem + L"  " + "密码：" + tem1);
	//	pRecordset->MoveNext();
	//	}
	//	
	//}
	//catch (_com_error e)
	//{
	//	MessageBox(e.Description());
	//}
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

//取消登录按钮
void Stu_Login::OnBnClickedButtonCancel()
{
	::CoUninitialize();
	m_pConnection->Close();
	CDialog::OnCancel();
}

//激活用户
void Stu_Login::OnBnClickedButtonRegister()
{
	this->ShowWindow(SW_HIDE);
	Register reg_user;
	reg_user.DoModal();
	this->ShowWindow(SW_SHOW);
}

//忘记密码
void Stu_Login::OnBnClickedButtonForget()
{
	UpdateData();
	//屏蔽汉子和特殊字符登陆
	for(int i = 0;i < m_LName.GetLength();++i)
		if(m_LName.GetAt(i) < 48 || m_LName.GetAt(i) > 57)
		{
			MessageBox(L"对不起！您输入的登录名不可用！\n正确的登录名为0-9数字组成！");
			m_LName = L"";
			UpdateData(FALSE);
			return;
		}
	CString str_Check = L"select * from Register where 学号 = '" + m_LName + L"'";
	try
	{
		pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
		if(pRecordset->adoEOF)
		{
			MessageBox(L"对不起！您输入的学号不存在！");
			UpdateData(0);
			return ;
		}
		else
			str_Check = pRecordset->GetCollect("激活状态");
	}
	catch (_com_error e)
	{
		MessageBox(e.Description());
		CDialog::OnCancel();
		return ;
	}
	if(str_Check == L"0")
	{
		MessageBox(L"对不起！该账号可能没有被激活！请先激活！");
		CDialog::OnCancel();
		return;
	}
	if (m_LName != L"")
	{
		CString str_Check = L"select * from Register R,User_Passwd U where R.学号 = '" + m_LName + L"' and R.学号 = U.学号";
		try
		{
			pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
			if (pRecordset->adoEOF)
			{
				MessageBox(L"对不起！该用户不存在！");
				m_LName = m_LPasswd = L"";
				UpdateData(FALSE);
				return;
			}
			else
			{
				FindPasswd Fpasswd;
				Fpasswd.question = pRecordset->GetCollect("问题");
				Fpasswd.User = pRecordset->GetCollect("学号");
				Fpasswd.answer = pRecordset->GetCollect("答案");
				Fpasswd.Passwd = pRecordset->GetCollect("密码");
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
		MessageBox(L"请先输入用户名！");
}

//登录按钮
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
				//屏蔽汉子和特殊字符登陆
				for(int i = 0;i < m_LName.GetLength();++i)
					if(m_LName.GetAt(i) < 48 || m_LName.GetAt(i) > 57)
					{
						MessageBox(L"对不起！您输入的登录名不可用！\n正确的登录名为0-9数字组成！");
						m_LName = m_LPasswd = L"";
						UpdateData(FALSE);
						this->ShowWindow(SW_SHOW);
						return;
					}
				CString str_Check = L"select * from User_Passwd where 学号 = '" + m_LName + L"' and 用户类型 = '" + str_stype + L"' and 激活状态 = 1";
				try
				{
					pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
					if (pRecordset->adoEOF)
					{
						MessageBox(L"对不起！该用户不存在或者是没有被激活！");
						m_LName = m_LPasswd = L"";
						UpdateData(FALSE);
						this->ShowWindow(SW_SHOW);
						return;
					}
					else
					{
						if (int(pRecordset->GetCollect("登陆状态")) == 1)
						{
							MessageBox(L"对不起！您输入的账号正在登陆中！");
							this->ShowWindow(SW_SHOW);
							return;
						}
						if (CString(pRecordset->GetCollect("密码")) != m_LPasswd)
						{
							//判断登陆数次
							if (--m_LoginCount != 0)
							{
								CString str;
								str.Format(L"%d", m_LoginCount);
								MessageBox(L"对不起您输入的密码不正确！\n您还有" + str + L"次登陆机会！");
								this->ShowWindow(SW_SHOW);
							}
							else
							{
								MessageBox(L"密码不正确,请重新登陆！");
								CDialog::OnCancel();
							}
							m_LPasswd = L"";
							UpdateData(FALSE);
							return;
						}
						else
						{
							//记住登录选择
							if (!m_Remember_Auto.Open(L"remember_auto.txt", CFile::typeBinary | CFile::modeCreate | CFile::modeReadWrite))
							{
								MessageBox(L"程序打开remember_auto.txt文件时出错！", L"警告", MB_OK | MB_ICONWARNING);
								CDialog::OnCancel();
								return;
							}
							if (m_RememberPasswd.GetCheck())
							{
								m_Remember_Auto.WriteString(m_LName + L"\r\n");
								m_Remember_Auto.WriteString(m_LPasswd + L"\r\n");
								m_Remember_Auto.WriteString(str_stype + L"\r\n");
								str_Check = L"update User_Passwd set 登陆状态 = 1,记住密码 = 1,自动登录 = 0 where 学号 = '" + m_LName + L"'";
								if (m_AutoLogin.GetCheck() == 1)
									str_Check = L"update User_Passwd set 登陆状态 = 1,记住密码 = 1,自动登录 = 1 where 学号 = '" + m_LName + L"'";
							}
							else
								str_Check = L"update User_Passwd set 登陆状态 = 1,记住密码 = 0,自动登录 = 0 where 学号 = '" + m_LName + L"'";
							m_Remember_Auto.Close();
							m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
							str_Check = L"select 用户名 from Register where 学号 = '" + m_LName + L"'";
							pRecordset = m_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
							m_str_name = pRecordset->GetCollect("用户名");
							m_pConnection->Close();
							MessageBox(L"登陆成功!");
							CDialog::OnOK();
							//添加登陆成功后代码
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
			MessageBox(L"密码不能为空！");
	}
	else
		MessageBox(L"请输入用户名！");
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

		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}
	if (CTLCOLOR_STATIC == nCtlColor)//静态文字控件
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}
	//if (CTLCOLOR_BTN == nCtlColor)
	//{
	//	pDC->SetBkMode(TRANSPARENT);
	//	pDC->SetTextColor(RGB(255, 0, 0));
	//	pDC->SetBkColor(RGB(253, 234, 3));
	//	return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
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
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
    { switch(pMsg->wParam)
        { case VK_RETURN: return TRUE; //屏蔽回车
          case VK_ESCAPE: return TRUE; //屏蔽Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

void Stu_Login::OnCbnSelchangeCombo1()
{
	CString str;
	m_LStyple.GetWindowTextW(str);
	if(str == L"管理员")
		GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_HIDE);
	else
		GetDlgItem(IDC_BUTTON_REGISTER)->ShowWindow(SW_SHOW);
}


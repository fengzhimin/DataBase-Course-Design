// SetUser.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "SetUser.h"
#include "afxdialogex.h"


// SetUser 对话框

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


// SetUser 消息处理程序

//修改密保问题
void SetUser::OnBnClickedCheck2()
{
	if(point1 == 0)
	{
		Confirm m_confirm;
		m_confirm.m_passwd = m_answer;
		m_confirm.m_static = L"当前密保答案：";
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
	m_font.CreatePointFont(175, L"宋体");
	for(int i = 1057;i <= 1062; i++)
		GetDlgItem(i)->SetFont(&m_font);
	m_font1.CreatePointFont(150, L"宋体");
	GetDlgItem(IDC_EDIT1_6)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_7)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_3)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_4)->SetFont(&m_font1);
	GetDlgItem(IDC_EDIT1_5)->SetFont(&m_font1);
	CRect rect = CRect(200,290,290,328);
	m_function.Create_Button(m_modify, L"保存", L"修改个人账号信息", this, IDC_BUTTON_SAVE, m_font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0,0,0));
	rect = CRect(360, 290, 450, 328);
	m_function.Create_Button(m_cancel,L"取消",L"放弃修改",this, IDC_BUTTON_NOSAVE, m_font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0,0,0));

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
	str_command = L"select * from Register R,User_Passwd U where R.学号 = '" + m_Loginname + L"' and R.学号 = U.学号";
	m_record = m_connect->Execute(_bstr_t(str_command), NULL, adCmdText);
	m_name = m_record->GetCollect("用户名");
	m_stuid = m_record->GetCollect("学号");
	m_question = m_record->GetCollect("问题");
	m_answer = m_record->GetCollect("答案");
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

		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}

	if (CTLCOLOR_STATIC == nCtlColor)//静态文字控件
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
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
//保存按钮
void SetUser::OnBnClickedButton1()
{
	if(m_point == 0)
	{
		MessageBox(L"您没有做任何的更改！");
		return;
	}
	Confirm m_confirm;
	m_confirm.m_passwd = m_Loginpasswd;
	m_confirm.m_static = L"请输入当前密码：";
	int confirm = m_confirm.DoModal();
	if(confirm == IDOK)
	{
		UpdateData(1);
		CString str_command;
		if(m_point == 1)    //是否修改密保问题
		{
			if(m_newquestion != L"")
			{
				if(m_newanswer != L"")
				{
					try
					{
						str_command = L"update dbo.Register set 问题 = '" + m_newquestion + "',答案 = '" + m_newanswer + L"' where 学号 = '" + m_Loginname + L"'";
						m_connect->Execute(_bstr_t(str_command), NULL, adCmdText);
					}
					catch (_com_error e)
			        {
						MessageBox(e.Description());
						return ;
					}
				}
				else
					MessageBox(L"请输入新的答案！");
			}
			else
				MessageBox(L"请输入新的密保问题！");
		}
		MessageBox(L"账号资料修改成功！");
		CDialog::OnOK();
	}
}
//取消按钮
void SetUser::OnBnClickedButton2()
{
	CDialog::OnCancel();
}

BOOL SetUser::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
    { 
		switch(pMsg->wParam)
        { 
		  case VK_RETURN: return TRUE; //屏蔽回车
          case VK_ESCAPE: return TRUE; //屏蔽Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

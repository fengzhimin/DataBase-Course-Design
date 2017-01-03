// ModifyPasswd.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "ModifyPasswd.h"
#include "afxdialogex.h"


// ModifyPasswd 对话框

IMPLEMENT_DYNAMIC(ModifyPasswd, CDialogEx)

ModifyPasswd::ModifyPasswd(CWnd* pParent /*=NULL*/)
	: CDialogEx(ModifyPasswd::IDD, pParent)
	, m_strpasswd(_T(""))
	, m_strrepasswd(_T(""))
{
	font.CreatePointFont(120, L"宋体");
	font1.CreatePointFont(180, L"宋体");
	m_button1 = new CMFCButton;
	m_button2 = new CMFCButton;
}

ModifyPasswd::~ModifyPasswd()
{
	font.DeleteObject();
	font1.DeleteObject();
	delete m_button1,m_button2;
}

void ModifyPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_repasswd);
	DDX_Control(pDX, IDC_EDIT1, m_passwd);
	DDX_Text(pDX, IDC_EDIT1, m_strpasswd);
	DDX_Text(pDX, IDC_EDIT2, m_strrepasswd);
	DDX_Control(pDX, IDC_RADIO2_1, m_ShowPasswd);
	DDX_Control(pDX, IDC_RADIO2_2, m_HidePasswd);
}


BEGIN_MESSAGE_MAP(ModifyPasswd, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &ModifyPasswd::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_NOMODIFY, &ModifyPasswd::OnBnClickedButton2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_RADIO2_1, &ModifyPasswd::OnBnClickedRadio21)
	ON_BN_CLICKED(IDC_RADIO2_2, &ModifyPasswd::OnBnClickedRadio22)
END_MESSAGE_MAP()


// ModifyPasswd 消息处理程序


BOOL ModifyPasswd::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC2_1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2_2)->SetFont(&font);
	GetDlgItem(IDC_STATIC2_3)->SetFont(&font);
	m_passwd.SetLimitText(15);
	m_repasswd.SetLimitText(15);
	m_HidePasswd.SetCheck(1);
	CRect rect = CRect(130,220,230,270);
	m_function.Create_Button(m_button1, L"保存", L"修改账号登陆密码", this, IDC_BUTTON_MODIFY, font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	rect = CRect(290, 220, 390, 270);
	m_function.Create_Button(m_button2,L"取消",L"放弃修改",this, IDC_BUTTON_NOMODIFY, font1, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));

	return TRUE;  // return TRUE unless you set the focus to a control
}


BOOL ModifyPasswd::PreTranslateMessage(MSG* pMsg)
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


HBRUSH ModifyPasswd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (IDC_RADIO2_1 == pWnd->GetDlgCtrlID() || IDC_RADIO2_2 == pWnd->GetDlgCtrlID())
	{
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		BITMAP bmp;
		CBitmap bkImg;
		bkImg.LoadBitmap(IDB_BITMAP_MODIFYPASSWD);
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


void ModifyPasswd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect   rect;
	GetClientRect(&rect);
	m_function.LoadBackgroud(dc, IDB_BITMAP_MODIFYPASSWD, rect);
}

//修改密码
void ModifyPasswd::OnBnClickedButton1()
{
	UpdateData(1);
	if(m_strpasswd != L"")
	{
		if(m_strrepasswd != L"")
		{
			if(m_strpasswd.GetLength() >= 6)
			{
				if(m_strpasswd == m_strrepasswd)
				{
					Confirm m_confirm;
					m_confirm.m_passwd = m_Loginpasswd;
					m_confirm.m_static = L"请输入当前密码：";
					int confirm = m_confirm.DoModal();
					if(confirm == IDOK)
						CDialog::OnOK();
				}
				else
				{
					MessageBox(L"你输入的密码不一致！\r请从新输入！");
					m_passwd.SetWindowTextW(L"");
					m_repasswd.SetWindowTextW(L"");
				}
			}
			else
				MessageBox(L"密码长度不符合要求！");
		}
		else
			MessageBox(L"请输入确认密码！");
	}
	else
		MessageBox(L"请输入新登陆密码！");
}
//取消修改
void ModifyPasswd::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void ModifyPasswd::OnBnClickedRadio21()
{
	m_passwd.GetWindowTextW(m_strpasswd);
	m_repasswd.GetWindowTextW(m_strrepasswd);
	if (m_ShowPasswd.GetCheck() == 1)
	{
		m_HidePasswd.SetCheck(0);
		m_passwd.SetPasswordChar('\0');
		m_repasswd.SetPasswordChar('\0');
	}
	else
	{
		m_HidePasswd.SetCheck(1);
		m_passwd.SetPasswordChar('*');
		m_repasswd.SetPasswordChar('*');
	}
	m_passwd.SetWindowTextW(m_strpasswd);
	m_repasswd.SetWindowTextW(m_strrepasswd);
}


void ModifyPasswd::OnBnClickedRadio22()
{
	m_passwd.GetWindowTextW(m_strpasswd);
	m_repasswd.GetWindowTextW(m_strrepasswd);
	if (m_HidePasswd.GetCheck() == 1)
	{
		m_ShowPasswd.SetCheck(0);
		m_passwd.SetPasswordChar('*');
		m_repasswd.SetPasswordChar('*');
	}
	else
	{
		m_ShowPasswd.SetCheck(1);
		m_passwd.SetPasswordChar('\0');
		m_repasswd.SetPasswordChar('\0');
	}
	m_passwd.SetWindowTextW(m_strpasswd);
	m_repasswd.SetWindowTextW(m_strrepasswd);
}

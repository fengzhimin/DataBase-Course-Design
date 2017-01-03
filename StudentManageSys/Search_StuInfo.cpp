// Search_StuInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_StuInfo.h"
#include "afxdialogex.h"


// Search_StuInfo 对话框

IMPLEMENT_DYNAMIC(Search_StuInfo, CDialogEx)

Search_StuInfo::Search_StuInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(Search_StuInfo::IDD, pParent)
{
	font.CreatePointFont(150, L"宋体");
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


// Search_StuInfo 消息处理程序


void Search_StuInfo::OnCbnSelchangeCombo1()
{
	m_Stype.GetWindowTextW(m_str);
	if(m_Teacher_Student == 0)
		if (m_str == L"按照学号")
		{
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入学生的学号：");
			Stu_Info.SetWindowTextW(L"");
		}
		else
		{
			Stu_Info.SetWindowTextW(L"");
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入学生的姓名：");
		}
	else
		if (m_str == L"按照学号")
		{
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入教师的编号：");
			Stu_Info.SetWindowTextW(L"");
		}
		else
		{
			Stu_Info.SetWindowTextW(L"");
			GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入教师的姓名：");
		}
	Invalidate();
}


BOOL Search_StuInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(IDC_STATIC1)->SetFont(&font);
	GetDlgItem(IDC_STATIC2)->SetFont(&font);
	m_Stype.AddString(L"按照姓名");
	m_Stype.AddString(L"按照学号");
	m_Stype.SetCurSel(0);
	m_Stype.SetFont(&font);
	Stu_Info.SetFont(&font);
	if(m_Teacher_Student == 0)
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入学生的姓名：");
	else
		GetDlgItem(IDC_STATIC2)->SetWindowTextW(L"请输入教师的姓名：");
	CRect rect = CRect(100,210,170,250);
	if(m_Teacher_Student == 0)
		m_function.Create_Button(m_button1, L"搜索", L"查看学生的课程表", this, IDC_BUTTON1, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	else
		m_function.Create_Button(m_button1, L"搜索", L"查看教师的课程表", this, IDC_BUTTON1, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	rect = CRect(220,210,290,250);
	m_function.Create_Button(m_button2,L"取消",L"放弃查询",this, IDC_BUTTON2, font, rect, RGB(207,206,206), RGB(49,49,49), RGB(0, 0, 0));
	GetDlgItem(IDC_BUTTON1)->SetFont(&font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&font);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
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
		if (m_str == L"按照学号")
			MessageBox(L"请输入要查询的学号!");
		else
			MessageBox(L"请输入要查询的姓名!");
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

	if (m_str == L"按照学号")
	{
		//屏蔽汉子和特殊字符登陆
		for(int i = 0;i < str_Info.GetLength();++i)
			if(str_Info.GetAt(i) < 48 || str_Info.GetAt(i) > 57)
			{
				MessageBox(L"对不起！您输入的学号不可用！\n正确的学号为0-9数字组成！");
				Stu_Info.SetWindowTextW(L"");
				return;
			}
		if(m_Teacher_Student == 0)
			str_command = L"select r.学号 from Register r,User_Passwd u where r.学号 ='" + str_Info + L"' and r.学号 = u.学号 and u.用户类型 = '学生'";
		else
			str_command = L"select r.学号 from Register r,User_Passwd u where r.学号 ='" + str_Info + L"' and r.学号 = u.学号 and u.用户类型 = '教师'";
		m_recordset = m_connection->Execute(_bstr_t(str_command),NULL,adCmdText);
		if (m_recordset->adoEOF)
		{
			if(m_Teacher_Student == 0)
				MessageBox(L"对不起！您输入的学生学号不存在！ \n请重新输入！");
			else
				MessageBox(L"对不起！您输入的教师学号不存在！ \n请重新输入！");
			Stu_Info.SetWindowTextW(L"");
			return;
		}
		else
			CDialog::OnOK();
	}
	else
	{
		if(m_Teacher_Student == 0)
			str_command = L"select count(r.学号) as c from Register r,User_Passwd u where r.用户名 ='" + str_Info + L"' and r.学号 = u.学号 and u.用户类型 = '学生'";
		else
			str_command = L"select count(r.学号) as c from Register r,User_Passwd u where r.用户名 ='" + str_Info + L"' and r.学号 = u.学号 and u.用户类型 = '教师'";
		m_recordset = m_connection->Execute(_bstr_t(str_command), NULL, adCmdText);
		CString m_str_count;
		str_command = m_recordset->GetCollect("c");
		if(m_recordset->adoEOF || str_command == L"0")
		{
			if(m_Teacher_Student == 0)
				MessageBox(L"对不起！您输入的学生姓名不存在！ \n请重新输入！");
			else
				MessageBox(L"对不起！您输入的教师姓名不存在！ \n请重新输入！");
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
					m_str_count = L"对不起！存在 " + str_command + L" 个学生的姓名与您输入的姓名相同！\n请按照学号进行查询！";
				else
					m_str_count = L"对不起！存在 " + str_command + L" 个教师的姓名与您输入的姓名相同！\n请按照学号进行查询！";
				m_Stype.SetCurSel(1);
				MessageBox(m_str_count);
				Stu_Info.SetWindowTextW(L"");
			}
		}
	}
}


BOOL Search_StuInfo::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN)
    { 
		switch(pMsg->wParam)
        { case VK_RETURN: return TRUE; //屏蔽回车
          case VK_ESCAPE: return TRUE; //屏蔽Esc
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

	if (CTLCOLOR_STATIC == nCtlColor)//静态文字控件
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}
	return hbr;
}


// StudentManageSysView.cpp : CStudentManageSysView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "StudentManageSys.h"
#endif

#include "StudentManageSysDoc.h"
#include "StudentManageSysView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

// CStudentManageSysView

IMPLEMENT_DYNCREATE(CStudentManageSysView, CView)

BEGIN_MESSAGE_MAP(CStudentManageSysView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_DYNAMICBUTTON, &CStudentManageSysView::OnBtnDown)
ON_COMMAND(ID_EXIT, &CStudentManageSysView::OnExit)
ON_COMMAND(ID_LOGIN, &CStudentManageSysView::OnLogin)
ON_WM_TIMER()
ON_COMMAND(ID_JXGRKB, &CStudentManageSysView::OnJxgrkb)
ON_COMMAND(ID_JXKCKB, &CStudentManageSysView::OnJxkckb)
ON_COMMAND(ID_JXJSKB, &CStudentManageSysView::OnJxjskb)
ON_COMMAND(ID_JXBJKB, &CStudentManageSysView::OnJxbjkb)
ON_COMMAND(ID_GLYCKXSKB, &CStudentManageSysView::OnGlyckxskb)
ON_COMMAND(ID_XJXX, &CStudentManageSysView::OnXjxx)
ON_WM_CTLCOLOR()
ON_COMMAND(ID_XGMM, &CStudentManageSysView::OnXgmm)
ON_COMMAND(ID_32808, &CStudentManageSysView::On32808)
ON_COMMAND(ID_32809, &CStudentManageSysView::On32809)
ON_COMMAND(ID_GLYCXJSKB, &CStudentManageSysView::OnGlycxjskb)
ON_COMMAND(ID_XJZC, &CStudentManageSysView::OnXjzc)
ON_COMMAND(ID_32817, &CStudentManageSysView::On32817)
ON_COMMAND(ID_XJBM, &CStudentManageSysView::OnXjbm)
ON_COMMAND(ID_32819, &CStudentManageSysView::On32819)
ON_COMMAND(ID_32811, &CStudentManageSysView::On32811)
ON_COMMAND(ID_32814, &CStudentManageSysView::On32814)
ON_COMMAND(ID_CJCK, &CStudentManageSysView::OnCjck)
ON_COMMAND(ID_GLYCJCK, &CStudentManageSysView::OnGlycjck)
ON_COMMAND(ID_GLYLRCJ, &CStudentManageSysView::OnGlylrcj)
ON_COMMAND(ID_CXXSCJ, &CStudentManageSysView::OnCxxscj)
ON_COMMAND(ID_CJFB, &CStudentManageSysView::OnCjfb)
END_MESSAGE_MAP()

// CStudentManageSysView 构造/析构

CStudentManageSysView::CStudentManageSysView()
{
	point = 0;
}

CStudentManageSysView::~CStudentManageSysView()
{
}

BOOL CStudentManageSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	
	return CView::PreCreateWindow(cs);
}

// CStudentManageSysView 绘制

void CStudentManageSysView::OnDraw(CDC* /*pDC*/)
{
	CStudentManageSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO:  在此处为本机数据添加绘制代码
}


// CStudentManageSysView 打印

BOOL CStudentManageSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CStudentManageSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CStudentManageSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CStudentManageSysView 诊断

#ifdef _DEBUG
void CStudentManageSysView::AssertValid() const
{
	CView::AssertValid();
}

void CStudentManageSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStudentManageSysDoc* CStudentManageSysView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentManageSysDoc)));
	return (CStudentManageSysDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentManageSysView 消息处理程序

void CStudentManageSysView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//背景图片
	CRect rctClient;
	GetClientRect(rctClient);
	function.LoadBackgroud(dc, IDB_BITMAP_Back, rctClient);
	if (point == 1)
	{
		str_Info = L"你好！" + m_str_Loginingname + L" ( " + User_Type + L" )";
		dc.SetBkMode(TRANSPARENT);
		dc.SelectObject(&font);
		dc.SetTextColor(RGB(0,0,0));
		TextOut(dc, rect_Client.right - 230, 0, str_Info, str_Info.GetLength());
	}
}


int CStudentManageSysView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*CRect rect(10, 30, 50, 100);
	button1.Create(L"hello", WS_CHILD | WS_VISIBLE | WS_BORDER, rect, this, IDC_DYNAMICBUTTON);
	button.ShowWindow(SW_SHOW);*/
	return 0;

}

void CStudentManageSysView::OnBtnDown()
{
	MessageBox(L"hello", L"helloworld", MB_OK);
}




void CStudentManageSysView::OnExit()
{
		if (m_LoginStatue == IDOK)
		{
			if (MessageBox(L"是否要注销当前账号？", L"提示", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
			{
				CMainFrame::point = 0;
				CString str_Check = L"update User_Passwd set 登陆状态 = 0 where 学号 = '" + Logining_Name + L"'";
				M_pRecordset = M_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
				MessageBox(L"注销成功！");
				M_pConnection->Close();
				m_LoginStatue = IDCANCEL;
				Logining_Name = L"";
				menu_Login.DestroyMenu();
				menu_Exit.LoadMenu(IDR_MAINFRAME);
				this->GetParent()->SetMenu(&menu_Exit);
	
				//终止计时器
				delete m_DateTimeCtrl;
				delete listbox;
				delete dlg;
				KillTimer(1);			
				font.DeleteObject();
				//delete listbox;
				point = 0;
				//重新绘制屏幕
				Invalidate();
			}
		}
}


void CStudentManageSysView::OnLogin()
{
	if (Logining_Name == L"")
	{
		Stu_Login login;
		m_LoginStatue = login.DoModal();
		if (m_LoginStatue == IDOK)
		{
			CMainFrame::point = 1;
			Logining_Name = login.m_LName;
			Logining_Passwd = login.m_LPasswd;
			m_str_Loginingname = login.m_str_name;
			User_Type = login.str_stype;
			if (User_Type == L"学生")
				menu_Login.LoadMenu(IDR_MENU1);
			else
			{
				if(User_Type == L"教师")
					menu_Login.LoadMenu(IDR_MENU2);
				else
					menu_Login.LoadMenu(IDR_MENU3);
			}
			this->GetParent()->SetMenu(&menu_Login);
			menu_Exit.DestroyMenu();

			::CoInitialize(NULL);
			try
			{
				M_pConnection.CreateInstance(__uuidof(Connection));
				M_pConnection->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
				M_pConnection->Open("", "", "", adConnectUnspecified);
				M_pConnection->DefaultDatabase = "USER";
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
			//显示信息
			font.CreatePointFont(120, L"宋体");
			GetClientRect(rect_Client);
			point = 1;

			CRect rect(0, 0, 190, 25);
			m_DateTimeCtrl = new CDateTimeCtrl;
			m_DateTimeCtrl->Create(WS_VISIBLE | WS_CHILD | WS_TABSTOP | DTS_SHOWNONE |
				DTS_SHORTDATEFORMAT, rect, this, IDC_DATETIMECTRL);
			m_DateTimeCtrl->EnableWindow(0);
			tm = CTime::GetCurrentTime();
			m_DateTimeCtrl->SetTime(&tm);
			m_DateTimeCtrl->SetFormat(L"yyyy-MM-dd HH:mm:ss");
			SetTimer(1, 1000, NULL);
			listbox = new CListCtrl;
			dlg = new Stu_Info; 
			Invalidate();  //用于重绘屏幕上显示的用户信息
		}
	}
}


void CStudentManageSysView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		tm = CTime::GetCurrentTime();
		m_DateTimeCtrl->SetTime(&tm);
		m_DateTimeCtrl->SetFormat(L"yyyy-MM-dd HH:mm:ss");
	}
	CView::OnTimer(nIDEvent);
}

//查看个人课表
void CStudentManageSysView::OnJxgrkb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课地点", L"上课教师" };
	m_listbox.Setlist(str, 6);
	if (User_Type == L"学生")
	{
		CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.学号 = '" +
			Logining_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号";
		m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
	}
	else
	{
		CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.学号 = '" +
			Logining_Name + "' and s1.课程编号 = s2.课程编号";
		m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
	}
}

//查看课表按课程
void CStudentManageSysView::OnJxkckb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课地点", L"上课教师" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.学号 = '" +
			Logining_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号 order by s1.科目名称";
	CString str_1 = str[0];
	str[0] = str[1];
	str[1] = str_1;
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//查看课表按教师
void CStudentManageSysView::OnJxjskb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"上课教师", L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课地点" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.学号 = '" +
			Logining_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号 order by s2.上课教师";
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//查看课表按教室
void CStudentManageSysView::OnJxbjkb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"上课地点", L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课教师" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.学号 = '" +
			Logining_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号 order by s1.上课地点";
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//教师查询学生的课表
void CStudentManageSysView::OnGlyckxskb()
{
	Invalidate();
	Search_StuInfo search;
	if (search.DoModal() == IDOK)
	{
		dlg->DestroyWindow();
		listbox->DestroyWindow();
		ListBox m_listbox(listbox);
		m_listbox.SetRect(rect_Client);
		m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
		CString str[6] = { L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课地点", L"上课教师" };
		m_listbox.Setlist(str, 6);
		if (search.m_str == L"按照学号")
		{
			CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.学号 = '" +
				search.str_Info + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		else
		{
			CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2,Register r where r.用户名 = '" +
				search.str_Info + "' and s.学号 = r.学号 and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		
	}
}
//查看学籍基本信息
void CStudentManageSysView::OnXjxx()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	dlg->str_Name = Logining_Name;   //将当前登录的用户名传入
	dlg->Create(IDD_DIALOG_StuInfo, this);
	dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
	if(dlg->point == 0)
	{
		MessageBox(L"对不起！你的信息没有被录入！",L"提示");
		dlg->DestroyWindow();
	}
	else
		dlg->ShowWindow(SW_SHOW);//显示
}


HBRUSH CStudentManageSysView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		//pDC->SetBkColor(RGB(255,0,0));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(0,0,0));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
	}  	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

//修改账号设置
void CStudentManageSysView::OnXgmm()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	SetUser m_setuser;
	m_setuser.m_Loginname = Logining_Name;
	m_setuser.m_Loginpasswd = Logining_Passwd;
	m_setuser.m_Loginstype = User_Type;
	m_setuser.DoModal();
}

//修改登陆密码
void CStudentManageSysView::On32808()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	ModifyPasswd m_modifypasswd;
	m_modifypasswd.m_Loginname = Logining_Name;
	m_modifypasswd.m_Loginpasswd = Logining_Passwd;
	int modify = m_modifypasswd.DoModal();
	if(modify == IDOK)
	{
		CString str = L"update User_Passwd set 密码 = '" + m_modifypasswd.m_strrepasswd + L"' where 学号 = '" + Logining_Name + L"'";
		M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
		
		if(PathFileExists(L"remember_auto.txt"))
		{
			CFile m_Remember_Auto;
			m_Remember_Auto.Remove(L"remember_auto.txt");
		}
		MessageBox(L"密码修改成功！注销后生效！\n请牢记你的密码！");	
	}
}

//添加学生
void CStudentManageSysView::On32809()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Register reg_user;
	reg_user.m_point = 1;
	reg_user.m_str = L"添加";
	reg_user.m_str1 = L"添加新学生";
	reg_user.m_str2 = L"取消添加学生";
	reg_user.DoModal();
}

//管理员查询教师课表
void CStudentManageSysView::OnGlycxjskb()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Invalidate();
	Search_StuInfo search;
	search.m_Teacher_Student = 1;
	if (search.DoModal() == IDOK)
	{
		dlg->DestroyWindow();
		listbox->DestroyWindow();
		ListBox m_listbox(listbox);
		m_listbox.SetRect(rect_Client);
		m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
		CString str[6] = { L"课程编号", L"科目名称", L"上课周次", L"上课时间", L"上课地点", L"上课教师" };
		m_listbox.Setlist(str, 6);
		if (search.m_str == L"按照学号")
		{
			CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.学号 = '" +
			search.str_Info + "' and s1.课程编号 = s2.课程编号";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		else
		{
			CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.上课教师 = '" +
			search.str_Info + "' and s1.课程编号 = s2.课程编号";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		
	}
}

//管理员注册个人信息
void CStudentManageSysView::OnXjzc()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Base_Info m_base(m_str_Loginingname,Logining_Name,2);
	if(m_base.DoModal() == IDOK)
		m_base.Insert_info(M_pConnection, M_pRecordset);
}

//录入学生信息
void CStudentManageSysView::On32817()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Choose m_choose;
	if(m_choose.DoModal() == IDOK)
	{
		Base_Info m_base(m_choose.m_name,m_choose.m_id,m_choose.point);
		if(m_base.DoModal() == IDOK)
			m_base.Insert_info(M_pConnection, M_pRecordset);
	}
}


//学生基本信息查询
void CStudentManageSysView::OnXjbm()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Select m_select(L"输入学生学号：",L"学生",L"查询");
	if(m_select.DoModal() == IDOK)
	{
		dlg->str_Name = m_select.m_id;   //将当前登录的用户名传入
		dlg->Create(IDD_DIALOG_StuInfo, this);
		dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
		if(dlg->point == 0)
		{
			MessageBox(L"对不起！你的信息没有被录入！",L"提示");
			dlg->DestroyWindow();
		}
		else
			dlg->ShowWindow(SW_SHOW);//显示
	}
	
}

//教师基本信息查询
void CStudentManageSysView::On32819()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Select m_select(L"输入教师编号：",L"教师",L"查询");
	if(m_select.DoModal() == IDOK)
	{
		dlg->str_Name = m_select.m_id;   //将当前登录的用户名传入
		dlg->Create(IDD_DIALOG_StuInfo, this);
		dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
		if(dlg->point == 0)
		{
			MessageBox(L"对不起！你的信息没有被录入！",L"提示");
			dlg->DestroyWindow();
		}
		else
			dlg->ShowWindow(SW_SHOW);//显示
	}
}

//修改学生密码
void CStudentManageSysView::On32811()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Select m_select(L"输入学生的学号：",L"学生",L"修改");
	if(m_select.DoModal() == IDOK)
	{
		CString str = L"update User_Passwd set 密码 = '" + m_select.m_newpasswd + L"' where 学号 = '" + m_select.m_id + L"'";
		try
			{
				M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
			MessageBox(L"修改成功！");
	}
}

//修改教师密码
void CStudentManageSysView::On32814()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Select m_select(L"输入教师的编号：",L"教师",L"修改");
	if(m_select.DoModal() == IDOK)
	{
		CString str = L"update User_Passwd set 密码 = '" + m_select.m_newpasswd + L"' where 学号 = '" + m_select.m_id + L"'";
		try
			{
				M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
			MessageBox(L"修改成功！");
	}
}


//学生查看成绩
void CStudentManageSysView::OnCjck()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Search_Score m_search_Score(Logining_Name);
	m_search_Score.DoModal();
}

//教师查看成绩
void CStudentManageSysView::OnGlycjck()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Search_Score m_search_Score(Logining_Name,1);
	m_search_Score.DoModal();
}

//录入成绩
void CStudentManageSysView::OnGlylrcj()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Insert_score m_insert(Logining_Name);
	m_insert.DoModal();
}

//管理员查询学生成绩
void CStudentManageSysView::OnCxxscj()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Search_StuScore m_stuScore;
	if(m_stuScore.DoModal() == IDOK)
	{
		Search_Score m_search_Score(m_stuScore.m_id);
		m_search_Score.DoModal();
	}
}

//学生成绩分布
void CStudentManageSysView::OnCjfb()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Score_Scope m_score;
	if(m_score.DoModal() == IDOK)
	{
		Search_Score m_search_Score(Logining_Name,2);
		m_search_Score.min = m_score.m_min;
		m_search_Score.max = m_score.m_max;
		m_search_Score.DoModal();
	}
}

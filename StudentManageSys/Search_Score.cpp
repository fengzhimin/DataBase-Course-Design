// Search_Score.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_Score.h"
#include "afxdialogex.h"


// Search_Score 对话框

IMPLEMENT_DYNAMIC(Search_Score, CDialogEx)

Search_Score::Search_Score(CString str,int i,CWnd* pParent /*=NULL*/)
	: CDialogEx(Search_Score::IDD, pParent)
{
	str_id = str;
	point = i;
}

Search_Score::~Search_Score()
{
}

void Search_Score::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
}


BEGIN_MESSAGE_MAP(Search_Score, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Search_Score 消息处理程序

BOOL Search_Score::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(&m_rect);
	::CoInitialize(NULL);
	try
	{
		m_pConnection.CreateInstance(__uuidof(Connection));
		m_pConnection->ConnectionString = "driver={SQL Server};server=LENOVO-PC;uid=sa;pwd=fzm;";
		m_pConnection->Open("", "", "", adConnectUnspecified);
		m_pConnection->DefaultDatabase = "USER";
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return false;
	}
	
	m_list.EnsureVisible(m_list.GetItemCount()-1,FALSE);
	if(point == 0)
		str_Command = L"select * from Student_Table s,Subject_Table s1,Teacher_Table t where s.课程编号 = s1.课程编号 and s.录入标记 = 1 and s.课程编号 = t.课程编号 and s.编号 = t.学号 and s.学号 = '" + str_id + L"'";
	else 
		if(point == 1)
			str_Command = L"select s.学号,s2.所在学院,s2.所学专业,s2.所在年级班级,s.课程成绩 from Student_Table s,Subject_Table s1,Stu_Info s2,Teacher_Table t where s.学号 = s2.学号 and s.课程编号 = s1.课程编号 and s.录入标记 = 1 and s.课程编号 = t.课程编号 and s.编号 = t.学号 and t.学号 = '" + str_id + L"'";
		else
			str_Command = L"select * from Student_Table s,Subject_Table s1,Teacher_Table t where s.课程编号 = s1.课程编号 and s.课程成绩 >= '" + min + L"' and s.课程成绩 <= '" + max + L"' and s.录入标记 = 1 and s.课程编号 = t.课程编号 and s.编号 = t.学号 and s.学号 = '" + str_id + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);

	if(m_pRecordset->adoEOF)
	{
		m_pConnection->Close();
		if(point == 2)
		{
			MessageBox(L"没有成绩在此范围内！");
			m_list.SetBkColor(RGB(50, 120, 46));
			m_list.SetTextBkColor(RGB(124, 121, 112));
			return TRUE;
		}

		MessageBox(L"暂时无成绩录入！");
		CDialog::OnCancel();
		return FALSE;
	}
	m_list.SetBkColor(RGB(50, 120, 46));
	m_list.SetTextBkColor(RGB(124, 121, 112));
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	m_list.GetWindowRect(&rect);
	if(point == 0 || point == 2)
	{
		m_list.InsertColumn(0, L"课程编号", LVCFMT_LEFT, rect.Width() / 5 - 50);
		m_list.InsertColumn(1, L"科目名称", LVCFMT_LEFT, rect.Width() / 5 + 50);
		m_list.InsertColumn(2, L"上课教师", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(3, L"编号", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(4, L"课程成绩", LVCFMT_LEFT, rect.Width() / 5);
	}
	else
	{
		m_list.InsertColumn(0, L"学号", LVCFMT_LEFT, rect.Width() / 5 - 50);
		m_list.InsertColumn(1, L"所在学院", LVCFMT_LEFT, rect.Width() / 5 + 50);
		m_list.InsertColumn(2, L"所学专业", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(3, L"所在年级班级", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(4, L"课程成绩", LVCFMT_LEFT, rect.Width() / 5);
	}

	int j = 0;
	CString str_1,str_2,str_3,str_4,str_5;
	while (!m_pRecordset->adoEOF)
	{
		if(point == 0 || point == 2)
		{
			str_1 = m_pRecordset->GetCollect("课程编号");
			str_2 = m_pRecordset->GetCollect("科目名称");
			str_3 = m_pRecordset->GetCollect("上课教师");
			str_4 = m_pRecordset->GetCollect("编号");
			str_5 = m_pRecordset->GetCollect("课程成绩");
		}
		else
		{
			str_1 = m_pRecordset->GetCollect("学号");
			str_2 = m_pRecordset->GetCollect("所在学院");
			str_3 = m_pRecordset->GetCollect("所学专业");
			str_4 = m_pRecordset->GetCollect("所在年级班级");
			str_5 = m_pRecordset->GetCollect("课程成绩");
		}
		m_list.InsertItem(j, str_1);
		m_list.SetItemText(j, 1, str_2);
		m_list.SetItemText(j, 2, str_3);
		m_list.SetItemText(j, 3, str_4);
		m_list.SetItemText(j, 4, str_5);
		j++;
		m_pRecordset->MoveNext();
	}
	m_pConnection->Close();
	return TRUE; 
}


void Search_Score::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//Stu_function.LoadBackgroud(dc, IDB_BITMAP_StuInfo, m_rect);
	CDialogEx::OnPaint();
}

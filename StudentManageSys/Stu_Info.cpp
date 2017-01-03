// Stu_Info.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Stu_Info.h"
#include "afxdialogex.h"


// Stu_Info 对话框

IMPLEMENT_DYNAMIC(Stu_Info, CDialogEx)

Stu_Info::Stu_Info(CWnd* pParent /*=NULL*/)
	: CDialogEx(Stu_Info::IDD, pParent)
{
	point = 1;
}

Stu_Info::~Stu_Info()
{

}

void Stu_Info::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_LIST4, m_list1);
}


BEGIN_MESSAGE_MAP(Stu_Info, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Stu_Info 消息处理程序


BOOL Stu_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
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
	
	str_Command = L"select * from Register s,Stu_Info s1 where s.学号 = s1.学号 and s.学号 = '" + str_Name + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);

	if(m_pRecordset->adoEOF)
	{
		m_pConnection->Close();
		point = 0;
		return TRUE;
	}

	CString str[] = { L"用户名", L"年龄", L"性别", L"民族", L"政治面貌", L"目前身份", L"目前所在地", L"毕业年份",
		L"学历", L"所在学校", L"所在学院", L"毕业学校", L"所学专业", L"所在年级班级" };
	CString str1;

	for (int i = 1042; i <= 1055; ++i)
	{
		str1 = m_pRecordset->GetCollect((const _variant_t)(str[i - 1042]));
			GetDlgItem(i)->SetWindowTextW(str1);
	}
	str1 = m_pRecordset->GetCollect("学号");
	GetDlgItem(IDC_STATIC_33)->SetWindowTextW(str1);
	str1 = m_pRecordset->GetCollect("个人特长");
	GetDlgItem(IDC_LIST3)->SetWindowTextW(str1);
	m_list.SetBkColor(RGB(255,255,255));
	m_list.SetTextBkColor(RGB(207,206,207));
	str_Command = L"select * from Stu_Education where 学号 = '" + str_Name + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	CString str_1, str_2, str_3;
	m_list.GetWindowRect(&rect);
	m_list.InsertColumn(0, L"年份", LVCFMT_LEFT, 2*rect.Width() / 5);
	m_list.InsertColumn(1, L"所在学校", LVCFMT_LEFT, 4 * rect.Width() / 5 - 60);
	m_list.InsertColumn(2, L"负责人", LVCFMT_LEFT, 2*rect.Width() / 5);
	int j = 0;
	while (!m_pRecordset->adoEOF)
	{
		str_1 = m_pRecordset->GetCollect("年份");
		str_2 = m_pRecordset->GetCollect("所在学校");
		str_3 = m_pRecordset->GetCollect("负责人");
		m_list.InsertItem(j, str_1);
		m_list.SetItemText(j, 1, str_2);
		m_list.SetItemText(j, 2, str_3);
		j++;
		m_pRecordset->MoveNext();
	}
	m_list1.SetBkColor(RGB(255,255,255));
	m_list1.SetTextBkColor(RGB(207,206,207));
	str_Command = L"select * from Stu_Award where 学号 = '" + str_Name + L"'order by 年份";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	m_list1.GetWindowRect(&rect);
	m_list1.InsertColumn(0, L"年份", LVCFMT_LEFT, rect.Width() / 2 - 50);
	m_list1.InsertColumn(1, L"奖项", LVCFMT_LEFT, rect.Width() + 50);

	j = 0;
	while (!m_pRecordset->adoEOF)
	{
		str_1 = m_pRecordset->GetCollect("年份");
		str_2 = m_pRecordset->GetCollect("奖项");
		m_list1.InsertItem(j, str_1);
		m_list1.SetItemText(j, 1, str_2);
		j++;
		m_pRecordset->MoveNext();
	}
	m_pConnection->Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void Stu_Info::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	Stu_function.LoadBackgroud(dc, IDB_BITMAP_StuInfo, m_rect);
	//dc.SetBkMode(TRANSPARENT);
	//dc.SetTextColor(RGB(171, 15, 132));
	//GetDlgItem(IDC_STATIC1)->SetWindowTextW(L"基本信息");
	CDialogEx::OnPaint();
}


HBRUSH Stu_Info::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SetBkMode(TRANSPARENT);

		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void Stu_Info::ChangeSize(UINT nID, int x, int y)  //nID为控件ID，x,y分别为对话框的当前长和宽
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL)     //判断是否为空，因为在窗口创建的时候也会调用OnSize函数，但是此时各个控件还没有创建，Pwnd为空
	{
		CRect rec;
		pWnd->GetWindowRect(&rec);  //获取控件变化前的大小
		ScreenToClient(&rec);   //将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x / m_rect.Width();  //按照比例调整空间的新位置
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec);   //伸缩控件
	}
}

void Stu_Info::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType != SIZE_MINIMIZED)  //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
		ChangeSize(IDC_STATIC1, cx, cy);  //对每一个控件依次做调整
		ChangeSize(IDC_STATIC2, cx, cy);
		ChangeSize(IDC_STATIC3, cx, cy);
		for (int i = 1034; i <= 1067;++i)
			ChangeSize(i, cx, cy);
		ChangeSize(IDC_STATIC_32,cx,cy);
		ChangeSize(IDC_STATIC_33,cx,cy);
		GetClientRect(&m_rect);   //最后要更新对话框的大小，当做下一次变化的旧坐标；
	}
}


BOOL Stu_Info::PreTranslateMessage(MSG* pMsg)
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

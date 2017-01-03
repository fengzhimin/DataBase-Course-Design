// FindPasswd.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "FindPasswd.h"
#include "afxdialogex.h"


// FindPasswd 对话框

IMPLEMENT_DYNAMIC(FindPasswd, CDialogEx)

FindPasswd::FindPasswd(CWnd* pParent /*=NULL*/)
	: CDialogEx(FindPasswd::IDD, pParent)
	, m_answer(_T(""))
{

}

FindPasswd::~FindPasswd()
{
	font_1.DeleteObject();
	font_2.DeleteObject();
}

void FindPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_Name, m_User);
	DDX_Control(pDX, IDC_STATIC_question, m_question);
	DDX_Text(pDX, IDC_EDIT_Answer, m_answer);
}


BEGIN_MESSAGE_MAP(FindPasswd, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &FindPasswd::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &FindPasswd::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// FindPasswd 消息处理程序


BOOL FindPasswd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	font_1.CreatePointFont(180, L"宋体");
	font_2.CreatePointFont(150, L"宋体");
	GetDlgItem(IDC_STATIC1)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC2)->SetFont(&font_1);
	GetDlgItem(IDC_STATIC3)->SetFont(&font_1);
	GetDlgItem(IDC_BUTTON1)->SetFont(&font_1);
	GetDlgItem(IDC_BUTTON2)->SetFont(&font_1);
	m_User.SetFont(&font_2);
	m_question.SetFont(&font_2);
	GetDlgItem(IDC_EDIT_Answer)->SetFont(&font_2);
	m_question.SetWindowTextW(question);
	m_User.SetWindowTextW(User);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void FindPasswd::OnBnClickedButton2()
{
	CDialog::OnCancel();
}


void FindPasswd::OnBnClickedButton1()
{
	UpdateData();
	if (m_answer == answer)
	{
		MessageBox(L"您的用户名为：" + User + L"\n" + L"密码为：" + Passwd);
		CDialog::OnOK();
	}
	else
	{
		MessageBox(L"对不起！您输入的答案不正确！");
		m_answer = L"";
		UpdateData(FALSE);
	}
}



HBRUSH FindPasswd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (CTLCOLOR_STATIC == nCtlColor)//静态文字控件
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//透明画刷
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void FindPasswd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect   rect;
	GetClientRect(&rect);
	Find_function.LoadBackgroud(dc, IDB_BITMAP_Search, rect);
	// 不为绘图消息调用 CDialogEx::OnPaint()
}


BOOL FindPasswd::PreTranslateMessage(MSG* pMsg)
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

// Insert_score.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Insert_score.h"
#include "afxdialogex.h"


// Insert_score 对话框

IMPLEMENT_DYNAMIC(Insert_score, CDialogEx)

Insert_score::Insert_score(CString str,CWnd* pParent /*=NULL*/)
	: CDialogEx(Insert_score::IDD, pParent)
	, m_score(_T(""))
{
	m_teacher_id = str;
	m_font.CreatePointFont(120, L"宋体");
}

Insert_score::~Insert_score()
{
	m_font.DeleteObject();
	M_pConnection->Close();
}

void Insert_score::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_id);
	DDX_Text(pDX, IDC_EDIT1, m_score);
}


BEGIN_MESSAGE_MAP(Insert_score, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Insert_score::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Insert_score::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Insert_score::OnBnClickedButton3)
END_MESSAGE_MAP()


// Insert_score 消息处理程序


BOOL Insert_score::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetDlgItem(IDC_STATIC_SCORE1)->SetFont(&m_font);
	GetDlgItem(IDC_STATIC_SCORE2)->SetFont(&m_font);
	m_id.SetFont(&m_font);
	GetDlgItem(IDC_EDIT1)->SetFont(&m_font);
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
		return FALSE;
	}
	CString str;
	strSQL = L"select s.学号 from Teacher_Table t,Student_Table s where s.编号 = t.学号 and t.学号 = '" + m_teacher_id + L"' order by s.学号";
	M_pRecord = M_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
	//int count = _ttoi(str);
	//for(int i = 0;i < count;++i)
	if(M_pRecord->adoEOF)
	{
		MessageBox(L"对不起！还没有学生选了这门课程！");
		CDialog::OnCancel();
		M_pConnection->Close();
		return TRUE;
	}
	while (!M_pRecord->adoEOF)
	{
		str = M_pRecord->GetCollect("学号");
		m_id.AddString(str);
		M_pRecord->MoveNext();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
}

//下一个学号
void Insert_score::OnBnClickedButton1()
{
	int i = m_id.GetCurSel();
	if(i == m_id.GetCount() - 1)
		MessageBox(L"已经是最后一个了！");
	else
		m_id.SetCurSel(++i);
}

//录入
void Insert_score::OnBnClickedButton2()
{
	UpdateData();
	CString str;
	m_id.GetWindowTextW(str);
	if(m_score == L"")
	{
		MessageBox(L"成绩不能为空！");
		return;
	}
	else
	{
		int i = _ttoi(m_score);
		//排除出现成绩为负数
		if(i < 0)
		{
			MessageBox(L"对不起！您输入的成绩不符合要求！");
			m_score = L"";
			UpdateData(0);
			return;
		}
		strSQL = L"update Student_Table set 课程成绩 = '" + m_score + L"',录入标记 = '1' where 学号 = '" + str + L"' and 编号 = '" + m_teacher_id + L"'";
		try
		{
			M_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
		}
		catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
		m_score = L"";
		UpdateData(0);
	}
}

//完成
void Insert_score::OnBnClickedButton3()
{
	strSQL = L"select 录入标记,学号 from Student_Table where 编号 = '" + m_teacher_id + L"'";
	int i = 0;
	try
	{
		M_pRecord = M_pConnection->Execute(_bstr_t(strSQL), NULL, adCmdText);
	}
	catch (_com_error e)
	{
		AfxMessageBox(e.Description());
		return;
	}
	CString str1,str2;
	while (!M_pRecord->adoEOF)
	{
		str1 = M_pRecord->GetCollect("录入标记");
		str2 = M_pRecord->GetCollect("学号");
		if(str1 == L"1")
			M_pRecord->MoveNext();
		else
		{
			str1 = L"您还没有给学号为：" + str2 + L" 的同学录入成绩！";
			i = 1;
			MessageBox(str1);
			break;
		}
	}
	if(i == 1)
		return;
	else
		CDialog::OnOK();
}

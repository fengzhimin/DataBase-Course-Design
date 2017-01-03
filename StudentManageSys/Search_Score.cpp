// Search_Score.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Search_Score.h"
#include "afxdialogex.h"


// Search_Score �Ի���

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


// Search_Score ��Ϣ�������

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
		str_Command = L"select * from Student_Table s,Subject_Table s1,Teacher_Table t where s.�γ̱�� = s1.�γ̱�� and s.¼���� = 1 and s.�γ̱�� = t.�γ̱�� and s.��� = t.ѧ�� and s.ѧ�� = '" + str_id + L"'";
	else 
		if(point == 1)
			str_Command = L"select s.ѧ��,s2.����ѧԺ,s2.��ѧרҵ,s2.�����꼶�༶,s.�γ̳ɼ� from Student_Table s,Subject_Table s1,Stu_Info s2,Teacher_Table t where s.ѧ�� = s2.ѧ�� and s.�γ̱�� = s1.�γ̱�� and s.¼���� = 1 and s.�γ̱�� = t.�γ̱�� and s.��� = t.ѧ�� and t.ѧ�� = '" + str_id + L"'";
		else
			str_Command = L"select * from Student_Table s,Subject_Table s1,Teacher_Table t where s.�γ̱�� = s1.�γ̱�� and s.�γ̳ɼ� >= '" + min + L"' and s.�γ̳ɼ� <= '" + max + L"' and s.¼���� = 1 and s.�γ̱�� = t.�γ̱�� and s.��� = t.ѧ�� and s.ѧ�� = '" + str_id + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);

	if(m_pRecordset->adoEOF)
	{
		m_pConnection->Close();
		if(point == 2)
		{
			MessageBox(L"û�гɼ��ڴ˷�Χ�ڣ�");
			m_list.SetBkColor(RGB(50, 120, 46));
			m_list.SetTextBkColor(RGB(124, 121, 112));
			return TRUE;
		}

		MessageBox(L"��ʱ�޳ɼ�¼�룡");
		CDialog::OnCancel();
		return FALSE;
	}
	m_list.SetBkColor(RGB(50, 120, 46));
	m_list.SetTextBkColor(RGB(124, 121, 112));
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	m_list.GetWindowRect(&rect);
	if(point == 0 || point == 2)
	{
		m_list.InsertColumn(0, L"�γ̱��", LVCFMT_LEFT, rect.Width() / 5 - 50);
		m_list.InsertColumn(1, L"��Ŀ����", LVCFMT_LEFT, rect.Width() / 5 + 50);
		m_list.InsertColumn(2, L"�Ͽν�ʦ", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(3, L"���", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(4, L"�γ̳ɼ�", LVCFMT_LEFT, rect.Width() / 5);
	}
	else
	{
		m_list.InsertColumn(0, L"ѧ��", LVCFMT_LEFT, rect.Width() / 5 - 50);
		m_list.InsertColumn(1, L"����ѧԺ", LVCFMT_LEFT, rect.Width() / 5 + 50);
		m_list.InsertColumn(2, L"��ѧרҵ", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(3, L"�����꼶�༶", LVCFMT_LEFT, rect.Width() / 5);
		m_list.InsertColumn(4, L"�γ̳ɼ�", LVCFMT_LEFT, rect.Width() / 5);
	}

	int j = 0;
	CString str_1,str_2,str_3,str_4,str_5;
	while (!m_pRecordset->adoEOF)
	{
		if(point == 0 || point == 2)
		{
			str_1 = m_pRecordset->GetCollect("�γ̱��");
			str_2 = m_pRecordset->GetCollect("��Ŀ����");
			str_3 = m_pRecordset->GetCollect("�Ͽν�ʦ");
			str_4 = m_pRecordset->GetCollect("���");
			str_5 = m_pRecordset->GetCollect("�γ̳ɼ�");
		}
		else
		{
			str_1 = m_pRecordset->GetCollect("ѧ��");
			str_2 = m_pRecordset->GetCollect("����ѧԺ");
			str_3 = m_pRecordset->GetCollect("��ѧרҵ");
			str_4 = m_pRecordset->GetCollect("�����꼶�༶");
			str_5 = m_pRecordset->GetCollect("�γ̳ɼ�");
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

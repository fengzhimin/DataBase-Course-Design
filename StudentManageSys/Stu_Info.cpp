// Stu_Info.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentManageSys.h"
#include "Stu_Info.h"
#include "afxdialogex.h"


// Stu_Info �Ի���

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


// Stu_Info ��Ϣ�������


BOOL Stu_Info::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	
	str_Command = L"select * from Register s,Stu_Info s1 where s.ѧ�� = s1.ѧ�� and s.ѧ�� = '" + str_Name + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);

	if(m_pRecordset->adoEOF)
	{
		m_pConnection->Close();
		point = 0;
		return TRUE;
	}

	CString str[] = { L"�û���", L"����", L"�Ա�", L"����", L"������ò", L"Ŀǰ���", L"Ŀǰ���ڵ�", L"��ҵ���",
		L"ѧ��", L"����ѧУ", L"����ѧԺ", L"��ҵѧУ", L"��ѧרҵ", L"�����꼶�༶" };
	CString str1;

	for (int i = 1042; i <= 1055; ++i)
	{
		str1 = m_pRecordset->GetCollect((const _variant_t)(str[i - 1042]));
			GetDlgItem(i)->SetWindowTextW(str1);
	}
	str1 = m_pRecordset->GetCollect("ѧ��");
	GetDlgItem(IDC_STATIC_33)->SetWindowTextW(str1);
	str1 = m_pRecordset->GetCollect("�����س�");
	GetDlgItem(IDC_LIST3)->SetWindowTextW(str1);
	m_list.SetBkColor(RGB(255,255,255));
	m_list.SetTextBkColor(RGB(207,206,207));
	str_Command = L"select * from Stu_Education where ѧ�� = '" + str_Name + L"'";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	CString str_1, str_2, str_3;
	m_list.GetWindowRect(&rect);
	m_list.InsertColumn(0, L"���", LVCFMT_LEFT, 2*rect.Width() / 5);
	m_list.InsertColumn(1, L"����ѧУ", LVCFMT_LEFT, 4 * rect.Width() / 5 - 60);
	m_list.InsertColumn(2, L"������", LVCFMT_LEFT, 2*rect.Width() / 5);
	int j = 0;
	while (!m_pRecordset->adoEOF)
	{
		str_1 = m_pRecordset->GetCollect("���");
		str_2 = m_pRecordset->GetCollect("����ѧУ");
		str_3 = m_pRecordset->GetCollect("������");
		m_list.InsertItem(j, str_1);
		m_list.SetItemText(j, 1, str_2);
		m_list.SetItemText(j, 2, str_3);
		j++;
		m_pRecordset->MoveNext();
	}
	m_list1.SetBkColor(RGB(255,255,255));
	m_list1.SetTextBkColor(RGB(207,206,207));
	str_Command = L"select * from Stu_Award where ѧ�� = '" + str_Name + L"'order by ���";
	m_pRecordset = m_pConnection->Execute((_bstr_t)str_Command, NULL, adCmdText);
	m_list1.GetWindowRect(&rect);
	m_list1.InsertColumn(0, L"���", LVCFMT_LEFT, rect.Width() / 2 - 50);
	m_list1.InsertColumn(1, L"����", LVCFMT_LEFT, rect.Width() + 50);

	j = 0;
	while (!m_pRecordset->adoEOF)
	{
		str_1 = m_pRecordset->GetCollect("���");
		str_2 = m_pRecordset->GetCollect("����");
		m_list1.InsertItem(j, str_1);
		m_list1.SetItemText(j, 1, str_2);
		j++;
		m_pRecordset->MoveNext();
	}
	m_pConnection->Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void Stu_Info::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	Stu_function.LoadBackgroud(dc, IDB_BITMAP_StuInfo, m_rect);
	//dc.SetBkMode(TRANSPARENT);
	//dc.SetTextColor(RGB(171, 15, 132));
	//GetDlgItem(IDC_STATIC1)->SetWindowTextW(L"������Ϣ");
	CDialogEx::OnPaint();
}


HBRUSH Stu_Info::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SetBkMode(TRANSPARENT);

		pDC->SetTextColor(RGB(0,0,0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);//͸����ˢ
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

void Stu_Info::ChangeSize(UINT nID, int x, int y)  //nIDΪ�ؼ�ID��x,y�ֱ�Ϊ�Ի���ĵ�ǰ���Ϳ�
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL)     //�ж��Ƿ�Ϊ�գ���Ϊ�ڴ��ڴ�����ʱ��Ҳ�����OnSize���������Ǵ�ʱ�����ؼ���û�д�����PwndΪ��
	{
		CRect rec;
		pWnd->GetWindowRect(&rec);  //��ȡ�ؼ��仯ǰ�Ĵ�С
		ScreenToClient(&rec);   //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x / m_rect.Width();  //���ձ��������ռ����λ��
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec);   //�����ؼ�
	}
}

void Stu_Info::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (nType != SIZE_MINIMIZED)  //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
		ChangeSize(IDC_STATIC1, cx, cy);  //��ÿһ���ؼ�����������
		ChangeSize(IDC_STATIC2, cx, cy);
		ChangeSize(IDC_STATIC3, cx, cy);
		for (int i = 1034; i <= 1067;++i)
			ChangeSize(i, cx, cy);
		ChangeSize(IDC_STATIC_32,cx,cy);
		ChangeSize(IDC_STATIC_33,cx,cy);
		GetClientRect(&m_rect);   //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ����ꣻ
	}
}


BOOL Stu_Info::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN)
    { 
		switch(pMsg->wParam)
        { case VK_RETURN: return TRUE; //���λس�
          case VK_ESCAPE: return TRUE; //����Esc
        }
    }
	return CDialogEx::PreTranslateMessage(pMsg);
}

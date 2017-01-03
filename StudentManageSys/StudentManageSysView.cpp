
// StudentManageSysView.cpp : CStudentManageSysView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CStudentManageSysView ����/����

CStudentManageSysView::CStudentManageSysView()
{
	point = 0;
}

CStudentManageSysView::~CStudentManageSysView()
{
}

BOOL CStudentManageSysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	
	return CView::PreCreateWindow(cs);
}

// CStudentManageSysView ����

void CStudentManageSysView::OnDraw(CDC* /*pDC*/)
{
	CStudentManageSysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CStudentManageSysView ��ӡ

BOOL CStudentManageSysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CStudentManageSysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CStudentManageSysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CStudentManageSysView ���

#ifdef _DEBUG
void CStudentManageSysView::AssertValid() const
{
	CView::AssertValid();
}

void CStudentManageSysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStudentManageSysDoc* CStudentManageSysView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentManageSysDoc)));
	return (CStudentManageSysDoc*)m_pDocument;
}
#endif //_DEBUG


// CStudentManageSysView ��Ϣ�������

void CStudentManageSysView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//����ͼƬ
	CRect rctClient;
	GetClientRect(rctClient);
	function.LoadBackgroud(dc, IDB_BITMAP_Back, rctClient);
	if (point == 1)
	{
		str_Info = L"��ã�" + m_str_Loginingname + L" ( " + User_Type + L" )";
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
			if (MessageBox(L"�Ƿ�Ҫע����ǰ�˺ţ�", L"��ʾ", MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
			{
				CMainFrame::point = 0;
				CString str_Check = L"update User_Passwd set ��½״̬ = 0 where ѧ�� = '" + Logining_Name + L"'";
				M_pRecordset = M_pConnection->Execute(_bstr_t(str_Check), NULL, adCmdText);
				MessageBox(L"ע���ɹ���");
				M_pConnection->Close();
				m_LoginStatue = IDCANCEL;
				Logining_Name = L"";
				menu_Login.DestroyMenu();
				menu_Exit.LoadMenu(IDR_MAINFRAME);
				this->GetParent()->SetMenu(&menu_Exit);
	
				//��ֹ��ʱ��
				delete m_DateTimeCtrl;
				delete listbox;
				delete dlg;
				KillTimer(1);			
				font.DeleteObject();
				//delete listbox;
				point = 0;
				//���»�����Ļ
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
			if (User_Type == L"ѧ��")
				menu_Login.LoadMenu(IDR_MENU1);
			else
			{
				if(User_Type == L"��ʦ")
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
			//��ʾ��Ϣ
			font.CreatePointFont(120, L"����");
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
			Invalidate();  //�����ػ���Ļ����ʾ���û���Ϣ
		}
	}
}


void CStudentManageSysView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		tm = CTime::GetCurrentTime();
		m_DateTimeCtrl->SetTime(&tm);
		m_DateTimeCtrl->SetFormat(L"yyyy-MM-dd HH:mm:ss");
	}
	CView::OnTimer(nIDEvent);
}

//�鿴���˿α�
void CStudentManageSysView::OnJxgrkb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽεص�", L"�Ͽν�ʦ" };
	m_listbox.Setlist(str, 6);
	if (User_Type == L"ѧ��")
	{
		CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.ѧ�� = '" +
			Logining_Name + "' and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱��";
		m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
	}
	else
	{
		CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.ѧ�� = '" +
			Logining_Name + "' and s1.�γ̱�� = s2.�γ̱��";
		m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
	}
}

//�鿴�α��γ�
void CStudentManageSysView::OnJxkckb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽεص�", L"�Ͽν�ʦ" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.ѧ�� = '" +
			Logining_Name + "' and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱�� order by s1.��Ŀ����";
	CString str_1 = str[0];
	str[0] = str[1];
	str[1] = str_1;
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//�鿴�α���ʦ
void CStudentManageSysView::OnJxjskb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"�Ͽν�ʦ", L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽεص�" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.ѧ�� = '" +
			Logining_Name + "' and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱�� order by s2.�Ͽν�ʦ";
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//�鿴�α�����
void CStudentManageSysView::OnJxbjkb()
{
	Invalidate();
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	ListBox m_listbox(listbox);
	m_listbox.SetRect(rect_Client);
	m_listbox.Create_ListBox(this, IDC_MYLISTBOX);
	CString str[6] = { L"�Ͽεص�", L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽν�ʦ" };
	m_listbox.Setlist(str, 6);
	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.ѧ�� = '" +
			Logining_Name + "' and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱�� order by s1.�Ͽεص�";
	m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
}

//��ʦ��ѯѧ���Ŀα�
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
		CString str[6] = { L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽεص�", L"�Ͽν�ʦ" };
		m_listbox.Setlist(str, 6);
		if (search.m_str == L"����ѧ��")
		{
			CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2 where s.ѧ�� = '" +
				search.str_Info + "' and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱��";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		else
		{
			CString str_Table = L"select * from Student_Table s,Subject_Table s1,Teacher_Table s2,Register r where r.�û��� = '" +
				search.str_Info + "' and s.ѧ�� = r.ѧ�� and s.�γ̱�� = s1.�γ̱�� and s.�γ̱�� = s2.�γ̱��";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		
	}
}
//�鿴ѧ��������Ϣ
void CStudentManageSysView::OnXjxx()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	dlg->str_Name = Logining_Name;   //����ǰ��¼���û�������
	dlg->Create(IDD_DIALOG_StuInfo, this);
	dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
	if(dlg->point == 0)
	{
		MessageBox(L"�Բ��������Ϣû�б�¼�룡",L"��ʾ");
		dlg->DestroyWindow();
	}
	else
		dlg->ShowWindow(SW_SHOW);//��ʾ
}


HBRUSH CStudentManageSysView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CView::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		//pDC->SetBkColor(RGB(255,0,0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0,0,0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}  	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

//�޸��˺�����
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

//�޸ĵ�½����
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
		CString str = L"update User_Passwd set ���� = '" + m_modifypasswd.m_strrepasswd + L"' where ѧ�� = '" + Logining_Name + L"'";
		M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
		
		if(PathFileExists(L"remember_auto.txt"))
		{
			CFile m_Remember_Auto;
			m_Remember_Auto.Remove(L"remember_auto.txt");
		}
		MessageBox(L"�����޸ĳɹ���ע������Ч��\n���μ�������룡");	
	}
}

//���ѧ��
void CStudentManageSysView::On32809()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Register reg_user;
	reg_user.m_point = 1;
	reg_user.m_str = L"���";
	reg_user.m_str1 = L"�����ѧ��";
	reg_user.m_str2 = L"ȡ�����ѧ��";
	reg_user.DoModal();
}

//����Ա��ѯ��ʦ�α�
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
		CString str[6] = { L"�γ̱��", L"��Ŀ����", L"�Ͽ��ܴ�", L"�Ͽ�ʱ��", L"�Ͽεص�", L"�Ͽν�ʦ" };
		m_listbox.Setlist(str, 6);
		if (search.m_str == L"����ѧ��")
		{
			CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.ѧ�� = '" +
			search.str_Info + "' and s1.�γ̱�� = s2.�γ̱��";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		else
		{
			CString str_Table = L"select * from Subject_Table s1,Teacher_Table s2 where s2.�Ͽν�ʦ = '" +
			search.str_Info + "' and s1.�γ̱�� = s2.�γ̱��";
			m_listbox.SetShowList(M_pConnection, M_pRecordset, str, 6, str_Table);
		}
		
	}
}

//����Աע�������Ϣ
void CStudentManageSysView::OnXjzc()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Base_Info m_base(m_str_Loginingname,Logining_Name,2);
	if(m_base.DoModal() == IDOK)
		m_base.Insert_info(M_pConnection, M_pRecordset);
}

//¼��ѧ����Ϣ
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


//ѧ��������Ϣ��ѯ
void CStudentManageSysView::OnXjbm()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Select m_select(L"����ѧ��ѧ�ţ�",L"ѧ��",L"��ѯ");
	if(m_select.DoModal() == IDOK)
	{
		dlg->str_Name = m_select.m_id;   //����ǰ��¼���û�������
		dlg->Create(IDD_DIALOG_StuInfo, this);
		dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
		if(dlg->point == 0)
		{
			MessageBox(L"�Բ��������Ϣû�б�¼�룡",L"��ʾ");
			dlg->DestroyWindow();
		}
		else
			dlg->ShowWindow(SW_SHOW);//��ʾ
	}
	
}

//��ʦ������Ϣ��ѯ
void CStudentManageSysView::On32819()
{
	listbox->DestroyWindow();
	dlg->DestroyWindow();
	Select m_select(L"�����ʦ��ţ�",L"��ʦ",L"��ѯ");
	if(m_select.DoModal() == IDOK)
	{
		dlg->str_Name = m_select.m_id;   //����ǰ��¼���û�������
		dlg->Create(IDD_DIALOG_StuInfo, this);
		dlg->MoveWindow(0, 30, rect_Client.right, rect_Client.bottom-30);
		if(dlg->point == 0)
		{
			MessageBox(L"�Բ��������Ϣû�б�¼�룡",L"��ʾ");
			dlg->DestroyWindow();
		}
		else
			dlg->ShowWindow(SW_SHOW);//��ʾ
	}
}

//�޸�ѧ������
void CStudentManageSysView::On32811()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Select m_select(L"����ѧ����ѧ�ţ�",L"ѧ��",L"�޸�");
	if(m_select.DoModal() == IDOK)
	{
		CString str = L"update User_Passwd set ���� = '" + m_select.m_newpasswd + L"' where ѧ�� = '" + m_select.m_id + L"'";
		try
			{
				M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
			MessageBox(L"�޸ĳɹ���");
	}
}

//�޸Ľ�ʦ����
void CStudentManageSysView::On32814()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Select m_select(L"�����ʦ�ı�ţ�",L"��ʦ",L"�޸�");
	if(m_select.DoModal() == IDOK)
	{
		CString str = L"update User_Passwd set ���� = '" + m_select.m_newpasswd + L"' where ѧ�� = '" + m_select.m_id + L"'";
		try
			{
				M_pConnection->Execute(_bstr_t(str), NULL, adCmdText);
			}
			catch (_com_error e)
			{
				AfxMessageBox(e.Description());
				return;
			}
			MessageBox(L"�޸ĳɹ���");
	}
}


//ѧ���鿴�ɼ�
void CStudentManageSysView::OnCjck()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Search_Score m_search_Score(Logining_Name);
	m_search_Score.DoModal();
}

//��ʦ�鿴�ɼ�
void CStudentManageSysView::OnGlycjck()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Search_Score m_search_Score(Logining_Name,1);
	m_search_Score.DoModal();
}

//¼��ɼ�
void CStudentManageSysView::OnGlylrcj()
{
	dlg->DestroyWindow();
	listbox->DestroyWindow();
	Insert_score m_insert(Logining_Name);
	m_insert.DoModal();
}

//����Ա��ѯѧ���ɼ�
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

//ѧ���ɼ��ֲ�
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

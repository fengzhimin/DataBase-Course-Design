#include "stdafx.h"
#include "Function.h"

Function::Function()
{
	button = new CMFCButton;
}


Function::~Function()
{
	delete button;
}

void Function::Show_Hide_Passwd(CButton& arg1, CButton& arg2, CEdit& cedit_1, CEdit& cedit_2)
{
	CString Reg_Passwd, Reg_rePasswd;
	cedit_1.GetWindowTextW(Reg_Passwd);
	cedit_2.GetWindowTextW(Reg_rePasswd);
	if (arg1.GetCheck() == 1)
	{
		arg2.SetCheck(0);
		cedit_1.SetPasswordChar('*');
		cedit_2.SetPasswordChar('*');
	}
	else
	{
		arg2.SetCheck(1);
		cedit_1.SetPasswordChar('\0');
		cedit_2.SetPasswordChar('\0');
	}
	cedit_1.SetWindowTextW(Reg_Passwd);
	cedit_2.SetWindowTextW(Reg_rePasswd);
}

void Function::LoadBackgroud(CPaintDC &dc,int IDB,CRect rect)
{
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap m_bmp;
	m_bmp.LoadBitmap(IDB);
	BITMAP bitmap;
	m_bmp.GetBitmap(&bitmap);
	CBitmap   *pbmpOld = dcMem.SelectObject(&m_bmp);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	dcMem.SelectObject(pbmpOld);
	DeleteObject(dcMem);
}

void Function::Create_Button(CMFCButton* button, CString title, CString info, CWnd* cwnd, int IDB, CFont& font, CRect rect,
	COLORREF BackgroudColor, COLORREF fontColor, COLORREF selectbuttonColor)
{
	//创建一个按钮控件
	button->Create(title, WS_CHILD | WS_VISIBLE | WS_BORDER, rect, cwnd, IDB);
	//设置字体大小
	button->SetFont(&font);
	//设置按钮背景颜色
	button->SetFaceColor(BackgroudColor);
	//设置按钮文本颜色
	button->SetTextColor(fontColor);
	//设置按钮被选中的颜色
	button->SetTextHotColor(selectbuttonColor);
	//设置光标图像
	button->SetMouseCursorHand();
	//设置工具提示文本与指定的控件相关联
	button->SetTooltip(info);
}

//void Function::Create_ListBox(CListCtrl* listbox, _ConnectionPtr& Connect, _RecordsetPtr& Record, CWnd* wnd, int ID, CRect rect, CString str_Name)
//{
//	listbox->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
//		CRect(10, 30, rect.right - 10, rect.bottom - 10), wnd, ID);
//	listbox->SetBkColor(RGB(12, 56, 23));
//	listbox->SetTextBkColor(RGB(124, 121, 112));
//	int i = (rect.right - 20) / 6;
//	listbox->InsertColumn(0, L"课程编号", LVCFMT_CENTER, i - 20);
//	listbox->InsertColumn(1, L"科目名称", LVCFMT_CENTER, i + 20);
//	listbox->InsertColumn(2, L"上课周次", LVCFMT_CENTER, i);
//	listbox->InsertColumn(3, L"上课时间", LVCFMT_CENTER, i);
//	listbox->InsertColumn(4, L"上课地点", LVCFMT_CENTER, i);
//	listbox->InsertColumn(5, L"教师", LVCFMT_LEFT, i);
//	CString str_Table = L"select * from Student_Table s,Subject_Table s1,Subject s2 where s.用户姓名 = '" +
//		str_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号";
//	Record = Connect->Execute(_bstr_t(str_Table), NULL, adCmdText);
//	CString str_1, str_2, str_3, str_4, str_5, str_6;
//	int j = 0;
//	while (!Record->adoEOF)
//	{
//		str_1 = Record->GetCollect("课程编号");
//		str_2 = Record->GetCollect("科目名称");
//		str_3 = Record->GetCollect("上课周次");
//		str_4 = Record->GetCollect("上课时间");
//		str_5 = Record->GetCollect("上课地点");
//		str_6 = Record->GetCollect("上课教师");
//		listbox->InsertItem(j, str_1);
//		listbox->SetItemText(j, 1, str_2);
//		listbox->SetItemText(j, 2, str_3);
//		listbox->SetItemText(j, 3, str_4);
//		listbox->SetItemText(j, 4, str_5);
//		listbox->SetItemText(j, 5, str_6);
//		j++;
//		Record->MoveNext();
//	}
//}
#include "stdafx.h"
#include "ListBox.h"


ListBox::ListBox(CListCtrl* listbox)
{
	m_listbox = listbox;
}

ListBox::~ListBox()
{
	
}

void ListBox::SetRect(CRect rect)
{
	m_rect = rect;
}

void ListBox::Setlist(CString* str_list, int size)
{
	int i = (m_rect.right - 20) / 6;
	for (int j = 0; j < size;++j)
		m_listbox->InsertColumn(j, str_list[j], LVCFMT_CENTER, i);
}

void ListBox::SetShowList(_ConnectionPtr& Connect, _RecordsetPtr& Record, CString* str_showlist, int size,CString str_command)
{
	/*CString str_Table = L"select * from Student_Table s,Subject_Table s1,Subject s2 where s.用户姓名 = '" +
		str_Name + "' and s.课程编号 = s1.课程编号 and s.课程编号 = s2.课程编号";*/
	Record = Connect->Execute(_bstr_t(str_command), NULL, adCmdText);
	CString str;
	int j = 0;
	while (!Record->adoEOF)
	{
		for (int i = 0; i < size; ++i)
		{
			if (i == 0)
			{
				str = Record->GetCollect((const _variant_t)(str_showlist[i]));
				m_listbox->InsertItem(j, str);
			}
			else
			{
				str = Record->GetCollect((const _variant_t)(str_showlist[i]));
				m_listbox->SetItemText(j, i, str);
			}
		}
		j++;
		Record->MoveNext();
		/*str_1 = Record->GetCollect("课程编号");
		str_2 = Record->GetCollect("科目名称");
		str_3 = Record->GetCollect("上课周次");
		str_4 = Record->GetCollect("上课时间");
		str_5 = Record->GetCollect("上课地点");
		str_6 = Record->GetCollect("上课教师");
		m_listbox->InsertItem(j, str_1);
		m_listbox->SetItemText(j, 1, str_2);
		m_listbox->SetItemText(j, 2, str_3);
		m_listbox->SetItemText(j, 3, str_4);
		m_listbox->SetItemText(j, 4, str_5);
		m_listbox->SetItemText(j, 5, str_6);
		j++;
		Record->MoveNext();*/
	}
}

void ListBox::Create_ListBox(CWnd* wnd, int ID)
{
	m_listbox->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT,
		CRect(10, 30, m_rect.right - 10, m_rect.bottom - 10), wnd, ID);
	m_listbox->SetBkColor(RGB(255,255,255));
	m_listbox->SetTextBkColor(RGB(207,206,207));
}
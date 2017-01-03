#pragma once
class ListBox
{
public:
	ListBox(CListCtrl* listbox);
	~ListBox();
private:
	CListCtrl* m_listbox;
	CRect m_rect;    //用于设置列表控件的大小
public:
	//str_list用于存储将要设置的列的名称
	void Setlist(CString* str_list,int size);    //设置列的个数
	//str_showlist用于存储获取从数据库中要得到的列名   str_command用于存储要执行的SQL语句
	void SetShowList(_ConnectionPtr& Connect, _RecordsetPtr& Record, CString* str_showlist, int size,CString str_command);    //设置在列中显示的内容
	void SetRect(CRect rect);    //设置列表控件的显示范围
	void Create_ListBox(CWnd* wnd, int ID);
};


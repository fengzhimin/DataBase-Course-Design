#pragma once
class ListBox
{
public:
	ListBox(CListCtrl* listbox);
	~ListBox();
private:
	CListCtrl* m_listbox;
	CRect m_rect;    //���������б�ؼ��Ĵ�С
public:
	//str_list���ڴ洢��Ҫ���õ��е�����
	void Setlist(CString* str_list,int size);    //�����еĸ���
	//str_showlist���ڴ洢��ȡ�����ݿ���Ҫ�õ�������   str_command���ڴ洢Ҫִ�е�SQL���
	void SetShowList(_ConnectionPtr& Connect, _RecordsetPtr& Record, CString* str_showlist, int size,CString str_command);    //������������ʾ������
	void SetRect(CRect rect);    //�����б�ؼ�����ʾ��Χ
	void Create_ListBox(CWnd* wnd, int ID);
};


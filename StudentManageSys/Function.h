#pragma once
#include <afx.h>
class Function : public CObject
{
public:
	Function();
	~Function();
	void Show_Hide_Passwd(CButton& arg1, CButton& arg2, CEdit& cedit_1, CEdit& cedit_2);
	void LoadBackgroud(CPaintDC &dc,int IDB,CRect rect);
	CMFCButton* button;
	//����һ����ť�ؼ�   ����ID����Ҫ�Լ��ֶ���Resource.h�ļ������
	void Create_Button(CMFCButton* button,CString title, CString info, CWnd* cwnd, int IDB, CFont& font, CRect rect,
		COLORREF BackgroudColor = RGB(125, 124, 125), COLORREF fontColor = RGB(255, 255, 255), COLORREF selectbuttonColor = RGB(12, 124, 12));
	
};


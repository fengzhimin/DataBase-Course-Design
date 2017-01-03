
// StudentManageSysView.h : CStudentManageSysView ��Ľӿ�
//
#include "Function.h"
#include "Stu_Login.h"
#include "ListBox.h"
#include "Search_StuInfo.h"
#include "Stu_Info.h"
#include "SetUser.h"
#include "MainFrm.h"
#include "ModifyPasswd.h"
#include "Register.h"
#include "Base_Info.h"
#include "Choose.h"
#include "Select.h"
#include "Search_Score.h"
#include "Insert_score.h"
#include "Search_StuScore.h"
#include "Score_Scope.h"
#pragma once


class CStudentManageSysView : public CView
{
protected: // �������л�����
	CStudentManageSysView();
	DECLARE_DYNCREATE(CStudentManageSysView)

// ����
public:
	CStudentManageSysDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CStudentManageSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBtnDown();
	CButton button;
	Function function;

	afx_msg void OnExit();
	afx_msg void OnLogin();

	_ConnectionPtr M_pConnection;
	_RecordsetPtr M_pRecordset;
	int m_LoginStatue;
	CString Logining_Name,Logining_Passwd,m_str_Loginingname;    //���ڴ洢���ڵ�½���û���������
	CMenu menu_Login, menu_Exit;
	CString User_Type;    //��¼��½����
	CFont font;
	CDateTimeCtrl* m_DateTimeCtrl;
	CTime tm;
	CString str_Info;   //����Ļ����ʾ��̬���û���
	CRect rect_Client;    
	Stu_Info* dlg; //����ȫ�ֱ���
	int point;    //��¼�ػ涯̬���û���
	CListCtrl* listbox;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnJxgrkb();
	afx_msg void OnJxkckb();
	afx_msg void OnJxjskb();
	afx_msg void OnJxbjkb();
	afx_msg void OnGlyckxskb();
	afx_msg void OnXjxx();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnXgmm();
	
	afx_msg void On32808();
	afx_msg void On32809();
	afx_msg void OnGlycxjskb();
	afx_msg void OnXjzc();
	afx_msg void On32817();
	afx_msg void OnXjbm();
	afx_msg void On32819();
	afx_msg void On32811();
	afx_msg void On32814();
	afx_msg void OnCjck();
	afx_msg void OnGlycjck();
	afx_msg void OnGlylrcj();
	afx_msg void OnCxxscj();
	afx_msg void OnCjfb();
};

#ifndef _DEBUG  // StudentManageSysView.cpp �еĵ��԰汾
inline CStudentManageSysDoc* CStudentManageSysView::GetDocument() const
   { return reinterpret_cast<CStudentManageSysDoc*>(m_pDocument); }
#endif


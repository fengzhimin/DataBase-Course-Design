
// StudentManageSysView.h : CStudentManageSysView 类的接口
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
protected: // 仅从序列化创建
	CStudentManageSysView();
	DECLARE_DYNCREATE(CStudentManageSysView)

// 特性
public:
	CStudentManageSysDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CStudentManageSysView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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
	CString Logining_Name,Logining_Passwd,m_str_Loginingname;    //用于存储正在登陆的用户名和密码
	CMenu menu_Login, menu_Exit;
	CString User_Type;    //记录登陆类型
	CFont font;
	CDateTimeCtrl* m_DateTimeCtrl;
	CTime tm;
	CString str_Info;   //在屏幕上显示动态的用户名
	CRect rect_Client;    
	Stu_Info* dlg; //申明全局变量
	int point;    //记录重绘动态的用户名
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

#ifndef _DEBUG  // StudentManageSysView.cpp 中的调试版本
inline CStudentManageSysDoc* CStudentManageSysView::GetDocument() const
   { return reinterpret_cast<CStudentManageSysDoc*>(m_pDocument); }
#endif


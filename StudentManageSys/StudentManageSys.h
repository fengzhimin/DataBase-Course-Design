
// StudentManageSys.h : StudentManageSys Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CStudentManageSysApp:
// �йش����ʵ�֣������ StudentManageSys.cpp
//

class CStudentManageSysApp : public CWinApp
{
public:
	CStudentManageSysApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStudentManageSysApp theApp;

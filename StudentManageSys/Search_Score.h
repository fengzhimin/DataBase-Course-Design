#pragma once
#include "afxcmn.h"
#include "Function.h"

// Search_Score �Ի���

class Search_Score : public CDialogEx
{
	DECLARE_DYNAMIC(Search_Score)

public:
	Search_Score(CString str,int i = 0,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Search_Score();

// �Ի�������
	enum { IDD = IDD_DIALOG13 };
	CRect m_rect;
	CRect rect;
	int point;   //�����ѧ���鿴�ɼ����ǽ�ʦ�鿴�ɼ�  0:ѧ��  1����ʦ
	Function Stu_function;
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	CString str_Command;
	CString str_id;
	CString min,max;   //���ڲ�ѯ�ɼ��ֲ�ʽʹ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CListCtrl m_list;
};

#pragma once

#include "Function.h"
#include "afxcmn.h"
// Stu_Info �Ի���

class Stu_Info : public CDialogEx
{
	DECLARE_DYNAMIC(Stu_Info)

public:
	Stu_Info(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Stu_Info();

// �Ի�������
	enum { IDD = IDD_DIALOG_StuInfo };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRect m_rect;
	Function Stu_function;
	CString str_Name;    //���ڼ�¼��ǰ��¼���û�
	CString str_Command;   //���ڴ洢ִ�е�SQL���
	CRect rect;
	_ConnectionPtr m_pConnection;
	_RecordsetPtr m_pRecordset;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void ChangeSize(UINT nID, int x, int y);   //�ı䴰�ڵ�ʱ��ؼ�Ҳ��֮�ı�
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CListCtrl m_list;
	CListCtrl m_list1;
	int point;  //���ڱ�ʶѧ����Ϣ�Ƿ��Ѿ�¼��
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

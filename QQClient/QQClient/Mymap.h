#pragma once
#include "explorer1.h"


// CMymap �Ի���

class CMymap : public CDialogEx
{
	DECLARE_DYNAMIC(CMymap)

public:
	CMymap(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMymap();

// �Ի�������
	enum { IDD = IDD_DLG_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_ie;
	virtual BOOL OnInitDialog();
	CString m_start1;
	CString m_end1;
	CString m_start2;
	CString m_end2;
	CString m_find;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
};

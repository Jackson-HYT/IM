#pragma once
#include "afxcmn.h"


// CHistDlg �Ի���

class CHistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistDlg)

public:
	CHistDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHistDlg();

// �Ի�������
	enum { IDD = IDD_CHAT_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	UserInfo m_info;
	CRichEditCtrl m_hist;
};

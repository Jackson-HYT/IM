#pragma once
#include "afxcmn.h"


// CAllHist �Ի���

class CAllHist : public CDialogEx
{
	DECLARE_DYNAMIC(CAllHist)

public:
	CAllHist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAllHist();

// �Ի�������
	enum { IDD = IDD_DLG_ALL_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_hist;
	virtual BOOL OnInitDialog();
	UserInfo m_info;
};

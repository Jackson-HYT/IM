#pragma once
#include "shockwaveflash1.h"


// CPlayGame �Ի���

class CPlayGame : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayGame)

public:
	CPlayGame(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlayGame();

// �Ի�������
	enum { IDD = IDD_DLG_PLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 flashshow;
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};

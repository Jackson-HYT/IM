#pragma once
#include "afxwin.h"

#include"About.h"
// CLogin �Ի���
#include"PictureEx.h"
#include "shockwaveflash1.h"
class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
	enum { IDD = IDD_LOGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_username;
	CString m_password;
	afx_msg void OnBnClickedBtnNewuser();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
//	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
//	CButton m_Btn;
	virtual BOOL OnInitDialog();
	CPictureEx *pAutoGif;
	CShockwaveflash1 flashshow;
	CString m_vir_Username;
	afx_msg void OnBnClickedButton1();
	CAbout ABdlg;
};


// QQServerDlg.h : ͷ�ļ�
//

#pragma once
#include"SocketL.h"
#include"SocketC.h"
#include "afxwin.h"
#include "afxcmn.h"
#include"LoginDlg.h"
#include"User.h"
// CQQServerDlg �Ի���
class CQQServerDlg : public CDialogEx
{
// ����
public:
	CQQServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_QQSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CSocketL m_sock;
	_ConnectionPtr m_pConn;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int OnAdd(UserInfo info);
	int OnLogin(UserInfo info);
	void OnReceive(UserInfo info);
	CEdit m_hist;
	CListCtrl m_ListCtrl_UserInfo;
	int i = 0;
	int m_user_number;
	void OnUpdata();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	CLoginDlg m_dlg;
	afx_msg void OnDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);
	CUser dlg;
	afx_msg void OnEnChangeEdtUsernumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_static;
	CEdit m_now;
};

#pragma once


// CUser �Ի���

class CUser : public CDialogEx
{
	DECLARE_DYNAMIC(CUser)

public:
	CUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUser();

// �Ի�������
	enum { IDD = IDD_USER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Username;
	CString m_Password;
	afx_msg void OnBnClickedOk();
};

#pragma once


// CURL �Ի���

class CURL : public CDialogEx
{
	DECLARE_DYNAMIC(CURL)

public:
	CURL(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CURL();

// �Ի�������
	enum { IDD = IDD_DLG_URL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_Add;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};

// URL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "URL.h"
#include "afxdialogex.h"
#define READ_BYTE_SIZE     1024  
#include <afxinet.h>

// CURL �Ի���

IMPLEMENT_DYNAMIC(CURL, CDialogEx)

CURL::CURL(CWnd* pParent /*=NULL*/)
	: CDialogEx(CURL::IDD, pParent)
	, m_Add(_T(""))
{

}

CURL::~CURL()
{
}

void CURL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Add);
}


BEGIN_MESSAGE_MAP(CURL, CDialogEx)
	ON_BN_CLICKED(IDOK, &CURL::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CURL::OnBnClickedCancel)
END_MESSAGE_MAP()


// CURL ��Ϣ�������


void CURL::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString m_PathName;
	CFileDialog    dlg(FALSE, _T("*.*"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"),
		NULL); //��������Ի���
	if (dlg.DoModal() != IDOK)
		return;
	m_PathName = dlg.GetPathName();

	CInternetSession    is;
	CStdioFile        *psf;
	UpdateData();
	psf = is.OpenURL(m_Add, 1, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
	CFile    file(m_PathName,
		CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);//���������ļ�

	char    buf[READ_BYTE_SIZE];
	int    readbyte;
	while (1)
	{
		readbyte = psf->Read(buf, READ_BYTE_SIZE);//ÿ������READ_BYTE_SIZE�ֽ�����
		if (!readbyte)
			break;
		file.Write(buf, readbyte); //�����ص�����д�뵽�ļ���
	}

	psf->Close();
	file.Close();
	delete psf;
	CString string1 = _T("�ļ��Ѿ�������");
	string1 += m_PathName;
	MessageBox(string1);
}


void CURL::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

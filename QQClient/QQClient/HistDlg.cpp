// HistDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "HistDlg.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"
#include<atlconv.h>
#define MAX_FILE_SIZE 5000
// CHistDlg �Ի���

IMPLEMENT_DYNAMIC(CHistDlg, CDialogEx)

CHistDlg::CHistDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHistDlg::IDD, pParent)
{

}

CHistDlg::~CHistDlg()
{
}

void CHistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICH_HIST, m_hist);
}


BEGIN_MESSAGE_MAP(CHistDlg, CDialogEx)
END_MESSAGE_MAP()


// CHistDlg ��Ϣ�������


BOOL CHistDlg::OnInitDialog()
{
	USES_CONVERSION;
	CDialogEx::OnInitDialog();
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	strcpy(m_info.Username, T2A(dlg->m_MyselfName));
	CFile HistFile;
	CString string1(m_info.Username);
	string1 += _T("��");
	string1 += m_info.From_Username;
	CString title(string1);
	string1 += _T("�������¼.txt");
	
	title += _T("�������¼");
	SetWindowText(title);
	HistFile.Open(string1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	char *buff = new char[MAX_FILE_SIZE];
	int nCount=0;
	nCount = HistFile.GetLength()/MAX_FILE_SIZE;
	if (HistFile.GetLength() % MAX_FILE_SIZE != 0)
	{
		nCount++;
	}
	int i = 0;
	for (i = 0; i < nCount; i++)
	{
		int nOther = MAX_FILE_SIZE;//ÿ�ζ���д�Ĵ�С���ʼ��ʼΪ��������С
		if (i == nCount - 1) //��������һ��
		{
			nOther = HistFile.GetLength() % MAX_FILE_SIZE;//�趨����д�Ĵ�С
		}
		//ZeroMemory(buff, nOther); //��buff�е�nOther��������Ϊ0
		ZeroMemory(buff, MAX_FILE_SIZE);
		HistFile.Read(buff, nOther);
		PARAFORMAT pf;
		pf.dwMask = PFM_ALIGNMENT;
		pf.wAlignment = PFA_CENTER; //PFA_CENTER or PFA_LEFT//���ó������
		m_hist.SetParaFormat(pf);
		m_hist.SetSel(-1, -1);
		CString str;
		str.Format(_T("%s"), (CStringW)buff);
		m_hist.ReplaceSel(str);

	}


	UpdateData(FALSE);
	CFont * f;
	f = new CFont;
	f->CreateFont(20, // nHeight   
		0, // nWidth   
		0, // nEscapement   
		0, // nOrientation   
		FW_BOLD, // nWeight   
		FALSE, // bItalic   
		FALSE, // bUnderline   
		0, // cStrikeOut   
		ANSI_CHARSET, // nCharSet   
		OUT_DEFAULT_PRECIS, // nOutPrecision   
		CLIP_DEFAULT_PRECIS, // nClipPrecision   
		DEFAULT_QUALITY, // nQuality   
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily   
		_T("΢���ź�")); // lpszFac   
	GetDlgItem(IDC_RICH_HIST)->SetFont(f);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

// AllHist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "AllHist.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"
#define MAX_FILE_SIZE 5000
// CAllHist �Ի���

IMPLEMENT_DYNAMIC(CAllHist, CDialogEx)

CAllHist::CAllHist(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAllHist::IDD, pParent)
{

}

CAllHist::~CAllHist()
{
}

void CAllHist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_hist);
}


BEGIN_MESSAGE_MAP(CAllHist, CDialogEx)
END_MESSAGE_MAP()


// CAllHist ��Ϣ�������


BOOL CAllHist::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	UpdateData(TRUE);
	
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	CString name; 
	name.Format(_T("%s"), m_info.Username);
	//GetDlgItemText(IDC_M_USERNAME);
	name += _T("1��������.txt");
	CFile HistFile;
	HistFile.Open(_T("1��������.txt"), CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	char *buff = new char[MAX_FILE_SIZE];
	int nCount = 0;
	nCount = HistFile.GetLength() / MAX_FILE_SIZE;
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
//	delete[]buff;
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
	GetDlgItem(IDC_RICHEDIT21)->SetFont(f);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

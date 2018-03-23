// LoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQServer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include"QQServerDlg.h"
#include<atlconv.h>
// CLoginDlg �Ի���

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_rootname(_T(""))
	, m_rootpassword(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROOT_NAME, m_rootname);
	DDX_Text(pDX, IDC_ROOT_PASSWORD, m_rootpassword);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH, flashshow);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
//	ON_EN_CHANGE(IDC_EDIT2, &CLoginDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CLoginDlg ��Ϣ�������


void CLoginDlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	USES_CONVERSION;
	UpdateData(TRUE);
	if (!strcmp(T2A(m_rootname), "root"))
	{
		if (!strcmp(T2A(m_rootpassword), "123456"))
		{
			OnOK();
		}
		else
		{
			MessageBox(_T("������󣡣���"), _T("���棡"));
			return;
		}
	}
	else
	{
		MessageBox(_T("��½ʧ�ܣ�����"), _T("���棡"));
		exit(0);
	}

}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this);


	RECT rc;
	this->GetClientRect(&rc);//��ÿͻ���������

	//����flash��λ��

	rc.left = 0;

	rc.right = rc.right;



	rc.bottom = rc.bottom;

	flashshow.MoveWindow(&rc, true);



	TCHAR strCurDrt[5000];

	int nLen = ::GetCurrentDirectory(5000, strCurDrt);

	if (strCurDrt[nLen] != '\\')

	{

		strCurDrt[nLen++] = '\\';

		strCurDrt[nLen] = '\0';

	}



	CString strFileName = strCurDrt;

	strFileName += _T("high.swf");//clock.swf��flash�ļ������֣���flash�ļ����ڹ���Ŀ¼�¡�

	flashshow.LoadMovie(0, strFileName);

	flashshow.Play();


	//return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	exit(0);
}


LRESULT CLoginDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
	{
		nHitTest = HTCAPTION;
	}
	return nHitTest;
}


void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * f;
	f = new CFont;
	f->CreateFont(30, // nHeight   
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
	GetDlgItem(IDC_ROOT_NAME)->SetFont(f);
	GetDlgItem(IDC_ROOT_PASSWORD)->SetFont(f);


	//CString m_sRootPath;
	//GetModuleFileName(NULL, m_sRootPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	//m_sRootPath.ReleaseBuffer();
	//int nPos;
	//nPos = m_sRootPath.ReverseFind('\\');
	//m_sRootPath = m_sRootPath.Left(nPos);
	//CString strMovieUrl = m_sRootPath + "\\6789.swf"; //flash�ļ���start.swf��Ӧ����DebugĿ¼��  
	//flashshow.LoadMovie(0, strMovieUrl);	  ////���ز����Ŷ��� 
	//flashshow.Play();



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//void CLoginDlg::OnEnChangeEdit2()
//{
//	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
//	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
//	// ���������� CRichEditCtrl().SetEventMask()��
//	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
//
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//}

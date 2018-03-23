// Newuser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "Newuser.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"
#include<atlconv.h>
// CNewuser �Ի���

IMPLEMENT_DYNAMIC(CNewuser, CDialogEx)

CNewuser::CNewuser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewuser::IDD, pParent)
	, m_newusername(_T(""))
	, m_newpassword1(_T(""))
	, m_newpassword2(_T(""))
{

}

CNewuser::~CNewuser()
{
}

void CNewuser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_newusername);
	DDX_Text(pDX, IDC_EDIT2, m_newpassword1);
	DDX_Text(pDX, IDC_EDIT3, m_newpassword2);
	DDX_Control(pDX, IDC_EDIT4, m_edt1);
	DDX_Control(pDX, IDC_EDIT5, m_edt2);
	DDX_Control(pDX, IDC_EDIT6, m_edt3);
}


BEGIN_MESSAGE_MAP(CNewuser, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewuser::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNewuser ��Ϣ�������


void CNewuser::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	/*if (!dlg->m_sock.Connect(_T("192.168.187.1"), 8888))
	AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));*/
	USES_CONVERSION;
	UpdateData(TRUE);
	
	if (strcmp(T2A(m_newpassword1), T2A(m_newpassword2)))
	{
		AfxMessageBox(_T("     ������������벻��ͬ,\n             ���������룡"));
		return;
	}
	//CQQClientDlg *dlg = (CQQClientDlg*)AfxGetMainWnd();
	int nCmd = INFO_ADD;
	UserInfo info;
	strcpy_s(info.Username, T2A(m_newusername));
	strcpy_s(info.Password, T2A(m_newpassword2));
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&info, sizeof(info));

}


void CNewuser::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP8);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(HALFTONE);             //*����ڴ�
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


HBRUSH CNewuser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT4)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0, 0, 0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
		//pDC->SetBkMode(TRANSPARENT); //͸��

	}
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT5)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0, 0, 0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
		//pDC->SetBkMode(TRANSPARENT); //͸��

	}
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT6)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(0, 0, 0));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
		//pDC->SetBkMode(TRANSPARENT); //͸��

	}
	return hbr;
}


BOOL CNewuser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * f1;
	f1 = new CFont;
	f1->CreateFont(20, // nHeight   
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
	m_edt1.SetFont(f1);
	m_edt2.SetFont(f1);
	m_edt3.SetFont(f1);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetDlgItemText(IDC_EDIT4,_T("�µ��û�"));
	SetDlgItemText(IDC_EDIT5, _T("����"));
	SetDlgItemText(IDC_EDIT6, _T("ȷ������"));
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
	GetDlgItem(IDC_EDIT1)->SetFont(f);
	GetDlgItem(IDC_EDIT2)->SetFont(f);
	GetDlgItem(IDC_EDIT3)->SetFont(f);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

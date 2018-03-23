// AllChat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "AllChat.h"
#include "afxdialogex.h"
#include<atlconv.h>
#include"QQClientDlg.h"
#include<string.h>

// CAllChat �Ի���

IMPLEMENT_DYNAMIC(CAllChat, CDialogEx)

CAllChat::CAllChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAllChat::IDD, pParent)
	, m_input(_T(""))
{

}

CAllChat::~CAllChat()
{
}

void CAllChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_hist);
	DDX_Text(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CAllChat, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAllChat::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PICTURE, &CAllChat::OnBnClickedBtnPicture)
	ON_BN_CLICKED(IDC_BTN_HIST, &CAllChat::OnBnClickedBtnHist)
END_MESSAGE_MAP()


// CAllChat ��Ϣ�������


void CAllChat::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	CFile WriteFile;
	USES_CONVERSION;
	UpdateData(TRUE);
	int nCmd = 0;
	nCmd = INFO_ALLTEXT;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString str;
	CString str1(m_input);//��ȡ���ͱ༭���ֵ
	CString name;
	CString name1;
	str.Format(_T("%d��%d��%d�� %02d:%02d:%02d "), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	name.Format(_T(" %s˵"), CStringW(dlg->m_info.Username));
	name1.Format(_T("%s��������.txt"), CStringW(dlg->m_info.Username));
	str += name;
	str += _T("\r\n");
	str += str1;
	str += _T("\r\n");
	//CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);
	PARAFORMAT pf;
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//���ó������
	m_hist.SetParaFormat(pf);
	m_hist.SetSel(-1, -1);
	m_hist.ReplaceSel(str);
	
	
	CStringA str2(str);
	WriteFile.Open(name1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	WriteFile.SeekToEnd();
	WriteFile.Write(str2, str2.GetLength());
	WriteFile.Close();
	
	UserInfo Send_Info;
	strcpy_s(Send_Info.Text, T2A(m_input));
	strcpy_s(Send_Info.From_Username, (dlg->m_info.Username));
	strcpy_s(Send_Info.From_sIP, dlg->m_info.sIP);
	PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));

	
	m_input.Format(_T(""));
	UpdateData(FALSE);



}


void CAllChat::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//CFont * f;
	//f = new CFont;
	//f->CreateFont(20, // nHeight   
	//	0, // nWidth   
	//	0, // nEscapement   
	//	0, // nOrientation   
	//	FW_BOLD, // nWeight   
	//	TRUE, // bItalic   
	//	FALSE, // bUnderline   
	//	0, // cStrikeOut   
	//	ANSI_CHARSET, // nCharSet   
	//	OUT_DEFAULT_PRECIS, // nOutPrecision   
	//	CLIP_DEFAULT_PRECIS, // nClipPrecision   
	//	DEFAULT_QUALITY, // nQuality   
	//	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily   
	//	_T("΢���ź�")); // lpszFac   
	//GetDlgItem(IDC_RICHEDIT21)->SetFont(f);
	//GetDlgItem(IDC_EDIT1)->SetFont(f);
}


BOOL CAllChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetWindowText(_T("������"));
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
	GetDlgItem(IDC_EDIT1)->SetFont(f);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CAllChat::OnBnClickedBtnPicture()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nCmd;
	nCmd = INFO_ALLPICTURE;
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("��ѡ����Ҫ���͵ı���");
	fileDlg.m_ofn.lpstrFilter = _T("All Files(*.*)\0*.*\0\0");
	if (IDOK == fileDlg.DoModal())
	{
		USES_CONVERSION;
		CString str(fileDlg.GetPathName());
		CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
		COleDateTime time = COleDateTime::GetCurrentTime();
		CString str1;
		str1.Format(_T("%d��%d��%d�� %02d:%02d:%02d "), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		CString name;
		name.Format(_T(" %s˵\r\n"), CStringW(dlg->m_info.Username));
		str1 += name;
		PARAFORMAT pf;
		pf.dwMask = PFM_ALIGNMENT;
		pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//���ó������
		m_hist.SetParaFormat(pf);
		m_hist.SetSel(-1, -1);
		m_hist.ReplaceSel(str1);
		InsertBitmap(str);
		m_hist.ReplaceSel(_T("\r\n"));
		UserInfo Send_Info;
		strcpy(Send_Info.From_Username, (dlg->m_info.Username));
		strcpy(Send_Info.From_sIP, dlg->m_info.sIP);
		strcpy(Send_Info.From_Path, T2A(str));
		dlg->m_sock.Send(&nCmd, sizeof(nCmd));
		dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));
	}
}


void CAllChat::InsertBitmap(CString pBmpFile)
{
	HBITMAP hBmp;
	hBmp = (HBITMAP)::LoadImage(NULL, pBmpFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);


	STGMEDIUM stgm;
	stgm.tymed = TYMED_GDI;
	stgm.hBitmap = hBmp;
	stgm.pUnkForRelease = NULL;


	FORMATETC fm;
	fm.cfFormat = CF_BITMAP;
	fm.ptd = NULL;
	fm.dwAspect = DVASPECT_CONTENT;
	fm.lindex = -1;
	fm.tymed = TYMED_GDI;


	//������������Դ  
	IStorage* pStorage;


	//�����ڴ�  
	LPLOCKBYTES lpLockBytes = NULL;
	SCODE sc = CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}
	ASSERT(lpLockBytes != NULL);


	sc = StgCreateDocfileOnILockBytes(lpLockBytes, STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);
	if (sc != S_OK)
	{
		VERIFY(lpLockBytes->Release() == 0);
		lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(pStorage != NULL);


	COleDataSource* pDataSource = new COleDataSource;
	pDataSource->CacheData(CF_BITMAP, &stgm);
	LPDATAOBJECT lpDataObject = (LPDATAOBJECT)pDataSource->GetInterface(&IID_IDataObject);


	//��ȡRichEdit��OLEClientSite  
	LPOLECLIENTSITE lpClientSite;
	m_hist.GetIRichEditOle()->GetClientSite(&lpClientSite);


	//����OLE����  
	IOleObject* pOleObject;
	sc = OleCreateStaticFromData(lpDataObject, IID_IOleObject, OLERENDER_FORMAT, &fm, lpClientSite, pStorage, (void**)&pOleObject);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}


	//����ole����  
	REOBJECT reObject;
	ZeroMemory(&reObject, sizeof(reObject));
	reObject.cbStruct = sizeof(REOBJECT);


	CLSID clsid;
	sc = pOleObject->GetUserClassID(&clsid);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}


	reObject.clsid = clsid;
	reObject.cp = REO_CP_SELECTION;
	reObject.dvaspect = DVASPECT_CONTENT;
	reObject.poleobj = pOleObject;
	reObject.polesite = lpClientSite;
	reObject.pstg = pStorage;


	HRESULT hr = m_hist.GetIRichEditOle()->InsertObject(&reObject);


	delete pDataSource;
}


void CAllChat::OnBnClickedBtnHist()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	USES_CONVERSION;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	strcpy(m_hist_dlg.m_info.Username,T2A(dlg->m_MyselfName));
	m_hist_dlg.DoModal();
	//if (m_hist_dlg == NULL)//û����
	//{
	//	m_hist_dlg = new CAllHist;
	//	m_hist_dlg->Create(IDD_DLG_ALL_HIST);
	//}

	//m_hist_dlg->ShowWindow(SW_SHOW);
	
}
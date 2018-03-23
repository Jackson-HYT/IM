
// QQClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "QQClientDlg.h"
#include "afxdialogex.h"
#include"ChatDlg.h"
#include"URL.h"
#include<atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#define ID_ME_TIMER 1001
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CQQClientDlg �Ի���
CQQClientDlg::~CQQClientDlg()
{
	delete m_all_chatdlg;
}


CQQClientDlg::CQQClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQClientDlg::IDD, pParent)
	, m_username(_T(""))
	, m_MyselfName(_T(""))
	, m_MyIP(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CQQClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_USERINFO, m_friendlist);
	DDX_Text(pDX, IDC_M_USERNAME, m_MyselfName);
	DDX_Text(pDX, IDC_EDT_IP, m_MyIP);
}

BEGIN_MESSAGE_MAP(CQQClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USERINFO, &CQQClientDlg::OnDblclkListUserinfo)
	ON_BN_CLICKED(IDC_BTN_REFRESH, &CQQClientDlg::OnBnClickedBtnRefresh)
	//ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USERINFO, &CQQClientDlg::OnLvnItemchangedListUserinfo)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USERINFO, &CQQClientDlg::OnDblclkListUserinfo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_USERINFO, &CQQClientDlg::OnLvnItemchangedListUserinfo)
	//ON_NOTIFY(NM_CLICK, IDC_LIST_USERINFO, &CQQClientDlg::OnClickListUserinfo)
	ON_WM_NCHITTEST()
//	ON_WM_NCLBUTTONDOWN()
//	ON_BN_CLICKED(IDOK, &CQQClientDlg::OnBnClickedOk)
//ON_BN_CLICKED(IDCANCEL, &CQQClientDlg::OnBnClickedCancel)
ON_MESSAGE(WM_SHOWTASK, OnShowTask)
ON_EN_CHANGE(IDC_M_USERNAME, &CQQClientDlg::OnEnChangeMUsername)
ON_BN_CLICKED(IDC_BTN_ALLCHAT, &CQQClientDlg::OnBnClickedBtnAllchat)
ON_WM_TIMER()
//ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_BN_CLICKED(IDC_BYN_PLAY, &CQQClientDlg::OnBnClickedBynPlay)
ON_BN_CLICKED(IDC_BUTTON1, &CQQClientDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BTN_MAP, &CQQClientDlg::OnBnClickedBtnMap)
ON_WM_CLOSE()
ON_BN_CLICKED(IDC_BTN_PALY, &CQQClientDlg::OnBnClickedBtnPaly)
ON_BN_CLICKED(IDC_BTN_MENU, &CQQClientDlg::OnBnClickedBtnMenu)
//ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CQQClientDlg ��Ϣ�������

BOOL CQQClientDlg::OnInitDialog()
{	
	if (!m_sock.Create(0))
	{
		AfxMessageBox(_T("����ʧ�ܣ�"));
	}
	if (!m_sock.Connect(_T("127.0.0.1"), 8888))
		AfxMessageBox(_T("���ӷ�����ʧ�ܣ�"));

	if ((m_dlg).DoModal() != IDOK)
	{
		OnOK();
	}
	int nCmd = 0;
	nCmd = INFO_BROW;
	m_sock.Send(&nCmd, sizeof(nCmd));
	CDialogEx::OnInitDialog();
	m_friendlist.InsertColumn(0, _T("�û���"), 0, 120);
	m_friendlist.InsertColumn(1, _T("IP��ַ"), 0, 120);
	m_friendlist.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//::SetWindowPos(GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	RECT rc;
	GetWindowRect(&rc);
	rc.bottom = rc.bottom - 95;
	SetWindowPos(NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);
	
	char szIP[50];
	gethostname(szIP, sizeof(szIP));//��ȡ��������
	hostent*pHost = gethostbyname(szIP);//ͨ���������ƻ�ȡ����IP
	in_addr * ad = (in_addr*)pHost->h_addr;//IPת��
	
	m_MyIP.Format(_T("%s"), CStringW(inet_ntoa(*ad)));
	SetDlgItemText(IDC_EDT_IP, m_MyIP);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
// ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CQQClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(SW_HIDE);
		m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		m_nid.hWnd = this->m_hWnd;
		m_nid.uID = IDI_ICON1;
		m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����  
		m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
		wcscpy_s(m_nid.szTip, _T("QQ"));                  // ��Ϣ��ʾ��Ϊ"zidlg"��VS2008 UNICODE������wcscpy_s()����  
		Shell_NotifyIcon(NIM_ADD, &m_nid);   // �����������ͼ��  
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CQQClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CRect rect;
		

		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP13);
		
		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		
		CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
		
		dc.SetStretchBltMode(HALFTONE);             //*����ڴ�
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CQQClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CQQClientDlg::OnDblclkListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
//	int nSel = p->iItem;
//	//CString Username;
//	if (nSel < 0)
//		return;
//	CChatDlg*pdlg = (CChatDlg*)m_friendlist.GetItemData(nSel);
//	pdlg->Create(IDD_CHAR_DLG, GetDesktopWindow());
//	pdlg->ShowWindow(SW_SHOW);
//	pdlg->SetForegroundWindow();
//	*pResult = 0;
//}


void CQQClientDlg::OnBnClickedBtnRefresh()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int nCmd = 0;
	nCmd = INFO_BROW;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	
	

}


//void CQQClientDlg::OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}


void CQQClientDlg::OnDblclkListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	USES_CONVERSION;
	//CFile WriteFile;

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString Username;
	CString szIP;
	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
	int nSel = p->iItem;
	
	if (nSel < 0)
		return;
	CChatDlg* pDlg = (CChatDlg*)m_friendlist.GetItemData(nSel);
	if (pDlg==NULL)
	{

		pDlg=new CChatDlg;
		Username = m_friendlist.GetItemText(p->iItem, 0);
		Username.TrimLeft();
		szIP = m_friendlist.GetItemText(p->iItem, 1);
		strcpy_s(pDlg->info.Username, T2A(Username));
		strcpy_s(pDlg->info.sIP, T2A(szIP));
		strcpy_s(pDlg->info.From_Username, T2A(m_MyselfName));//�Ի����Ա�����������˭
		//m_friendlist.GetItemText(nSel, 0, LPTSTR(pDlg->info.Username), sizeof(pDlg->info.Username));
		//m_friendlist.GetItemText(nSel, 1, LPTSTR(pDlg->info.sIP), sizeof(pDlg->info.sIP));
		pDlg->Create(IDD_CHAR_DLG, GetDesktopWindow());
		m_friendlist.SetItemData(nSel, (DWORD)pDlg);
	}
	pDlg->ShowWindow(SW_SHOW);
	pDlg->SetForegroundWindow();
	//CString str1(pDlg->info.From_Username), str2;
	//
	//str1+=_T("��");
	//
	//str2.Format(_T("�������¼.txt"));
	//str1 += pDlg->info.Username;
	//str1 += str2;
	//WriteFile.Open(str1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	//WriteFile.Close();
	*pResult = 0;
}


void CQQClientDlg::OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


//void CQQClientDlg::OnClickListUserinfo(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	USES_CONVERSION;
//	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	UpdateData();
//	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
//	int nSel = p->iItem;
//
//	if (nSel < 0)
//		return;
//	CTalkDlg*pDlg = NULL;
//	pDlg=	(CTalkDlg*)m_friendlist.GetItemData(nSel);
//	if (!pDlg)
//	{
//		pDlg = new CTalkDlg;
//		pDlg->Create(IDD_DLG_CHAT, GetDesktopWindow());
//	}
//	pDlg->ShowWindow(SW_SHOW);
//	pDlg->SetForegroundWindow();
//	*pResult = 0;
//}


void CQQClientDlg::OnText(UserInfo info)
{
	USES_CONVERSION;
	CQQClientDlg*dlg = (CQQClientDlg*)AfxGetMainWnd();
	//CString str;
	//str.Format(_T("���յ�������%s����Ϣ��", info.From_Username));
	//AfxMessageBox(str);
	int i = -1;
	int nCount = 0;
	nCount = m_friendlist.GetItemCount();
	while (++i<nCount)
	{
		CString str_user(m_friendlist.GetItemText(i, 0));
		CString str_IP(m_friendlist.GetItemText(i, 1));
		str_user.TrimLeft();
		str_IP.TrimLeft();
		if (!strcmp(T2A(str_user), info.From_Username) /*|| !strcmp(T2A(str_IP), info.sIP)*/)
		{
			CChatDlg*pDlg = (CChatDlg*)m_friendlist.GetItemData(i);
			if (pDlg==NULL)
			{
				pDlg = new CChatDlg;
				strcpy_s(pDlg->info.Username, info.From_Username);
				strcpy_s(pDlg->info.sIP, info.sIP);
				pDlg->Create(IDD_CHAR_DLG, GetDesktopWindow());
				m_friendlist.SetItemData(i, (DWORD)pDlg);
			}
			strcpy_s(pDlg->info.Username, info.From_Username);
			CString str;
			COleDateTime time = COleDateTime::GetCurrentTime();
			str.Format(_T("%d��%d��%d�� %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
			CString msg;
			msg.Format(_T("%s"), CStringW(info.Text));
			str += msg;
			str += _T("\r\n\r\n");
			//CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);
			//richEdit = new CRichEditCtrl;
			PARAFORMAT pf;
			pf.dwMask = PFM_ALIGNMENT;
			pf.wAlignment = PFA_LEFT; //PFA_CENTER or PFA_LEFT//���ó������
			//richEdit->SetParaFormat(pf);
			//richEdit->SetSel(-1, -1);
			//richEdit->ReplaceSel(str);
			//delete richEdit;
			pDlg->m_hist.SetParaFormat(pf);
			pDlg->m_hist.SetSel(-1, -1);
			pDlg->m_hist.ReplaceSel(str);
			pDlg->ShowWindow(SW_SHOW);
			pDlg->SetForegroundWindow();
			pDlg->FlashWindow(TRUE);

			CFile HistFile;
			CString filename(info.Username);
			filename += _T("��");
			filename += info.From_Username;
			filename += _T("�������¼.txt");
			HistFile.Open(filename, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
			HistFile.SeekToEnd();
			CString name(info.From_Username);
			name += _T("˵\r\n");
			CStringA str3;
			str3 = str;
			name += str3;
			name += _T("\r\n\r\n");
			HistFile.Write((CStringA)name, name.GetLength());
			HistFile.Close();
			return;
		}
	}
}


CString CQQClientDlg::OnFile(UserInfo Rece_Info)
{
	USES_CONVERSION;
	int i = -1;
	int nCount = 0;
	nCount = m_friendlist.GetItemCount();
	while (++i < nCount)
	{
		CString str_user(m_friendlist.GetItemText(i, 0));
		CString str1(m_friendlist.GetItemText(i, 1));
		str_user.TrimLeft();
		if (!strcmp(T2A(str_user), Rece_Info.From_Username))
		{
			CChatDlg*pDlg = (CChatDlg*)m_friendlist.GetItemData(i);
			if (!pDlg)
			{
				pDlg = new CChatDlg;
				strcpy_s(pDlg->info.Username, Rece_Info.From_Username);
				
				strcpy_s(pDlg->info.sIP, T2A(str1));
				pDlg->Create(IDD_CHAR_DLG, GetDesktopWindow());
				m_friendlist.SetItemData(i, (DWORD)pDlg);
			}
			pDlg->ShowWindow(SW_SHOW);
			pDlg->SetForegroundWindow();
			pDlg->FlashWindow(TRUE);
			TCHAR szFilter[] = _T("�ı��ļ�(*.txt)|*.txt|ѹ���ļ�(*.rar)|*.rar|�����ļ�(*.*)|*.*||");
			CFileDialog fileDlg(FALSE, _T("doc"),A2T(Rece_Info.fileName), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
			if (IDOK == fileDlg.DoModal())
			{
				
				return fileDlg.GetPathName();
			}

			
		}

	}


}


LRESULT CQQClientDlg::OnNcHitTest(CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
	{
		nHitTest = HTCAPTION;
	}
	return nHitTest;
}


//void CQQClientDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	if (nHitTest == HTTOP)
//	{
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
//	}
//	else if (nHitTest == HTBOTTOM)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTTOPLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTTOPRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTBOTTOMLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTBOTTOMRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTCAPTION)
//		SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
//	CDialogEx::OnNcLButtonDown(nHitTest, point);
//
//
//	CDialogEx::OnNcLButtonDown(nHitTest, point);
//}


//void CQQClientDlg::OnBnClickedOk()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnOK();
//}


//void CQQClientDlg::OnBnClickedCancel()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CDialogEx::OnCancel();
//}
BOOL CQQClientDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class  
	// ��������ɾ��ͼ��  
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	return CDialog::DestroyWindow();
}
afx_msg LRESULT CQQClientDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDI_ICON1)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�  
	{

		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);                    // �õ����λ��  
		CMenu menu;
		menu.CreatePopupMenu();                    // ����һ������ʽ�˵�  
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�ر�"));
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDOWN:                                 // ��������Ĵ���  
	{
		CWnd *pWnd = AfxGetMainWnd();
		HWND hHwnd = pWnd->m_hWnd;
		HMODULE hUser32 = GetModuleHandle(_T("user32"));
		SwitchToThisWindow = (PROCSWITCHTOTHISWINDOW)GetProcAddress(hUser32, ("SwitchToThisWindow"));
		SwitchToThisWindow(hHwnd, TRUE);
		// ��ʾ������  
	}
	break;
	}
	return 0;
}


void CQQClientDlg::OnEnChangeMUsername()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CQQClientDlg::OnBnClickedBtnAllchat()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_all_chatdlg == NULL)//û����
	{
		m_all_chatdlg = new CAllChat;
		m_all_chatdlg->Create(IDD_ALL_CHAT);
	}
	
	m_all_chatdlg->ShowWindow(SW_SHOW);
}


void CQQClientDlg::OnAllText(UserInfo info)
{
	UpdateData(TRUE);
	CFile WriteFile;

	if (!m_all_chatdlg)
	{
		m_all_chatdlg = new CAllChat;
		m_all_chatdlg->Create(IDD_ALL_CHAT, GetDesktopWindow());
		
	}
	m_all_chatdlg->ShowWindow(SW_SHOW);
	m_all_chatdlg->SetForegroundWindow();
	CString str;
	COleDateTime time = COleDateTime::GetCurrentTime();
	str.Format(_T("%d��%d��%d�� %02d:%02d:%02d"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	CString name;
	name.Format(_T(" %s˵\r\n"), CStringW(info.From_Username));
	CString msg;
	msg.Format(_T("%s"), CStringW(info.Text));
	str += name;
	str += msg;
	str += _T("\r\n\r\n");
	PARAFORMAT pf;
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_LEFT; //PFA_CENTER or PFA_LEFT//���ó������
	//richEdit->SetParaFormat(pf);
	//richEdit->SetSel(-1, -1);
	//richEdit->ReplaceSel(str);
	//delete richEdit;
	m_all_chatdlg->m_hist.SetParaFormat(pf);
	m_all_chatdlg->m_hist.SetSel(-1, -1);
	m_all_chatdlg->m_hist.ReplaceSel(str);
	m_all_chatdlg->ShowWindow(SW_SHOW);
	m_all_chatdlg->SetForegroundWindow();
	m_all_chatdlg->FlashWindow(TRUE);

	CString name1(m_info.Username);
	name1 += _T("��������.txt");
	CStringA str1(str);
	WriteFile.Open(name1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	WriteFile.SeekToEnd();
	WriteFile.Write(str1, str1.GetLength());
	WriteFile.Close();
	UpdateData(FALSE);

	
}


//void CAboutDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnTimer(nIDEvent);
//}


void CQQClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nCmd = 0;
	nCmd = INFO_BROW;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));


	CDialogEx::OnTimer(nIDEvent);
}


//void CQQClientDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}


void CQQClientDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
	
}


void CQQClientDlg::OnBnClickedBynPlay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_Music_dlg == NULL)//û����
	{
		m_Music_dlg = new CMusicDlg;
		m_Music_dlg->Create(IDD_DLG_MUSIC);
	}

	m_Music_dlg->ShowWindow(SW_SHOW);
}


void CQQClientDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_url == NULL)//û����
	{
		m_url = new CURL;
		m_url->Create(IDD_DLG_URL);
	}

	m_url->ShowWindow(SW_SHOW);

}


void CQQClientDlg::OnBnClickedBtnMap()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_map == NULL)//û����
	{
		m_map = new CMymap;
		m_map->Create(IDD_DLG_MAP);
	}

	m_map->ShowWindow(SW_SHOW);
}


void CQQClientDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DWORD dwStyle = AW_CENTER;    //���ж���  
	HINSTANCE hInst = LoadLibrary(_T("User32.DLL")); //���붯̬��  
	typedef BOOL(WINAPI MYFUNC(HWND, DWORD, DWORD));//���庯������  
	MYFUNC* AnimateWindow;//���庯��ָ��  
	AnimateWindow = (MYFUNC *)::GetProcAddress(hInst, "AnimateWindow");//��ȡ������ַ  
	AnimateWindow(this->GetSafeHwnd(), 500, AW_HIDE | dwStyle);//���ô��嶯��  
	FreeLibrary(hInst);//�ͷŶ�̬��  
	CDialogEx::OnClose();
}


void CQQClientDlg::OnBnClickedBtnPaly()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_game == NULL)//û����
	{
		m_game = new CPlayGame;
		m_game->Create(IDD_DLG_PLAY);
	}

	m_game->ShowWindow(SW_SHOW);
}

bool min = true;
void CQQClientDlg::OnBnClickedBtnMenu()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	RECT rc;
	GetWindowRect(&rc);
	if (min == false)
	{
		rc.bottom = rc.bottom-95;
		SetWindowPos(NULL, 0, 0, rc.right-rc.left, rc.bottom-rc.top , SWP_NOMOVE);
		min = true;
		GetDlgItem(IDC_BTN_MENU)->SetWindowTextW(_T("����"));

	}
	else
	{
		rc.bottom = rc.bottom + 95;
		SetWindowPos(NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_NOMOVE);
		min = false;
		GetDlgItem(IDC_BTN_MENU)->SetWindowTextW(_T("����"));
	}
	
}


//HBRUSH CQQClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CQQClientDlg::OnCtlColor(pDC, pWnd, nCtlColor);
//	//if (CTLCOLOR_STATIC == nCtlColor)
//	//{
//	//	pDC->SetBkMode(TRANSPARENT);
//	//	return   (HBRUSH)::GetStockObject(NULL_BRUSH);
//
//	//}
//	// TODO:  �ڴ˸��� DC ���κ�����
//	//pDC->SetBkColor(RGB(255,255,255));
//	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
//	//return (HBRUSH)GetStockObject(WHITE_BRUSH);
//	return hbr;
//}


HBRUSH CQQClientDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_M_USERNAME)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(255, 255, 255));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
		//pDC->SetBkMode(TRANSPARENT); //͸��

	}
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDT_IP)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(255, 255, 255));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
		//pDC->SetBkMode(TRANSPARENT); //͸��

	}

	return hbr;
}


void CQQClientDlg::OnPicture(UserInfo info)
{
	USES_CONVERSION;
	//CString str;
	//str.Format(_T("���յ�������%s����Ϣ��", info.From_Username));
	//AfxMessageBox(str);
	int i = -1;
	int nCount = 0;
	nCount = m_friendlist.GetItemCount();
	while (++i < nCount)
	{
		CString str_user(m_friendlist.GetItemText(i, 0));
		CString str_IP(m_friendlist.GetItemText(i, 1));
		str_user.TrimLeft();
		str_IP.TrimLeft();
		if (!strcmp(T2A(str_user), info.From_Username) /*|| !strcmp(T2A(str_IP), info.sIP)*/)
		{
			CChatDlg*pDlg = (CChatDlg*)m_friendlist.GetItemData(i);
			if (!pDlg)
			{
				pDlg = new CChatDlg;
				strcpy_s(pDlg->info.Username, info.From_Username);
				strcpy_s(pDlg->info.sIP, info.sIP);
				pDlg->Create(IDD_CHAR_DLG, GetDesktopWindow());
				m_friendlist.SetItemData(i, (DWORD)pDlg);
			}
			strcpy_s(pDlg->info.Username, info.From_Username);
			CString str;
			COleDateTime time = COleDateTime::GetCurrentTime();
			str.Format(_T("%d��%d��%d�� %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

			//CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);
			//richEdit = new CRichEditCtrl;
			PARAFORMAT pf;
			pf.dwMask = PFM_ALIGNMENT;
			pf.wAlignment = PFA_LEFT; //PFA_CENTER or PFA_LEFT//���ó������
			pDlg->m_hist.SetParaFormat(pf);
			pDlg->m_hist.SetSel(-1, -1);
			pDlg->m_hist.ReplaceSel(str);
			pDlg->InsertBitmap(A2T(info.From_Path));
			pDlg->m_hist.ReplaceSel(_T("\r\n"));
			pDlg->ShowWindow(SW_SHOW);
			pDlg->SetForegroundWindow();
			pDlg->FlashWindow(TRUE);
		}
	}
}

void CQQClientDlg::OnAllPicture(UserInfo info)
{
	USES_CONVERSION;
	UpdateData(TRUE);
	if (!m_all_chatdlg)
	{
		m_all_chatdlg = new CAllChat;
		m_all_chatdlg->Create(IDD_CHAR_DLG, GetDesktopWindow());

	}
	m_all_chatdlg->ShowWindow(SW_SHOW);
	m_all_chatdlg->SetForegroundWindow();
	CString str;
	COleDateTime time = COleDateTime::GetCurrentTime();
	str.Format(_T("%d��%d��%d�� %02d:%02d:%02d"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	CString name;
	name.Format(_T(" ��%s˵\r\n"), CStringW(info.From_Username));
	str += name;
	str += _T("\r\n");
	PARAFORMAT pf;
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_LEFT; //PFA_CENTER or PFA_LEFT//���ó������
	//richEdit->SetParaFormat(pf);
	//richEdit->SetSel(-1, -1);
	//richEdit->ReplaceSel(str);
	//delete richEdit;
	m_all_chatdlg->m_hist.SetParaFormat(pf);
	m_all_chatdlg->m_hist.SetSel(-1, -1);
	m_all_chatdlg->m_hist.ReplaceSel(str);
	m_all_chatdlg->InsertBitmap(A2T(info.From_Path));
	m_all_chatdlg->m_hist.ReplaceSel(_T("\r\n"));
	m_all_chatdlg->ShowWindow(SW_SHOW);
	m_all_chatdlg->SetForegroundWindow();
	m_all_chatdlg->FlashWindow(TRUE);
}

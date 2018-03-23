// MusicDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "MusicDlg.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"

// CMusicDlg �Ի���
#include <MMSystem.h>  
#include <Digitalv.h>  

#pragma comment(lib, "Winmm.lib")  

HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;

void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //�ڼ����ļ�ǰ�������һ�β��ŵ��豸  
	mciopenparms.lpstrElementName = strFilepath; //�������ļ�·�������豸  
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//��������ʧ��,��������Ϣ������buffer,����ʾ������  
		char buffer[256];
		mciGetErrorString(dwReturn, (LPWSTR)buffer, 256); //��ȡ�������Ӧ�Ĵ�����Ϣ  
		MessageBox(hWnd, (LPWSTR)buffer, _T("�����棡"), MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //����������Ϣ��ʾ�Ի���  
	}
	DeviceId = mciopenparms.wDeviceID;
	//���ļ��ɹ��͹����ļ����豸  
}

void play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //ÿ�β��Ŷ��Ǵ�0��ʼ����  
	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
}


void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}


void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}

void stop()
{
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	//�����ֹͣ��ťʱ,�����е���Ϣ�������  
}


DWORD setVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS setvolume; //���������Ĳ����ṹ��  
	setvolume.dwCallback = NULL; //  
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //��������������  
	setvolume.dwValue = vol; //����ֵ��vol  
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}







IMPLEMENT_DYNAMIC(CMusicDlg, CDialogEx)

CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicDlg::IDD, pParent)
	, m_path(_T(""))
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSIC_LIST, m_music_list);
	DDX_Text(pDX, IDC_filename, m_path);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_exitbtn, &CMusicDlg::OnBnClickedexitbtn)
	ON_BN_CLICKED(IDC_filechoice, &CMusicDlg::OnBnClickedfilechoice)
	ON_BN_CLICKED(IDC_play, &CMusicDlg::OnBnClickedplay)
	ON_BN_CLICKED(IDC_pause, &CMusicDlg::OnBnClickedpause)
	ON_BN_CLICKED(IDC_stop, &CMusicDlg::OnBnClickedstop)
	ON_NOTIFY(NM_DBLCLK, IDC_MUSIC_LIST, &CMusicDlg::OnDblclkMusicList)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMusicDlg ��Ϣ�������


void CMusicDlg::OnBnClickedexitbtn()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel(); //�˳�  
}

void GetFileFromDir(CString csDirPath)
{
	csDirPath += _T("\\*.mp3");
	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	theApp.m_musiclist.AddTail(fileData.cFileName);
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState){
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		theApp.m_musiclist.AddTail(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}
















void CMusicDlg::OnBnClickedfilechoice()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	CString csDirParth;
	CString m_csFileName;
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);
	CString musicpath = m_csFileName.Right(iEndPos);

	theApp.m_musiclist.RemoveAll();
	GetFileFromDir(csDirParth);

	POSITION pos = theApp.m_musiclist.GetHeadPosition();
	
	int i = 0;
	int nCount=theApp.m_musiclist.GetCount();
	m_music_list.DeleteAllItems();
	while (i<nCount&&pos)
	{
		m_music_list.InsertItem(i, theApp.m_musiclist.GetAt(pos)); 
		theApp.m_musiclist.GetNext(pos);
		
	}
	POSITION pos2 = theApp.m_musiclist.GetHeadPosition();
	m_path = csDirParth;
	while (pos2)
	{
		theApp.m_pathlist.AddTail(csDirParth +_T("\\") +theApp.m_musiclist.GetAt(pos2));
		theApp.m_musiclist.GetNext(pos2);
	}


	
	//Load(this->m_hWnd, strFilepath);

	//TCHAR szFileFilter[] = _T("mp3�ļ�(*.mp3)|*.mp3|wma�ļ�(*.wma)|*.wma|wav�ļ�(*.wav)|*.wav|�����ļ�(*.*)|*.*||");
	////TCHAR szFilter[] = _T("mp3�ļ�(*.mp3)|*.txt|ͼƬ�ļ�(*.png)|*.png|ͼƬ�ļ�(*.jpg)|*.jpg|�����ļ�(*.*)|*.*||");
	////CQQClientDlg Dlg1 = (CQQClientDlg*)AfxGetMainWnd();
	//CFileDialog dlg(TRUE, _T("mp3"), NULL, 0, szFileFilter);
	//if (dlg.DoModal() == IDOK)
	//{
	//	CString strFilepath = dlg.GetPathName();
	//	CString strFilename = dlg.GetFileName();
	//	SetDlgItemText(IDC_filename, strFilename);
	//	Load(this->m_hWnd, strFilepath);
	//}
	GetDlgItem(IDC_play)->EnableWindow(true); //�ļ���ȡ�ɹ�ʱ���а�ť��ɿ�ѡ  
	GetDlgItem(IDC_pause)->EnableWindow(true);
	GetDlgItem(IDC_stop)->EnableWindow(true);
	UpdateData(FALSE);
}


void CMusicDlg::OnBnClickedplay()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	play();
	SetDlgItemText(IDC_pause, _T("��ͣ"));
}


void CMusicDlg::OnBnClickedpause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //��ȡ��ť��״̬  
	if (strTemp.Compare(_T("��ͣ")) == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, _T("�ָ�"));
	}

	if (strTemp.Compare(_T("�ָ�")) == 0)
	{
		resume();
		SetDlgItemText(IDC_pause, _T("��ͣ"));
	}
}



void CMusicDlg::OnBnClickedstop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	stop();
	SetDlgItemText(IDC_pause, _T("��ͣ"));
	GetDlgItem(IDC_play)->EnableWindow(false); //������stop��ʱ��,���ź���ͣ����ѡ  
	GetDlgItem(IDC_pause)->EnableWindow(false);
}


BOOL CMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_music_list.InsertColumn(0, _T("������"), 0, 200);

	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMusicDlg::OnDblclkMusicList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	USES_CONVERSION;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
	int nSel = p->iItem;

	if (nSel < 0)
		return;
	CString str=m_music_list.GetItemText(p->iItem, 0);
	POSITION pos = theApp.m_musiclist.GetHeadPosition();
	POSITION pos1 = theApp.m_pathlist.GetHeadPosition();
	while (pos)
	{
		if (!strcmp(T2A(theApp.m_musiclist.GetAt(pos)), T2A(str)))
		{
			Load(this->m_hWnd, theApp.m_pathlist.GetAt(pos1));
			play();
			SetDlgItemText(IDC_pause, _T("��ͣ"));
			//theApp.m_pathlist.GetNext(pos1);
			//while (pos1)
			//{
			//	Load(this->m_hWnd, theApp.m_pathlist.GetAt(pos1));
			//	play();
			//	//SetDlgItemText(IDC_pause, _T("��ͣ"));
			//	theApp.m_pathlist.GetNext(pos1);
			//}
			break;
			
		}
		theApp.m_musiclist.GetNext(pos);
		theApp.m_pathlist.GetNext(pos1);
	}
	
	*pResult = 0;
}


void CMusicDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP6);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(HALFTONE);             //*����ڴ�
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}

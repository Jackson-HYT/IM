// PlayGame.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "PlayGame.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"


// CPlayGame �Ի���

IMPLEMENT_DYNAMIC(CPlayGame, CDialogEx)

CPlayGame::CPlayGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayGame::IDD, pParent)
{

}

CPlayGame::~CPlayGame()
{
}

void CPlayGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, flashshow);
}


BEGIN_MESSAGE_MAP(CPlayGame, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CPlayGame::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPlayGame ��Ϣ�������


BOOL CPlayGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	RECT rc;
	this->GetClientRect(&rc);//��ÿͻ���������

	//����flash��λ��

	rc.left = 0;

	rc.right = rc.right;

	rc.top += 0;

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

	strFileName += _T("3.swf");//clock.swf��flash�ļ������֣���flash�ļ����ڹ���Ŀ¼�¡�

	flashshow.LoadMovie(0, strFileName);

	flashshow.Play();
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


//void CPlayGame::OnBnClickedOk()
//{
//	// TODO:  �ڴ���ӿؼ�֪ͨ����������
//	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
//	//flashshow.MoveWindow(0, 0, 0, 0);
//	
//	//flashshow.Stop();
//	CDialogEx::OnClose();
//	//(CQQClientDlg*)cdlg = (CQQClientDlg*)AfxGetMainWnd();
//	
//}


void CPlayGame::OnCancel()
{
	// TODO:  �ڴ����ר�ô����/����û���
	//DestroyWindow();
	flashshow.StopPlay();
	CDialogEx::OnCancel();
}


void CPlayGame::PostNcDestroy()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::PostNcDestroy();
	//delete this;
}


void CPlayGame::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	dlg->m_game = NULL;
	CDialogEx::OnClose();
}

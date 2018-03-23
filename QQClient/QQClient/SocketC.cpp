// SocketC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "SocketC.h"
#include"QQClientDlg.h"
#include<atlconv.h>
#include"Login.h"
#define MAX_FILE_SIZE 5000
#define ID_ME_TIMER 1001
// CSocketC

CSocketC::CSocketC()
{
}

CSocketC::~CSocketC()
{
}


// CSocketC ��Ա����


void CSocketC::OnReceive(int nErrorCode)
{
	USES_CONVERSION;
	// TODO:  �ڴ����ר�ô����/����û���
	int nCmd=0;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	dlg->m_sock.Receive(&nCmd, sizeof(nCmd));
	switch (nCmd)
	{
	case INFO_ADD:
	{
		AfxMessageBox(_T("ע��ɹ���"));
	
		SendMessage(GetActiveWindow(), WM_CLOSE, 0, 0);
		break;
	}
	case INFO_LOGIN:
	
	{
		//AfxMessageBox(_T("��½�ɹ���"));
		//dlg->SetDlgItemTextW(IDC_M_USERNAME,(LPTSTR) dlg->m_info.Username);
		//dlg->m_dlg.CloseWindow();
		CString msg;
		msg.Format(_T("%s"), CStringW(dlg->m_info.Username));
		dlg->SetDlgItemTextW(IDC_M_USERNAME, msg);
		
		//dlg->m_dlg.DestroyWindow();
		PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		break;
		//delete dlg->m_dlg;
	}
	case INFO_FAILLOFIN:
	{
		
		AfxMessageBox(_T("��½ʧ�ܣ�"));
		exit(0);
		break;
	}
	case INFO_FAILADD:
	{
		AfxMessageBox(_T("ע��ʧ�ܣ�"));
		break;
	}
	case INFO_BROW:
	{
		int i = 0;
		int nCount=0;
		dlg->m_sock.Receive(&nCount, sizeof(nCount));
		dlg->m_friendlist.DeleteAllItems();
		while (i < nCount)
		{
			CString str = _T(" ");
			UserInfo info;
			dlg->m_sock.Receive(&info, sizeof(info));
			str += info.Username;
			dlg->m_friendlist.InsertItem(i, str);
			CString MSG;
			MSG.Format(_T("%s"), CStringW(info.sIP));
			dlg->m_friendlist.SetItemText(i, 1, MSG);
			++i;
		}
	//	PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		break;

	}
	case INFO_TEXT:
	{
		UserInfo SendInfo;
		
		dlg->m_sock.Receive(&SendInfo, sizeof(SendInfo));
		//PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		dlg->OnText(SendInfo);
		break;
	}
	case INFO_ALLTEXT:
	{
		UserInfo SendInfo;
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		dlg->m_sock.Receive(&SendInfo, sizeof(SendInfo));
		//PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		dlg->OnAllText(SendInfo);
		break;
	}
	case INFO_FILE:
	{
		
		//int i = 0;
		//int nOther = MAX_FILE_SIZE;
		//CFile Rece_File;
		//dlg->m_sock.Receive(&nCount, sizeof(nCount));
		//UserInfo ReceInfo;
		//dlg->m_sock.Receive(&ReceInfo, sizeof(ReceInfo));
		//CString str = dlg->OnFile(ReceInfo);
		//Rece_File.Open(str,  CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
		//if (i == nCount - 1)
		//	nOther = (ReceInfo).fileLen%MAX_FILE_SIZE;
		//Rece_File.Write(&ReceInfo.sendFile, nOther);

		//for (i = 1; i < nCount; i++)
		//{
		//	
		//	UserInfo ReceInfo;
		//	
		//	if (i == nCount - 1)
		//		nOther = (ReceInfo).fileLen%MAX_FILE_SIZE;
		//	ZeroMemory((ReceInfo).sendFile, nOther);
		//	dlg->m_sock.Receive(&ReceInfo, sizeof(ReceInfo));	
		//	Rece_File.Write((ReceInfo).sendFile, nOther*2);

		//}
		//Rece_File.Close();
		//CString msg;
		//msg.Format(_T("�ļ��Ѿ������� "));//�����������
		//msg += str;
		//AfxMessageBox(msg);
		//break;
		UserInfo Rece_Info;
		dlg->m_sock.Receive(&Rece_Info, sizeof(Rece_Info));
		CString msg1;
		msg1.Format(_T("�㽫���յ�����%s���ļ�"), CStringW(Rece_Info.From_Username));//�����������

		AfxMessageBox(msg1);
		CString str1 = dlg->OnFile(Rece_Info);//Ҫ���浽�ĵ�ַ
		CFile Rece_File;
		CFile Write_File;
		int nCount = Rece_Info.fileLen / MAX_FILE_SIZE;
		if (Rece_Info.fileLen%MAX_FILE_SIZE != 0)
		{
			nCount++;
		}
		CString str2;//��ȡ��ַ
		str2.Format(_T("%s"), CStringW(Rece_Info.From_Path));//�����������

		Rece_File.Open(str2, CFile::modeRead);
		Write_File.Open(str1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);

		char *buff = new char[MAX_FILE_SIZE];
		int i = 0;
		for (i = 0; i < nCount; i++)
		{
			int nOther = MAX_FILE_SIZE;//ÿ�ζ���д�Ĵ�С���ʼ��ʼΪ��������С
			if (i == nCount - 1) //��������һ��
			{
				nOther = Rece_Info.fileLen % MAX_FILE_SIZE;//�趨����д�Ĵ�С
			}
			//ZeroMemory(buff, nOther); //��buff�е�nOther��������Ϊ0
			Rece_File.Read(buff, nOther);
			Write_File.Write(buff, nOther);

		}
		Rece_File.Close();
		Write_File.Close();
		delete[]buff;
		Sleep(2000);
		CString msg;
		msg.Format(_T("�ļ��Ѿ������� "));//�����������
		msg += str1;
		AfxMessageBox(msg);
		break;

	
	}
	case INFO_BYE:
	{
		AfxMessageBox(_T("���Ѿ���ǿ�����ߣ�"));
		exit(0);
		//dlg->OnClose();
		
		break;
	}
	case INFO_PICTRUE:
	{
		UserInfo info;
		dlg->m_sock.Receive(&info, sizeof(info));
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		dlg->OnPicture(info);
		break;
	}
	case INFO_ALLPICTURE:
	{
		UserInfo info;
		PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		dlg->m_sock.Receive(&info, sizeof(info));
		dlg->OnAllPicture(info);
		break;
	}
	

	}

	CSocket::OnReceive(nErrorCode);
}


//void CSocketC::OnBrow()
//{
//
//}

// SocketL.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQServer.h"
#include "SocketL.h"
#include"SocketC.h"

// CSocketL

CSocketL::CSocketL()
{
}

CSocketL::~CSocketL()
{
}


// CSocketL ��Ա����


void CSocketL::OnAccept(int nErrorCode)
{
	// TODO:  �ڴ����ר�ô����/����û���
	CSocketC *p = new CSocketC;
	if (!Accept(*p))
	{
		delete p;
		return;
	}
	theApp.m_list1.AddTail(p);
	CSocket::OnAccept(nErrorCode);

}

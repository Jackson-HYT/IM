
// QQServer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQQServerApp: 
// �йش����ʵ�֣������ QQServer.cpp
//

class CQQServerApp : public CWinApp
{
public:
	CQQServerApp();

// ��д
public:
	virtual BOOL InitInstance();
	CList<UserInfo, UserInfo>m_list;
	CList<CSocketC*, CSocketC*>m_list1;

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQServerApp theApp;

// QQClient.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQQClientApp: 
// �йش����ʵ�֣������ QQClient.cpp
//

class CQQClientApp : public CWinApp
{
public:
	CQQClientApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
public:
	CList<CString, CString>m_musiclist;
	CList<CString, CString>m_pathlist;
};

extern CQQClientApp theApp;
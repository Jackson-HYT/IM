
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "SkinPPWTL.h"   //������ط���
#pragma comment(lib,"SkinPPWTL.lib")
#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ

enum
{
	INFO_ADD = 0X1234,//ע��
	INFO_LOGIN,//��¼
	INFO_BYE,//����
	INFO_HELLO,//���
	INFO_TEXT,//����
	INFO_FILE,//�ļ�
	INFO_BROW,//����
	INFO_FAILLOFIN,//��½ʧ��
	INFO_FAILADD,//ע��ʧ��
	INFO_ALLTEXT,//Ⱥ��
	INFO_ACTIVE,//�Զ�ˢ��
	INFO_PICTRUE,
	INFO_ALLPICTURE,
};
class CSocketC;
struct UserInfo
{
	char Username[16];
	char Password[16];
	char sIP[16];
	CSocketC *pSock;
	UINT nPort;
	char Text[2048];
	char From_Username[16];
	char From_sIP[16];
	char From_Path[1000];
	//�ļ�����
	BOOL isFile;
	BOOL isFinished;
	UINT transSize;
	UINT fileOffset;
	char sendFile[5000];
	char fileName[100];
	ULONGLONG fileLen;
};


#include <windows.h>

#include <mmsystem.h>

#pragma comment(lib, "WINMM.LIB")

#undef  WINVER  
#define WINVER 0X500  

#define WM_SHOWTASK WM_USER+1 
typedef void (WINAPI *PROCSWITCHTOTHISWINDOW) (HWND, BOOL);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



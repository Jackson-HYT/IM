// Mymap.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "QQClient.h"
#include "Mymap.h"
#include "afxdialogex.h"
#include <MsHTML.h>

// CMymap �Ի���

IMPLEMENT_DYNAMIC(CMymap, CDialogEx)

CMymap::CMymap(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMymap::IDD, pParent)
	, m_start1(_T(""))
	, m_end1(_T(""))
	, m_start2(_T(""))
	, m_end2(_T(""))
	, m_find(_T(""))
{

}

CMymap::~CMymap()
{
}

void CMymap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_ie);
	DDX_Text(pDX, IDC_EDIT2, m_start1);
	DDX_Text(pDX, IDC_EDIT3, m_end1);
	DDX_Text(pDX, IDC_EDIT6, m_start2);
	DDX_Text(pDX, IDC_EDIT4, m_end2);
	DDX_Text(pDX, IDC_EDIT5, m_find);
}


BEGIN_MESSAGE_MAP(CMymap, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMymap::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMymap::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &CMymap::OnBnClickedOk)
END_MESSAGE_MAP()


// CMymap ��Ϣ�������


BOOL CMymap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TCHAR szPath[_MAX_PATH];//_MAX_PATH�꣬260
	GetCurrentDirectory(_MAX_PATH, szPath);
	CString str = szPath;
	str += _T("\\map1.html");
	//���strһ��Ҫ�Ǿ���·����ע�����·�������·��������
	m_ie.Navigate(str, NULL, NULL, NULL, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CMymap::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//�����������ص�����,com���
	//����ָ�� <>�������Ĳ��ֱ�ʾ����
	CComQIPtr<IHTMLDocument2> pDoc = m_ie.get_Document();
	CComDispatchDriver  spPrict;
	pDoc->get_Script(&spPrict);//���ú�����JS�Ĵ��������

	CComVariant varStart, varEnd, res;
	varStart = m_start1;
	varEnd = m_end1;

	//spPrict.Invoke2(L"theFun3",&varStart,&varEnd,&res);
	spPrict.Invoke2(L"theFun4", &varStart, &varEnd, &res);

}


void CMymap::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	//�����������ص�����,com���
	//����ָ�� <>�������Ĳ��ֱ�ʾ����
	CComQIPtr<IHTMLDocument2> pDoc = m_ie.get_Document();
	CComDispatchDriver  spPrict;
	pDoc->get_Script(&spPrict);//���ú�����JS�Ĵ��������

	CComVariant varStart, varEnd, res;
	varStart = m_start2;
	varEnd = m_end2;

	//spPrict.Invoke2(L"theFun3",&varStart,&varEnd,&res);
	spPrict.Invoke2(L"theFun3", &varStart, &varEnd, &res);

}


void CMymap::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();
	CComQIPtr<IHTMLDocument2> pDoc = m_ie.get_Document();
	CComDispatchDriver  spPrict;
	pDoc->get_Script(&spPrict);//���ú�����JS�Ĵ��������

	CComVariant varFind,res;
	varFind = m_find;

	//spPrict.Invoke2(L"theFun3",&varStart,&varEnd,&res);
	spPrict.Invoke2(L"Search", &varFind,&res);
}

#pragma once

// CSocketL ����Ŀ��

class CSocketL : public CSocket
{
public:
	CSocketL();
	virtual ~CSocketL();
	virtual void OnAccept(int nErrorCode);
};



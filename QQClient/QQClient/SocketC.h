#pragma once

// CSocketC ����Ŀ��

class CSocketC : public CSocket
{
public:
	CSocketC();
	virtual ~CSocketC();
	virtual void OnReceive(int nErrorCode);
//	void OnBrow();
};



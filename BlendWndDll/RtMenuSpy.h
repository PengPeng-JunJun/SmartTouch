#pragma once

// CMouseSpy ����Ŀ��

class CRtMenuSpy : public CObject
{
public:
	CRtMenuSpy();
	virtual ~CRtMenuSpy();

	BOOL StartMsgHook(CWnd * pMonitor);
	BOOL StopMsgHook(void);
	void RemoveMsg(void);

protected:
	BOOL m_bMsgHookOn;
};


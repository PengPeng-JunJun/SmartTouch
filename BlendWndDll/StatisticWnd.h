#pragma once

#include "NgWarnLimit.h"

static UINT gMsgStatisticBeyongLimit = RegisterWindowMessage(_T("gMsgStatisticBeyongLimit"));
static UINT gMsgStatisticReport = RegisterWindowMessage(_T("gMsgStatisticReport"));

// CStatisticWnd 对话框

class AFX_EXT_CLASS CStatisticWnd : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CStatisticWnd)

public:
	CStatisticWnd(CWnd* pParent = NULL);   // 标准构造函数
	CStatisticWnd(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CStatisticWnd();

// 对话框数据
	enum { IDD = IDD_STATISTICWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	virtual void LockCtrls(int nLock);

	void PassIncrease(int nInc);
	void FailIncrease(int nInc);
	void ClearData(void);

	void LoadData(CString strFile);
	void SaveData(CString strFile);
protected:
	CString m_strFile;

	BOOL m_bUseNum;
	BOOL m_bUseRate;

	int m_nNgLimit;
	double m_dNgRateLimit;

	virtual void _PreShowWnd(void);
	virtual void _DefaultFocus(void);
public:	
	void RtDbClickStatisticChart();
	void NgNumReachLimitStatisticChart(long nNgNum);
	void NgRateReachLimitStatisticChart(double dNgRate);
	void LBtClickedBtStatisticClear(long nFlags);
	void LBtClickedBtStatisticReport(long nFlags);
	void LBtClickedBtStatisticExit(long nFlags);
protected:
	afx_msg LRESULT OnDataChangeed(WPARAM wParam, LPARAM lParam);
};

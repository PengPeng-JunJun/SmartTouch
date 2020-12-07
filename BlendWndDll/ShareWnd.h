#pragma once

#include "MsgBox.h"

#define TEST_INFO_ARRAY_LEN		128
#define START_TYPE_MENU			0
#define START_TYPE_SHARE_WND	1
#define START_TYPE_COPY_DATA	2

typedef struct _tagMemTransData
{
	int nImgWidth;
	int nImgHeight;
	int nType;
	int nDepth;
	int nChannels;
	int nDataSize;
	int nParam;
	BYTE *pData;
}TEST_ITEM_INFO;


typedef struct _tagStartInfo
{
	int nID;
	int nParam1;
	int nParam2;
	int nParam3;
	int nParam4;
	char szSrcWnd[TEST_INFO_ARRAY_LEN];
}TEST_START_INFO;

//#define RV3_ONLY

#ifdef RV3_ONLY
typedef struct _tagRestInfo
{
	int nID;
	int nResult;
	char szInfo[512];
}TEST_RESULT_INFO;

static UINT gMsgShareWndStart = RegisterWindowMessage(_T("MsgTestStart"));
static UINT gMsgShareMemWriteOver = RegisterWindowMessage(_T("ShareMemWriteOver"));
#else

typedef struct _tagResultInfo
{
	int nID;
	int nResult;
	int nParam1;
	int nParam2;
	int nParam3;
	int nParam4;
	char szInfo[TEST_INFO_ARRAY_LEN];
	char szSrcWnd[TEST_INFO_ARRAY_LEN];
}TEST_RESULT_INFO;

static UINT gMsgShareWndStart = RegisterWindowMessage(_T("gMsgShareWndStart"));
static UINT gMsgShareMemWriteOver = RegisterWindowMessage(_T("gMsgShareMemWriteOver"));
#endif // RV3_ONLY

static UINT gMsgShareCopyStart = RegisterWindowMessage(_T("gMsgShareCopyStart"));

// CShareWnd �Ի���

class AFX_EXT_CLASS CShareWnd : public CTpLayerWnd
{
	DECLARE_SERIAL(CShareWnd)

public:
	CShareWnd(CWnd* pParent = NULL);   // ��׼���캯��
	CShareWnd(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CShareWnd();

// �Ի�������
	enum { IDD = IDD_SHAREWND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	CString m_strWndName;

	TEST_ITEM_INFO m_ItemInfo;
	TEST_START_INFO m_StartInfo;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);

	DWORD CreateShareBlock(const CString &strMemName, int nShareID, int nBufSize, BOOL bServer);

	DWORD WriteData(LPVOID pData, BOOL bSendMsg,
		const CString & strWnd = _T(""), int nWaitTime = 3000);

	DWORD WriteDataEx(LPVOID pData, int nLength, BOOL bSendMsg,
		const CString & strWnd = _T(""), int nWaitTime = 3000);

	DWORD ReadData(LPVOID pData, int nWaitTime = 3000);
	DWORD ReadDataEx(LPVOID pData, int nStart, int nLength, int nWaitTime = 3000);
	DWORD Release(void);

	int GetShareId(void);
protected:
	CString m_strWndNameBkup;

	CString m_strMemName;
	int m_nShareID;
	int m_nBufSize;
	BOOL m_bServer;
	HANDLE m_hMapFile;
	BYTE *m_pData;
	HANDLE m_hMutex;
	HANDLE m_hEvent;

	virtual void _PreShowWnd(void);
	void _UpdateUi(void);
	void _TraceErr(CString strFun, DWORD dwErr);
protected:
	afx_msg LRESULT OnGmsgsharememwriteover(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGmsgsharewndstart(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
public:
	void ValueChangedEditShareWndName(LPCTSTR strNew);
};

#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

// CNewSmartDots 对话框
#define TEST_INFO_ARRAY_LEN  128

#define WM_NEWSMARTDOTS_CODE  WM_USER + 400//啟動焊點檢測
#define WM_NEWSMARTDOTS_FINISH  WM_USER + 401//焊點檢測結果

class CNewSmartDots : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CNewSmartDots)

public:
	CNewSmartDots(CWnd* pParent = NULL);   // 标准构造函数
	CNewSmartDots(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CNewSmartDots();

// 对话框数据
	enum { IDD = IDD_NEWSMARTDOTS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CString m_strRegistersStart; //R起始地址
	CString m_strRegistersEnd;   //R結束地址
	CString m_strRegistersStart1;//D起始地址
	CString m_strRegistersEnd1;//D結束地址
	CString m_strRegisters;//R的switch狀態
	CString m_strRegisters1;//D的switch狀態
	CString m_strRegistersPos;//R的起始位
	CString m_strRegistersPos1;//D的起始位

	typedef struct _tagIpcCopyInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;
		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	} IPC_COPY_INFO;

public:
	CWnd *m_pNewSmartDotsDlg;
	CBL_List m_BL_NewSmartDotsList;
	CBL_Edit m_BL_edNewSmartDotsCode;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
public:
	int m_nNewSmartDotsCode;
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBlednewsmartdotscode(LPCTSTR strNew);
	void ItemChangedBlNewsmartdotslist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlNewsmartdotslist(long nRow, long nCol, short* pnParam, short nFlags);
protected:
	afx_msg LRESULT OnNewSmartDotsCode(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};

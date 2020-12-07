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
// CSmartDotsListDlg 对话框
#define TEST_INFO_ARRAY_LEN  128

#define WM_SMARTDOTS_CODE  WM_USER + 50//啟動焊點檢測
#define WM_SMARTDOTS_FINISH  WM_USER + 51//焊點檢測結果

class CSmartDotsListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSmartDotsListDlg)

public:
	CSmartDotsListDlg(CWnd* pParent = NULL);   // 标准构造函数
	CSmartDotsListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSmartDotsListDlg();

// 对话框数据
	enum { IDD = IDD_SMARTDOTSLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
public:
	CString m_strRegistersStart; //R起始地址
	CString m_strRegistersEnd;   //R結束地址
	CString m_strRegistersStart1;//D起始地址
	CString m_strRegistersEnd1;//D結束地址
	CString m_strRegisters;//R的switch狀態
	CString m_strRegisters1;//D的switch狀態
	CString m_strRegistersPos;//R的起始位
	CString m_strRegistersPos1;//D的起始位
public:
	CWnd *m_pSmartDotsListDlg;
public:
	CBL_List m_BL_SmartDotsList;
	CBL_Edit m_BL_edSmartDotsCode;
	CBL_Edit m_BL_edSmartDotsResult;
	CBL_Button m_BL_btLoadSmartDots;
	CBL_Button m_BL_btSaveSmartDots;
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBledsmartdotscode(LPCTSTR strNew);
	void ItemChangedBlSmartdotslist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlSmartdotslist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemEditFinishBlSmartdotslist(long nRow, long nCol, LPCTSTR strNew);
	void ValueChangedBledsmartdotsresult(LPCTSTR strNew);
	void LBtClickedBlbtsavesmartdots(long nFlags);
	void LBtClickedBlbtloadsmartdots(long nFlags);
public:
	int m_nSmartDotsCode;

	typedef struct _tagStartInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_START_INFO;

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

protected:
	afx_msg LRESULT OnReceiveSmartdotsCode(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};

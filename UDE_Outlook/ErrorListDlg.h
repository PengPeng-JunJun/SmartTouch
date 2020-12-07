#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"
#include "MsgInfoDlg.h"

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
// CErrorListDlg 对话框


#define TEST_INFO_ARRAY_LEN  128

#define WM_ERROR_CODE  WM_USER + 40//出現錯誤
class CErrorListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CErrorListDlg)

public:
	CErrorListDlg(CWnd* pParent = NULL);   // 标准构造函数
	CErrorListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CErrorListDlg();

// 对话框数据
	enum { IDD = IDD_ERRORLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBL_List m_BL_ErrorList;
	CBL_Edit m_BL_edErrorListInfo;
	CBL_Edit m_BL_edErrorCode;

	CBL_Button m_BL_btLoadError;
	CBL_Button m_BL_btSaveError;
public:
	CBlender<CMsgInfoDlg> m_MsgInfoDlg;
public:
	CWnd *m_pErrorListDlg;
public:
	int m_nErrorCode;
public:

	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void LBtDbClickBlErrorlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemChangedBlErrorlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
public:
	CString m_strRegistersStart; //R起始地址
	CString m_strRegistersEnd;   //R結束地址
	CString m_strRegistersStart1;//D起始地址
	CString m_strRegistersEnd1;//D結束地址
	CString m_strRegisters;//R的switch狀態
	CString m_strRegisters1;//D的switch狀態
	CString m_strRegistersPos;//R的起始位
	CString m_strRegistersPos1;//D的起始位
	void ValueChangedBlederrorcode(LPCTSTR strNew);
	virtual void Serialize(CArchive& ar);
	void LBtClickedBlbtsaveerror(long nFlags);
	void LBtClickedBlbtloaderror(long nFlags);
	void ItemEditFinishBlErrorlist(long nRow, long nCol, LPCTSTR strNew);
protected:
	afx_msg LRESULT OnReceiveErrorCode(WPARAM wParam, LPARAM lParam);
public:
	typedef struct _tagResultInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_RESULT_INFO;
};

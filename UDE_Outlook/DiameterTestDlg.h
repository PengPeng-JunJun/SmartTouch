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
// CDiameterTestDlg 对话框

#define TEST_INFO_ARRAY_LEN  128

#define WM_DIAMETERTEST_CODE  WM_USER + 110//
#define WM_DIAMETERTEST_FINISH  WM_USER + 110//

class CDiameterTestDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CDiameterTestDlg)

public:
	CDiameterTestDlg(CWnd* pParent = NULL);   // 标准构造函数
	CDiameterTestDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CDiameterTestDlg();

// 对话框数据
	enum { IDD = IDD_DIAMETERTESTDLG };

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
	CWnd *m_pDiameterTestListDlg;
public:
	int m_nDiameterTestCode;

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
};

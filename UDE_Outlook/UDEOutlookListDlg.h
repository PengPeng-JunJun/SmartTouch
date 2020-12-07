#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>

#include "tlhelp32.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif
// CUDEOutlookListDlg 对话框
#define WM_ED_UDEOUTLOOK_RES  4000


#define TEST_INFO_ARRAY_LEN  128
#define UDEOUTLOOK_COLS_COUNTER 12//列计数

#define WM_UDEOUTLOOK_CODE  WM_USER + 130//
#define WM_UDEOUTLOOK_FINISH  WM_USER + 131//
#define WM_UDEOUTLOOK_FINISH_ROBOT  WM_USER + 132//
#define WM_UDEOUTLOOK_CODE_ROBOT  WM_USER + 133//

#define PLC2UDEOUTLOOK 1
#define ROBOT2UDEOUTLOOK 2

#define WAIT_DELAY 2500
#define RESET_DELAY 6000
#define RESTAR_DELAY 7000

//#define PROCESS_PATH _T("D:\\VC Project\\UDE_Outlook\\Release\\CCD.exe")
#define PROCESS_PATH _T("D:\\Software\\UDEOutlook\\CCD.exe")

#define PROCESS_NAME _T("CCD.exe")

class CUDEOutlookListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CUDEOutlookListDlg)

public:
	CUDEOutlookListDlg(CWnd* pParent = NULL);   // 标准构造函数
	CUDEOutlookListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CUDEOutlookListDlg();

// 对话框数据
	enum { IDD = IDD_UDEOUTLOOKLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CWnd *m_pUDEOutlookListDlg;//窗口指针
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnInitDialog();
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
	CBL_List m_BL_UDEOutlookList;
	CBL_Edit m_BL_edUDEOutlookCode;
	CBL_Edit m_BL_edUDEOutlookResult;
	CBL_Button m_BL_btLoadUDEOutlook;
	CBL_Button m_BL_btSaveUDEOutlook;
	CBL_Edit m_BL_edUDEOutlookRes[10];
	CBL_Edit m_BL_edUDEOutlookInfo;
	CBL_Button m_BL_btUDEOutlookContinue;
	CBL_Radio m_BL_rdUDEOutlook_PLC;
	CBL_Radio m_BL_rdUDEOutlook_Robot;

public:
	int m_nUDEOutlookCode;
	int m_nUDEOutlookCodeRobot;
	vector<CString> m_vstrUDEOutlookInfo;//群組測試項目向量
	vector<CString> m_vstrUDEOutlookRes;
	vector<byte> m_vbyRobotStarUDEOutlookGroup;//裝手臂啟動外觀的群組編號
	int m_nUDEOutlookNO;//正在修改的群組測試項目編號
	typedef struct _tagTestInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		int nResult;
		double dResult;
		BOOL bResult;
		int nResCounter;

		int Result[TEST_INFO_ARRAY_LEN];

		byte byStarGroup[TEST_INFO_ARRAY_LEN];
		char szResult[TEST_INFO_ARRAY_LEN];
		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_INFO;

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_EVENTSINK_MAP()
	void StatusChangedBlrdudeoutlookPlc(BOOL bNewStatus);
	void StatusChangedBlrdudeoutlookRobot(BOOL bNewStatus);
protected:
	afx_msg LRESULT OnEdUdeoutlookRes(WPARAM wParam, LPARAM lParam);
public:
	void ValueChangedBledudeoutlookresult(LPCTSTR strNew);
	void ValueChangedBledudeoutlookcode(LPCTSTR strNew);
	void LBtClickedBlbtsaveudeoutlook(long nFlags);
	void LBtClickedBlbtloadudeoutlook(long nFlags);
	void ItemChangedBlUdeoutlooklist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlUdeoutlooklist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemEditFinishBlUdeoutlooklist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlbtudeoutlookcontinue(long nFlags);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
protected:
//	afx_msg LRESULT OnUdeoutlookCode(WPARAM wParam, LPARAM lParam);//启动视觉检测
	afx_msg LRESULT OnReceiveUdeoutlookCode(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveUdeoutlookCodeRobot(WPARAM wParam, LPARAM lParam);
public:
	void _OpenProcess(CString sExeName);//开启进程
	void _KillProcess(CString sExeName);
	void _KillProcess(DWORD Pid);
	BOOL m_bAutoRestarUDEOutlook;//自動重啟視覺軟件
};

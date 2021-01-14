#pragma once

#include "..\BlendWndDll\MsgBox.h"
#include "..\ExcelDll\Excel.h"
#include "..\FindFileDll\FindCtrlFile.h"

#include "CtrlSet.h"
#include "MsgListDlg.h"
#include "ParameterListDlg.h"
#include "ErrorListDlg.h"

#include "SmartDotsListDlg.h"
#include "SmartRobotListDlg.h"
#include "AngleTestListDlg.h"
#include "DiameterTestDlg.h"
#include "UDEOutlookListDlg.h"
#include "UDEVisionListDlg.h"
#include "SmartLEDListDlg.h"
#include "DataCollectionDlg.h"
#include "NewSmartDots.h"
#include "AutoLockTime.h"

#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\ExcelDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#pragma comment(lib, "..\\Debug\\FindFileDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\ExcelDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#pragma comment(lib, "..\\Release\\FindFileDll.lib")
#endif

#define  WM_STARTCOLLECT  WM_USER + 10//主->從
#define  WM_STOPCOLLECT  WM_USER + 11
#define  WM_DELETFILE    WM_USER + 12//刪除多餘的文件夾
#define  WM_COLLECTRUN   WM_USER + 13//開始收集數據，用在間斷性收集數據
#define  WM_COLLECTFINISH WM_USER + 14//數據收集完成，開始生成報表
#define  WM_COLLECTLOSE   WM_USER + 15//設備掉線
#define  WM_WRITE_FINISH  WM_USER + 16//数据写入完成
#define  WM_WRITE_DATA  WM_USER + 17//数据写入

#define  WM_LOCK_STATE  WM_USER + 18//权限锁定或解锁

#define  READ_DATA    0//讀取設備中的數據
#define  WRITE_DATA    1//數據寫入設備中
#define  SAVE_DATA     2//保存數據，保存採集數據的時間


#define TIME_RATIO   1//時間倍率

#define DATE_BEFORE 0//計算當前日期之前的日期
#define DATE_AFTER  1//計算當前日期之後的日期

#define DATE_REPORT 1//日報
#define MOUTH_REPORT 2//月報


#define WM_BT_REALY 1025
#define WM_CK_REALY 1026
#define WM_DP_REALY 1027

// CControllerDlg 对话框

class CControllerDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CControllerDlg)

public:
	CControllerDlg(CWnd* pParent = NULL);   // 标准构造函数
	CControllerDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CControllerDlg();

// 对话框数据
	enum { IDD = IDD_CONTROLLERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExcel  m_Excel;
	CFindCtrlFile m_FindCtrlFile;
	CBlender<CCtrlSet> m_CtrlSet;//控件屬性設置
	CBlender<CMsgListDlg> m_MsgListDlg;//總消息表格顯示界面
	CBlender<CParameterListDlg> m_ParameterListDlg;//
	CBlender<CDataCollectionDlg> m_DataCollectionDlg;//
	CBlender<CErrorListDlg> m_ErrorListDlg;//

	CBlender<CSmartDotsListDlg> m_SmartDotsListDlg;
	CBlender<CSmartRobotListDlg> m_SmartRobotListDlg;
	CBlender<CAngleTestListDlg> m_AngleTestListDlg;
	CBlender<CDiameterTestDlg> m_DiameterTestListDlg;
	CBlender<CUDEOutlookListDlg> m_UDEOutlookListDlg;
	CBlender<CUDEVisionListDlg> m_UDEVisionListDlg;
	CBlender<CSmartLEDListDlg> m_SmartLEDListDlg;
	CBlender<CNewSmartDots>  m_NewSmartDotsDlg;
	CBlender<CAutoLockTime>  m_AutoLockTimeDlg;
public:

	//CString m_strExcelPath;
	CString m_strExcelPathTem;

public:
	CBL_List m_BL_ReportCollectList;
	CBL_Menu m_BL_ControllerMenu;

	CBL_Button m_BL_btRelay[BT_RELAY_SUM];
	CBL_CheckBox m_BL_ckRelay[CK_RELAY_SUM];
	CBL_DropDown m_BL_dpRelay[DP_RELAY_SUM];


	CBL_Button m_BL_btAddCtrl;//添加控件
	CBL_Button m_BL_btChangeCtrl;//修改控件

	CBL_Button m_BL_btRelayStar;
	CBL_Button m_BL_btRelayStop;
	CBL_Button m_BL_btRelayReset;
	CBL_Button m_BL_btRelayError;
	CBL_Button m_BL_btRelayPause;

	CBL_Switch m_BL_swRelayAuto;
	CBL_Switch m_BL_swRelayUnAuto;
	CBL_Switch m_BL_swConnect;

public:
	int m_nControllerDlgCounter;//每个对话框独一无二的变量，用来区别发送消息的数据

	BOOL m_bLocked;//权限锁定
	virtual void Serialize(CArchive& ar);

	virtual BOOL OnInitDialog();
	virtual void _DefaultFocus(void);
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);

	DECLARE_EVENTSINK_MAP()
	void RowsChangedBlReportcollectlist(long nOldRows, long nNewRows, BOOL bAppend);
	void LBtDbClickBlReportcollectlist(long nRow, long nCol, short* pnParam, short nFlags);
	void LBtClickedBlGetreport(long nFlags);
public:
	CString GetExePath(void) ;

public:
	void GetSystemTime(int & nYear, int & nMouth, int & nDay, int & nHour, int & nMinute, int & nSeconds);
	void GetSystemTime(CString & strYear, CString & strMouth, CString & strDay, CString & strHour, CString & strMinute, CString & strSeconds);

	static UINT _CollectDataThread(LPVOID pParam);
	UINT _CollectDataThreadKernal(void);
	void CollectData();
	void SetMainMenu();
public://报表生成线程
	afx_msg void OnClose();
	virtual void OnCancel();
protected:
	afx_msg LRESULT OnStartCollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopCollect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int m_nReportColCounter;
	CString m_strInput;
	CString m_strControllerName;
	CString m_strSoftwareVersion;//軟件版本號

	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;

	int m_nAutoLockTime;//自動鎖定時長
	void LoadFileData();

public:
	CString m_strRegistersStart; //R起始地址
	CString m_strRegistersEnd;   //R結束地址
	CString m_strRegistersStart1;//D起始地址
	CString m_strRegistersEnd1;//D結束地址
	CString m_strRegisters;//R的switch狀態
	CString m_strRegisters1;//D的switch狀態
	CString m_strRegistersPos;//R的起始位
	CString m_strRegistersPos1;//D的起始位
	CString m_strCoil;//M的switch狀態
	CString m_strCoilStart; //M起始地址
	CString m_strCoilEnd;   //M結束地址
	CString m_strCoilPos;//M的起始位

	void ItemChangedBlReportcollectlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void ItemEditFinishBlReportcollectlist(long nRow, long nCol, LPCTSTR strNew);
public:
	CWnd *m_pController;//設備運行對話框窗口指針
	BOOL m_bUninterrupted;//不間斷收集數據 TRUE 為不間斷收集，FALSE 為間斷收集，只是在子窗口發來消息時收集
protected:
	afx_msg LRESULT OnCollectFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWriteFinish(WPARAM wParam, LPARAM lParam);
public:
	BOOL m_bCollecting;//處於收集狀態

	void AutoDeletData();
public:
	CValueCalculate m_ValueCalculate;
	CString DateCalculate_GetSpan(COleDateTime TimeBegin, COleDateTime TimeEnd);//根據提供的時間開始和結束，計算中間間隔的天數
	CString DateCalculate_GetDate(CTime Time, int nTimeSpan, int nOffset);//根據提供的日期，間隔天數，間隔方式，計算目標日期
	
protected:
	afx_msg LRESULT OnCollectLose(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg LRESULT OnBtRealyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCkRealy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDpRealy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnParamFinish(WPARAM wParam, LPARAM lParam);//參數輸入完成

public:
	void LBtClickedBlAddctrl(long nFlags);
	void LBtClickedBlChangectrl(long nFlags);

public:
	vector<BOOL> m_vbRelayBtStatus;
	vector<BOOL> m_vbRelayCkStatus;
	vector<BOOL> m_vbRelayDpStatus;

	vector<CString> m_vstrRelayBt;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayBtName;//按键中间继电器名称
	vector<int>     m_vnRelayBtMode;//按键中间继电器类型
	vector<BOOL>    m_vbIsRelayBtClickAuto;//自動模式下是否可以點擊按鈕

	vector<CString> m_vstrRelayCk;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayCkName;//按键中间继电器名称

	vector<CString> m_vstrRelayDp;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayDpName;//按键中间继电器名称
	vector<CString> m_vstrRelayDpCaption;

	BOOL m_bRelayBtStarStatus;
	BOOL m_bRelayBtStopStatus;
	BOOL m_bRelayBtResetStatus;
	BOOL m_bRelayBtErrorStatus;
	BOOL m_bRelayBtPauseStatus;
	BOOL m_bRelaySwAutoStatus;
	BOOL m_bRelaySwUnAutoStatus;

	CString m_strRelayStar;
	CString m_strRelayStop;
	CString m_strRelayReset;
	CString m_strRelayError;
	CString m_strRelayPause;
	CString m_strRelayAuto;
	CString m_strRelayUnAuto;

	vector<CString> m_vstrParameter;
	vector<CString> m_vstrParameterName;
	vector<CString> m_vstrParameterByte;
	vector<CString> m_vstrParameterPt;//小數位數
	vector<CString> m_vstrParameterUnit;//數據單位

	vector<CString> m_vstrDataCollection;
	vector<CString> m_vstrDataCollectionName;
	vector<CString> m_vstrDataCollectionByte;
	vector<CString> m_vstrDataCollectionPt;//小數位數
	vector<CString> m_vstrDataCollectionUnit;//數據單位

public:
	void UpdateMsgList();//更新消息列表
	void UpdateParameterList();
	void UpdateDataCollectionList();
	void UpdateErrorList();
	void UpdateSmartDotsList();
	void UpdateUDEVisionList();
	void UpdateUDEOutlookList();
	void UpdateSmartRobotList();
	void UpdateSmartLEDList();
	void UpdateAngleTestList();
	void UpdateDiameterTestList();
	void UpdateNewSmartDots();

	void CollectStar();
	CString UpdateMsgListAddress(CString strRelayMode);//更新列表中的地址列,返回地址字符串
	void StartConnect();//開始連接
	void SearchSendData(CString strDatInfo, int nData);//查询需要发送的数据，查找表格中的第一个对应缓存器或继电器，修改对应状态

	void SearchSendData_Angle(CString strDatInfo, int nData);

public:
	void ItemClickBlControllermenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);
	void StatusChangedBlswconnect(BOOL bStatus);
	void StatusChangedBlswrelayauto(BOOL bStatus);
	void StatusChangedBlswrelayunauto(BOOL bStatus);
	void LBtClickedBlbtrelaystar(long nFlags);
	void LBtClickedBlbtrelaystop(long nFlags);
	void LBtClickedBlbtrelayreset(long nFlags);
	void LBtClickedBlbtrelaypause(long nFlags);
	void LBtClickedBlbtrelayerror(long nFlags);
protected:
	
	afx_msg LRESULT OnSmartdotsFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdevisionFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotStarUdevision(WPARAM wParam, LPARAM lParam);//手臂啟動外觀
	afx_msg LRESULT OnUdevisionFinishRobot(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartledFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdeoutlookFinishRobot(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdeoutlookFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotStarUdeoutlook(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetLockState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewsSmartDotsFinish(WPARAM wParam, LPARAM lParam);
};

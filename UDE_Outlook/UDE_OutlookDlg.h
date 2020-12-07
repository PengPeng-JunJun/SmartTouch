
// UDE_OutlookDlg.h : 头文件
//
//●
#pragma once

#include "ControllerDlg.h"
#include "ControllerAddDlg.h"
#include "FindCtrlFile.h"
#include "MsgInfoDlg.h"
#include "..\\BlendWndDll\Register.h"

#include "..\\SerialPortDll\RS232.h"
#include "..\\BlendWndDll\MsgBox.h"
#include "..\\CRCDll\\CRC.h"
#include "..\\CRCDll\\CRCDlg.h"
#include "..\\ExcelDll\Excel.h"
#include "..\\RegisterDll\RegisterDlg.h"
#include "..\\SoftwareInfoDll\\SoftwareInfoDlg.h"

#include <vector>
#include <math.h>
#include <stdio.h>  
#include <windows.h> 

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\SerialPortDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#pragma comment(lib, "..\\Debug\\ExcelDll.lib")
#pragma comment(lib, "..\\Debug\\RegisterDll.lib")
#pragma comment(lib, "..\\Debug\\SoftwareInfoDll.lib")
#define DEBUGSTYLE   0
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\SerialPortDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#pragma comment(lib, "..\\Release\\ExcelDll.lib")
#pragma comment(lib, "..\\Release\\RegisterDll.lib")
#pragma comment(lib, "..\\Release\\SoftwareInfoDll.lib")
#define RELEASESTYLE   1
#endif


#define  MAXLEN  50
#define  MAXHISTORYPATH   6

#define WM_SHOWTASK     WM_USER + 100 //鼠标点击任务栏上的图标时，图标要发出的消息，消息的接收者就是当前你写定义语句的窗体

#define SLEEPTIME 1//延時時長，單位為微妙


using namespace std;
// CUDE_OutlookDlg 对话框
class CUDE_OutlookDlg : public CAppBase
{
// 构造
public:
	CUDE_OutlookDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_UDE_OUTLOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int m_nRunStyle;

public:
	CBlender<CMsgInfoDlg> m_MsgInfoDlg;
	vector<CBlender<CControllerDlg>*> m_pControllerDlg;
	CBlender<CControllerAddDlg> m_ControllerAddDlg;
	CBlender<CRegisterDlg> m_Register;
	CBlender<CSoftwareInfoDlg> m_SoftwareInfoDlg;

public:

	BOOL m_nInit;
	int m_nCollectCounter_Main;//主表格的收集行计数
	int m_nCollectCounter_Slave;//类里的表格收集行计数

	int m_nCommunicationMode;//正在通訊的模式，讀取或寫入

	int m_nStationNO;//设备站号
	int m_nStationAddress;//数据起始地址
	vector<int> m_nReceiveData;
	
	vector<CString> m_strCollectStatus;//用于显示数据采集状态

	BOOL m_bReceive;//接受的數據是否有效

	BOOL m_bItemFinish;//主表個內容是否輸入完成  

	int m_nCommend;//命令码
	CString m_strFilePath;

	BOOL m_bOpenFile;
	BOOL m_bIfExcel;

	UINT m_nHistoryPathCounter;
	vector<CString> m_strHistoryPath;
	
	BOOL m_bAutoRun;//自動開機

	BOOL m_bAutoFindFile;//自動加載檔案

	vector<vector<int>> m_nvMsg;//二維向量，每個窗口發送來的消息，最裡層是窗口發來消息的類型，是採集數據還是寫入數據
	vector<vector<int>> m_nvWriteMsg;//二維向量，每個窗口發送來的消息，最裡層是窗口發來消息的類型，是採集數據還是寫入數據

	vector<BOOL> m_bvConnecting;//設備是否處於鏈接狀態
	BOOL m_bIsBalloonTipShow;//氣泡窗口是否在顯示

	CString m_strSoftwareVersion;//軟件版本號

public:
	CRS232  m_Port;
	CCRC    m_CRC;
	CFindCtrlFile m_FindCtrlFile;
	CCRCDlg m_CRCDlg;
	CExcel m_Excel;

public:
	CBL_Menu  m_BL_MainMenu;
	CBL_List  m_BL_ReportMainList;
	CBL_Switch m_BL_Collect;
	CBL_Button m_BL_CollectStatus;
	CBL_Edit   m_BL_ReportLimit;
	CBL_Radio  m_BL_DateReport;
	CBL_Radio  m_BL_MouthReport;

public:
	virtual void LockCtrls(int nLock);//相应锁定控件消息
	virtual void PreInitDialog();
protected:
	BOOL _RegisterActivex(BOOL bRegister);
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//從托盤還原到桌面
	NOTIFYICONDATA m_nid;
	BOOL m_bShowDlg;//是否顯示主對話框

	BOOL m_bMin2Tray;//是否最小化到托盤

	BOOL m_bCommuncating;//正在通讯中, 用于限制通讯中，消息向量间的切换
	BOOL m_bInterruptRead;//TRUE有写入数据来，切断读取数据  FALSE 继续读取数据


public:
	void InitMainWindow();//初始化主窗口，確定解鎖按鈕的位置

	void SetMainMenu();//设置主菜单栏內容

	void CreateChildWindow();//创建各個類對象对话框

	void CreateNewReportList();//创建主線程表格

	void CleanCurrentReportList();//清空主線程表格的內容，同時清空設備類對象指針向量

	void SearchConfigurationFile();//查找CRC配置文件

	void SearchControllerFile();//查找机台名称文件夹

	void SearchReportFile();//查找报表生成文件夹

	void SearchTemplateFile();//創建EXCEL模板文件夾

	CString GetExePath();//获取EXE的绝对路径

	void Saveproject();//文件保存

	void Openproject();//文件加載

	void OpenprojectWithFilePath(CString strPath);//根據路徑加載檔案

	void Saveasproject();//文件另存為

	void StartCollect();//开始收集数据

	void InterruptedSendMsg2Ctrl();//根據消息列表整理並控制PLC消息

	CString GetCRCCheck(vector<BYTE> bySend, CString strChecckMode);//获取CRC校验码

	void TranslateReveiveData();//解析设备回传消息

	void SaveHistoryPath();//保存檔案歷史路徑

	void LoadHistoryPath();//加載檔案歷史路徑

	void UpdateMenu();//更新菜單欄

	void SetAutoRun(BOOL bAutoRun);//設備開機啟動項

	void CheckFileCounter();//查找收集報表的數量是否超過設置數量上限

	void DelayTimeRun();//延時控制設備之間的運行

	BOOL ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, UINT uTimeout, DWORD dwInfoFlags);//設置氣泡消息

	DECLARE_EVENTSINK_MAP()
	void ItemClickBlMainMenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);//菜單點擊響應消息

public:
	void LBtDbClickBlReportMainList(long nRow, long nCol, short* pnParam, short nFlags);//主線程列表雙擊單元格響應消息
	void ItemChangedBlReportMainList(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);//主線程列表單元格內容變化響應消息
	void ItemEditFinishBlReportmainlist(long nRow, long nCol, LPCTSTR strNew);//主線程列表單元格內容輸入完成響應消息
	void RowsChangedBlReportmainlist(long nOldRows, long nNewRows, BOOL bAppend);//主線程列表行數量變化變化響應消息，設備的添加和刪除

	afx_msg void OnClose();
public:
	virtual void Serialize(CArchive& ar);//串行化和反串行化

protected:
	afx_msg LRESULT OnGmsgserialreceivechar(WPARAM wParam, LPARAM lParam);//收到串口消息
	afx_msg LRESULT OnGetRegisterMsg(WPARAM wParam, LPARAM lParam);//收到註冊消息
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();

public:
	CRect m_startRect;     //窗口的初始位置所在的矩形
	CPoint m_startPoint;   //鼠标按下的位置
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnGmsgminwindow(WPARAM wParam, LPARAM lParam);//接收最小化按鍵傳遞的消息
	afx_msg LRESULT OnDeletFlie(WPARAM wParam, LPARAM lParam);//接受創建了新的文件夾消息
	afx_msg LRESULT OnCollectRun(WPARAM wParam, LPARAM lParam);//開始收集數據，用於間斷收集數據
public:
	void StatusChangedBlDatereport(BOOL bNewStatus);
	void StatusChangedBlMouthreport(BOOL bNewStatus);
	static UINT _SaveProjectThread(LPVOID pParam);
	UINT _SaveProjectThreadKernal(void);

	static UINT _DelayTimeRunThread(LPVOID pParam);
	UINT _DelayTimeRunThreadKernal(void);

protected:
	afx_msg LRESULT OnStopcollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartcollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWriteData(WPARAM wParam, LPARAM lParam);
};

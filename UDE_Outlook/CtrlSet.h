#pragma once
#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>

#define WM_RD_CTRL_MODE  2000//控件類型消息
#define WM_RD_RELAY_BT_MODE  2001//按鍵類型消息


#define WM_BT_RELAY_BT_STATUS  2002//
#define WM_BT_RELAY_CK_STATUS  2003//
#define WM_BT_RELAY_DP_STATUS  2004//
#define WM_BG_RELAY_BASIC      2005//启动，停止，复位消息

#define RELAY_BT_MODE_COUNTER 2//按鍵類型計數

#define RELAY_BT_MODE_LOCK    1//按键自锁
#define RELAY_BT_MODE_UNLOCK  2//按键自复 

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

#define BT_RELAY_SUM 100//按鍵總數
#define CK_RELAY_SUM 16//checkbox總數
#define DP_RELAY_SUM 10//dropdown总数

// CCtrlSet 对话框

class CCtrlSet : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CCtrlSet)

public:
	CCtrlSet(CWnd* pParent = NULL);   // 标准构造函数
	CCtrlSet(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CCtrlSet();

// 对话框数据
	enum { IDD = IDD_CTRLSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void _DefaultFocus(void);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);

	DECLARE_MESSAGE_MAP()
public:
	CBL_Radio m_BL_rdRelayBtMode[RELAY_BT_MODE_COUNTER];//
	CBL_CheckBox m_BL_ckRelayBtClickAuto;

	CBL_Edit m_BL_edRelayBt;
	CBL_Edit m_BL_edRelayBtName;

	CBL_Edit m_BL_edRelayCk;
	CBL_Edit m_BL_edRelayCkName;

	CBL_Edit m_BL_edRelayDp;
	CBL_Edit m_BL_edRelayDpName;
	CBL_Edit m_BL_edRelayDpCaption;

	CBL_Button m_BL_btRelayBtStatus[BT_RELAY_SUM];
	CBL_Button m_BL_btRelayCkStatus[CK_RELAY_SUM];
	CBL_Button m_BL_btRelayDpStatus[DP_RELAY_SUM];

	CBL_Button m_BL_btRelayStarStatus;
	CBL_Button m_BL_btRelayStopStatus;
	CBL_Button m_BL_btRelayResetStatus;
	CBL_Button m_BL_btRelayErrorStatus;
	CBL_Button m_BL_btRelayPauseStatus;
	CBL_Button m_BL_btRelayAutoStatus;
	CBL_Button m_BL_btRelayUnAutoStatus;

	CBL_Button m_BL_btRelayBtOK;
	CBL_Button m_BL_btRelayCkOK;
	CBL_Button m_BL_btRelayDpOK;

	CBL_Button m_BL_btSaveCtrl;
	CBL_Button m_BL_btLoadCtrl;


public:
	vector<BOOL> m_vbRelayBtStatus;
	vector<BOOL> m_vbRelayCkStatus;
	vector<BOOL> m_vbRelayDpStatus;

	int m_nRelayBtFocus;//按键继电器被命中的编号（0~99）
	vector<CString> m_vstrRelayBt;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayBtName;//按键中间继电器名称
	vector<int>     m_vnRelayBtMode;//按键中间继电器类型
	vector<BOOL>    m_vbIsRelayBtClickAuto;//自動模式下是否可以電機按鈕

	int m_nRelayCkFocus;//勾选继电器被命中的编号（0~15）
	vector<CString> m_vstrRelayCk;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayCkName;//按键中间继电器名称

	int m_nRelayDpFocus;//单选继电器被命中的编号（0~9）
	vector<CString> m_vstrRelayDpCaption;
	vector<CString> m_vstrRelayDp;//按键中间继电器（Mxx）
	vector<CString> m_vstrRelayDpName;//按键中间继电器名称

	int m_nBasicFocus;
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


	CString m_strCoilStart; //M起始地址
	CString m_strCoilEnd;   //M結束地址
	CString m_strCoilPos;//M的起始位

public:
	CValueCalculate m_ValueCalculate;

protected:
	afx_msg LRESULT OnRdRelayBtModeChange(WPARAM wParam, LPARAM lParam);//按鍵類型改變
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnBtRelayBtStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBtRelayCkStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBtRelayDpStatus(WPARAM wParam, LPARAM lParam);
public:
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlRelaybtok(long nFlags);
	void ValueChangedBlRelaybt(LPCTSTR strNew);
	void LBtClickedBlRelayckok(long nFlags);
	void ValueChangedBlRelayck(LPCTSTR strNew);
	void LBtClickedBlRelaydpok(long nFlags);
	void ValueChangedBlRelaydrop(LPCTSTR strNew);
protected:
	afx_msg LRESULT OnBgRelayBasic(WPARAM wParam, LPARAM lParam);
public:
	void SetBasicRelayColor();//设置基础空间状态
	void LBtClickedBlbtsavectrl(long nFlags);
	void LBtClickedBlbtloadctrl(long nFlags);
	virtual void Serialize(CArchive& ar);
public:
	void UpdateCtrlInfo();
	void StatusChangedBlckrelayclickauto(short nNewStatus);
};

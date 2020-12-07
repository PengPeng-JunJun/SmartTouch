#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include <vector>
#include <math.h>
#include "..\\CRCDll\\ValueCalculate.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif
// CNumberInputDlg 对话框

#define WM_BT_NUMBER_INPUT  1100

class CNumberInputDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CNumberInputDlg)

public:
	CNumberInputDlg(CWnd* pParent = NULL);   // 标准构造函数
	CNumberInputDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CNumberInputDlg();

// 对话框数据
	enum { IDD = IDD_NUMBERINPUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
public:
	CValueCalculate m_ValueCalculate;
public:
	CBL_Button m_BL_btNumberInput[11];
	CBL_Edit m_BL_edSendValue;
	CBL_Edit m_BL_edCurrentValue;
	CBL_Edit m_BL_edPtByte;
public:
	int m_nSendValue;//傳送值（更新值）
	CString m_strCurrentValue;//當前值
	CString m_strPtByte;//小數位數
protected:
	afx_msg LRESULT OnBtNumberInput(WPARAM wParam, LPARAM lParam);
public:
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBledsendvalue(LPCTSTR strNew);
	void LBtClickedBlbtdelet(long nFlags);
	virtual void OnOK();
	void LBtClickedBlbtinputClean(long nFlags);
};

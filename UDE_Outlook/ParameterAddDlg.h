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


// CParameterAddDlg 对话框

class CParameterAddDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CParameterAddDlg)

public:
	CParameterAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	CParameterAddDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CParameterAddDlg();

// 对话框数据
	enum { IDD = IDD_PARAMETER };

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
public:

	CString m_strDataStar;
	CString m_strDataEnd;   
	int m_nDataStar;
	int m_nDataEnd;
	int m_nDataInterval;//數據間隔
	int m_nDataBits;//數據位數

public:
	CBL_Edit m_BL_edDataStar;
	CBL_Edit m_BL_edDataEnd;
	CBL_Edit m_BL_edDataInterval;
	CBL_DropDown m_BL_dpDataBits;

	DECLARE_EVENTSINK_MAP()
	void ValueChangedBleddatastar(LPCTSTR strNew);
	void ValueChangedBleddataend(LPCTSTR strNew);
	virtual void OnOK();
};

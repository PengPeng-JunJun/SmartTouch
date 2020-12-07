#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"
#include "NumberInputDlg.h"
#include "ParameterAddDlg.h"


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

#define WM_PARAM_FINISH   WM_USER + 30
#define WM_PARAM_UPDATE   WM_USER + 31

// CParameterListDlg 对话框

class CParameterListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CParameterListDlg)

public:
	CParameterListDlg(CWnd* pParent = NULL);   // 标准构造函数
	CParameterListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CParameterListDlg();

// 对话框数据
	enum { IDD = IDD_PARAMETERLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void _DefaultFocus(void);
public:
	CBlender<CNumberInputDlg> m_NumberInput;
	CBlender<CParameterAddDlg> m_ParameterAdd;

public:
	CString m_strRegistersStart; //R起始地址
	CString m_strRegistersEnd;   //R結束地址
	CString m_strRegistersStart1;//D起始地址
	CString m_strRegistersEnd1;//D結束地址
	CString m_strRegisters;//R的switch狀態
	CString m_strRegisters1;//D的switch狀態
	CString m_strRegistersPos;//R的起始位
	CString m_strRegistersPos1;//D的起始位

	vector<int> m_vnUpdateData;// 更新數據向量

	BOOL m_bLocked;//参数项目操作权限是否锁定,TRUE--锁定，FALSE--解锁

	BOOL m_bParamInpiutLocked;//参数输入权限是否锁定,TRUE--锁定，FALSE--解锁

	BOOL m_bParamInputting;//參數輸入中
public:
	CBL_List m_BL_ParameterList;
	CBL_Button m_BL_btSaveParam;
	CBL_Button m_BL_btLoadParam;
	CBL_Button m_BL_btAddParam;
	CBL_CheckBox m_BL_ckUpdateData;

	DECLARE_EVENTSINK_MAP()
	void ItemChangedBlParameterlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlParameterlist(long nRow, long nCol, short* pnParam, short nFlags);
	void RowsChangedBlParameterlist(long nOldRows, long nNewRows, BOOL bAppend);
public:
	CWnd *m_pParameterListDlg;
public:
	
	void LBtClickedBlbtsaveparam(long nFlags);
	void LBtClickedBlbtloadparam(long nFlags);
	virtual void Serialize(CArchive& ar);
	void ItemEditFinishBlParameterlist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlbtaddparam(long nFlags);
protected:
	afx_msg LRESULT OnParamUpdate(WPARAM wParam, LPARAM lParam);
public:
	void StatusChangedBlckupdatedata(short nNewStatus);
};

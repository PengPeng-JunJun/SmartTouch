#pragma once

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


#define  WINDOWTITLE   _T("設備添加")

#define  OK                   0
#define  NOFILENAME           1
#define  NOCHECKNAME          2
#define  NOCOILSTART          3
#define  NOCOILEND            4
#define  NOREGISTERSSTART     5
#define  NOREGISTERSEND       6
#define  REGISTERDATAERROR    7
#define  COILDATAERROR        8


// CControllerAddDlg 对话框

class CControllerAddDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CControllerAddDlg)

public:
	CControllerAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	CControllerAddDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CControllerAddDlg();

// 对话框数据
	enum { IDD = IDD_CONTROLLERADDDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBL_DropDown  m_BL_ControllerName;
	CBL_DropDown m_BL_ControllerCheckModeName;

	
	CBL_Edit m_BL_CtrlRegistersStart;
	CBL_Edit m_BL_CtrlRegistersEnd;
	CBL_Edit m_BL_CtrlRegistersStart1;
	CBL_Edit m_BL_CtrlRegistersEnd1;
	CBL_Switch m_BL_CtrlRegisters;
	CBL_Switch m_BL_CtrlRegisters1;
	CBL_Edit m_BL_CtrlRegistersPos;
	CBL_Edit m_BL_CtrlRegistersPos1;


	CBL_Switch m_BL_CtrlCoil;
	CBL_Edit m_BL_CtrlCoilPos;
	CBL_Edit m_BL_CtrlCoilStart;
	CBL_Edit m_BL_CtrlCoilEnd;
public:
	CWnd  *m_pMsgCtrlAddDlg;
public:
	virtual BOOL OnInitDialog();
	virtual void _DefaultFocus(void);
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlAddok(long nFlags);
	void LBtClickedBlAddcancel(long nFlags);

public:
	int AddFile();//添加控制字文件
public:
	CString GetExePath(void);
	void SaveCtrlParam();
	void LoadCtrlParam();
public:
	BOOL m_bIsFileChanged;

	void SelectChangedBlControllername(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void TextChangedBlControllername(LPCTSTR strNew);
	void SelectChangedBlControllercheckmodename(LPCTSTR strOld, LPCTSTR strNew, short nPos);
	void ValueChangedBlCtrlcoilstart(LPCTSTR strNew);
	void ValueChangedBlCtrlcoilend(LPCTSTR strNew);
	void ValueChangedBlCtrlregistersstart(LPCTSTR strNew);
	void ValueChangedBlCtrlregistersend(LPCTSTR strNew);
	void StatusChangedBlCtrlregisters(BOOL bStatus);
	void StatusChangedBlCtrlregisters1(BOOL bStatus);
	void ValueChangedBlCtrlregistersstart1(LPCTSTR strNew);
	void ValueChangedBlCtrlregistersend1(LPCTSTR strNew);
	void ValueChangedBlCtrlregisterspos(LPCTSTR strNew);
	void ValueChangedBlCtrlregisterspos1(LPCTSTR strNew);
	void StatusChangedBlCtrlcoil(BOOL bStatus);
	void ValueChangedBlCtrlcoilpos(LPCTSTR strNew);
};

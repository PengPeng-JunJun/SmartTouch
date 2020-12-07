#pragma once

#include "..\BlendWndDll\MsgBox.h"
#include "Resource.h"
#include "..\HardwareInfoDll\HardwareInfo.h"


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\HardwareInfoDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\HardwareInfoDll.lib")
#endif

#define WM_REGISTER  WM_USER + 20
#define  CHECKREGISTERLIST  1

#define REGISTEROK    1
#define REGISTERERROR 0

// CRegisterDlg �Ի���

class AFX_EXT_CLASS CRegisterDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CRegisterDlg)

public:
	CRegisterDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CRegisterDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CRegisterDlg();

// �Ի�������
	enum { IDD = IDD_REGISTERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CBL_Edit m_BL_SoftwareID;
	CBL_Edit m_BL_RegisterID;
	CBL_Button m_BL_StartRegister;
	CBL_Button m_BL_StopRegister;

public:
	CWnd *m_pRegister;
public:
	CHardwareInfo m_HardwareInfo;
public:
	CString m_strRegisterID;

public:
	CString GetSoftwareID();
	void GetRegisterID(CString strMacAdd);
	void Write2RegisterList();
	void CheckRegisterList(int nCheckMode);//�]�Լ��ܷ�������ǰʹ��MAC��ַ
	BOOL CheckRegisterID(CString strRegisterID);
	int Rand(int nMin, int nMax);
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlStopRegister(long nFlags);
	void LBtClickedBlStartRegister(long nFlags);
	virtual void _DefaultFocus(void);
};

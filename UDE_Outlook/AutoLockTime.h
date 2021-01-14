#pragma once

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


// CAutoLockTime �Ի���

class CAutoLockTime : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CAutoLockTime)

public:
	CAutoLockTime(CWnd* pParent = NULL);   // ��׼���캯��
	CAutoLockTime(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAutoLockTime();

// �Ի�������
	enum { IDD = IDD_AUTOLOCKTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nAutoLockTime;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	CBL_Edit m_BL_edAutoLockTime;
};

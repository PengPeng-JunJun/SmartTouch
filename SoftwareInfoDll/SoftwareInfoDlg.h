#pragma once

#include "Resource.h"


#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif
// CSoftwareInfoDlg �Ի���

class AFX_EXT_CLASS CSoftwareInfoDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSoftwareInfoDlg)

public:
	CSoftwareInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSoftwareInfoDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSoftwareInfoDlg();
	virtual void _DefaultFocus(void);

// �Ի�������
	enum { IDD = IDD_SOFTWAREINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBL_Button m_BL_btVersion;
};

#pragma once


#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CMsgInfoDlg �Ի���

class CMsgInfoDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CMsgInfoDlg)

public:
	CMsgInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CMsgInfoDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CMsgInfoDlg();

// �Ի�������
	enum { IDD = IDD_MSGINFODLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBL_Button    m_BL_btErrorInfo;
	CBL_Button    m_BL_btErrorReason[3];
public:
	virtual void _DefaultFocus(void);

};

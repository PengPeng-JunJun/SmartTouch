#pragma once
#include "resource.h"

#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CParamManage �Ի���

class AFX_EXT_CLASS CParamManage : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CParamManage)

public:
	CParamManage(CWnd* pParent = NULL);   // ��׼���캯��
	CParamManage(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CParamManage();

// �Ի�������
	enum { IDD = IDD_PARAMMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CBL_List m_BL_ltParamManage;
	void _ShowInfo();
};

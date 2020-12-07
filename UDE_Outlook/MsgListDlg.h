#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include <vector>
#include <math.h>


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif

// CMsgListDlg �Ի���

class CMsgListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CMsgListDlg)

public:
	CMsgListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CMsgListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CMsgListDlg();
	virtual void _DefaultFocus(void);
// �Ի�������
	enum { IDD = IDD_MSGLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CBL_List m_BL_MsgList;
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void RowsChangedBlMsglist(long nOldRows, long nNewRows, BOOL bAppend);
};

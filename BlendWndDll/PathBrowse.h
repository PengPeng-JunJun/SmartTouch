#pragma once

#include "MsgBox.h"

// CPathBrowse �Ի���

class AFX_EXT_CLASS CPathBrowse : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CPathBrowse)

public:
	CPathBrowse(CWnd* pParent = NULL);   // ��׼���캯��
	CPathBrowse(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CPathBrowse();

// �Ի�������
	enum { IDD = IDD_PATHBROWSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);
protected:
	CString m_strPathBkup;
	void _UpdateUi(void);
public:
	void LBtClickedBtPathBroseGo(long nFlags);
};

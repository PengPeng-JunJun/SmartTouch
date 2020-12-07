#pragma once

#include "MsgBox.h"

// CFileBackMsg �Ի���

class AFX_EXT_CLASS CFileBackMsg : public CTpLayerWnd
{
	DECLARE_SERIAL(CFileBackMsg)

public:
	CFileBackMsg(CWnd* pParent = NULL);   // ��׼���캯��
	CFileBackMsg(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CFileBackMsg();

// �Ի�������
	enum { IDD = IDD_REMOTEFILEMSG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strOk;
	CString m_strNg;

	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
	virtual void OnOK();
	virtual void OnCancel();
	virtual void LockCtrls(int nLock);
protected:
	CString m_strOkBkup;
	CString m_strNgBkup;

	void _UpdateUi(void);
};

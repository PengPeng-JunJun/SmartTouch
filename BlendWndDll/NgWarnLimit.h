#pragma once

#include "MsgBox.h"

// CNgWarnLimit �Ի���

class CNgWarnLimit : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CNgWarnLimit)

public:
	CNgWarnLimit(CWnd* pParent = NULL);   // ��׼���캯��
	CNgWarnLimit(UINT nIDTemplate, CWnd * pParent = nullptr);

	virtual ~CNgWarnLimit();

// �Ի�������
	enum { IDD = IDD_NGWARNLIMIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bUseNum;
	BOOL m_bUseRate;

	int m_nNgLimit;
	double m_dNgRateLimit;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void LockCtrls(int nLock);
protected:
	void _UpdateUi(void);
};

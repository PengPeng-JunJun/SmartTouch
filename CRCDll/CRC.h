#pragma once

#include "CRCDlg.h"
#include "ValueCalculate.h"


class AFX_EXT_CLASS CCRC
{
public:
	CCRC(void);
	~CCRC(void);

public:
	CBlender<CCRCDlg> m_CRCDlg;
	CValueCalculate m_ValueCalculate;

public:
	void CreateBlendWnd(CWnd *pParent);

	INT_PTR CreateTopWnd(BOOL bModal, BOOL bShowNow = TRUE);

	void ShowParamWnd(int nShow);

	//BOOL LoadConfigurationFile();//���������ļ�

	BOOL SearchConfigurationFile();//�����Ƿ���������ļ���

	void CRCCheck(CString strInput, int nDataType, CString strChecckMode, CString & strResult_HEX, CString & strResult_Bin);//����У����

	CString LoadConfigurationFile(CString strPath, CString strFormat, BOOL bSelf);

	int String2Int(CString strValue, int nTransform);
	
};


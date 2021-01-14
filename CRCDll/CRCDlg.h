#pragma once

#include "Resource.h"
#include "CRC_16Modbus.h"
#include "ValueCalculate.h"
#include "AddConfigurationFile.h"


#include "..\BlendWndDll\MsgBox.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#endif


// CCRCDlg �Ի���

class AFX_EXT_CLASS CCRCDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CCRCDlg)

public:
	CCRCDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CCRCDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CCRCDlg();

	// �Ի�������
	enum { IDD = IDD_CRCDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CValueCalculate m_ValueCalculate;//ֵ������
	CBlender<CAddConfigurationFile> m_AddConfigurationFile;//��������ļ���
	 
public:
	CBL_Edit m_BL_InputString;

	CBL_Radio m_BL_DataStyle_HEX;
	CBL_Radio m_BL_DataStyle_DEC;
	CBL_Radio m_BL_DataStyle_ASCII;

	CBL_DropDown m_BL_CheckMode;

	CBL_Edit m_BL_CheckResult_HEX;
	CBL_Edit m_BL_CheckResult_Bin;

public:
	virtual BOOL OnInitDialog();
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBlInputstring(LPCTSTR strNew);
	void StatusChangedBlDataStyleHex(BOOL bNewStatus);
	void StatusChangedBlDataStyleDec(BOOL bNewStatus);
	void LBtClickedBlCleanInput(long nFlags);//�����������
	void LBtClickedBlCheckInput(long nFlags);//��ʼ�������ݣ��ڼ���ǰ��Ҫ���ж������һ�����������ַ�,���������ȷ���Ƿ����Ӹ�8λ
	void StatusChangedBlDataStyleASCII(BOOL bNewStatus);

public:
	CString m_strExePath;
public:
	BOOL SearchConfigurationFile();

	CString LoadConfigurationFile(CString strPath, CString strFormat);

	CString LoadConfigurationFile(CString strPath, CString strFormat, BOOL bSelf);

	void CRCCheck(CString strInput, int nDataType, CString strChecckMode);

	void CRCCheck(CString strInput, int nDataType, CString strChecckMode, CString & strResult_HEX, CString & strResult_Bin);

	void LBtClickedBlAddconfigurationshow(long nFlags);

	CString SearchFile(CString strDir, CString strExt, BOOL bSelf);

};

#pragma once


#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"


#include <vector>
#include <math.h>


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif


// CParameterAddDlg �Ի���

class CParameterAddDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CParameterAddDlg)

public:
	CParameterAddDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CParameterAddDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CParameterAddDlg();

// �Ի�������
	enum { IDD = IDD_PARAMETER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strRegistersStart; //R��ʼ��ַ
	CString m_strRegistersEnd;   //R�Y����ַ
	CString m_strRegistersStart1;//D��ʼ��ַ
	CString m_strRegistersEnd1;//D�Y����ַ
	CString m_strRegisters;//R��switch��B
	CString m_strRegisters1;//D��switch��B
	CString m_strRegistersPos;//R����ʼλ
	CString m_strRegistersPos1;//D����ʼλ
public:

	CString m_strDataStar;
	CString m_strDataEnd;   
	int m_nDataStar;
	int m_nDataEnd;
	int m_nDataInterval;//�����g��
	int m_nDataBits;//����λ��

public:
	CBL_Edit m_BL_edDataStar;
	CBL_Edit m_BL_edDataEnd;
	CBL_Edit m_BL_edDataInterval;
	CBL_DropDown m_BL_dpDataBits;

	DECLARE_EVENTSINK_MAP()
	void ValueChangedBleddatastar(LPCTSTR strNew);
	void ValueChangedBleddataend(LPCTSTR strNew);
	virtual void OnOK();
};

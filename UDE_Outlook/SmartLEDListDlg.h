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

// CSmartLEDListDlg �Ի���
#define TEST_INFO_ARRAY_LEN  128

#define WM_SMARTLED_CODE  WM_USER + 80//
#define WM_SMARTLED_FINISH  WM_USER + 81//



class CSmartLEDListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSmartLEDListDlg)

public:
	CSmartLEDListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSmartLEDListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSmartLEDListDlg();

// �Ի�������
	enum { IDD = IDD_SMARTLEDLISTDLG };

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
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
public:
	CWnd *m_pSmartLEDListDlg;
public:
	CBL_List m_BL_SmartLEDList;
	CBL_Edit m_BL_edSmartLEDCode;
	CBL_Button m_BL_btLoadSmartLED;
	CBL_Button m_BL_btSaveSmartLED;
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBledsmartledcode(LPCTSTR strNew);
	void ItemChangedBlSmartledlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlSmartledlist(long nRow, long nCol, short* pnParam, short nFlags);
	void LBtClickedBlbtsavesmartled(long nFlags);
	void LBtClickedBlbtloadsmartled(long nFlags);
public:
	int m_nSmartLEDCode;

	typedef struct _tagStartInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_START_INFO;

	typedef struct _tagResultInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_RESULT_INFO;
protected:
	afx_msg LRESULT OntReceiveSmartledCode(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};

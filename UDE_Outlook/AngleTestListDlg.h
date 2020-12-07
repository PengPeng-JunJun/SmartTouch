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
// CAngleTestListDlg �Ի���
#define TEST_INFO_ARRAY_LEN  128

#define WM_ANGLETEST_CODE  WM_USER + 120//
#define WM_ANGLETEST_FINISH  WM_USER + 120//

class CAngleTestListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CAngleTestListDlg)

public:
	CAngleTestListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CAngleTestListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CAngleTestListDlg();

// �Ի�������
	enum { IDD = IDD_ANGLETESTLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
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
	CWnd *m_pAngleTestListDlg;
public:
	int m_nAngleTestCode;

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
		int nResult;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_RESULT_INFO;
};

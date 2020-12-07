#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>

#include "ParameterAddDlg.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif
// CDataCollectionDlg �Ի���

class CDataCollectionDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CDataCollectionDlg)

public:
	CDataCollectionDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CDataCollectionDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CDataCollectionDlg();
	virtual void _DefaultFocus(void);
// �Ի�������
	enum { IDD = IDD_DATACOLLECTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

public:
	CBL_List m_BL_DataCollectionList;
	CBL_Button m_BL_btSaveData;
	CBL_Button m_BL_btLoadData;
	CBL_Button m_BL_btAddData;

	CString m_strRegistersStart; //R��ʼ��ַ
	CString m_strRegistersEnd;   //R�Y����ַ
	CString m_strRegistersStart1;//D��ʼ��ַ
	CString m_strRegistersEnd1;//D�Y����ַ
	CString m_strRegisters;//R��switch��B
	CString m_strRegisters1;//D��switch��B
	CString m_strRegistersPos;//R����ʼλ
	CString m_strRegistersPos1;//D����ʼλ

public:
	CBlender<CParameterAddDlg> m_ParameterAdd;
	DECLARE_EVENTSINK_MAP()
	void ItemChangedBlDatacollectionlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlDatacollectionlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemEditFinishBlDatacollectionlist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlbtsavedata(long nFlags);
	void LBtClickedBlbtloaddata(long nFlags);
	void LBtClickedBlbtadddata(long nFlags);
public:

	virtual void Serialize(CArchive& ar);
};

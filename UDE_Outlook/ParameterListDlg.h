#pragma once

#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"
#include "NumberInputDlg.h"
#include "ParameterAddDlg.h"


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

#define WM_PARAM_FINISH   WM_USER + 30
#define WM_PARAM_UPDATE   WM_USER + 31

// CParameterListDlg �Ի���

class CParameterListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CParameterListDlg)

public:
	CParameterListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CParameterListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CParameterListDlg();

// �Ի�������
	enum { IDD = IDD_PARAMETERLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void _DefaultFocus(void);
public:
	CBlender<CNumberInputDlg> m_NumberInput;
	CBlender<CParameterAddDlg> m_ParameterAdd;

public:
	CString m_strRegistersStart; //R��ʼ��ַ
	CString m_strRegistersEnd;   //R�Y����ַ
	CString m_strRegistersStart1;//D��ʼ��ַ
	CString m_strRegistersEnd1;//D�Y����ַ
	CString m_strRegisters;//R��switch��B
	CString m_strRegisters1;//D��switch��B
	CString m_strRegistersPos;//R����ʼλ
	CString m_strRegistersPos1;//D����ʼλ

	vector<int> m_vnUpdateData;// ����������

	BOOL m_bLocked;//������Ŀ����Ȩ���Ƿ�����,TRUE--������FALSE--����

	BOOL m_bParamInpiutLocked;//��������Ȩ���Ƿ�����,TRUE--������FALSE--����

	BOOL m_bParamInputting;//����ݔ����
public:
	CBL_List m_BL_ParameterList;
	CBL_Button m_BL_btSaveParam;
	CBL_Button m_BL_btLoadParam;
	CBL_Button m_BL_btAddParam;
	CBL_CheckBox m_BL_ckUpdateData;

	DECLARE_EVENTSINK_MAP()
	void ItemChangedBlParameterlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlParameterlist(long nRow, long nCol, short* pnParam, short nFlags);
	void RowsChangedBlParameterlist(long nOldRows, long nNewRows, BOOL bAppend);
public:
	CWnd *m_pParameterListDlg;
public:
	
	void LBtClickedBlbtsaveparam(long nFlags);
	void LBtClickedBlbtloadparam(long nFlags);
	virtual void Serialize(CArchive& ar);
	void ItemEditFinishBlParameterlist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlbtaddparam(long nFlags);
protected:
	afx_msg LRESULT OnParamUpdate(WPARAM wParam, LPARAM lParam);
public:
	void StatusChangedBlckupdatedata(short nNewStatus);
};

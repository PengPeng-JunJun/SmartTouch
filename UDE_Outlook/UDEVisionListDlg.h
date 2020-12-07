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
// CUDEVisionListDlg �Ի���

#define WM_ED_UDEVISION_RES  3000

#define UDEVISION_COLS_COUNTER 23 
#define TEST_INFO_ARRAY_LEN  128

#define WM_UDEVISION_CODE  WM_USER + 60//���Ӻ��c�z�y
#define WM_UDEVISION_FINISH  WM_USER + 61//���c�z�y�Y��
#define WM_UDEVISION_FINISH_ROBOT  WM_USER + 62//���c�z�y�Y��
#define WM_UDEVISION_CODE_ROBOT  WM_USER + 63//�ֱۆ��Ӻ��c�z�y

#define PLC2UDEVISION 1
#define ROBOT2UDEVISION 2

class CUDEVisionListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CUDEVisionListDlg)

public:
	CUDEVisionListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CUDEVisionListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CUDEVisionListDlg();

// �Ի�������
	enum { IDD = IDD_UDEVISION };

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
	CWnd *m_pUDEVisionListDlg;
public:
	CBL_List m_BL_UDEVisionList;
	CBL_Edit m_BL_edUDEVisionCode;
	CBL_Edit m_BL_edUDEVisionResult;
	CBL_Button m_BL_btLoadUDEVision;
	CBL_Button m_BL_btSaveUDEVision;
	CBL_Edit m_BL_edUDEVisionRes[21];
	CBL_Edit m_BL_edUDEVisionInfo;
	CBL_Button m_BL_btUDEVisionContinue;
	CBL_Radio m_BL_rdUDEVision_PLC;
	CBL_Radio m_BL_rdUDEVision_Robot;

public:
	int m_nUDEVisionCode;
	int m_nUDEVisionCodeRobot;
	vector<CString> m_vstrUDEVisionInfo;//Ⱥ�M�yԇ�Ŀ����
	vector<CString> m_vstrUDEVisionRes;
	vector<byte> m_vbyRobotStarUDEVisionGroup;//�b�ֱۆ������^��Ⱥ�M��̖
	int m_nUDEVisionNO;//�����޸ĵ�Ⱥ�M�yԇ�Ŀ��̖
	typedef struct _tagTestInfo
	{
		int nID;
		int nParam1;
		int nParam2;
		int nParam3;
		int nParam4;

		int nResult;
		double dResult;
		BOOL bResult;

		byte byStarGroup[TEST_INFO_ARRAY_LEN];
		char szResult[TEST_INFO_ARRAY_LEN];
		char szInfo[TEST_INFO_ARRAY_LEN];
		char szSrcWnd[TEST_INFO_ARRAY_LEN];
	}TEST_INFO;

	DECLARE_EVENTSINK_MAP()
	void ValueChangedBledudevisioncode(LPCTSTR strNew);
	void ItemChangedBlUdevisionlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlUdevisionlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemEditFinishBlUdevisionlist(long nRow, long nCol, LPCTSTR strNew);
	void LBtClickedBlbtsaveudevision(long nFlags);
	void LBtClickedBlbtloadudevision(long nFlags);
protected:
	afx_msg LRESULT OnReceiveUdevisionCode(WPARAM wParam, LPARAM lParam);
public:
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
protected:
	afx_msg LRESULT OnEdUdevisionRes(WPARAM wParam, LPARAM lParam);
public:
	void LBtClickedBlbtudevisioncontinue(long nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void EnterPressedBledudevisioninfo(LPCTSTR strValue);
protected:
	afx_msg LRESULT OnReceiveUdevisionCodeRobot(WPARAM wParam, LPARAM lParam);
public:
	void StatusChangedBlrdudevisionPlc(BOOL bNewStatus);
	void StatusChangedBlrdudevisionRobot(BOOL bNewStatus);
};

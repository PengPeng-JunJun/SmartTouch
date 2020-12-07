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
// CSmartRobotListDlg �Ի���
#define TEST_INFO_ARRAY_LEN  128

#define WM_SMARTROBOT_CODE  WM_USER + 70//���ƙCе����Ϣ
#define WM_SMARTROBOT_FINISH  WM_USER + 71//
#define WM_SMARTROBOT_STAR_UDEVISION  WM_USER + 72//
#define WM_SMARTROBOT_FINISH_UDEVISION  WM_USER + 73//
#define WM_SMARTROBOT_STAR_UDEOUTLOOK  WM_USER + 74//
#define WM_SMARTROBOT_FINISH_UDEOUTLOOK  WM_USER + 75//

class CSmartRobotListDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CSmartRobotListDlg)

public:
	CSmartRobotListDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CSmartRobotListDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CSmartRobotListDlg();

// �Ի�������
	enum { IDD = IDD_SMARTROBOTLISTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void Serialize(CArchive& ar);
public:
	CWnd *m_pSmartRobotListDlg;
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
	int m_nSmartRobotCode;
	CString m_strRobotStarUDEVisionWnd;//�ֱۆ������^�Ĵ������Q
	CString m_strRobotStarUDEOutlookWnd;
public:
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

public:
	CBL_List m_BL_SendSmartRobotList;
	CBL_List m_BL_GetSmartRobotList;
	CBL_Edit m_BL_edSmartRobotCode;
	CBL_Button m_BL_btSaveSmartRobot;
	CBL_Button m_BL_btLoadSmartRobot;
	DECLARE_EVENTSINK_MAP()
	void ValueChangedBledsmartrobotcode(LPCTSTR strNew);
	void ItemChangedBlSendsmartrobotlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlSendsmartrobotlist(long nRow, long nCol, short* pnParam, short nFlags);
protected:
	afx_msg LRESULT OnReceiveSmartrobotCode(WPARAM wParam, LPARAM lParam);
public:
	void ItemChangedBlGetsmartrobotlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void LBtDbClickBlGetsmartrobotlist(long nRow, long nCol, short* pnParam, short nFlags);
	void ItemEditFinishBlGetsmartrobotlist(long nRow, long nCol, LPCTSTR strNew);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	void LBtClickedBlbtsavesmartrobot(long nFlags);
	void LBtClickedBlbtloadsmartrobot(long nFlags);
protected:
	afx_msg LRESULT OnReceiveSmartrobotFinishUdevision(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnReceiveSmartrobotFinishUdeoutlook(WPARAM wParam, LPARAM lParam);
};

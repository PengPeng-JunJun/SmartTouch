#pragma once

#include "..\BlendWndDll\MsgBox.h"
#include "..\ExcelDll\Excel.h"
#include "..\FindFileDll\FindCtrlFile.h"

#include "CtrlSet.h"
#include "MsgListDlg.h"
#include "ParameterListDlg.h"
#include "ErrorListDlg.h"

#include "SmartDotsListDlg.h"
#include "SmartRobotListDlg.h"
#include "AngleTestListDlg.h"
#include "DiameterTestDlg.h"
#include "UDEOutlookListDlg.h"
#include "UDEVisionListDlg.h"
#include "SmartLEDListDlg.h"
#include "DataCollectionDlg.h"
#include "NewSmartDots.h"
#include "AutoLockTime.h"

#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>


#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\ExcelDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#pragma comment(lib, "..\\Debug\\FindFileDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\ExcelDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#pragma comment(lib, "..\\Release\\FindFileDll.lib")
#endif

#define  WM_STARTCOLLECT  WM_USER + 10//��->��
#define  WM_STOPCOLLECT  WM_USER + 11
#define  WM_DELETFILE    WM_USER + 12//�h�����N���ļ��A
#define  WM_COLLECTRUN   WM_USER + 13//�_ʼ�ռ������������g�����ռ�����
#define  WM_COLLECTFINISH WM_USER + 14//�����ռ���ɣ��_ʼ���Ɉ��
#define  WM_COLLECTLOSE   WM_USER + 15//�O�����
#define  WM_WRITE_FINISH  WM_USER + 16//����д�����
#define  WM_WRITE_DATA  WM_USER + 17//����д��

#define  WM_LOCK_STATE  WM_USER + 18//Ȩ�����������

#define  READ_DATA    0//�xȡ�O���еĔ���
#define  WRITE_DATA    1//���������O����
#define  SAVE_DATA     2//���攵��������񼯔����ĕr�g


#define TIME_RATIO   1//�r�g����

#define DATE_BEFORE 0//Ӌ�㮔ǰ����֮ǰ������
#define DATE_AFTER  1//Ӌ�㮔ǰ����֮�������

#define DATE_REPORT 1//�Ո�
#define MOUTH_REPORT 2//��


#define WM_BT_REALY 1025
#define WM_CK_REALY 1026
#define WM_DP_REALY 1027

// CControllerDlg �Ի���

class CControllerDlg : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CControllerDlg)

public:
	CControllerDlg(CWnd* pParent = NULL);   // ��׼���캯��
	CControllerDlg(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CControllerDlg();

// �Ի�������
	enum { IDD = IDD_CONTROLLERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CExcel  m_Excel;
	CFindCtrlFile m_FindCtrlFile;
	CBlender<CCtrlSet> m_CtrlSet;//�ؼ������O��
	CBlender<CMsgListDlg> m_MsgListDlg;//����Ϣ����@ʾ����
	CBlender<CParameterListDlg> m_ParameterListDlg;//
	CBlender<CDataCollectionDlg> m_DataCollectionDlg;//
	CBlender<CErrorListDlg> m_ErrorListDlg;//

	CBlender<CSmartDotsListDlg> m_SmartDotsListDlg;
	CBlender<CSmartRobotListDlg> m_SmartRobotListDlg;
	CBlender<CAngleTestListDlg> m_AngleTestListDlg;
	CBlender<CDiameterTestDlg> m_DiameterTestListDlg;
	CBlender<CUDEOutlookListDlg> m_UDEOutlookListDlg;
	CBlender<CUDEVisionListDlg> m_UDEVisionListDlg;
	CBlender<CSmartLEDListDlg> m_SmartLEDListDlg;
	CBlender<CNewSmartDots>  m_NewSmartDotsDlg;
	CBlender<CAutoLockTime>  m_AutoLockTimeDlg;
public:

	//CString m_strExcelPath;
	CString m_strExcelPathTem;

public:
	CBL_List m_BL_ReportCollectList;
	CBL_Menu m_BL_ControllerMenu;

	CBL_Button m_BL_btRelay[BT_RELAY_SUM];
	CBL_CheckBox m_BL_ckRelay[CK_RELAY_SUM];
	CBL_DropDown m_BL_dpRelay[DP_RELAY_SUM];


	CBL_Button m_BL_btAddCtrl;//��ӿؼ�
	CBL_Button m_BL_btChangeCtrl;//�޸Ŀؼ�

	CBL_Button m_BL_btRelayStar;
	CBL_Button m_BL_btRelayStop;
	CBL_Button m_BL_btRelayReset;
	CBL_Button m_BL_btRelayError;
	CBL_Button m_BL_btRelayPause;

	CBL_Switch m_BL_swRelayAuto;
	CBL_Switch m_BL_swRelayUnAuto;
	CBL_Switch m_BL_swConnect;

public:
	int m_nControllerDlgCounter;//ÿ���Ի����һ�޶��ı�����������������Ϣ������

	BOOL m_bLocked;//Ȩ������
	virtual void Serialize(CArchive& ar);

	virtual BOOL OnInitDialog();
	virtual void _DefaultFocus(void);
	virtual void DrawTitle(CDC * pDC, CRect rcDraw);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);

	DECLARE_EVENTSINK_MAP()
	void RowsChangedBlReportcollectlist(long nOldRows, long nNewRows, BOOL bAppend);
	void LBtDbClickBlReportcollectlist(long nRow, long nCol, short* pnParam, short nFlags);
	void LBtClickedBlGetreport(long nFlags);
public:
	CString GetExePath(void) ;

public:
	void GetSystemTime(int & nYear, int & nMouth, int & nDay, int & nHour, int & nMinute, int & nSeconds);
	void GetSystemTime(CString & strYear, CString & strMouth, CString & strDay, CString & strHour, CString & strMinute, CString & strSeconds);

	static UINT _CollectDataThread(LPVOID pParam);
	UINT _CollectDataThreadKernal(void);
	void CollectData();
	void SetMainMenu();
public://���������߳�
	afx_msg void OnClose();
	virtual void OnCancel();
protected:
	afx_msg LRESULT OnStartCollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStopCollect(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int m_nReportColCounter;
	CString m_strInput;
	CString m_strControllerName;
	CString m_strSoftwareVersion;//ܛ���汾̖

	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER m_nEndTime;
	CString m_strTime;

	int m_nAutoLockTime;//�Ԅ��i���r�L
	void LoadFileData();

public:
	CString m_strRegistersStart; //R��ʼ��ַ
	CString m_strRegistersEnd;   //R�Y����ַ
	CString m_strRegistersStart1;//D��ʼ��ַ
	CString m_strRegistersEnd1;//D�Y����ַ
	CString m_strRegisters;//R��switch��B
	CString m_strRegisters1;//D��switch��B
	CString m_strRegistersPos;//R����ʼλ
	CString m_strRegistersPos1;//D����ʼλ
	CString m_strCoil;//M��switch��B
	CString m_strCoilStart; //M��ʼ��ַ
	CString m_strCoilEnd;   //M�Y����ַ
	CString m_strCoilPos;//M����ʼλ

	void ItemChangedBlReportcollectlist(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);
	void ItemEditFinishBlReportcollectlist(long nRow, long nCol, LPCTSTR strNew);
public:
	CWnd *m_pController;//�O���\�Ќ�Ԓ�򴰿�ָ�
	BOOL m_bUninterrupted;//���g���ռ����� TRUE �鲻�g���ռ���FALSE ���g���ռ���ֻ�����Ӵ��ڰl����Ϣ�r�ռ�
protected:
	afx_msg LRESULT OnCollectFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWriteFinish(WPARAM wParam, LPARAM lParam);
public:
	BOOL m_bCollecting;//̎��ռ���B

	void AutoDeletData();
public:
	CValueCalculate m_ValueCalculate;
	CString DateCalculate_GetSpan(COleDateTime TimeBegin, COleDateTime TimeEnd);//�����ṩ�ĕr�g�_ʼ�ͽY����Ӌ�����g�g�����씵
	CString DateCalculate_GetDate(CTime Time, int nTimeSpan, int nOffset);//�����ṩ�����ڣ��g���씵���g����ʽ��Ӌ��Ŀ������
	
protected:
	afx_msg LRESULT OnCollectLose(WPARAM wParam, LPARAM lParam);
protected:
	afx_msg LRESULT OnBtRealyMessage(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCkRealy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDpRealy(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnParamFinish(WPARAM wParam, LPARAM lParam);//����ݔ�����

public:
	void LBtClickedBlAddctrl(long nFlags);
	void LBtClickedBlChangectrl(long nFlags);

public:
	vector<BOOL> m_vbRelayBtStatus;
	vector<BOOL> m_vbRelayCkStatus;
	vector<BOOL> m_vbRelayDpStatus;

	vector<CString> m_vstrRelayBt;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayBtName;//�����м�̵�������
	vector<int>     m_vnRelayBtMode;//�����м�̵�������
	vector<BOOL>    m_vbIsRelayBtClickAuto;//�Ԅ�ģʽ���Ƿ�����c�����o

	vector<CString> m_vstrRelayCk;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayCkName;//�����м�̵�������

	vector<CString> m_vstrRelayDp;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayDpName;//�����м�̵�������
	vector<CString> m_vstrRelayDpCaption;

	BOOL m_bRelayBtStarStatus;
	BOOL m_bRelayBtStopStatus;
	BOOL m_bRelayBtResetStatus;
	BOOL m_bRelayBtErrorStatus;
	BOOL m_bRelayBtPauseStatus;
	BOOL m_bRelaySwAutoStatus;
	BOOL m_bRelaySwUnAutoStatus;

	CString m_strRelayStar;
	CString m_strRelayStop;
	CString m_strRelayReset;
	CString m_strRelayError;
	CString m_strRelayPause;
	CString m_strRelayAuto;
	CString m_strRelayUnAuto;

	vector<CString> m_vstrParameter;
	vector<CString> m_vstrParameterName;
	vector<CString> m_vstrParameterByte;
	vector<CString> m_vstrParameterPt;//С��λ��
	vector<CString> m_vstrParameterUnit;//������λ

	vector<CString> m_vstrDataCollection;
	vector<CString> m_vstrDataCollectionName;
	vector<CString> m_vstrDataCollectionByte;
	vector<CString> m_vstrDataCollectionPt;//С��λ��
	vector<CString> m_vstrDataCollectionUnit;//������λ

public:
	void UpdateMsgList();//������Ϣ�б�
	void UpdateParameterList();
	void UpdateDataCollectionList();
	void UpdateErrorList();
	void UpdateSmartDotsList();
	void UpdateUDEVisionList();
	void UpdateUDEOutlookList();
	void UpdateSmartRobotList();
	void UpdateSmartLEDList();
	void UpdateAngleTestList();
	void UpdateDiameterTestList();
	void UpdateNewSmartDots();

	void CollectStar();
	CString UpdateMsgListAddress(CString strRelayMode);//�����б��еĵ�ַ��,���ص�ַ�ַ���
	void StartConnect();//�_ʼ�B��
	void SearchSendData(CString strDatInfo, int nData);//��ѯ��Ҫ���͵����ݣ����ұ���еĵ�һ����Ӧ��������̵������޸Ķ�Ӧ״̬

	void SearchSendData_Angle(CString strDatInfo, int nData);

public:
	void ItemClickBlControllermenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);
	void StatusChangedBlswconnect(BOOL bStatus);
	void StatusChangedBlswrelayauto(BOOL bStatus);
	void StatusChangedBlswrelayunauto(BOOL bStatus);
	void LBtClickedBlbtrelaystar(long nFlags);
	void LBtClickedBlbtrelaystop(long nFlags);
	void LBtClickedBlbtrelayreset(long nFlags);
	void LBtClickedBlbtrelaypause(long nFlags);
	void LBtClickedBlbtrelayerror(long nFlags);
protected:
	
	afx_msg LRESULT OnSmartdotsFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdevisionFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotStarUdevision(WPARAM wParam, LPARAM lParam);//�ֱۆ������^
	afx_msg LRESULT OnUdevisionFinishRobot(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartledFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdeoutlookFinishRobot(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnUdeoutlookFinish(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSmartrobotStarUdeoutlook(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnGetLockState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnNewsSmartDotsFinish(WPARAM wParam, LPARAM lParam);
};


// UDE_OutlookDlg.h : ͷ�ļ�
//
//��
#pragma once

#include "ControllerDlg.h"
#include "ControllerAddDlg.h"
#include "FindCtrlFile.h"
#include "MsgInfoDlg.h"
#include "..\\BlendWndDll\Register.h"

#include "..\\SerialPortDll\RS232.h"
#include "..\\BlendWndDll\MsgBox.h"
#include "..\\CRCDll\\CRC.h"
#include "..\\CRCDll\\CRCDlg.h"
#include "..\\ExcelDll\Excel.h"
#include "..\\RegisterDll\RegisterDlg.h"
#include "..\\SoftwareInfoDll\\SoftwareInfoDlg.h"

#include <vector>
#include <math.h>
#include <stdio.h>  
#include <windows.h> 

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\SerialPortDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#pragma comment(lib, "..\\Debug\\ExcelDll.lib")
#pragma comment(lib, "..\\Debug\\RegisterDll.lib")
#pragma comment(lib, "..\\Debug\\SoftwareInfoDll.lib")
#define DEBUGSTYLE   0
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\SerialPortDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#pragma comment(lib, "..\\Release\\ExcelDll.lib")
#pragma comment(lib, "..\\Release\\RegisterDll.lib")
#pragma comment(lib, "..\\Release\\SoftwareInfoDll.lib")
#define RELEASESTYLE   1
#endif


#define  MAXLEN  50
#define  MAXHISTORYPATH   6

#define WM_SHOWTASK     WM_USER + 100 //������������ϵ�ͼ��ʱ��ͼ��Ҫ��������Ϣ����Ϣ�Ľ����߾��ǵ�ǰ��д�������Ĵ���

#define SLEEPTIME 1//�ӕr�r�L����λ��΢��


using namespace std;
// CUDE_OutlookDlg �Ի���
class CUDE_OutlookDlg : public CAppBase
{
// ����
public:
	CUDE_OutlookDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDE_OUTLOOK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	int m_nRunStyle;

public:
	CBlender<CMsgInfoDlg> m_MsgInfoDlg;
	vector<CBlender<CControllerDlg>*> m_pControllerDlg;
	CBlender<CControllerAddDlg> m_ControllerAddDlg;
	CBlender<CRegisterDlg> m_Register;
	CBlender<CSoftwareInfoDlg> m_SoftwareInfoDlg;

public:

	BOOL m_nInit;
	int m_nCollectCounter_Main;//�������ռ��м���
	int m_nCollectCounter_Slave;//����ı���ռ��м���

	int m_nCommunicationMode;//����ͨӍ��ģʽ���xȡ����

	int m_nStationNO;//�豸վ��
	int m_nStationAddress;//������ʼ��ַ
	vector<int> m_nReceiveData;
	
	vector<CString> m_strCollectStatus;//������ʾ���ݲɼ�״̬

	BOOL m_bReceive;//���ܵĔ����Ƿ���Ч

	BOOL m_bItemFinish;//���킀�����Ƿ�ݔ�����  

	int m_nCommend;//������
	CString m_strFilePath;

	BOOL m_bOpenFile;
	BOOL m_bIfExcel;

	UINT m_nHistoryPathCounter;
	vector<CString> m_strHistoryPath;
	
	BOOL m_bAutoRun;//�Ԅ��_�C

	BOOL m_bAutoFindFile;//�ԄӼ��d�n��

	vector<vector<int>> m_nvMsg;//���S������ÿ�����ڰl�́����Ϣ�����e���Ǵ��ڰl����Ϣ����ͣ��ǒ񼯔���߀�ǌ��딵��
	vector<vector<int>> m_nvWriteMsg;//���S������ÿ�����ڰl�́����Ϣ�����e���Ǵ��ڰl����Ϣ����ͣ��ǒ񼯔���߀�ǌ��딵��

	vector<BOOL> m_bvConnecting;//�O���Ƿ�̎�朽Ӡ�B
	BOOL m_bIsBalloonTipShow;//���ݴ����Ƿ����@ʾ

	CString m_strSoftwareVersion;//ܛ���汾̖

public:
	CRS232  m_Port;
	CCRC    m_CRC;
	CFindCtrlFile m_FindCtrlFile;
	CCRCDlg m_CRCDlg;
	CExcel m_Excel;

public:
	CBL_Menu  m_BL_MainMenu;
	CBL_List  m_BL_ReportMainList;
	CBL_Switch m_BL_Collect;
	CBL_Button m_BL_CollectStatus;
	CBL_Edit   m_BL_ReportLimit;
	CBL_Radio  m_BL_DateReport;
	CBL_Radio  m_BL_MouthReport;

public:
	virtual void LockCtrls(int nLock);//��Ӧ�����ؼ���Ϣ
	virtual void PreInitDialog();
protected:
	BOOL _RegisterActivex(BOOL bRegister);
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);//���бP߀ԭ������
	NOTIFYICONDATA m_nid;
	BOOL m_bShowDlg;//�Ƿ��@ʾ����Ԓ��

	BOOL m_bMin2Tray;//�Ƿ���С�����бP

	BOOL m_bCommuncating;//����ͨѶ��, ��������ͨѶ�У���Ϣ��������л�
	BOOL m_bInterruptRead;//TRUE��д�����������ж϶�ȡ����  FALSE ������ȡ����


public:
	void InitMainWindow();//��ʼ�������ڣ��_�����i���o��λ��

	void SetMainMenu();//�������˵�������

	void CreateChildWindow();//�����������Ի���

	void CreateNewReportList();//���������̱��

	void CleanCurrentReportList();//��������̱��ă��ݣ�ͬ�r����O�����ָ�����

	void SearchConfigurationFile();//����CRC�����ļ�

	void SearchControllerFile();//���һ�̨�����ļ���

	void SearchReportFile();//���ұ��������ļ���

	void SearchTemplateFile();//����EXCELģ���ļ��A

	CString GetExePath();//��ȡEXE�ľ���·��

	void Saveproject();//�ļ�����

	void Openproject();//�ļ����d

	void OpenprojectWithFilePath(CString strPath);//����·�����d�n��

	void Saveasproject();//�ļ�����

	void StartCollect();//��ʼ�ռ�����

	void InterruptedSendMsg2Ctrl();//������Ϣ�б�����K����PLC��Ϣ

	CString GetCRCCheck(vector<BYTE> bySend, CString strChecckMode);//��ȡCRCУ����

	void TranslateReveiveData();//�����豸�ش���Ϣ

	void SaveHistoryPath();//����n���vʷ·��

	void LoadHistoryPath();//���d�n���vʷ·��

	void UpdateMenu();//���²ˆΙ�

	void SetAutoRun(BOOL bAutoRun);//�O���_�C�����

	void CheckFileCounter();//�����ռ����Ĕ����Ƿ��^�O�Ô�������

	void DelayTimeRun();//�ӕr�����O��֮�g���\��

	BOOL ShowBalloonTip(LPCTSTR szMsg, LPCTSTR szTitle, UINT uTimeout, DWORD dwInfoFlags);//�O�Ú�����Ϣ

	DECLARE_EVENTSINK_MAP()
	void ItemClickBlMainMenu(LPCTSTR strMenu, LPCTSTR strItem, short nItemPos, BOOL bChecked, long nFlags);//�ˆ��c��푑���Ϣ

public:
	void LBtDbClickBlReportMainList(long nRow, long nCol, short* pnParam, short nFlags);//�������б��p���Ԫ��푑���Ϣ
	void ItemChangedBlReportMainList(long nRow, long nCol, LPCTSTR strOld, LPCTSTR strNew);//�������б��Ԫ�����׃��푑���Ϣ
	void ItemEditFinishBlReportmainlist(long nRow, long nCol, LPCTSTR strNew);//�������б��Ԫ�����ݔ�����푑���Ϣ
	void RowsChangedBlReportmainlist(long nOldRows, long nNewRows, BOOL bAppend);//�������б��Д���׃��׃��푑���Ϣ���O�����Ӻ̈́h��

	afx_msg void OnClose();
public:
	virtual void Serialize(CArchive& ar);//���л��ͷ����л�

protected:
	afx_msg LRESULT OnGmsgserialreceivechar(WPARAM wParam, LPARAM lParam);//�յ�������Ϣ
	afx_msg LRESULT OnGetRegisterMsg(WPARAM wParam, LPARAM lParam);//�յ��]����Ϣ
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnCancel();

public:
	CRect m_startRect;     //���ڵĳ�ʼλ�����ڵľ���
	CPoint m_startPoint;   //��갴�µ�λ��
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnGmsgminwindow(WPARAM wParam, LPARAM lParam);//������С�����I���f����Ϣ
	afx_msg LRESULT OnDeletFlie(WPARAM wParam, LPARAM lParam);//���܄������µ��ļ��A��Ϣ
	afx_msg LRESULT OnCollectRun(WPARAM wParam, LPARAM lParam);//�_ʼ�ռ�����������g���ռ�����
public:
	void StatusChangedBlDatereport(BOOL bNewStatus);
	void StatusChangedBlMouthreport(BOOL bNewStatus);
	static UINT _SaveProjectThread(LPVOID pParam);
	UINT _SaveProjectThreadKernal(void);

	static UINT _DelayTimeRunThread(LPVOID pParam);
	UINT _DelayTimeRunThreadKernal(void);

protected:
	afx_msg LRESULT OnStopcollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStartcollect(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnWriteData(WPARAM wParam, LPARAM lParam);
};

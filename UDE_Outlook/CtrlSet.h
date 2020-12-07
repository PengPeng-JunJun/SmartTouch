#pragma once
#include "..\BlendWndDll\MsgBox.h"


#include "..\\CRCDll\\ValueCalculate.h"

#include <vector>
#include <math.h>

#define WM_RD_CTRL_MODE  2000//�ؼ������Ϣ
#define WM_RD_RELAY_BT_MODE  2001//���I�����Ϣ


#define WM_BT_RELAY_BT_STATUS  2002//
#define WM_BT_RELAY_CK_STATUS  2003//
#define WM_BT_RELAY_DP_STATUS  2004//
#define WM_BG_RELAY_BASIC      2005//������ֹͣ����λ��Ϣ

#define RELAY_BT_MODE_COUNTER 2//���I���Ӌ��

#define RELAY_BT_MODE_LOCK    1//��������
#define RELAY_BT_MODE_UNLOCK  2//�����Ը� 

#ifdef _DEBUG
#pragma comment(lib, "..\\Debug\\BlendWndDll.lib")
#pragma comment(lib, "..\\Debug\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Debug\\CRCDll.lib")
#else
#pragma comment(lib, "..\\Release\\BlendWndDll.lib")
#pragma comment(lib, "..\\Release\\BlActiveXDll.lib")
#pragma comment(lib, "..\\Release\\CRCDll.lib")
#endif

#define BT_RELAY_SUM 100//���I����
#define CK_RELAY_SUM 16//checkbox����
#define DP_RELAY_SUM 10//dropdown����

// CCtrlSet �Ի���

class CCtrlSet : public CTpLayerWnd
{
	DECLARE_DYNAMIC(CCtrlSet)

public:
	CCtrlSet(CWnd* pParent = NULL);   // ��׼���캯��
	CCtrlSet(UINT nIDTemplate, CWnd * pParent = nullptr);
	virtual ~CCtrlSet();

// �Ի�������
	enum { IDD = IDD_CTRLSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void _DefaultFocus(void);
	virtual void DrawElement(CDC * pDC, CRect rcDraw);

	DECLARE_MESSAGE_MAP()
public:
	CBL_Radio m_BL_rdRelayBtMode[RELAY_BT_MODE_COUNTER];//
	CBL_CheckBox m_BL_ckRelayBtClickAuto;

	CBL_Edit m_BL_edRelayBt;
	CBL_Edit m_BL_edRelayBtName;

	CBL_Edit m_BL_edRelayCk;
	CBL_Edit m_BL_edRelayCkName;

	CBL_Edit m_BL_edRelayDp;
	CBL_Edit m_BL_edRelayDpName;
	CBL_Edit m_BL_edRelayDpCaption;

	CBL_Button m_BL_btRelayBtStatus[BT_RELAY_SUM];
	CBL_Button m_BL_btRelayCkStatus[CK_RELAY_SUM];
	CBL_Button m_BL_btRelayDpStatus[DP_RELAY_SUM];

	CBL_Button m_BL_btRelayStarStatus;
	CBL_Button m_BL_btRelayStopStatus;
	CBL_Button m_BL_btRelayResetStatus;
	CBL_Button m_BL_btRelayErrorStatus;
	CBL_Button m_BL_btRelayPauseStatus;
	CBL_Button m_BL_btRelayAutoStatus;
	CBL_Button m_BL_btRelayUnAutoStatus;

	CBL_Button m_BL_btRelayBtOK;
	CBL_Button m_BL_btRelayCkOK;
	CBL_Button m_BL_btRelayDpOK;

	CBL_Button m_BL_btSaveCtrl;
	CBL_Button m_BL_btLoadCtrl;


public:
	vector<BOOL> m_vbRelayBtStatus;
	vector<BOOL> m_vbRelayCkStatus;
	vector<BOOL> m_vbRelayDpStatus;

	int m_nRelayBtFocus;//�����̵��������еı�ţ�0~99��
	vector<CString> m_vstrRelayBt;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayBtName;//�����м�̵�������
	vector<int>     m_vnRelayBtMode;//�����м�̵�������
	vector<BOOL>    m_vbIsRelayBtClickAuto;//�Ԅ�ģʽ���Ƿ����늙C���o

	int m_nRelayCkFocus;//��ѡ�̵��������еı�ţ�0~15��
	vector<CString> m_vstrRelayCk;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayCkName;//�����м�̵�������

	int m_nRelayDpFocus;//��ѡ�̵��������еı�ţ�0~9��
	vector<CString> m_vstrRelayDpCaption;
	vector<CString> m_vstrRelayDp;//�����м�̵�����Mxx��
	vector<CString> m_vstrRelayDpName;//�����м�̵�������

	int m_nBasicFocus;
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


	CString m_strCoilStart; //M��ʼ��ַ
	CString m_strCoilEnd;   //M�Y����ַ
	CString m_strCoilPos;//M����ʼλ

public:
	CValueCalculate m_ValueCalculate;

protected:
	afx_msg LRESULT OnRdRelayBtModeChange(WPARAM wParam, LPARAM lParam);//���I��͸�׃
public:
	virtual BOOL OnInitDialog();
protected:
	afx_msg LRESULT OnBtRelayBtStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBtRelayCkStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnBtRelayDpStatus(WPARAM wParam, LPARAM lParam);
public:
	DECLARE_EVENTSINK_MAP()
	void LBtClickedBlRelaybtok(long nFlags);
	void ValueChangedBlRelaybt(LPCTSTR strNew);
	void LBtClickedBlRelayckok(long nFlags);
	void ValueChangedBlRelayck(LPCTSTR strNew);
	void LBtClickedBlRelaydpok(long nFlags);
	void ValueChangedBlRelaydrop(LPCTSTR strNew);
protected:
	afx_msg LRESULT OnBgRelayBasic(WPARAM wParam, LPARAM lParam);
public:
	void SetBasicRelayColor();//���û����ռ�״̬
	void LBtClickedBlbtsavectrl(long nFlags);
	void LBtClickedBlbtloadctrl(long nFlags);
	virtual void Serialize(CArchive& ar);
public:
	void UpdateCtrlInfo();
	void StatusChangedBlckrelayclickauto(short nNewStatus);
};

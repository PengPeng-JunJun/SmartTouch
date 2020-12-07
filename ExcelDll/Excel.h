#pragma once
#include "Resource.h"
#include "CRange.h"
#include "CWorkbook.h"
#include "CWorkbooks.h"
#include "CWorksheet.h"
#include "CWorksheets.h"
#include "CApplication.h"
#include <TlHelp32.h> 
#include <stdio.h>
#include <iostream>  

#include <vector>


using namespace std;


#define  WM_EXCEL  WM_USER + 1

#define  CREATEXCEL    1
#define  OPENEXCEL     2
#define  SAVEEXCEL     3
#define  WRITEEXCEL    4
#define  CLOSEEXCEL    10


#if !defined _HEAD_FILE_EXCEL9_
#define _HEAD_FILE_EXCEL9_
#endif

// CExcel �Ի���

class AFX_EXT_CLASS CExcel : public CDialogEx
{
	DECLARE_DYNAMIC(CExcel)

public:
	CExcel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExcel();

// �Ի�������
	enum { IDD = IDD_EXCEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void CreateExcelFile(CString filename);//ͨ���ļ������ұ��
	void ClearExcelValue(long iRow, long iColumn);

protected:
	///�򿪵�EXCEL�ļ�����
	CString       open_excel_file_;

	///EXCEL BOOK���ϣ�������ļ�ʱ��
	CWorkbooks    excel_books_; 
	///��ǰʹ�õ�BOOK����ǰ������ļ�
	CWorkbook     excel_work_book_; 
	///EXCEL��sheets����
	CWorksheets   excel_sheets_; 
	///��ǰʹ��sheet
	CWorksheet    excel_work_sheet_; 
	///��ǰ�Ĳ�������
	CRange        excel_current_range_; 

	///�Ƿ��Ѿ�Ԥ������ĳ��sheet������
	BOOL          already_preload_;
	///Create the SAFEARRAY from the VARIANT ret.
	COleSafeArray ole_safe_array_;
public:
	CString m_strFilePath;//������򿪱���·��
	CString m_strFilePathPart;//������򿪱���·��

public:

	///EXCEL�Ľ���ʵ��
	 CApplication excel_application_;
	 
public:

	BOOL m_bOpenFile;
	///
	void ShowInExcel(BOOL bShow);

	///���һ��CELL�Ƿ����ַ���
	BOOL    IsCellString(long iRow, long iColumn);
	///���һ��CELL�Ƿ�����ֵ
	BOOL    IsCellInt(long iRow, long iColumn);

	///�õ�һ��CELL��String
	CString GetCellString(long iRow, long iColumn);
	///�õ�����
	int     GetCellInt(long iRow, long iColumn);
	///�õ�double������
	double  GetCellDouble(long iRow, long iColumn);

	///ȡ���е�����
	int GetRowCount();
	///ȡ���е�����
	int GetColumnCount();

	///ʹ��ĳ��shet��shit��shit
	BOOL LoadSheet(long table_index,BOOL pre_load = FALSE);
	///ͨ������ʹ��ĳ��sheet��
	BOOL LoadSheet(LPCTSTR sheet,BOOL pre_load = FALSE);
	///ͨ�����ȡ��ĳ��Sheet������
	CString GetSheetName(long table_index);

	///�õ�Sheet������
	int GetSheetCount();

	
	////�м�����
	int m_nReportRowCounter;


	///�������ݵ�ʱ��
	vector<CString> m_strReportTime;

	vector<CString> m_strDataName;

	vector<CString> m_strData;

	///���ļ�
	void OpenExcelFile(LPCTSTR file_name);
	///�رմ򿪵�Excel �ļ�����ʱ���EXCEL�ļ���Ҫ
	void CloseExcelFile(BOOL if_save = FALSE);
	//���Ϊһ��EXCEL�ļ�
	void SaveasXSLFile(const CString &xls_file);
	///ȡ�ô��ļ�������
	CString GetOpenFileName();
	///ȡ�ô�sheet������
	CString GetLoadSheetName();

	///д��һ��CELLһ��int
	void SetCellInt(long irow, long icolumn, int new_int);
	///д��һ��CELLһ��string
	void SetCellString(long irow, long icolumn, CString new_string);
	

public:
	///��ʼ��EXCEL OLE
	 BOOL InitExcel();
	///�ͷ�EXCEL�� OLE
	 void ReleaseExcel();
	///ȡ���е����ƣ�����27->AA
	static char *GetColumnName(long iColumn);

protected:

	//Ԥ�ȼ���
	void PreLoadSheet();
public:

	CWnd *m_pExcel;

protected:
	afx_msg LRESULT OnReceivExcelMsg(WPARAM wParam, LPARAM lParam);
public:
	void SetCurSheet(int nSheet);
	void SetSheetName(int nSheet, CString strName);
	void AddSheet(void);//���빤����
	void InputData2Excel(int nRow, int nCol, CString strNew, BOOL bSave);
	void InputData2Excel(int nRow, int nCol, int nNew);
	void InputReportTime();
	void InputDataName();
	void InputData();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	int m_nSavExcelCircle;
	BOOL KillProcessFromName(CString strProcessName);
	BOOL RecycleFileOrFolder(CString strPath, BOOL bDelete/*=FALSE*/) ; 
};
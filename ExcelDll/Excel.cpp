// Excel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Excel.h"
#include "afxdialogex.h"


// CExcel �Ի���

IMPLEMENT_DYNAMIC(CExcel, CDialogEx)

COleVariant
covTrue((short)TRUE),
covFalse((short)FALSE),
covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);    

#define EXCEL_DEFAULT_PARAM	 COleVariant((long)DISP_E_PARAMNOTFOUND, VT_ERROR)

//
//CApplication CExcel::excel_application_;



CExcel::CExcel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExcel::IDD, pParent)
	, m_strFilePath(_T(""))
	, m_bOpenFile(FALSE)
	, m_nReportRowCounter(0)
	, m_nSavExcelCircle(0)
{

}

CExcel::~CExcel()
{
	CloseExcelFile();
	ReleaseExcel();
}

void CExcel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExcel, CDialogEx)
	ON_MESSAGE(WM_EXCEL, &CExcel::OnReceivExcelMsg)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CExcel ��Ϣ�������
//��ʼ��EXCEL�ļ���
BOOL CExcel::InitExcel()
{
	CoUninitialize();
	if(CoInitialize(NULL) == S_FALSE) 
	{ 
		AfxMessageBox(_T("��ʼ��COM֧�֎�ʧ����")); 
		return FALSE; 
	}
	//����Excel 2000������(����Excel) 
	if (!excel_application_.CreateDispatch(_T("Excel.Application"),NULL)) 
	{ 
		AfxMessageBox(_T("����Excel����ʧ��,����ܛ]�а��bEXCEL��Ո�z��!")); 
		return FALSE;
	}

	excel_application_.put_DisplayAlerts(FALSE); 
	return TRUE;
}

//
void CExcel::ReleaseExcel()
{
	//excel_application_.Quit();
	excel_application_.ReleaseDispatch();
	excel_application_ = NULL;
}



//�رմ򿪵�Excel �ļ�,Ĭ������������ļ�
void CExcel::CloseExcelFile(BOOL if_save)
{
	//����Ѿ��򿪣��ر��ļ�
	if (open_excel_file_.IsEmpty() == FALSE)
	{
		//�������,�����û�����,���û��Լ��棬����Լ�SAVE�������Ī���ĵȴ�
		if (if_save)
		{
			ShowInExcel(TRUE);
		}
		else
		{
			//
			excel_work_book_.Close(COleVariant(short(FALSE)),COleVariant(open_excel_file_),covOptional);
			excel_books_.Close();
		}

		//���ļ����������
		open_excel_file_.Empty();
	}

	excel_work_book_.Close(COleVariant(short(FALSE)),COleVariant(m_strFilePath),covOptional);
	excel_books_.Close();

	excel_current_range_.ReleaseDispatch();  
	excel_work_sheet_.ReleaseDispatch();  
	excel_sheets_.ReleaseDispatch();  
	excel_work_book_.ReleaseDispatch();  
	excel_books_.ReleaseDispatch();  
	excel_application_.ReleaseDispatch();  
	m_bOpenFile = FALSE;
}

void CExcel::SaveasXSLFile(const CString &xls_file)
{
	excel_work_book_.SaveAs(COleVariant(xls_file),
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		0,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional);
	return;
}


int CExcel::GetSheetCount()
{
	return excel_sheets_.get_Count();
}


CString CExcel::GetSheetName(long table_index)
{
	CWorksheet sheet;
	sheet.AttachDispatch(excel_sheets_.get_Item(COleVariant((long)table_index)),true);
	CString name = sheet.get_Name();
	sheet.ReleaseDispatch();
	return name;
}

//������ż���Sheet���,������ǰ�������еı���ڲ�����
BOOL CExcel::LoadSheet(long table_index,BOOL pre_load)
{
	LPDISPATCH lpDis = NULL;
	excel_current_range_.ReleaseDispatch();
	excel_work_sheet_.ReleaseDispatch();
	lpDis = excel_sheets_.get_Item(COleVariant((long)table_index));
	if (lpDis)
	{
		excel_work_sheet_.AttachDispatch(lpDis,true);
		excel_current_range_.AttachDispatch(excel_work_sheet_.get_Cells(), true);
	}
	else
	{
		return FALSE;
	}

	already_preload_ = FALSE;
	//�������Ԥ�ȼ���
	if (pre_load)
	{
		PreLoadSheet();
		already_preload_ = TRUE;
	}

	return TRUE;
}

//�������Ƽ���Sheet���,������ǰ�������еı���ڲ�����
BOOL CExcel::LoadSheet(LPCTSTR sheet,BOOL pre_load)
{
	LPDISPATCH lpDis = NULL;
	excel_current_range_.ReleaseDispatch();
	excel_work_sheet_.ReleaseDispatch();
	lpDis = excel_sheets_.get_Item(COleVariant(sheet));
	if (lpDis)
	{
		excel_work_sheet_.AttachDispatch(lpDis,true);
		excel_current_range_.AttachDispatch(excel_work_sheet_.get_Cells(), true);

	}
	else
	{
		return FALSE;
	}
	//
	already_preload_ = FALSE;
	//�������Ԥ�ȼ���
	if (pre_load)
	{
		already_preload_ = TRUE;
		PreLoadSheet();
	}

	return TRUE;
}

//�õ��е�����
int CExcel::GetColumnCount()
{
	CRange range;
	CRange usedRange;
	usedRange.AttachDispatch(excel_work_sheet_.get_UsedRange(), true);
	range.AttachDispatch(usedRange.get_Columns(), true);
	int count = range.get_Count();
	usedRange.ReleaseDispatch();
	range.ReleaseDispatch();
	return count;
}

//�õ��е�����
int CExcel::GetRowCount()
{
	CRange range;
	CRange usedRange;
	usedRange.AttachDispatch(excel_work_sheet_.get_UsedRange(), true);
	range.AttachDispatch(usedRange.get_Rows(), true);
	int count = range.get_Count();
	usedRange.ReleaseDispatch();
	range.ReleaseDispatch();
	return count;
}

//���һ��CELL�Ƿ����ַ���
BOOL CExcel::IsCellString(long irow, long icolumn)
{
	CRange range;
	range.AttachDispatch(excel_current_range_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
	COleVariant vResult =range.get_Value2();
	//VT_BSTR��ʾ�ַ���
	if(vResult.vt == VT_BSTR)       
	{
		return TRUE;
	}
	return FALSE;
}

//���һ��CELL�Ƿ�����ֵ
BOOL CExcel::IsCellInt(long irow, long icolumn)
{
	CRange range;
	range.AttachDispatch(excel_current_range_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
	COleVariant vResult =range.get_Value2();
	//����һ�㶼��VT_R8
	if(vResult.vt == VT_INT || vResult.vt == VT_R8)       
	{
		return TRUE;
	}
	return FALSE;
}

//
CString CExcel::GetCellString(long irow, long icolumn)
{

	COleVariant vResult ;
	CString str;
	//�ַ���
	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
		vResult =range.get_Value2();
		range.ReleaseDispatch();
	}
	//�����������Ԥ�ȼ�����
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vResult = val;
	}

	if(vResult.vt == VT_BSTR)
	{
		str=vResult.bstrVal;
	}
	//����
	else if (vResult.vt==VT_INT)
	{
		str.Format(_T("%d"),vResult.pintVal);
	}
	//8�ֽڵ����� 
	else if (vResult.vt==VT_R8)     
	{
		str.Format(_T("%0.0f"),vResult.dblVal);
	}
	//ʱ���ʽ
	else if(vResult.vt==VT_DATE)    
	{
		SYSTEMTIME st;
		VariantTimeToSystemTime(vResult.date, &st);
		CTime tm(st); 
		str=tm.Format("%Y-%m-%d");

	}
	//��Ԫ��յ�
	else if(vResult.vt==VT_EMPTY)   
	{
		str="";
	}  

	return str;
}

double CExcel::GetCellDouble(long irow, long icolumn)
{
	double rtn_value = 0;
	COleVariant vresult;
	//�ַ���
	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
		vresult =range.get_Value2();
		range.ReleaseDispatch();
	}
	//�����������Ԥ�ȼ�����
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vresult = val;
	}

	if (vresult.vt==VT_R8)     
	{
		rtn_value = vresult.dblVal;
	}

	return rtn_value;
}

//VT_R8
int CExcel::GetCellInt(long irow, long icolumn)
{
	int num;
	COleVariant vresult;

	if (already_preload_ == FALSE)
	{
		CRange range;
		range.AttachDispatch(excel_current_range_.get_Item (COleVariant((long)irow),COleVariant((long)icolumn)).pdispVal, true);
		vresult = range.get_Value2();
		range.ReleaseDispatch();
	}
	else
	{
		long read_address[2];
		VARIANT val;
		read_address[0] = irow;
		read_address[1] = icolumn;
		ole_safe_array_.GetElement(read_address, &val);
		vresult = val;
	}
	//
	num = static_cast<int>(vresult.dblVal);

	return num;
}

void CExcel::SetCellString(long irow, long icolumn,CString new_string)
{
	CRange cols;

	COleVariant new_value(new_string);
	CRange start_range = excel_work_sheet_.get_Range(COleVariant(_T("A1")),covOptional);
	excel_current_range_ = start_range.get_Offset(COleVariant((long)irow -1),COleVariant((long)icolumn -1) );

	excel_current_range_.put_Value2(new_value);

	cols = excel_current_range_.get_EntireColumn();
	cols.AutoFit();

	start_range.ReleaseDispatch();
}

void CExcel::SetCellInt(long irow, long icolumn,int new_int)
{
	CRange cols;
	COleVariant new_value((long)new_int);

	CRange start_range = excel_work_sheet_.get_Range(COleVariant(_T("A1")),covOptional);
	excel_current_range_ = start_range.get_Offset(COleVariant((long)irow -1),COleVariant((long)icolumn -1) );

	excel_current_range_.put_Value2(new_value);

	cols = excel_current_range_.get_EntireColumn();
	cols.AutoFit();

	start_range.ReleaseDispatch();
}


//
void CExcel::ShowInExcel(BOOL bShow)
{
	excel_application_.put_Visible(bShow);
	excel_application_.put_UserControl(bShow);
}

//���ش򿪵�EXCEL�ļ�����
CString CExcel::GetOpenFileName()
{
	return open_excel_file_;
}

//ȡ�ô�sheet������
CString CExcel::GetLoadSheetName()
{
	return excel_work_sheet_.get_Name();
}

//ȡ���е����ƣ�����27->AA
char *CExcel::GetColumnName(long icolumn)
{   
	static char column_name[64];
	size_t str_len = 0;

	while(icolumn > 0)
	{
		int num_data = icolumn % 26;
		icolumn /= 26;
		if (num_data == 0)
		{
			num_data = 26;
			icolumn--;
		}
		column_name[str_len] = (char)((num_data-1) + 'A' );
		str_len ++;
	}
	column_name[str_len] = '\0';
	//��ת
	_strrev(column_name);

	return column_name;
}

//Ԥ�ȼ���
void CExcel::PreLoadSheet()
{

	CRange used_range;

	used_range = excel_work_sheet_.get_UsedRange();    


	VARIANT ret_ary = used_range.get_Value2();
	if (!(ret_ary.vt & VT_ARRAY))
	{
		return;
	}
	//
	ole_safe_array_.Clear();
	ole_safe_array_.Attach(ret_ary); 
}

void CExcel::ClearExcelValue(long iRow, long iColumn)
{
	CRange start_range = excel_work_sheet_.get_Range(COleVariant(_T("A1")),covOptional);
	CRange write_range = start_range.get_Offset(COleVariant((long)iRow -1),COleVariant((long)iColumn -1) );
	write_range.Clear();
	start_range.ReleaseDispatch();
	write_range.ReleaseDispatch();

}


//��excel�ļ�
void CExcel::OpenExcelFile(LPCTSTR file_name)
{
// 	CWorkbooks books;  
// 	CWorkbook book;  
// 	CWorksheets sheets;  
// 	CWorksheet sheet;  
// 	CApplication app;  
	CRange range;  


	LPDISPATCH lpDisp;  
	COleVariant vResult;  
	COleVariant  covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR);  
	if (!excel_application_.CreateDispatch(_T("Excel.Application")))
	{  
		AfxMessageBox(_T("�o�����_Excel����"),MB_OK|MB_ICONWARNING);  
		return ;  
	}  
	excel_books_.AttachDispatch(excel_application_.get_Workbooks());  
	//���ļ�  
	lpDisp = excel_books_.Open(file_name,covOptional,covOptional,covOptional,covOptional,covOptional  
		,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,covOptional,  
		covOptional,covOptional);  
	//�õ��õ���ͼworkbook  
 	excel_work_book_.AttachDispatch(lpDisp);  
 //	//�õ�worksheets  
 	excel_sheets_.AttachDispatch(excel_work_book_.get_Worksheets());  
 //	//�õ�sheet  
 	lpDisp = excel_work_book_.get_ActiveSheet();  
 	excel_work_sheet_.AttachDispatch(lpDisp);  
	//ȡ���û���  
//  	CRange userRange;  
//  	userRange.AttachDispatch(excel_work_sheet_.get_UsedRange());  
//  	//�õ��û���������  
//  	excel_current_range_.AttachDispatch(userRange.get_Rows());  
//  	long rowNum = excel_current_range_.get_Count();  
//  	//�õ��û���������  
//  	excel_current_range_.AttachDispatch(userRange.get_Columns());  
//  	long colNum = excel_current_range_.get_Count();  
//  	//�õ��û����Ŀ�ʼ�кͿ�ʼ��  
//  	long startRow = userRange.get_Row();  
//  	long startCol = userRange.get_Column();  
//  
//  	long startWriteRow = startRow + rowNum ;  
//  	long startWriteCol = startCol + colNum ;  

//	excel_current_range_ = excel_work_sheet_.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));  //���õ�Ԫ������ΪHello Exce
// 	CString writeLocation;  
//  
// 	//�õ����ݵ�λ��  
// 	writeLocation.Format(_T("A%d"),startWriteRow + 2);  
// 	//ȡ��Ҫ�༭������  
// 	range = sheet.get_Range(COleVariant(writeLocation),COleVariant(writeLocation));  
// 	//result1 = "\'" + result1;  
// 	//�����ݷ���ȡ�õ�������  
// 	//range.put_Value2(COleVariant(result1));  
// 
// 	writeLocation.Format(_T("A%d"),startWriteRow + 3);  
// 	range = sheet.get_Range(COleVariant(writeLocation),COleVariant(writeLocation));  
// 	//range.put_Value2(COleVariant(result2));  
// 	//////д�����ݵķ�����֪���кź��к�д����  
// 	//range.AttachDispatch(sheet.get_Cells());  
// 	//range.AttachDispatch(range.get_Item(COleVariant((long)2),COleVariant((long)2)).pdispVal);  
// 	//range.put_Value2(COleVariant("test"));  
// 	//�����޸ĺ������ 
// 	book.Save();  
// 	//�ͷŶ���      
// 	book.Close(COleVariant(short(FALSE)),COleVariant(file_name),covOptional);
// 	books.Close();
// 
// 	range.ReleaseDispatch();    
// 	sheet.ReleaseDispatch();    
// 	sheets.ReleaseDispatch();    
// 	book.ReleaseDispatch();    
// 	books.ReleaseDispatch();   
// 	app.ReleaseDispatch();  

  //  app.Quit();   
	m_bOpenFile = TRUE;//Excel�򿪳ɹ�
}

void CExcel::CreateExcelFile(CString filename)
{ 
	CRange cols; 
	//LPDISPATCH lpDisp;

	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND,VT_ERROR); 
	if (!excel_application_.CreateDispatch(_T("Excel.Application")))
	{   
		AfxMessageBox(_T("�o������Excel���ã�")); 
		CloseExcelFile();
		ReleaseExcel();
		return;
	}   
	excel_books_ = excel_application_.get_Workbooks(); 
	excel_work_book_ = excel_books_.Add(covOptional);  
	excel_sheets_ = excel_work_book_.get_Worksheets();

	excel_work_sheet_ = excel_sheets_.get_Item(COleVariant((short)1));  //�������Ϊ��A��1���ͣ�B��1����������Ԫ�� 
// 	excel_current_range_ = excel_work_sheet_.get_Range(COleVariant(_T("A1")), COleVariant(_T("B1")));  //���õ�Ԫ������ΪHello Exce
// 	excel_current_range_.put_Value2(COleVariant(_T("Hello Excel")));  
// 	//ѡ�����У������ÿ��Ϊ����Ӧ 
// 	cols = excel_current_range_.get_EntireColumn();  
// 	cols.AutoFit();  
// 
// 	//�������Ϊ��C��2����Ԫ�� 
// 	excel_current_range_ = excel_work_sheet_.get_Range(COleVariant(_T("C2")), COleVariant(_T("C2"))); 
// 	//���ù�ʽ��=RAND()*100000��
// 	excel_current_range_.put_Formula(COleVariant(_T("=RAND()*100000"))); 
// 	//�������ָ�ʽΪ������  
// 	excel_current_range_.put_NumberFormat(COleVariant(_T("$0.00"))); 
// 	//ѡ�����У������ÿ��Ϊ����Ӧ  

	excel_application_.put_UserControl(FALSE);

	excel_work_book_.SaveAs(COleVariant(filename),
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		(long)0,
		covOptional,
		covOptional,
		covOptional,
		covOptional,
		covOptional);


	m_bOpenFile = TRUE;//Excel�򿪳ɹ�
}


void CExcel::AddSheet(void)//���빤����
{
	excel_sheets_.Add(EXCEL_DEFAULT_PARAM, COleVariant(_T("Sheet3")), EXCEL_DEFAULT_PARAM, EXCEL_DEFAULT_PARAM);	
}

void CExcel::SetCurSheet(int nSheet)
{
	excel_work_sheet_ = excel_sheets_.get_Item(COleVariant((short)nSheet));
}


void CExcel::SetSheetName(int nSheet, CString strName)
{
	SetCurSheet(nSheet);
	excel_work_sheet_.put_Name(strName);
}

void CExcel::InputData2Excel(int nRow, int nCol, CString strNew, BOOL bSave)
{
	CRange cols;
	excel_application_.put_UserControl(FALSE);
	SetCellString(nRow,nCol,strNew);
	if (bSave)
	{
		excel_work_book_.Save();
	}
}


void CExcel::InputData2Excel(int nRow, int nCol, int nNew)
{
	CRange cols;
	excel_application_.put_UserControl(FALSE);
	SetCellInt(nRow,nCol,nNew);
	excel_work_book_.Save();
}

void CExcel::InputDataName()
{
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 1))
	{
		for (UINT nNameCouter = 0; nNameCouter < m_strDataName.size(); nNameCouter++)
		{
			InputData2Excel(1, nNameCouter + 2, m_strDataName[nNameCouter], FALSE);
		}
	}
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 2))
	{
		InputData2Excel(1, 1, _T("����"), FALSE);
		InputData2Excel(1, 2, _T("�r�g"), FALSE);
		for (UINT nNameCouter = 0; nNameCouter < m_strDataName.size(); nNameCouter++)
		{
			InputData2Excel(1, nNameCouter + 3, m_strDataName[nNameCouter], FALSE);
		}
	}
	
}


void CExcel::InputReportTime()
{
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 1))
	{
		InputData2Excel(m_nReportRowCounter, 1, m_strReportTime[0], FALSE);//�ɼ�ʱ��
	}
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 2))
	{
		InputData2Excel(m_nReportRowCounter, 1, m_strReportTime[0], FALSE);//�ɼ�ʱ��
		InputData2Excel(m_nReportRowCounter, 2, m_strReportTime[1], FALSE);//�ɼ�ʱ��
	}
	
}

void CExcel::InputData()
{
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 1))
	{
		for (UINT nNameCouter = 0; nNameCouter < m_strData.size(); nNameCouter++)
		{
			InputData2Excel(m_nReportRowCounter, nNameCouter + 2, m_strData[nNameCouter], FALSE);
		}
	}
	if ((m_strReportTime.size() > 0) && (m_strReportTime.size() == 2))
	{
		for (UINT nNameCouter = 0; nNameCouter < m_strData.size(); nNameCouter++)
		{
			InputData2Excel(m_nReportRowCounter, nNameCouter + 3, m_strData[nNameCouter], FALSE);
		}
	}
}

afx_msg LRESULT CExcel::OnReceivExcelMsg(WPARAM wParam, LPARAM lParam)
{
	int nSeconds;
	CTime time = CTime::GetCurrentTime(); ///����CTime����  
	nSeconds = time.GetSecond();
	CString strPart;
	switch (wParam)
	{
	case CREATEXCEL://����EXCEL
		CreateExcelFile(m_strFilePath);
		break;
	case OPENEXCEL://��EXCEL
		
		break;
	case CLOSEEXCEL://�ر�EXCEL
		CloseExcelFile();
		ReleaseExcel();
		break;
	case WRITEEXCEL:
		excel_application_.put_UserControl(FALSE);
		//InputData2Excel();//�򿪱��׼����������д��
		SetCurSheet(1);
		InputDataName();
		InputReportTime();
		InputData();
		excel_work_book_.Save();
		if (((nSeconds % m_nSavExcelCircle) == 0))
		{
			//CloseTcpConnection("192.168.200.74", 445);
			//excel_work_book_.Save();
			RecycleFileOrFolder(m_strFilePathPart, TRUE);
			CopyFile(m_strFilePath, m_strFilePathPart, FALSE);
		}
		else
		{
			SetTimer(0, 10, nullptr);
		}
		break;
	default:
		break;
	}
	return 0;
}


void CExcel::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

// 	CStdioFile	 logFile;
// 	CString path = _T("D:\\VC Project\\UDE_Report\\Back125���˜ʰ汾��\\Release\\Report\\123456_201805.xlsx");
// 	BOOL openLogFiles = logFile.Open(path, CFile::modeWrite|CFile::typeText,NULL);
	
	int nSeconds;
	CTime time = CTime::GetCurrentTime(); ///����CTime����  
	nSeconds = time.GetSecond();
	CString strPart;
	switch (nIDEvent)
	{
	case 0:
		KillTimer(0);
		if (((nSeconds % m_nSavExcelCircle) == 0))// && (nSeconds != 0))
		{
			RecycleFileOrFolder(m_strFilePathPart, TRUE);
			CopyFile(m_strFilePath, m_strFilePathPart, FALSE);
		}
		else
		{
			SetTimer(0, 10, nullptr);
		}
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

BOOL CExcel::KillProcessFromName(CString strProcessName)  
{  
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);  
	PROCESSENTRY32 pe;//ͷ�ļ�#include<TlHelp32.h>  
	pe.dwSize = sizeof(PROCESSENTRY32);  
	if(!Process32First(hSnapShot,&pe))  
	{  
		return FALSE;  
	}  
	strProcessName.MakeLower();  
	while (Process32Next(hSnapShot,&pe))  
	{  
		CString scTmp = pe.szExeFile;  
		scTmp.MakeLower();  
		if(!scTmp.Compare(strProcessName))  
		{  
			DWORD dwProcessID = pe.th32ProcessID;  
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE,FALSE,dwProcessID);  
			::TerminateProcess(hProcess,0);  
			CloseHandle(hProcess);  
			return TRUE;  
		}  
		scTmp.ReleaseBuffer();  
	}  
	strProcessName.ReleaseBuffer();  
	return FALSE;  
}  
 



BOOL CExcel::RecycleFileOrFolder(CString strPath, BOOL bDelete/*=FALSE*/)  
{  
	strPath += '\0';  
	SHFILEOPSTRUCT  shDelFile;  
	memset(&shDelFile,0,sizeof(SHFILEOPSTRUCT));  
	shDelFile.fFlags |= FOF_SILENT;             // ����ʾ����  
	shDelFile.fFlags |= FOF_NOERRORUI;          // �����������Ϣ  
	shDelFile.fFlags |= FOF_NOCONFIRMATION;     // ֱ��ɾ����������ȷ��  

	// ����SHFILEOPSTRUCT�Ĳ���Ϊɾ����׼��  
	shDelFile.wFunc = FO_DELETE;        // ִ�еĲ���  
	shDelFile.pFrom = strPath;          // �����Ķ���Ҳ����Ŀ¼��ע�⣺�ԡ�\0\0����β��  
	shDelFile.pTo = NULL;               // ��������ΪNULL  
	if (bDelete) //���ݴ��ݵ�bDelete����ȷ���Ƿ�ɾ��������վ  
	{      
		shDelFile.fFlags &= ~FOF_ALLOWUNDO;    //ֱ��ɾ�������������վ  
	}   
	else   
	{             
		shDelFile.fFlags |= FOF_ALLOWUNDO;    //ɾ��������վ  
	}  

	BOOL bres = SHFileOperation(&shDelFile);    //ɾ��  
	return !bres;  
}
#pragma once
#include <vector>
using namespace std;
class CFindCtrlFile
{
public:
	CFindCtrlFile(void);
	~CFindCtrlFile(void);
public:
	vector <CString> m_vstrFileName;
public:
	BOOL SearchControllerFile();
	BOOL SearchReportFile();
	BOOL SearchTemplateFile();
	BOOL SearchFile(CString strPath, BOOL & bIfCreate);
	CString GetExePath();
	CString LoadSignalData(CString strFileName);
	BOOL CheckFile(CString strFilePath);//查找是否存在文件

	vector<pair<CString,CString>> FindFilesInDirecotry(CString fileName, CString directory, int & filecounter);
	vector<pair<CString,CString>> FindFilesInDirecotryRecursion( CString fileName, CString directory, int recursionCount, int & filecounter, vector <CString> & vstrFileName);
	BOOL RecycleFileOrFolder(CString strPath, BOOL bDelete/*=FALSE*/);
};


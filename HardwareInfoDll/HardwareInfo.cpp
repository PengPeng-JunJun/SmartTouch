#include "stdafx.h"
#include "HardwareInfo.h"

#define  IDE_ATAPI_IDENTIFY			0xA1  //  Returns ID sector for ATAPI.
#define  IDE_ATA_IDENTIFY			0xEC  //  Returns ID sector for ATA.


CHardwareInfo::CHardwareInfo(void)
{
}


CHardwareInfo::~CHardwareInfo(void)
{
}


HANDLE CHardwareInfo::OpenDevice(CString strDevice)
{
	HANDLE hDeviceIOCTL = CreateFile(strDevice,
		GENERIC_READ | GENERIC_WRITE, 
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		nullptr,
		OPEN_EXISTING,
		0,
		nullptr);

	return hDeviceIOCTL;
}


BOOL CHardwareInfo::GetDriveInfo(int nDisk, PDRIVEINFO pInfo)
{
	if (nullptr == pInfo)
	{
		return FALSE;
	}

	BOOL bResult = FALSE;

	CString strDriverName;
	strDriverName.Format(_T("\\\\.\\PhysicalDrive%d"), nDisk);

	HANDLE hDevice = OpenDevice(strDriverName);

	if (INVALID_HANDLE_VALUE == hDevice)
	{
		return bResult;
	}

	PSENDCMDINPARAMS pSCIP;					// �������ݽṹָ��
	PSENDCMDOUTPARAMS pSCOP;				// ������ݽṹָ��
	DWORD dwOutBytes;						// IOCTL������ݳ���

	// ��������/������ݽṹ�ռ�   
	pSCIP = (PSENDCMDINPARAMS)::GlobalAlloc(LMEM_ZEROINIT, sizeof(SENDCMDINPARAMS) - 1);
	pSCOP = (PSENDCMDOUTPARAMS)::GlobalAlloc(LMEM_ZEROINIT, sizeof(SENDCMDOUTPARAMS) + sizeof(DRIVEINFO) - 1); // ָ��ATA/ATAPI����ļĴ���ֵ

	pSCIP->irDriveRegs.bFeaturesReg		= 0;
	pSCIP->irDriveRegs.bSectorCountReg	= 0;
	pSCIP->irDriveRegs.bSectorNumberReg	= 0;
	pSCIP->irDriveRegs.bCylLowReg		= 0;
	pSCIP->irDriveRegs.bCylHighReg		= 0;
	pSCIP->irDriveRegs.bDriveHeadReg		= 0;
	pSCIP->irDriveRegs.bCommandReg		= IDE_ATA_IDENTIFY; // ָ������/������ݻ�������С IDENTIFY DEVICE
	pSCIP->cBufferSize					= 0;
	pSCOP->cBufferSize					= sizeof(DRIVEINFO);

	bResult = ::DeviceIoControl(hDevice,					// �豸���
		SMART_RCV_DRIVE_DATA,								// ָ��IOCTL
		pSCIP,
		sizeof(SENDCMDINPARAMS) - 1,							// �������ݻ�����
		pSCOP,
		sizeof(SENDCMDOUTPARAMS) + sizeof(DRIVEINFO) - 1,	// ������ݻ�����
		&dwOutBytes,										// ������ݳ���
		(LPOVERLAPPED)nullptr);								// �����豸�����ṹ

	ZeroMemory(pInfo, sizeof(DRIVEINFO));
	::memcpy(pInfo, pSCOP->bBuffer, sizeof(DRIVEINFO));		// �ͷ�����/������ݿռ�

	::GlobalFree(pSCOP);
	::GlobalFree(pSCIP);

	_AdjustString(pInfo->sSerialNumber, 20);
	_AdjustString(pInfo->sModelNumber, 40);
	_AdjustString(pInfo->sFirmwareRev, 8);
	
	::CloseHandle(hDevice);

	return bResult;
}


void CHardwareInfo::GetMacAdd(vector<CString> * pvMac)
{
	pvMac->clear();

	DWORD dwMacAdd = 0;
	IP_ADAPTER_INFO AdapterInfo[16];				// Allocate information
	// for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);			// Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(				// Call GetAdapterInfo
		AdapterInfo,								// [out] buffer to receive data
		&dwBufLen);									// [in] size of receive data buffer

	ASSERT(ERROR_SUCCESS == dwStatus);				// Verify return value is
	// valid, no buffer overflow

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;	// Contains pointer to
	// current adapter info
	do
	{
		if (!dwMacAdd)
		{
			dwMacAdd = pAdapterInfo->Address[5] + pAdapterInfo->Address[4] * 256 +
			pAdapterInfo->Address[3] * 256 * 256 + 
			pAdapterInfo->Address[2] * 256 * 256 * 256;
		}

		CString strMac;
		strMac.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

		pvMac->push_back(strMac);
		
		pAdapterInfo = pAdapterInfo->Next;			// Progress through linked list

	}while(pAdapterInfo);							// Terminate if last adapter
}


void CHardwareInfo::_AdjustString(char *pszData, int nLenght)
{
	char chTemp;
	int i = 0;

	// �����Ҷ���ģ�����Ϊ�����, ȥ����ߵĿո�
	i = 0;
	while (i < nLenght && ' ' == pszData[i])
	{
		i++;
	}

	::memmove(pszData, &pszData[i], nLenght - i);

	for (i = nLenght - i; i < nLenght; i++)
	{
		pszData[i] = ' ';
	}

	// ȥ���ұߵĿո�
	i = nLenght - 1;

	while(i >= 0 && ' ' == pszData[i])
	{
		pszData[i] = '\0';
		i--;
	}

	for (int i = 0; i < nLenght && ' ' != pszData[i]; i += 2)
	{
		chTemp					= pszData[i];
		pszData[i]		= pszData[i + 1];
		pszData[i + 1]	= chTemp;
	}
}

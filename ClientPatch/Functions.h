#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <atlstr.h>

class Func
{
public:
	static char* stringFormat(const char* str, ...);

	static char* GetSerialHD();

	bool GetFileName(char* text);

	static char* GetMacAddress();

	static void SendMessageExp(int color, char* s, ...);

	static void Change_ChatColor(int color);

	static void Shown(int color, const char* str, ...);

	static void ShowClientMessage(int delay, char* msg);

	static void AgruparItem(int slot, int index);

	static int GetClientID();

	static short GetPosClientX();

	static short GetPosClientY();

	static STRUCT_MOB GetChar();

	static DWORD GetPhysicalDriveSerialNumber(UINT nDriveNumber, CString& strSerialNumber)
	{
		DWORD dwResult = NO_ERROR;
		strSerialNumber.Empty();

		// Format physical drive path (may be '\\.\PhysicalDrive0', '\\.\PhysicalDrive1' and so on).
		CString strDrivePath;
		strDrivePath.Format(_T("\\\\.\\PhysicalDrive%u"), nDriveNumber);

		// call CreateFile to get a handle to physical drive
		HANDLE hDevice = ::CreateFile(strDrivePath, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, 0, NULL);

		if (INVALID_HANDLE_VALUE == hDevice)
			return ::GetLastError();

		// set the input STORAGE_PROPERTY_QUERY data structure
		STORAGE_PROPERTY_QUERY storagePropertyQuery;
		ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
		storagePropertyQuery.PropertyId = StorageDeviceProperty;
		storagePropertyQuery.QueryType = PropertyStandardQuery;

		// get the necessary output buffer size
		STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
		DWORD dwBytesReturned = 0;
		if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
			&storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
			&dwBytesReturned, NULL)) {
			dwResult = ::GetLastError();
			::CloseHandle(hDevice);
			return dwResult;
		}

		// allocate the necessary memory for the output buffer
		const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
		BYTE* pOutBuffer = new BYTE[dwOutBufferSize];
		ZeroMemory(pOutBuffer, dwOutBufferSize);

		// get the storage device descriptor
		if (!::DeviceIoControl(hDevice, IOCTL_STORAGE_QUERY_PROPERTY,
			&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
			pOutBuffer, dwOutBufferSize,
			&dwBytesReturned, NULL)) {
			dwResult = ::GetLastError();
			delete[]pOutBuffer;
			::CloseHandle(hDevice);
			return dwResult;
		}

		// Now, the output buffer points to a STORAGE_DEVICE_DESCRIPTOR structure
		// followed by additional info like vendor ID, product ID, serial number, and so on.
		STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
		const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;
		if (dwSerialNumberOffset != 0) {
			// finally, get the serial number
			strSerialNumber = CString(pOutBuffer + dwSerialNumberOffset);
		}

		// perform cleanup and return
		delete[]pOutBuffer;
		::CloseHandle(hDevice);
		return dwResult;
	}

	static std::string exec(const char* cmd)
	{
		std::array<char, 128> buffer;
		std::string result;
		std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
		if (!pipe) throw std::runtime_error("_popen() failed!");
		while (!feof(pipe.get())) {
			if (fgets(buffer.data(), 128, pipe.get()) != NULL)
				result += buffer.data();
		}
		return result;
	}

private:

};
__forceinline int GetClientID()
{
	__asm
	{
		MOV ECX, DWORD PTR DS : [0x13FA9D4]
		ADD ECX, 0xDFC
		XOR EAX, EAX
		MOV AX, WORD PTR DS : [ECX]
	}
}

__forceinline STRUCT_MOB GetChar()
{
	__asm
	{
		MOV EAX, DWORD PTR DS : [0x13FA9D4]
		ADD EAX, 0x6EC
	}
}
 

__forceinline short GetCPosX() {
	return (short)(*(float*)((*(int*)((char*)(*(int**)0x6BDAF0) + 76)) + 40));
}

__forceinline short GetCPosY() {
	return (short)(*(float*)((*(int*)((char*)(*(int**)0x6BDAF0) + 76)) + 44));
} 
extern bool MacroPega; // Desativado Por Padrão
#endif // !FUNCTIONS_H

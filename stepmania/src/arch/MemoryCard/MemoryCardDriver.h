#ifndef MEMORY_CARD_ENUMERATOR_H
#define MEMORY_CARD_ENUMERATOR_H 1


struct UsbStorageDevice
{
	UsbStorageDevice() { MakeBlank(); }

	void MakeBlank()
	{
		iBus = -1;
		iDeviceOnBus = -1;
		iPortOnHub = -1;
		iUsbStorageIndex = -1;
		sSerial = "";
		sOsMountDir = "";
	};
	int iBus;
	int iDeviceOnBus;
	int iPortOnHub;
	CString sSerial;
	int iUsbStorageIndex;
	CString	sOsMountDir;	// WITHOUT trailing slash

	bool IsBlank() { return sOsMountDir.empty(); }

	bool operator==(const UsbStorageDevice& other)
	{
		// ugly...
#if _WINDOWS
		// we don't have hub/port number info on Windows
		return sOsMountDir==other.sOsMountDir;  // every time a device is plugged in, it gets a unique device number
#else	// LINUX or other
		return iBus==other.iBus &&
			iDeviceOnBus==other.iDeviceOnBus;  // every time a device is plugged in, it gets a unique device number
#endif
	}
};

class MemoryCardDriver
{
public:
	MemoryCardDriver() {};
	virtual ~MemoryCardDriver() {};
	virtual bool StorageDevicesChanged() = 0;
	virtual void GetStorageDevices( vector<UsbStorageDevice>& vStorageDevicesOut ) = 0;
	virtual bool MountAndTestWrite( UsbStorageDevice* pDevice ) = 0;	// return false if mount or write fails
	virtual void Flush( UsbStorageDevice* pDevice ) = 0;
};

#endif

/*
 * Copyright (c) 2003 by the person(s) listed below.  All rights reserved.
 *	Chris Danford
 */

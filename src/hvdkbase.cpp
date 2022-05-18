#include "hvdkbase.h"

extern "C"
{
    #include <setupapi.h>
    #include <hidsdi.h>
}

hvdk::Base::Base()
{
    _deviceConnected = false;
    _deviceHandle = 0;
    _VID = 0;
    _PID = 0;
    _sendDataSize = 0;

    _handleMutex = new std::mutex();
}

hvdk::Base::~Base()
{
    disconnectFromDevice();

    delete _handleMutex;
}

bool hvdk::Base::deviceConnected()
{
    return _deviceConnected;
}

void hvdk::Base::setIDs(unsigned short VID, unsigned short PID)
{
    _VID = VID;
    _PID = PID;
}

void hvdk::Base::setSendDataSize(unsigned long size)
{
    _sendDataSize = size;
}

bool hvdk::Base::connectToDevice()
{
    _deviceConnected = false;
    bool GotRequiredSize = false;
    DWORD DataSize;
    PSP_DEVICE_INTERFACE_DETAIL_DATA detailData = 0;
    DWORD RequiredSize;
    HIDD_ATTRIBUTES HIDAttrib;
    GUID HidGuid;
    HidD_GetHidGuid(&HidGuid);
    HDEVINFO HidDevInfo = SetupDiGetClassDevs(&HidGuid,
                                              0,
                                              0,
                                              DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);
    DWORD index = 0;
    SP_DEVICE_INTERFACE_DATA devInfoData;
    devInfoData.cbSize = sizeof(devInfoData);
    BOOL result;
    do
    {
        result = SetupDiEnumDeviceInterfaces(HidDevInfo,
                                             0,
                                             &HidGuid,
                                             index,
                                             &devInfoData);
        if (!result)
        {
            SetupDiDestroyDeviceInfoList(HidDevInfo);
            _deviceConnected = false;
            return false;
        }
        if (!GotRequiredSize)
        {
            SetupDiGetDeviceInterfaceDetail(HidDevInfo,
                                            &devInfoData,
                                            0,
                                            0,
                                            &DataSize,
                                            0);
            GotRequiredSize = true;
            detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(DataSize);
            detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
        }
        SetupDiGetDeviceInterfaceDetail(HidDevInfo,
                                        &devInfoData,
                                        detailData,
                                        DataSize,
                                        &RequiredSize,
                                        0);
        _deviceHandle = CreateFile(detailData->DevicePath,
                                   0,
                                   FILE_SHARE_READ | FILE_SHARE_WRITE,
                                   (LPSECURITY_ATTRIBUTES)0,
                                   OPEN_EXISTING,
                                   0,
                                   0);
        if (_deviceHandle != INVALID_HANDLE_VALUE)
        {
            HIDAttrib.Size = sizeof(HIDAttrib);
            HidD_GetAttributes(_deviceHandle, &HIDAttrib);
            if ((HIDAttrib.VendorID == _VID) && (HIDAttrib.ProductID == _PID))
            {
                SetupDiDestroyDeviceInfoList(HidDevInfo);
                _deviceConnected = true;
                break;

            }
            else
            {
                _deviceConnected = false;
            }
            CloseHandle(_deviceHandle);
        }
        index++;
    }
    while (result);
    return _deviceConnected;
}

void hvdk::Base::disconnectFromDevice()
{
    if (_deviceConnected)
    {
        CloseHandle(_deviceHandle);
        _deviceHandle = 0;
        _deviceConnected = false;
    }
}

bool hvdk::Base::sendData(PVOID data, DWORD size)
{
    bool result = false;
    if (_deviceConnected)
    {
        _handleMutex->lock();
        result = HidD_SetFeature(_deviceHandle, data, size);
        _handleMutex->unlock();
    }
    return result;
}

bool hvdk::Base::sendData(PVOID data)
{
    if (_sendDataSize == 0)
    {
        return false;
    }
    return sendData(data, static_cast<DWORD>(_sendDataSize));
}

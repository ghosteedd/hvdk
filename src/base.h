#ifndef BASE_H
#define BASE_H

#include <mutex>

#include <windows.h>

namespace hvdk
{
    class Base
    {
    public:
        Base();

        ~Base();

        bool connectToDevice();

        void disconnectFromDevice();

        bool deviceConnected();

    private:
        std::mutex* _handleMutex;

        HANDLE _deviceHandle;

        USHORT _VID;

        USHORT _PID;

        DWORD _sendDataSize;

        bool _deviceConnected;

    protected:
        void setIDs(unsigned short VID, unsigned short PID);

        void setSendDataSize(unsigned long size);

        bool sendData(PVOID data, DWORD size);

        bool sendData(PVOID data);
    };
}
#endif // BASE_H

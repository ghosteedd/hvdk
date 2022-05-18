#include "keyboard.h"

#include <thread>
#include <chrono>

#include <windows.h>

#define DRIVER_TIMEOUT 1024
#define SLEEP_PING 256
#define KEYBOARD_DATA_SIZE 14

#define SLEEP(time) std::this_thread::sleep_for(std::chrono::milliseconds(time))

struct KeyboardReport
{
    BYTE reportID = 0;
    BYTE commandCode = 0;
    UINT32 timeout = 0;
    BYTE modifier = 0;
    BYTE padding = 0;
    BYTE key0 = 0;
    BYTE key1 = 0;
    BYTE key2 = 0;
    BYTE key3 = 0;
    BYTE key4 = 0;

    void getByteArray(BYTE (&result)[KEYBOARD_DATA_SIZE])
    {
        result[0] = reportID;
        result[1] = commandCode;
        result[2] = timeout & 0xFF;
        result[3] = (timeout >> 8) & 0xFF;
        result[4] = (timeout >> 16) & 0xFF;
        result[5] = (timeout >> 24) & 0xFF;
        result[6] = modifier;
        result[7] = padding;
        result[8] = key0;
        result[9] = key1;
        result[10] = key2;
        result[11] = key3;
        result[12] = key4;
        result[13] = 0;
    }
};

hvdk::Keyboard::Keyboard()
{
    setIDs(0xF00F, 0x00000003);
    setSendDataSize(KEYBOARD_DATA_SIZE);
    resetData();

    _pingWorking = false;

    _sleepBetweenActions = 75;
    _sleepAfterAction = 32;
}

hvdk::Keyboard::~Keyboard()
{
    stopPing();
}

void hvdk::Keyboard::resetData()
{
    _lCtrlDown = false;
    _lShiftDown = false;
    _lAltDown = false;
    _lWinDown = false;
    _rCtrlDown = false;
    _rAltDown = false;
    _rWinDown = false;

    for (int i = 0; i < 5; i++)
    {
        _keys[i] = 0;
    }
}

bool hvdk::Keyboard::startPing()
{
    if (_pingWorking)
    {
        return false;
    }
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }

    _pingWorking = true;
    std::thread(&hvdk::Keyboard::pingDriver, this).detach();
    return true;
}

void hvdk::Keyboard::stopPing()
{
    if (_pingWorking)
    {
        _pingWorking = false;
        SLEEP(SLEEP_PING);
    }
}

void hvdk::Keyboard::pingDriver()
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 3;
    report.timeout = DRIVER_TIMEOUT;
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    while (_pingWorking)
    {
        sendData(data4Send);
        SLEEP(SLEEP_PING);
    }
}

bool hvdk::Keyboard::resetDriver()
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 1;
    report.timeout = DRIVER_TIMEOUT;
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!_pingWorking)
    {
        if (!startPing())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::Keyboard::releaseAllKeys()
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.timeout = DRIVER_TIMEOUT;
    report.modifier = 0;
    report.padding = 0;
    report.key0 = 0;
    report.key1 = 0;
    report.key2 = 0;
    report.key3 = 0;
    report.key4 = 0;
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!_pingWorking)
    {
        if (!startPing())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

void hvdk::Keyboard::setModKeyState(unsigned char keyCode, bool isDown)
{
    switch (keyCode)
    {
        case KEYBD_MOD_LCTRL:
            _lCtrlDown = isDown;
            break;
        case KEYBD_MOD_LSHIFT:
            _lShiftDown = isDown;
            break;
        case KEYBD_MOD_LALT:
            _lAltDown = isDown;
            break;
        case KEYBD_MOD_LWIN:
            _lWinDown = isDown;
            break;
        case KEYBD_MOD_RCTRL:
            _rCtrlDown = isDown;
            break;
        case KEYBD_MOD_RSHIFT:
            _rShiftDown = isDown;
            break;
        case KEYBD_MOD_RALT:
            _rAltDown = isDown;
            break;
        case KEYBD_MOD_RWIN:
            _rWinDown = isDown;
            break;
    }
}

unsigned char hvdk::Keyboard::getFreeKeysCount()
{
    unsigned char result = 0;
    for (int i = 0; i < 5; i++)
    {
        if (_keys[i] == 0)
        {
            result++;
        }
    }
    return result;
}

bool hvdk::Keyboard::setKeyState(unsigned char keyCode,bool isDown)
{
    if (isDown)
    {
        for (int i = 0; i < 5; i++)
        {
            if (_keys[i] == keyCode)
            {
                return true;
            }
        }
        for (int i = 0; i < 5; i++)
        {
            if (_keys[i] == 0)
            {
                _keys[i] = keyCode;
                return true;
            }
        }
        return false;
    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (_keys[i] == keyCode)
            {
                _keys[i] = 0;
                return true;
            }
        }
        return false;
    }
}

bool hvdk::Keyboard::commit(bool resetDataAfterCommit)
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.timeout = DRIVER_TIMEOUT;
    report.modifier = 0;
    if (_lCtrlDown)
    {
        report.modifier += 1;
    }
    if (_lShiftDown)
    {
        report.modifier += 2;
    }
    if (_lAltDown)
    {
        report.modifier += 4;
    }
    if (_lWinDown)
    {
        report.modifier += 8;
    }
    if (_rCtrlDown)
    {
        report.modifier += 16;
    }
    if (_rShiftDown)
    {
        report.modifier += 32;
    }
    if (_rAltDown)
    {
        report.modifier += 64;
    }
    if (_rWinDown)
    {
        report.modifier += 128;
    }
    report.key0 = _keys[0];
    report.key1 = _keys[1];
    report.key2 = _keys[2];
    report.key3 = _keys[3];
    report.key4 = _keys[4];
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!_pingWorking)
    {
        if (!startPing())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    if (result && resetDataAfterCommit)
    {
        resetData();
    }
    return result;

}

bool hvdk::Keyboard::clickOnKeys(unsigned char keyCode0,
                              unsigned char keyCode1,
                              unsigned char keyCode2,
                              unsigned char keyCode3,
                              unsigned char keyCode4)
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.timeout = DRIVER_TIMEOUT;
    report.key0 = keyCode0;
    report.key1 = keyCode1;
    report.key2 = keyCode2;
    report.key3 = keyCode3;
    report.key4 = keyCode4;
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!_pingWorking)
    {
        if (!startPing())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.key0 = 0;
    report.key1 = 0;
    report.key2 = 0;
    report.key3 = 0;
    report.key4 = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::Keyboard::clickOnKeys(unsigned char keyCodes[5])
{
    return clickOnKeys(keyCodes[0], keyCodes[1],
                       keyCodes[2], keyCodes[3],
                       keyCodes[4]);
}

bool hvdk::Keyboard::clickOnModKeys(unsigned char keyCodes)
{
    KeyboardReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.timeout = DRIVER_TIMEOUT;
    report.modifier = keyCodes;
    BYTE data4Send[KEYBOARD_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!_pingWorking)
    {
        if (!startPing())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.modifier = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

void hvdk::Keyboard::setSleepTimerAfterActions(unsigned short value)
{
    _sleepAfterAction = value;
}

unsigned short hvdk::Keyboard::getSleepTimerAfterActions()
{
    return _sleepAfterAction;
}

void hvdk::Keyboard::setSleepTimerBetweenActions(unsigned short value)
{
    if (value >= _sleepAfterAction)
    {
        _sleepBetweenActions = value;
    }
}

unsigned short hvdk::Keyboard::getSleepTimerBetweenActions()
{
    return _sleepBetweenActions;
}

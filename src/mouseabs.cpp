#include "mouseabs.h"

#include <thread>
#include <chrono>

#include <windows.h>

#define MOUSE_ABS_DATA_SIZE 7

#define SLEEP(time) std::this_thread::sleep_for(std::chrono::milliseconds(time))

struct MouseAbsReport
{
    BYTE reportID = 0;
    BYTE commandCode = 0;
    BYTE buttons = 0;
    UINT16 x = 0;
    UINT16 y = 0;

    void getByteArray(BYTE (&result)[MOUSE_ABS_DATA_SIZE])
    {
        result[0] = reportID;
        result[1] = commandCode;
        result[2] = buttons;
        result[3] = x & 0xFF;
        result[4] = (x >> 8) & 0xFF;
        result[5] = y & 0xFF;
        result[6] = (y >> 8) & 0xFF;

    }
};

hvdk::MouseAbs::MouseAbs()
{
    setIDs(0xF00F, 0x00000002);
    setSendDataSize(MOUSE_ABS_DATA_SIZE);
    resetData();

    _sleepBetweenActions = 75;
    _sleepAfterAction = 32;
}

void hvdk::MouseAbs::resetData()
{
    _x = 0;
    _y = 0;

    _leftButtonDown =   false;
    _middleButtonDown = false;
    _rightButtonDown =  false;
}

void hvdk::MouseAbs::setNewPos(unsigned short x, unsigned short y)
{
    _x = x;
    _y = y;
}

void hvdk::MouseAbs::setButtonState(unsigned char button, bool isDown)
{
    switch (button)
    {
        case MOUSE_ABS_L_BTN:
            _leftButtonDown = isDown;
            break;
        case MOUSE_ABS_M_BTN:
            _middleButtonDown = isDown;
            break;
        case MOUSE_ABS_R_BTN:
            _rightButtonDown = isDown;
            break;
    }
}

bool hvdk::MouseAbs::resetDriver()
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 1;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    return sendData(data4Send);
}

bool hvdk::MouseAbs::commit(bool resetDataAfterCommit)
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 0;
    if (_leftButtonDown)
    {
        report.buttons = 1;
    }
    if (_rightButtonDown)
    {
        report.buttons += 2;
    }
    if (_middleButtonDown)
    {
        report.buttons += 4;
    }
    report.x = _x;
    report.y = _y;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
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

bool hvdk::MouseAbs::clickOnPoint(unsigned short x, unsigned short y)
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 1;
    report.x = x;
    report.y = y;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseAbs::doubleClickOnPoint(unsigned short x, unsigned short y)
{
    bool result = clickOnPoint(x, y);
    if (!result)
    {
        return result;
    }
    SLEEP(_sleepBetweenActions - _sleepAfterAction);
    result = clickOnPoint(x, y);
    return result;
}

bool hvdk::MouseAbs::middleClickOnPoint(unsigned short x, unsigned short y)
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 4;
    report.x = x;
    report.y = y;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseAbs::rightClickOnPoint(unsigned short x, unsigned short y)
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 2;
    report.x = x;
    report.y = y;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseAbs::moveToPoint(unsigned short x, unsigned short y)
{
    MouseAbsReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.x = x;
    report.y = y;
    BYTE data4Send[MOUSE_ABS_DATA_SIZE];
    report.getByteArray(data4Send);
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(data4Send);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    report.getByteArray(data4Send);
    SLEEP(_sleepBetweenActions);
    result = sendData(data4Send);
    SLEEP(_sleepAfterAction);
    return result;
}

void hvdk::MouseAbs::setSleepTimerAfterActions(unsigned short value)
{
    _sleepAfterAction = value;
}

unsigned short hvdk::MouseAbs::getSleepTimerAfterActions()
{
    return _sleepAfterAction;
}

void hvdk::MouseAbs::setSleepTimerBetweenActions(unsigned short value)
{
    if (value >= _sleepAfterAction)
    {
        _sleepBetweenActions = value;
    }
}

unsigned short hvdk::MouseAbs::getSleepTimerBetweenActions()
{
    return _sleepBetweenActions;
}

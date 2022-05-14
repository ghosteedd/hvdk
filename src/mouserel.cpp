#include "mouserel.h"

#include <thread>
#include <chrono>

#include <windows.h>

#define MOUSE_REL_DATA_SIZE 5

#define SLEEP(time) std::this_thread::sleep_for(std::chrono::milliseconds(time))

struct MouseRelReport
{
    BYTE reportID = 0;
    BYTE commandCode = 0;
    BYTE buttons = 0;
    BYTE x = 0;
    BYTE y = 0;
};

hvdk::MouseRel::MouseRel()
{
    setIDs(0xF00F, 0x00000005);
    setSendDataSize(MOUSE_REL_DATA_SIZE);
    resetData();

    _sleepBetweenActions = 75;
    _sleepAfterAction = 32;
}

void hvdk::MouseRel::resetData()
{
    _x = 0;
    _y = 0;

    _leftButtonDown =   false;
    _middleButtonDown = false;
    _rightButtonDown =  false;
}

void hvdk::MouseRel::setNewPos(char x, char y)
{
    _x = x;
    _y = y;
}

void hvdk::MouseRel::setButtonState(unsigned char button, bool isDown)
{
    switch(button)
    {
        case MOUSE_REL_L_BTN:
            _leftButtonDown = isDown;
            break;
        case MOUSE_REL_M_BTN:
            _middleButtonDown = isDown;
            break;
        case MOUSE_REL_R_BTN:
            _rightButtonDown = isDown;
            break;
    }
}

bool hvdk::MouseRel::resetDriver()
{
    MouseRelReport report;
    report.reportID = 1;
    report.commandCode = 1;
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    return sendData(&report);
}

bool hvdk::MouseRel::commit(bool resetDataAfterCommit)
{
    MouseRelReport report;
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
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(&report);
    SLEEP(_sleepAfterAction);
    if (result && resetDataAfterCommit)
    {
        resetData();
    }
    return result;
}

bool hvdk::MouseRel::click()
{
    MouseRelReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 1;
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(&report);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    SLEEP(_sleepBetweenActions);
    result = sendData(&report);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseRel::doubleClick()
{
    bool result = click();
    if (!result)
    {
        return false;
    }
    SLEEP(_sleepBetweenActions - _sleepAfterAction);
    result = click();
    return result;
}

bool hvdk::MouseRel::rightClick()
{
    MouseRelReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 2;
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(&report);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    SLEEP(_sleepBetweenActions);
    result = sendData(&report, static_cast<DWORD>(sizeof(report)));
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseRel::middleClick()
{
    MouseRelReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.buttons = 4;
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(&report);
    if (!result)
    {
        return false;
    }
    report.buttons = 0;
    SLEEP(_sleepBetweenActions);
    result = sendData(&report);
    SLEEP(_sleepAfterAction);
    return result;
}

bool hvdk::MouseRel::move(char x, char y)
{
    MouseRelReport report;
    report.reportID = 1;
    report.commandCode = 2;
    report.x = x;
    report.y = y;
    if (!deviceConnected())
    {
        if (!connectToDevice())
        {
            return false;
        }
    }
    bool result = sendData(&report);
    SLEEP(_sleepAfterAction);
    return result;
}

void hvdk::MouseRel::setSleepTimerAfterActions(unsigned short value)
{
    _sleepAfterAction = value;
}

unsigned short hvdk::MouseRel::getSleepTimerAfterActions()
{
    return _sleepAfterAction;
}

void hvdk::MouseRel::setSleepTimerBetweenActions(unsigned short value)
{
    if (value >= _sleepAfterAction)
    {
        _sleepBetweenActions = value;
    }
}

unsigned short hvdk::MouseRel::getSleepTimerBetweenActions()
{
    return _sleepBetweenActions;
}

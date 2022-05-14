#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "base.h"
#include "keybdkeys.h"

namespace hvdk
{
    class Keyboard : public Base
    {
    public:
        Keyboard();

        ~Keyboard();

        void resetData();

        bool resetDriver();

        bool releaseAllKeys();

        void setModKeyState(unsigned char keyCode, bool isDown = true);

        unsigned char getFreeKeysCount();

        bool setKeyState(unsigned char keyCode, bool isDown = true);

        bool commit(bool resetDataAfterCommit = true);

        bool clickOnKeys(unsigned char keyCode0 = 0,
                         unsigned char keyCode1 = 0,
                         unsigned char keyCode2 = 0,
                         unsigned char keyCode3 = 0,
                         unsigned char keyCode4 = 0);

        bool clickOnKeys(unsigned char keyCodes[5]);

        bool clickOnModKeys(unsigned char keyCodes);

        void setSleepTimerAfterActions(unsigned short value);

        unsigned short getSleepTimerAfterActions();

        void setSleepTimerBetweenActions(unsigned short value);

        unsigned short getSleepTimerBetweenActions();

    private:
        bool _pingWorking;

        bool _lCtrlDown;
        bool _lShiftDown;
        bool _lAltDown;
        bool _lWinDown;
        bool _rCtrlDown;
        bool _rShiftDown;
        bool _rAltDown;
        bool _rWinDown;

        unsigned char _keys[5];

        unsigned short _sleepBetweenActions;
        unsigned short _sleepAfterAction;

        bool startPing();

        void stopPing();

        void pingDriver();
    };
}

#endif // KEYBOARD_H

#ifndef MOUSEABS_H
#define MOUSEABS_H

#include "base.h"

#define MOUSE_ABS_L_BTN 0x01
#define MOUSE_ABS_M_BTN 0x04
#define MOUSE_ABS_R_BTN 0x02

namespace hvdk
{
    class MouseAbs : public Base
    {
    public:
        MouseAbs();

        void setNewPos(unsigned short x, unsigned short y);

        void setButtonState(unsigned char button, bool isDown = true);

        void resetData();

        bool resetDriver();

        bool commit(bool resetDataAfterCommit = true);

        bool clickOnPoint(unsigned short x, unsigned short y);

        bool doubleClickOnPoint(unsigned short x, unsigned short y);

        bool middleClickOnPoint(unsigned short x, unsigned short y);

        bool rightClickOnPoint(unsigned short x, unsigned short y);

        bool moveToPoint(unsigned short x, unsigned short y);

        void setSleepTimerAfterActions(unsigned short value);

        unsigned short getSleepTimerAfterActions();

        void setSleepTimerBetweenActions(unsigned short value);

        unsigned short getSleepTimerBetweenActions();

    private:
        unsigned short _x;
        unsigned short _y;

        bool _leftButtonDown;
        bool _middleButtonDown;
        bool _rightButtonDown;

        unsigned short _sleepBetweenActions;
        unsigned short _sleepAfterAction;
    };
}

#endif // MOUSEABS_H

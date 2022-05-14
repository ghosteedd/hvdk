#ifndef MOUSEREL_H
#define MOUSEREL_H

#include "base.h"

#define MOUSE_REL_L_BTN 0x01
#define MOUSE_REL_M_BTN 0x04
#define MOUSE_REL_R_BTN 0x02

namespace hvdk
{
    class MouseRel : public Base
    {
    public:
        MouseRel();

        void setNewPos(char x, char y);

        void setButtonState(unsigned char button, bool isDown = true);

        void resetData();

        bool resetDriver();

        bool commit(bool resetDataAfterCommit = true);

        bool click();

        bool doubleClick();

        bool middleClick();

        bool rightClick();

        bool move(char x, char y);

        void setSleepTimerAfterActions(unsigned short value);

        unsigned short getSleepTimerAfterActions();

        void setSleepTimerBetweenActions(unsigned short value);

        unsigned short getSleepTimerBetweenActions();

    private:
        unsigned char _x;
        unsigned char _y;

        bool _leftButtonDown;
        bool _middleButtonDown;
        bool _rightButtonDown;

        unsigned short _sleepBetweenActions;
        unsigned short _sleepAfterAction;
    };
}

#endif // MOUSEREL_H

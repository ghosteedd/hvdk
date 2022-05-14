#include <boost/python.hpp>

#include "src/mouserel.h"
#include "src/mouseabs.h"
#include "src/keyboard.h"

using namespace boost::python;
using namespace hvdk;

namespace mouserel
{
    void setNewPos(MouseRel& self, short x, short y)
    {
        if(x < -127 || x > 127 || y < -127 || y > 127)
        {
            return;
        }
        else
        {
            self.setNewPos(x, y);
        }
    }

    void setButtonState(MouseRel& self,
                        unsigned short button,
                        bool isDown = true)
    {
        if(button > 255)
        {
            return;
        }
        else
        {
            self.setButtonState(button, isDown);
        }
    }

    bool move(MouseRel& self, short x, short y)
    {
        if(x < -127 || x > 127 || y < -127 || y > 127)
        {
            return false;
        }
        else
        {
            return self.move(x, y);
        }
    }
}

namespace keyboard
{
    void setModKeyState(Keyboard& self,
                        unsigned short keyCode,
                        bool isDown = true)
    {
        if(keyCode > 255)
        {
            return;
        }
        else
        {
            self.setModKeyState(keyCode, isDown);
        }
    }

    unsigned short getFreeKeysCount(Keyboard& self)
    {
        return self.getFreeKeysCount();
    }

    bool setKeystate(Keyboard& self,
                     unsigned short keyCode,
                     bool isDown = true)
    {
        if(keyCode > 255)
        {
            return false;
        }
        else
        {
            return self.setKeyState(keyCode, isDown);
        }
    }

    bool clickOnKeys(Keyboard& self, unsigned short keyCode0 = 0,
                                        unsigned short keyCode1 = 0,
                                        unsigned short keyCode2 = 0,
                                        unsigned short keyCode3 = 0,
                                        unsigned short keyCode4 = 0)
    {
        if(keyCode0 > 255 || keyCode1 > 255 ||
           keyCode2 > 255 || keyCode3 > 255 ||
           keyCode4 > 255)
        {
            return false;
        }
        else
        {
            return self.clickOnKeys(keyCode0, keyCode1, keyCode2, keyCode3, keyCode4);
        }
    }

    bool clickOnModKeys(Keyboard& self, unsigned short modKeys)
    {
        if(modKeys > 255)
        {
            return false;
        }
        else
        {
            return self.clickOnModKeys(modKeys);
        }
    }
}

#ifdef MODULE_NAME
BOOST_PYTHON_MODULE(MODULE_NAME)
#else
BOOST_PYTHON_MODULE(pyhvdk)
#endif
{
    class_<MouseRel>("MouseRel")
            .def("connect_to_device", &MouseRel::connectToDevice)
            .def("disconnect_from_device", &MouseRel::disconnectFromDevice)
            .def("device_connected", &MouseRel::deviceConnected)
            .def("set_new_pos", &mouserel::setNewPos, (arg("self"), arg("x"), arg("y")))
            .def("set_button_state", &mouserel::setButtonState, (arg("self"), arg("button"), arg("is_down") = true))
            .def("reset_data", &MouseRel::resetData)
            .def("reset_driver", &MouseRel::resetDriver)
            .def("commit", &MouseRel::commit, arg("reset_data_after_commit") = true)
            .def("click", &MouseRel::click)
            .def("double_click", &MouseRel::doubleClick)
            .def("middle_click", &MouseRel::middleClick)
            .def("right_click", &MouseRel::rightClick)
            .def("move", &mouserel::move, (arg("self"), arg("x"), arg("y")))
            .def("set_sleep_timer_after_actions", &MouseRel::setSleepTimerAfterActions, arg("value"))
            .def("get_sleep_timer_after_actions", &MouseRel::getSleepTimerAfterActions)
            .def("set_sleep_timer_between_actions", &MouseRel::setSleepTimerBetweenActions, arg("value"))
            .def("get_sleep_timer_between_actions", &MouseRel::getSleepTimerBetweenActions);

    class_<MouseAbs>("MouseAbs")
            .def("connect_to_device", &MouseAbs::connectToDevice)
            .def("disconnect_from_device", &MouseAbs::disconnectFromDevice)
            .def("device_connected", &MouseAbs::deviceConnected)
            .def("set_new_pos", &MouseAbs::setNewPos, (arg("x"), arg("y")))
            .def("set_button_state", &MouseAbs::setButtonState, (arg("button"), arg("is_down") = true))
            .def("reset_data", &MouseAbs::resetData)
            .def("reset_driver", &MouseAbs::resetDriver)
            .def("commit", &MouseAbs::commit, arg("reset_data_after_commit") = true)
            .def("click_on_point", &MouseAbs::clickOnPoint, (arg("x"), arg("y")))
            .def("double_click_on_point", &MouseAbs::doubleClickOnPoint, (arg("x"), arg("y")))
            .def("middle_click_on_point", &MouseAbs::middleClickOnPoint, (arg("x"), arg("y")))
            .def("right_click_on_point", &MouseAbs::rightClickOnPoint, (arg("x"), arg("y")))
            .def("move_to_point", &MouseAbs::moveToPoint, (arg("x"), arg("y")))
            .def("set_sleep_timer_after_actions", &MouseAbs::setSleepTimerAfterActions, arg("value"))
            .def("get_sleep_timer_after_actions", &MouseAbs::getSleepTimerAfterActions)
            .def("set_sleep_timer_between_actions", &MouseAbs::setSleepTimerBetweenActions, arg("value"))
            .def("get_sleep_timer_between_actions", &MouseAbs::getSleepTimerBetweenActions);

    class_<Keyboard>("Keyboard")
            .def("connect_to_device", &Keyboard::connectToDevice)
            .def("disconnect_from_device", &Keyboard::disconnectFromDevice)
            .def("device_connected", &Keyboard::deviceConnected)
            .def("reset_data", &Keyboard::resetData)
            .def("reset_driver", &Keyboard::resetDriver)
            .def("release_all_keys", &Keyboard::releaseAllKeys)
            .def("set_mod_key_state", &keyboard::setModKeyState, (arg("self"), arg("key_code"), arg("is_down") = true))
            .def("get_free_keys_count", &keyboard::getFreeKeysCount, arg("self"))
            .def("set_key_state", &keyboard::setKeystate, (arg("self"), arg("key_code"), arg("is_down") = true))
            .def("commit", &Keyboard::commit, arg("reset_data_after_commit") = true)
            .def("click_on_keys", &keyboard::clickOnKeys, (arg("self"), arg("key_code0") = 0, arg("key_code1") = 0, arg("key_code2") = 0, arg("key_code3") = 0, arg("key_code4") = 0))
            .def("click_on_mod_keys", &keyboard::clickOnModKeys, (arg("self"), arg("key_codes")))
            .def("set_sleep_timer_after_actions", &Keyboard::setSleepTimerAfterActions, arg("value"))
            .def("get_sleep_timer_after_actions", &Keyboard::getSleepTimerAfterActions)
            .def("set_sleep_timer_between_actions", &Keyboard::setSleepTimerBetweenActions, arg("value"))
            .def("get_sleep_timer_between_actions", &Keyboard::getSleepTimerBetweenActions);
}

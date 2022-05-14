# hvdk::MouseAbs class

The mouse driver abs (absolute) allows you to:

* Position the cursor with absolute desktop coordinates. Note that this is desktop coordinates, not monitor coordinates.

* Press and/or release the left, middle and right buttons.

About coordinates you can read [here](https://tetherscript.com/kbhid/hid-using-the-mouse-driver-abs/).

## Class methods

### Connect to device

Search mouse absolute driver and open his handle.

**Syntax:**

C++: `bool connectToDevice()` 

Python: `connect_to_device() -> bool`

**Return value:**

> true - device found and handle opened.
> 
> false - device not found or connection error.

### Disconnect from device

Close driver handle.

**Syntax:**

C++: `void disconnectFromDevice()` 

Python: `disconnect_from_device() -> None`

### Get device connection status

Getting handle status.

**Syntax:**

C++: `bool deviceConnected()` 

Python: `device_connected() -> bool`

**Return value:**

> true - device handle opened.
> 
> false - device handle closed or not found.

### Reset driver

Send a reset command to the mouse driver. This will release all mouse buttons. 

**Syntax:**

C++: `bool resetDriver()` 

Python: `reset_driver() -> bool`

**Return value:**

> true - command send successful.
> 
> false - command send failed or opening handle error.

### Left button click on point

Left mouse button press and release with pause of between actions (75ms) on specific position. Other button release.

**Syntax:**

C++: `bool clickOnPoint(unsigned short x, unsigned short y);` 

Python: `click_on_point(x: int, y: int) -> bool`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

**Return value:**

> true - commands send successful.
> 
> false -  any command send failed or opening handle error.

### Double left button click on point

Double execute left click on point method with pause of between actions (107 ms). Other button release.

**Syntax:**

C++: `bool doubleClickOnPoint(unsigned short x, unsigned short y)` 

Python: `double_click_on_point(x: int, y: int) -> bool`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

**Return value:**

> true - commands send successful.
> 
> false -  any command send failed or opening handle error.

### Middle button click on point

Middle mouse button press and release with pause of between actions (75ms) on specific position. Other button release.

**Syntax:**

C++: `bool middleClickOnPoint(unsigned short x, unsigned short y)` 

Python: `middle_click_on_point(x: int, y: int) -> bool`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

**Return value:**

> true - commands send successful.
> 
> false -  any command send failed or opening handle error.

### Right button click on point

Right mouse button press and release with pause of between actions (75ms) on specific position. Other button release.

**Syntax:**

C++: `bool rightClickOnPoint(unsigned short x, unsigned short y)` 

Python: `right_click_on_point(x: int, y: int) -> bool`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

**Return value:**

> true - commands send successful.
> 
> false -  any command send failed or opening handle error.

### Absolute mouse move

Change cursor position in absolute desktop coordinates (all buttons release).

**Syntax:**

C++: `bool moveToPoint(unsigned short x, unsigned short y)` 

Python: `move_to_point(x: int, y: int) -> bool`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

**Return value:**

> true - commands send successful.
> 
> false - command send failed or opening handle error.

### Absolute mouse move (custom action)

Set new cursor position in absolute desktop coordinates for custom action.

**Syntax:**

C++: `void setNewPos(unsigned short x, unsigned short y)` 

Python: `set_new_pos(x: int, y: int) -> None`

**Parameters:**

> x - new position the cursor on X axis absolute desktop coordinates. Accepting value: [0:32767]. 

> y - new position the cursor on Y axis absolute desktop coordinates. Accepting value: [0:32767]. 

### Set button state (custom action)

Set key state for custom action.

**Syntax:**

C++: `void setButtonState(unsigned char button, bool isDown = true)` 

Python: `set_button_state(button: int, is_down: bool = True) -> None`

**Parameters:**

> button - single button code.

> isDown - button state (true - button press, false - button release).

**Remarks:**

Button codes table:

| Button code | Button |    C++ define   |       Python constant      |
|:-----------:|:------:|:---------------:|:--------------------------:|
|      1      |  Left  | MOUSE_ABS_L_BTN | hvdk.const.MOUSE_ABS_L_BTN |
|      4      | Middle | MOUSE_ABS_M_BTN | hvdk.const.MOUSE_ABS_M_BTN |
|      2      |  Right | MOUSE_ABS_R_BTN | hvdk.const.MOUSE_ABS_R_BTN |

P.S. Button codes for C++ defined in `src/mouseabs.h` file.

### Reset custom action data

Reset data for custom action.

**Syntax:**

C++: `void resetData()` 

Python: `reset_data() -> None`

### Apply custom action

Send data of custom action to driver.

**Syntax:**

C++: `bool commit(bool resetDataAfterCommit = true)` 

Python: `commit(reset_data_after_commit: bool = True) -> bool`

**Parameters:**

> resetDataAfterCommit - if set this parameter to false аfter sending the data to driver, values specified by the `setNewPos / setButtonState` methods will not be reset. 

**Return value:**

> true - commands send successful.
> 
> false -  command send failed or opening handle error.

### Change time after send data to driver

Set new value of time after send data to driver

**Syntax:**

C++: `void setSleepTimerAfterActions(unsigned short value)`

Python: `set_sleep_timer_after_actions(value: int) -> None`

**Parameters:**

> value - new value in milliseconds of time after send data to driver.

### Get current time after send data to driver

Getting current value of time after send data to driver

**Syntax:**

C++: `unsigned short getSleepTimerAfterActions()`

Python: `get_sleep_timer_after_actions() -> int`

**Return value:**

> value in milliseconds of time after send data to driver.

### Change time between actions

Set new value of time between actions (button press/release, double click)

**Syntax:**

C++: `void setSleepTimerBetweenActions(unsigned short value)`

Python: `set_sleep_timer_between_actions(value: int) -> None`

**Parameters:**

> value - new value in milliseconds of time between actions. Accepted value >= timer after action

### Get current time between actions

Getting current value of time between actions. 

**Syntax:**

C++: `unsigned short getSleepTimerAfterActions()`

Python: `get_sleep_timer_after_actions() -> int`

**Return value:**

> value in milliseconds of time between actions.

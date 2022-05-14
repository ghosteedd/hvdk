# hvdk::Keyboard class

The keyboard driver allows you to:

* Press and release any regular keys plus any eight modifier keys to the driver.

The driver appears equivalent to the OS as a physical keyboard. The OS will apply the keystrokes to the active application.

## What the modifier keys

On any keyboards left/right ctrl, alt, shift, win keys are modifiers.

## Class methods

### Connect to device

Search keyboard driver and open his handle.

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

Send a reset command to the keyboard driver. This will release all keyboard keys. 

**Syntax:**

C++: `bool resetDriver()` 

Python: `reset_driver() -> bool`

**Return value:**

> true - command send successful.
> 
> false - command send failed or opening handle error.

### Relese all keys

Send command to keyboard driver for release all keys. It's not a reset command (commandCode = 1), but a command to release all keys (commandCode = 2).

**Syntax:**

C++: `bool releaseAllKeys()` 

Python: `release_all_keys() -> bool`

**Return value:**

> true - command send successful.
> 
> false - command send failed or opening handle error.

### Click on modifier key(s)

Press and release on modifier keys with pause of between actions (75 ms). You can use multiple keys by stacking them.

**Syntax:**

C++: `bool clickOnModKeys(unsigned char keyCodes)` 

Python: `click_on_mod_keys(key_codes: int) -> bool`

**Parameters:**

> keyCodes - result of stacking modifier keys. Key codes you can found [here](KeyboardKeys.md)

**Return value:**

> true - command send successful.
> 
> false - any command send failed or opening handle error.

### Click on key(s)

Press and release on keyboard keys with pause of between actions (75 ms).

**Syntax:**

C++:
```
bool clickOnKeys(unsigned char keyCode0 = 0,
                 unsigned char keyCode1 = 0,
                 unsigned char keyCode2 = 0,
                 unsigned char keyCode3 = 0,
                 unsigned char keyCode4 = 0)
```
```
bool clickOnKeys(unsigned char keyCodes[5])
```

Python: 
```
click_on_keys(key_code0: int = 0, 
              key_code1: int = 0, 
              key_code2: int = 0,
              key_code3: int = 0,
              key_code4: int = 0) -> bool
```

**Parameters:**

> keyCode0 ... keyCode4 or keyCodes[5] - key codes for click. Key codes you can found [here](KeyboardKeys.md). Max count keys is 5.

**Return value:**

> true - command send successful.
> 
> false - any command send failed or opening handle error.

### Set modifier key state (custom action)

Set modifier key state for custom action. You CAN'T use multiple keys in one parameter.

**Syntax:**

C++: `void setModKeyState(unsigned char keyCode, bool isDown = true)` 

Python: `set_mod_key_state(key_code: int, is_down: boot = True) -> None`

**Parameters:**

> keyCode - modifier key code. Key codes you can found [here](KeyboardKeys.md)

> isDown - key state (true - key press, false - key release).

### Set key state (custom action)

Set keyboard key state for custom action.

**Syntax:**

C++: `bool setKeyState(unsigned char keyCode, bool isDown = true)`

Python: `set_key_state(key_code: int, is_down: bool = True) -> bool`

**Parameters:**

> keyCode - keyboard key code. Key codes you can found [here](KeyboardKeys.md)

> isDown - key state (true - key press, false - key release).

**Return value:**

> true - key added to pool.
> 
> false - key pool is full or (if isDown = false) key in pool not found.

### Free keys count for custom action

Getting of free count in keys pool

**Syntax:**

C++: `unsigned char getFreeKeysCount()`

Python: `get_free_keys_count() -> int`

**Return value:**

> Value of free count in keys pool

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

> resetDataAfterCommit - if set this parameter to false аfter sending the data to driver, values specified by the `setModKeyState / setKeyState` methods will not be reset. 

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

Set new value of time between actions ((mod)key(s) click)

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

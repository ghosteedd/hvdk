# Tetherscript HID Virtual Drivers SDK

It's unofficial C++ library and Python module for control [Tetherscript HID Virtual Drivers](https://tetherscript.com/hid-driver-kit-home/). If you want use Tetherscript drivers, but don't want write routines on WDK, it's project for you. You can [download drivers pack here](https://tetherscript.com/hid-driver-kit-download/) ([see drivers license here](https://tetherscript.com/kbhid/hidkb-licensing/)).

So, this project has working with:

* Virtual mouse absolute ([info](https://tetherscript.com/kbhid/hid-using-the-mouse-driver-abs/))
* Virtual mouse relative ([info](https://tetherscript.com/kbhid/hid-using-the-mouse-driver-rel/))
* Virtual keyboard ([info](https://tetherscript.com/kbhid/hidkb-using-the-keyboard-driver/))

SDK for **gamepad and joystick not created**. Maybe I do it later, keep for updates.

## How to use it in your project

### Python

For Python version *3.7 - 3.10* (i386 and AMD64 builds) you can just download module archive from releases page and put the contents of the archive into [sys.path](https://docs.python.org/3/using/windows.html#finding-modules/) directory. When import a module, it will automatically detect your version and  architecture of Python, after which the necessary build of the module will be imported.

If you want use other Python version clone this repository, download [WDK, WinSDK](https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk) and [boost library](https://www.boost.org/users/download/). [Build boost for your Python version](https://www.boost.org/doc/libs/1_79_0/libs/python/doc/html/building.html). Connect `hid.lib`, `setupapi.lib` and boost library into your project and build all codes from `src` and `python-warp` directories. Keys codes you can get from module archive on releases page (file: `const.py`).

### C++

If your compiler is binary compatible with these build versions (MinGW 8.1 or MSVC v142), you can simply download them from the releases page and include them in your project.

In other cases, you will need to clone this repository and build code from `src` directory manually. For successful build needed `hid.lib` and `setupapi.lib` from [WDK](https://docs.microsoft.com/en-us/windows-hardware/drivers/download-the-wdk).

## Features

For control virtual devices use next classes:

* [hvdk::MouseRel - for control virtual mouse (relative)](docs/MouseRel.md)
* [hvdk::MouseAbs - for control virtual mouse (absolute)](docs/MouseAbs.md)
* [hvdk::Keyboard - for control virtual keyboard](docs/Keyboard.md)

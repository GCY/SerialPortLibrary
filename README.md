# SerialPortLibrary
This is cross-platform serial port library written in C++, build passing MAC-High-Sierra and Win10.
</br>

## Easy-to-use
First - include "Library" folder into your project.
* serialport.h
* serialport.cpp
* enumserial.h
* enumserial.cpp
* Third/dirent.h(MSVC only)

### Dependence: Native API only!
* MAC OS X (POSIX)
* Windows10 (WinAPI)

### Initialization SerialPort-Class and EnumSerial-Class
```cpp
EnumSerial enumserial;
SerialPort serial;

std::vector<std::string> paths = enumserial.EnumSerialPort();  //Enum device driver of serial port

int choice_path = 0;  // get user selection

#ifdef _WIN_
      serial.Open(paths[choice_path]);
#elif _MAC_
      serial.Open(enumserial.GetRoot() + paths[choice_path]);  //root = /dev/
#endif

int baud_rate = 115200;
serial.SetBaudRate(baud_rate);
serial.SetParity(8,1,'N');

```

### SerialPort Write and Read
```cpp
unsigned char str[17] = "Hello Terminal \n";
serial.Write(str,17);

unsigned char serial_buffer[5000] = {0};
int length = serial.Read(serial_buffer);
if(length != -1){
  std::cout << serial_buffer;
}  
```
### Compile
#### MAC OS X
#define \_MAC\_ or g++ -D \_MAC\_
#### Windows 10 - Visual Studio 2017
#define \_WIN\_ or setting VS2017 property of compile flag \_WIN\_

## Example
### wxTerm
wxTerm is cross-platform and Arduino-like IDE serial monitor example.
#### Dependence
* wxWidgets 3.x
#### MAC OS X
```cpp
make
```

![alt text](https://github.com/GCY/SerialPortLibrary/blob/master/wxterm%20mac.png?raw=true)

#### Windows 10 - Visual Studio 2017
setting compile flag \_WIN\_

![alt text](https://github.com/GCY/SerialPortLibrary/blob/master/wxterm%20windows10.PNG?raw=true)

## Terminal device for demo
### STM32F4 VCP example

Install STM32 Virtual COM Port Driver([STSW-STM32102](https://www.st.com/en/development-tools/stsw-stm32102.html) - Windows10 only
)

#### Edit usbd_desc.c
```cpp
#define USBD_VID                        0x0483
#define USBD_PID                        0x5740
```
#### Compile
```cpp
cd STM32F4/src/STM32F4
make
```
Load main.elf file with arm-none-eabi-gdb .

wxTerm baud rate - none

### Arduino Serial Port example
Arduino IDE open ArduinoSerialTest.ino file and burning the code on Arduino-board

wxTerm baud rate - 115200

## Another version wxArduino(Linux and Windows7 build passing)
### [wxArduino](https://github.com/GCY/wxArduino) - previous version of SerialPortLibrary


LICENSE
-------

MIT License

Copyright (c) 2019 Tony Guo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.



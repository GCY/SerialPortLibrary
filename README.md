# SerialPortLibrary
This is cross-platform serial port library written in C++ 
</br>

## Easy-to-use
First - include "Library" folder into your project.
* serialport.h
* serialport.cpp
* enumserial.h
* enumserial.cpp
* Third/dirent.h(MSVC only)

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
make
```
Load main.elf file with arm-none-eabi-gdb .

### Arduino Serial Port example
Arduino IDE open *.ino file and burning the code on Arduino-board

# SerialPortLibrary
This is cross-platform serial port library written in C++ 
</br>

## Easy-to-use
First include library folder
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

#pragma once

// C library headers
#include <stdio.h>
#include <iostream>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

class SerialDevice {
public:
    SerialDevice(const std::string& port, int baudRate);
    ~SerialDevice();

    bool openComm();
    void closeComm();
    void sendCommand(const std::string& command);
    std::string readResponse();
    bool isOpen() const;

private:
    std::string _port;
    bool _isOpen;
    int _baudRate;
    int _fd;

    bool configureBaud(int baudRate);
};
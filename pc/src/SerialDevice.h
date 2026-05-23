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

const int MAX_RETRY = 3;

class ISerialDevice {
public:
    virtual ~ISerialDevice() = default;
    virtual bool openComm() = 0;
    virtual void closeComm() = 0;
    virtual void sendCommand(const std::string& command) = 0;
    virtual std::string readResponse() = 0;
};

class SerialDevice : public ISerialDevice {
public:
    SerialDevice(const std::string& port, int baudRate);
    SerialDevice();
    ~SerialDevice();

    bool openComm() override;
    void closeComm() override;
    void sendCommand(const std::string& command) override;
    std::string readResponse() override;

    bool isOpen() const;

private:
    std::string _port;
    bool _isOpen;
    int _baudRate;
    int _fd;
};

class TSerialDevice : public ISerialDevice {
public:
    TSerialDevice();
    ~TSerialDevice();

    bool openComm() override;
    void closeComm() override;
    void sendCommand(const std::string& command) override;
    std::string readResponse() override;

    void setFailState(bool fail);

private:
    bool _failState;
};
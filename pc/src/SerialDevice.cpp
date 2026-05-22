#include "SerialDevice.h"

SerialDevice::SerialDevice(const std::string& port, int baudRate) {
    _port = port;
    _baudRate = baudRate;
}

SerialDevice::~SerialDevice() {

}

bool SerialDevice::openComm() {
    _fd = open(_port.c_str(), O_RDWR);
    if (_fd < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return false;
    }

    struct termios tty;

    // Read in existing settings, and handle any error
    // NOTE: This is important! POSIX states that the struct passed to tcsetattr()
    // must have been initialized with a call to tcgetattr() overwise behaviour
    // is undefined
    if(tcgetattr(_fd, &tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return false;
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all the size bits, then use one of the statements below
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 10;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    // Set in/out baud rate to be 9600
    speed_t baud;
    switch(_baudRate) {
        case 9600:
            baud = B9600;
            break;
        case 19200:
            baud = B19200;
            break;
        default:
            baud = B9600;
    }

    cfsetispeed(&tty, baud);
    cfsetospeed(&tty, baud);

    // Save tty settings, also checking for error
    if (tcsetattr(_fd, TCSANOW, &tty) != 0) {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return false;
    }

    // Sleep for 2 seconds, when tty port opens, arduino may reset
    // give a couple seconds to reboot
    std::cout << "Arduino booting...\n";
    sleep(2);
    return true;
}

void SerialDevice::closeComm() {
    close(_fd);
}

void SerialDevice::sendCommand(const std::string& command) {
    int n = write(_fd, command.c_str(), command.size());
    if (n == -1) {
        std::cout << "Write failed\n";
    }
}

std::string SerialDevice::readResponse() {
    char read_buf [256] = {'\0'};

    int n = read(_fd, &read_buf, sizeof(read_buf));
    if (n == -1) {
        std::cout << "Read failed\n";
    }

    return read_buf;
}

bool SerialDevice::isOpen() const {
    return _isOpen;
}

bool SerialDevice::configureBaud(int baudRate) {
    return true;
}
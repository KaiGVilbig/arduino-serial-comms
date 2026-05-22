#include "SerialManager.h"
#include <log4cxx/logmanager.h>
#include <log4cxx/basicconfigurator.h>

auto serialManagerLogger = log4cxx::LogManager::getLogger("ardiono-serial-comms.SerialManager");

// Init device
SerialManager::SerialManager() : _device("/dev/ttyUSB0", 9600) {}

SerialManager::~SerialManager() {}

bool SerialManager::init() {
    // Open serial port
    if (!_device.openComm()) {
        LOG4CXX_ERROR(serialManagerLogger, "Comms open failed.");
        return false;
    } else {
        LOG4CXX_INFO(serialManagerLogger, "Serial port opened.");
    }

    // Device discovery
    _device.sendCommand("IDENTIFY\n");
    std::string response = _device.readResponse();
    std::cout << response << std::endl;

    return true;
}

void SerialManager::start() {

    std::string input;
    do {
        std::cout << "# ";
        std::cin >> input;

        _device.sendCommand(input);
        std::string response = _device.readResponse();
        std::cout << response << std::endl;

    } while(input != QUIT);

    _device.closeComm();
}
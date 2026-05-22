#include "SerialManager.h"
#include <log4cxx/logmanager.h>
#include <log4cxx/basicconfigurator.h>
#include <thread>

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

void SerialManager::writer() {
    while (!stopThreads) {
        if (_writeQueue.empty()) continue;

        // Lock write queue, grab front and unlock queue
        writeLock.lock();
        std::string command = _writeQueue.front();
        _writeQueue.pop();
        writeLock.unlock();

        _device.sendCommand(command);
    }
}

void SerialManager::reader() {
    std::string response = _device.readResponse();
    std::cout << response;
}

void SerialManager::start() {

    std::string input;

    std::thread _writer = std::thread(&SerialManager::writer, this);

    do {
        std::cout << "# ";
        std::cin >> input;

        if (input == QUIT) continue;

        writeLock.lock();
        _writeQueue.push(input);
        writeLock.unlock();

        reader();

    } while(input != QUIT);

    // Close threads
    stopThreads = true;
    _writer.join();

    _device.closeComm();
}
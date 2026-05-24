#include "SerialManager.h"
#include <log4cxx/logmanager.h>
#include <log4cxx/basicconfigurator.h>
#include <thread>

auto serialManagerLogger = log4cxx::LogManager::getLogger("ardiono-serial-comms.SerialManager");

// Overridden constructor allows Test to pass in TSerialDevice instead of using SerialDevice
SerialManager::SerialManager(ISerialDevice& device) {
    _device = &device;
    _deviceOwner = false;
    _dataSent = false;
}

// Init device
SerialManager::SerialManager() {
    SerialDevice* device = new SerialDevice("/dev/ttyUSB0", 9600);
    _device = device;
    _deviceOwner = true;
    _dataSent = false;
}

SerialManager::~SerialManager() {
    if (_deviceOwner) delete _device;
}

bool SerialManager::init() {
    // Open serial port
    if (!_device->openComm()) {
        LOG4CXX_ERROR(serialManagerLogger, "Comms open failed.");
        return false;
    } else {
        LOG4CXX_INFO(serialManagerLogger, "Serial port opened.");
    }

    // Device discovery
    _device->sendCommand("IDENTIFY\n");
    std::string response = _device->readResponse();
    std::cout << response << std::endl;

    return true;
}

void SerialManager::writer() {
    while (!stopThreads) {
        std::unique_lock<std::mutex> writeWait(writeLock);
        _cv.wait(writeWait, [this] { return !_writeQueue.empty() || stopThreads; });
        if (stopThreads) break;

        // writeWait is held here, queue is safe to access
        Message command = _writeQueue.front();
        _writeQueue.pop();
        writeWait.unlock(); // done with queue, release before sending

        std::lock_guard<std::mutex> lock(mtx);
        _device->sendCommand(MessageParser::messageSerializer(&command));
        _dataSent = true;

        // Add command to the history
        historyLock.lock();
        _commandHistory.push(command);
        historyLock.unlock();

        _cv.notify_one();
    }
}

void SerialManager::reader() {
    std::unique_lock<std::mutex> lock(mtx);
    _cv.wait(lock, [this] {return _dataSent;});
    std::string response = _device->readResponse();

    historyLock.lock();
    Message resp = _commandHistory.back();
    MessageParser::parseMessage(&resp, response);
    historyLock.unlock();

    std::cout << response;
    _dataSent = false;
}

void SerialManager::start() {

    std::string input;

    std::thread _writer = std::thread(&SerialManager::writer, this);

    do {
        std::cout << "# ";
        std::cin >> input;

        if (input == QUIT) continue;
        Message msg;
        MessageParser::constructMessage(&msg, input);

        writeLock.lock();
        _writeQueue.push(msg);
        writeLock.unlock();

        _cv.notify_one();
        reader();

    } while(input != QUIT);

    // Close threads
    stopThreads = true;
    _cv.notify_all();
    _writer.join();

    _device->closeComm();
}